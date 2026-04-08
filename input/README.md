# Datasets

1. the datasets utilized in this study, consisting of human gut samples, were retrieved from the MSE (Microbiome Search Engine) [1] and are summarized in **Table 1** of the main manuscript. 

2. for WGS sequences, taxonomic annotation was performed using MetaPhlAn (Metagenomic Phylogenetic Analysis) [2] based on the RefSeq (Reference Sequence) database [3], with analyses restricted exclusively to bacterial taxonomic profiles.
3. for 16S rRNA amplicon data, analysis was conducted using the PMS (Parallel-Meta Suite) [4]: sequences underwent ASV (Amplicon Sequence Variant) denoising, followed by OTU (Operational Taxonomic Unit) clustering based on the denoised ASVs and mapping to the Greengenes (v13.8) [5] reference database. 
4. finally, to mitigate inter-sample heterogeneity, both 16S rRNA and WGS taxonomic profiles were log-transformed prior to downstream analysis (refer to *Experimental design* for details about log-transformation in the main manuscript).

|    **Dataset**    | **#  of samples** | **#  of studies** |        **Type**        |                             Link                             |
| :---------------: | :---------------: | :---------------: | :--------------------: | :----------------------------------------------------------: |
|     Asia_WGS      |      *n*=961      |      *n*=11       |    Metagenomic WGS     | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_WGS.7z |
|   Australia_WGS   |      *n*=397      |       *n*=3       |    Metagenomic WGS     | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Australia_WGS.7z |
|    Europe_WGS     |     *n*=2,547     |      *n*=20       |    Metagenomic WGS     | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_WGS.7z |
| North America_WGS |     *n*=5,045     |      *n*=21       |    Metagenomic WGS     | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/North%20America_WGS.7z |
|     Asia_16S      |    *n*=10,223     |      *n*=18       | 16S rRNA gene amplicon | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_16S.7z |
|    Europe_16S     |     *n*=6,377     |      *n*=28       | 16S rRNA gene amplicon | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_16S.7z |

[1] Jing et al. *mSystems*. 2021

[2] Manghi et al. *Cell Reports*. 2023

[3] Goldfarb et al. *Nucleic Acids Research*. 2025

[4] Chen et al. *iMeta*. 2022

[5] DeSantis et al. *Applied* and *Environmental Microbiology*. 2006

## Contact

All problems please contact CAM-Net development team: **Dr. Su, Xiaoquan**  Email: [**suxq@qdu.edu.cn**](mailto:suxq@qdu.edu.cn)
