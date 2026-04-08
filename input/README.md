# Datasets

1. The datasets utilized in this study, consisting of human gut samples, were retrieved from the [MSE](http://bioinfo-ai.cn/) (Microbiome Search Engine) [1].

1. For WGS sequences, taxonomic annotation was performed using MetaPhlAn (Metagenomic Phylogenetic Analysis) [2] based on the RefSeq (Reference Sequence) database [3], with analyses restricted exclusively to bacterial taxonomic profiles.

2. For 16S rRNA amplicon data, analysis was conducted using the PMS (Parallel-Meta Suite) [4]: sequences underwent ASV (Amplicon Sequence Variant) denoising, followed by OTU (Operational Taxonomic Unit) clustering based on the denoised ASVs and mapping to the Greengenes (v13.8) [5] reference database. 

3. Finally, to mitigate inter-sample heterogeneity, both 16S rRNA and WGS taxonomic profiles were log-transformed prior to downstream analysis. Here, the suffixes "original relative abundance" and "log-transformation" indicate raw abundance and log10-transformed abundance, respectively.

   

[1] Jing et al. *mSystems*. 2021

[2] Manghi et al. *Cell Reports*. 2023

[3] Goldfarb et al. *Nucleic Acids Research*. 2025

[4] Chen et al. *iMeta*. 2022

[5] DeSantis et al. *Applied* *and* *Environmental Microbiology*. 2006

## Contact

All problems please contact CAM-Net development team: **Dr. Su, Xiaoquan**  Email: [**suxq@qdu.edu.cn**](mailto:suxq@qdu.edu.cn)
