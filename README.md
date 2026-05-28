# CAM-Net

## Content

- [Introduction](#introduction)
- [Package requirement](#package-requirement)
- [Installation](#installation)
- [Usage example](#usage-example)
- [Results](#results)
- [Datasets](#datasets)
- [Contact](#contact)

## Introduction

1. CAM-Net introduces a context-aware network framework that identifies an optimal microbial consortium by modeling community context rather than relying on isolated pairwise correlations. 
2. The optimal consortium paradigm enables robust ecological inference, distinguishing stable indigenous microbes from transient exogenous species while substantially reducing spurious associations. 
3. Large-scale validation across over 25,000 gut microbiomes demonstrates that CAM-Net provide superior biological reliability for microbial interaction discovery. 

## Package requirement

```
python=3.10
pandas>=2.0,<2.3
numpy
scikit-learn
matplotlib
seaborn
networkx
pybind11
typer
openpyxl
```

## Installation

```
1.Download the ".whl" file from GitHub.
2.conda create -n camnet python=3.10
3.conda activate camnet
4.pip install cam_net-1.0-cp310-cp310-linux_x86_64.whl

Linux system selection: cam_net-1.0-cp310-cp310-linux_x86_64.whl
MacOS system selection: cam_net-1.0-cp310-cp310-macosx_11_0_arm64.whl
```

## **Usage example**

The input format is as follows:

| SampleID | target microbe | microbe1 | microbe2 | microbe3 |
| :------: | :------------: | :------: | :------: | :------: |
| Sample1  |     0.0001     |  0.004   |  0.001   |  0.006   |
| Sample2  |     0.0002     |  0.005   |  0.002   |  0.007   |
| Sample2  |     0.0003     |  0.0006  |  0.003   |  0.0008  |



The **command** is as follows:

| Command parameters |                        Representative                        |
| :----------------: | :----------------------------------------------------------: |
|         -i         |   represents the input microbe abundance table ".csv" file   |
|         -t         | represents the input table contains the names of the target microbe (e.g., s__Akkermansia_muciniphila) |
|         -o         |       represents the location of output results folder       |

```
cam-net -i example/example.csv -t s__Akkermansia_muciniphila -o results
```

## Results

| Output file |                           Content                            |
| :---------: | :----------------------------------------------------------: |
| summary.csv | 1. the name of the target microbe you input<br />2. optimal consortium of target microbe<br />3. *R* values of the predicted target microbe from the optimal consortium |
|  edges.csv  |                  network edges and weights                   |

## Datasets

All data supporting the findings of this study are derived from publicly available sources. Specifically, microbiome datasets and their source are hosted on the MSE (Microbiome Search Engine; http://bioinfo-ai.cn) [1] platform. Detailed information about the dataset is available at [here](https://github.com/qdu-bioinfo/CAM-Net/tree/main/input).

|                         **Dataset**                          | **#  of samples** | **#  of studies** |        **Type**        |
| :----------------------------------------------------------: | :---------------: | :---------------: | :--------------------: |
| [Asia_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_WGS.7z) |      *n*=961      |      *n*=11       |    Metagenomic WGS     |
| [Australia_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Australia_WGS.7z) |      *n*=397      |       *n*=3       |    Metagenomic WGS     |
| [Europe_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_WGS.7z) |     *n*=2,547     |      *n*=20       |    Metagenomic WGS     |
| [North America_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/North%20America_WGS.7z) |     *n*=5,045     |      *n*=21       |    Metagenomic WGS     |
| [Asia_16S](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_16S.7z) |    *n*=10,223     |      *n*=18       | 16S rRNA gene amplicon |
| [Europe_16S](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_16S.7z) |     *n*=6,377     |      *n*=28       | 16S rRNA gene amplicon |


[1] Jing et al. *mSystems*. 2021

## Contact

All problems please contact CAM-Net development team: **Dr. Su, Xiaoquan**  Email: [**suxq@qdu.edu.cn**](mailto:suxq@qdu.edu.cn)
