from typing import Union

import pandas as pd
import os
from pathlib import Path

from matplotlib.backends.backend_pdf import PdfPages
from sklearn.linear_model import LinearRegression
import networkx as nx
from .utils import set_seed, pearson_r, plot_prediction
import cam_net.graph_builder2 as gb
import cam_net.clique_finder_identical as cf

def run_pipeline(
    csv_path: Union[str, Path],
    seed_taxa: str,
    output_dir: Union[str, Path],
    seed_quantile: float = 0.99,
    random_state: int = 42,
    n_random_pairs: int = 10000
) -> pd.DataFrame | None:

    set_seed(random_state)
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    # input CSV
    df = pd.read_csv(csv_path)
    if 'SampleID' not in df.columns:
        df = pd.read_csv(csv_path, index_col=0)
        df = df.reset_index(names='SampleID')

    if seed_taxa not in df.columns:
        raise ValueError(f"Microbe: {seed_taxa} is not listed in the table")

    numeric_df = df.drop(columns=['SampleID']).select_dtypes(include='number')

    # build graph
    graph, signal_graph = gb.build_graph_from_abundance_cpp(
        abd_df=numeric_df.values,
        features=numeric_df.columns.tolist(),
        seed_taxa=seed_taxa,
        seed_quantile=seed_quantile,
        n_random_pairs=n_random_pairs,
        random_seed=random_state
    )
    edges = []
    for src, targets in signal_graph.items():
        for tgt, weight in targets.items():
            edges.append([src, tgt, weight])

    pd.DataFrame(edges, columns=["Node1", "Node2", "Weight"]).to_csv(
        output_dir / "edges.csv", index=False
    )
    # find optimal consortium
    cliques = cf.find_max_cliques_with_seed_identical(graph, seed_taxa)
    if not cliques or not cliques[0]:
        print("No group containing the current microbe was found.")
        return None

    max_clique = cliques[0]
    features = [x for x in max_clique if x != seed_taxa]

    # optimal consortium predicted target microbe
    model = LinearRegression(n_jobs=-1)
    X = df[features]
    y = df[seed_taxa]
    model.fit(X, y)
    y_pred = model.predict(X)

    pearson = pearson_r(y, y_pred)

    pred_df = pd.DataFrame({
        'SampleID': df['SampleID'],
        'True': y,
        'Predicted': y_pred
    })
    pred_df.to_csv(output_dir / "predictions.csv", index=False)

    # PDF
    with PdfPages(output_dir / "prediction_plot.pdf") as pdf:
        plot_prediction(y, y_pred, "Current Microbe Prediction", pdf)

    # results
    pd.DataFrame({
        'Seed': [seed_taxa],
        'Clique_Members': [", ".join(max_clique)],
        'Clique_Size': [len(max_clique)],
        'r-value': [pearson]
    }).to_csv(output_dir / "summary.csv", index=False)

    
    return pd.DataFrame({
        'Seed_Taxon': [seed_taxa],
        'Clique_Members': [", ".join(sorted(max_clique))],
        'Clique_Size': [len(max_clique)],
        'r-value': [pearson]
    })
