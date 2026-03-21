
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <functional>

namespace py = pybind11;

namespace {


void set_seed(unsigned int seed) {
    static std::mt19937 rng;
    rng.seed(seed);
}


using Adj = std::unordered_map<std::string, std::unordered_set<std::string>>;


Adj build_adj_from_graph(const py::dict& graph) {
    Adj adj;
    for (auto item : graph) {
        std::string node = py::cast<std::string>(item.first);
        py::dict neigh_dict = py::cast<py::dict>(item.second);
        auto& bucket = adj[node];
        for (auto kv : neigh_dict) {
            std::string neigh = py::cast<std::string>(kv.first);
            bucket.insert(neigh);
        }
    }
    return adj;
}


std::string choose_pivot_identical(
    const std::unordered_set<std::string>& P,
    const std::unordered_set<std::string>& X,
    const Adj& adj
) {

    std::vector<std::string> candidates;
    candidates.reserve(P.size() + X.size());
    candidates.insert(candidates.end(), P.begin(), P.end());
    candidates.insert(candidates.end(), X.begin(), X.end());

    if (candidates.empty()) {
        return "";
    }


    std::sort(candidates.begin(), candidates.end());

    std::string best_pivot;
    size_t max_deg = 0;
    bool has_pivot = false;

    for (const auto& v : candidates) {
        size_t deg = 0;
        auto it = adj.find(v);
        if (it != adj.end()) {
            deg = it->second.size();
        }

        if (!has_pivot || deg > max_deg) {
            max_deg = deg;
            best_pivot = v;
            has_pivot = true;
        }
    }
    return best_pivot;
}



std::vector<std::string> to_sorted_vector(const std::unordered_set<std::string>& s) {
    std::vector<std::string> vec(s.begin(), s.end());
    std::sort(vec.begin(), vec.end());
    return vec;
}

}



py::list find_max_cliques_with_seed_identical(const py::dict& graph, const std::string& seed) {
    set_seed(42);

    Adj adj = build_adj_from_graph(graph);

    if (adj.find(seed) == adj.end()) {
        return py::list();
    }

    std::vector<std::unordered_set<std::string>> all_maximal_cliques;

    std::function<void(std::unordered_set<std::string>,
                       std::unordered_set<std::string>,
                       std::unordered_set<std::string>)> bron_kerbosch_identical;

    bron_kerbosch_identical =
        [&](std::unordered_set<std::string> R,
            std::unordered_set<std::string> P,
            std::unordered_set<std::string> X) {
            set_seed(42);

            if (P.empty() && X.empty()) {
                if (R.count(seed)) {
                    all_maximal_cliques.push_back(R);
                }
                return;
            }

            std::string pivot = choose_pivot_identical(P, X, adj);

            std::unordered_set<std::string> pivot_neighbors;
            if (!pivot.empty()) {
                auto it = adj.find(pivot);
                if (it != adj.end()) pivot_neighbors = it->second;
            }

            std::vector<std::string> to_process_sorted;
            for (const auto& v : P) {
                if (pivot_neighbors.find(v) == pivot_neighbors.end()) {
                    to_process_sorted.push_back(v);
                }
            }
            std::sort(to_process_sorted.begin(), to_process_sorted.end());

            for (const auto& v : to_process_sorted) {
                set_seed(42);

                std::unordered_set<std::string> v_neighbors;
                auto itv = adj.find(v);
                if (itv != adj.end()) v_neighbors = itv->second;

                std::unordered_set<std::string> new_R = R;
                new_R.insert(v);

                std::unordered_set<std::string> new_P;
                for (const auto& x : P) if (v_neighbors.count(x)) new_P.insert(x);

                std::unordered_set<std::string> new_X;
                for (const auto& x : X) if (v_neighbors.count(x)) new_X.insert(x);

                bron_kerbosch_identical(new_R, new_P, new_X);

                P.erase(v);
                X.insert(v);
            }
        };

    std::unordered_set<std::string> R = { seed };
    std::unordered_set<std::string> P;
    auto it_seed = adj.find(seed);
    if (it_seed != adj.end()) P = it_seed->second;
    std::unordered_set<std::string> X;

    bron_kerbosch_identical(R, P, X);

    if (all_maximal_cliques.empty()) {
        py::list outer;
        py::list inner;
        inner.append(seed);
        outer.append(inner);
        return outer;
    }

    std::sort(all_maximal_cliques.begin(), all_maximal_cliques.end(), [](const auto& a, const auto& b) {
        return to_sorted_vector(a) < to_sorted_vector(b);
    });

    const std::unordered_set<std::string>* max_clique_set = &all_maximal_cliques.front();
    for (const auto& c : all_maximal_cliques) {
        if (c.size() > max_clique_set->size()) {
            max_clique_set = &c;
        }
    }

    py::list outer;
    py::list inner;
    auto final_clique_sorted = to_sorted_vector(*max_clique_set);
    for (const auto& v : final_clique_sorted) {
        inner.append(v);
    }
    outer.append(inner);
    return outer;
}

PYBIND11_MODULE(clique_finder_identical, m) {
    m.doc() = "C++ Bron–Kerbosch clique finder, logically identical to the Python script";
    m.def("find_max_cliques_with_seed_identical", &find_max_cliques_with_seed_identical,
          py::arg("graph"), py::arg("seed"),
          "Find the global maximum clique containing `seed`, replicating the Python logic identically.");
}