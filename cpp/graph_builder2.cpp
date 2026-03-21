
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <deque>
//#include <omp.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
using Graph = std::map<std::string, std::map<std::string, double>>;

namespace detail {

    double pearson_correlation(const std::vector<double>& x, const std::vector<double>& y) {
        if (x.size() != y.size() || x.empty()) return 0.0;
        double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0, sum_y2 = 0.0;
//        #pragma omp parallel for reduction(+:sum_x,sum_y,sum_xy,sum_x2,sum_y2)
        for (size_t i = 0; i < x.size(); ++i) {
            sum_x += x[i];
            sum_y += y[i];
            sum_xy += x[i] * y[i];
            sum_x2 += x[i] * x[i];
            sum_y2 += y[i] * y[i];
        }
        double n = static_cast<double>(x.size());
        double numerator = n * sum_xy - sum_x * sum_y;
        double denom_x = n * sum_x2 - sum_x * sum_x;
        double denom_y = n * sum_y2 - sum_y * sum_y;
        if (denom_x <= 0.0 || denom_y <= 0.0) return 0.0;
        return numerator / (std::sqrt(denom_x) * std::sqrt(denom_y));
    }

    std::vector<double> softmax(const std::vector<double>& x) {
        std::vector<double> abs_x(x.size());
        for (size_t i = 0; i < x.size(); ++i) abs_x[i] = std::abs(x[i]);
        std::vector<double> result(x.size());
        double max_val = *std::max_element(abs_x.begin(), abs_x.end());
        if (max_val == 0.0) return std::vector<double>(x.size(), 1.0 / x.size());  // 避免全0
        double sum_exp = 0.0;
        for (size_t i = 0; i < x.size(); ++i) {
            result[i] = std::exp(abs_x[i] - max_val);
            sum_exp += result[i];
        }
        for (double& val : result) val /= sum_exp;
        return result;
    }

    double quantile(std::vector<double>& data, double q) {
        std::sort(data.begin(), data.end());
        double index = q * (data.size() - 1);
        size_t li = static_cast<size_t>(std::floor(index));
        size_t ui = static_cast<size_t>(std::ceil(index));
        if (ui >= data.size()) ui = data.size() - 1;
        return data[li] + (index - li) * (data[ui] - data[li]);
    }
}

