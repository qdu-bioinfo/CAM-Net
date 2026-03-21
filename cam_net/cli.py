# cam_net/cli.py
from pathlib import Path
import typer
from cam_net.pipeline import run_pipeline

app = typer.Typer(
    help="CAM-Net: Context-aware microbial correlation analysis"
    # ,add_completion=False,
)

@app.command("run")
def run_analysis(
    input_csv: Path = typer.Option(
        ...,
        "--input", "-i",
        help="CSV file path",
        exists=True,
        dir_okay=False,
    ),
    seed: str = typer.Option(
        ...,
        "--seed",
        "-t",
        help="target microbe e.g., g__Lactobacillus",
    ),
    output: Path = typer.Option(
        Path("results"),
        "--output",
        "-o",
        help="output directory",
    ),

):

    typer.echo(f"Run CAM-Net | target microbe: {seed} | input: {input_csv.name}")
    typer.echo(f"output directory: {output.resolve()}")

    result_df = run_pipeline(
        csv_path=input_csv,
        seed_taxa=seed,
        output_dir=output,

    )

    if result_df is None or result_df.empty:
        typer.secho("Analysis failed: No effective optimal consortium containing the target microbe was found.", fg=typer.colors.RED)
        raise typer.Exit(code=1)


    row = result_df.iloc[0]

    typer.secho("\n" + "═" * 70, fg=typer.colors.GREEN)
    typer.secho(f"target microbe: {row['Seed_Taxon']}", bold=True)
    typer.secho(f"Members of the optimal consortium: {row['Clique_Members']}")
    typer.secho(f"the size of optimal consortium: {row['Clique_Size']}")
    typer.secho(f"predicted r-value: {row['r-value']:.4f}", bold=True)
    typer.secho("═" * 70, fg=typer.colors.GREEN)

    typer.echo("\nDetailed results have been saved:")
    typer.echo(f"  • {output / 'predictions.csv'}      → All sample actual vs. predicted abundance")
    typer.echo(f"  • {output / 'prediction_plot.pdf'}  → Scatter plot + predicted r-value")
    typer.echo(f"  • {output / 'summary.csv'}          → Summarize the information (seeds, clusters, r values)")
    typer.echo(f"  • {output / 'edges.csv'}            → Network edge list (Optional view)")


if __name__ == "__main__":
    app()