std::pair<Graph, Graph> build_graph_from_abundance(
    const std::vector<std::vector<double>>& abundance_matrix,
    const std::vector<std::string>& features,
    const std::string& seed_taxa,
    double seed_quantile,
    int n_random_pairs,
    int random_seed) {

    size_t n_samples = abundance_matrix.size();
    size_t n_features = features.size();

    std::vector<std::vector<double>> abundance_by_feature(n_features, std::vector<double>(n_samples));
    for (size_t i = 0; i < n_samples; ++i)
        for (size_t j = 0; j < n_features; ++j)
            abundance_by_feature[j][i] = abundance_matrix[i][j];

    std::map<std::string, int> feature_to_idx;
    for (size_t i = 0; i < n_features; ++i)
        feature_to_idx[features[i]] = static_cast<int>(i);

    std::vector<std::vector<double>> pearson_matrix(n_features, std::vector<double>(n_features, 0.0));

//    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < static_cast<int>(n_features); ++i) {
        pearson_matrix[i][i] = 1.0;
        for (int j = i + 1; j < static_cast<int>(n_features); ++j) {
            double corr = detail::pearson_correlation(abundance_by_feature[i], abundance_by_feature[j]);
            pearson_matrix[i][j] = corr;
            pearson_matrix[j][i] = corr;
        }
    }

    int seed_idx = feature_to_idx.at(seed_taxa);
    double seed_max_abs = 0.0;
    for (int j = 0; j < static_cast<int>(n_features); ++j) {
        if (j == seed_idx) continue;
        double v = std::abs(pearson_matrix[seed_idx][j]);
        if (v > seed_max_abs) seed_max_abs = v;
    }

    std::mt19937 gen(random_seed);
    std::vector<double> random_abs_corrs;
    random_abs_corrs.reserve(n_random_pairs);
    std::vector<int> idxs(n_features);
    std::iota(idxs.begin(), idxs.end(), 0);

    while (static_cast<int>(random_abs_corrs.size()) < n_random_pairs) {
        std::shuffle(idxs.begin(), idxs.end(), gen);
        double c = std::abs(pearson_matrix[idxs[0]][idxs[1]]);
        if (c <= seed_max_abs) {
            random_abs_corrs.push_back(c);
        }
    }

    double seed_thresh = detail::quantile(random_abs_corrs, seed_quantile);
    std::cout << "threshold = "
              << seed_thresh << "（the top 1%, based on " << random_abs_corrs.size() << " random pairs）" << std::endl;

    Graph graph, signal_graph;
    std::deque<std::string> pending = { seed_taxa };
    std::unordered_set<std::string> visited = { seed_taxa };

    while (!pending.empty()) {
        std::string current = pending.front(); pending.pop_front();
        std::vector<std::string> cond_nodes = { current };
        if (graph.count(current)) {
            for (const auto& p : graph[current]) cond_nodes.push_back(p.first);
        }

        for (const auto& target : features) {
            if (std::find(cond_nodes.begin(), cond_nodes.end(), target) != cond_nodes.end()) continue;
            int ti = feature_to_idx[target];
            double final_corr = 0.0;

            if (cond_nodes.size() == 1) {
                int ci = feature_to_idx[cond_nodes[0]];
                final_corr = pearson_matrix[ci][ti];
            } else {

                std::vector<double> abs_scores, weights;
                std::vector<const std::vector<double>*> cond_ptrs;
                for (const auto& cn : cond_nodes) {
                    int ci = feature_to_idx[cn];
                    double corr = pearson_matrix[ci][ti];
                    abs_scores.push_back(std::abs(corr));
                    cond_ptrs.push_back(&abundance_by_feature[ci]);
                }
                weights = detail::softmax(abs_scores);

                std::vector<double> agg(n_samples, 0.0);
                for (size_t i = 0; i < cond_ptrs.size(); ++i)
                    for (size_t j = 0; j < n_samples; ++j)
                        agg[j] += weights[i] * (*cond_ptrs[i])[j];

                final_corr = detail::pearson_correlation(agg, abundance_by_feature[ti]);
            }


            if (std::abs(final_corr) > seed_thresh) {
                double strength = std::abs(final_corr);
                graph[current][target] = strength;
                graph[target][current] = strength;
                signal_graph[current][target] = final_corr;
                signal_graph[target][current] = final_corr;
                if (!visited.count(target)) {
                    pending.push_back(target);
                    visited.insert(target);
                }
            }
        }
    }

    return { graph, signal_graph };
}


std::pair<Graph, Graph> build_graph_wrapper(
    py::array_t<double, py::array::c_style | py::array::forcecast> abundance_arr,
    std::vector<std::string> features,
    std::string seed_taxa,
    double seed_quantile,
    int n_random_pairs,
    int random_seed)
{
    if (abundance_arr.ndim() != 2) {
        throw std::runtime_error("The input must be a two-dimensional array");
    }
    py::buffer_info buf = abundance_arr.request();
    std::vector<std::vector<double>> abundance_matrix(buf.shape[0], std::vector<double>(buf.shape[1]));
    double* ptr = static_cast<double*>(buf.ptr);
    for (py::ssize_t i = 0; i < buf.shape[0]; i++) {
        for (py::ssize_t j = 0; j < buf.shape[1]; j++) {
            abundance_matrix[i][j] = ptr[i * buf.shape[1] + j];
        }
    }
    return build_graph_from_abundance(abundance_matrix, features, seed_taxa, seed_quantile, n_random_pairs, random_seed);
}

PYBIND11_MODULE(graph_builder2, m) {
    m.doc() = "C++ implementation of build_graph_from_abundance using Pearson correlation (signed, abs threshold)";
    m.def("build_graph_from_abundance_cpp", &build_graph_wrapper, "Builds graph using Pearson, with signed weights and absolute threshold",
          py::arg("abd_df"),
          py::arg("features"),
          py::arg("seed_taxa"),
          py::arg("seed_quantile") = 0.99,
          py::arg("n_random_pairs") = 10000,
          py::arg("random_seed") = 42);
}