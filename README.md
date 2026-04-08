# CAM-Net

## Content

- [Introduction](#introduction)
- [Package requirement](#package-requirement)
- [Installation environment](#installation-environment)
- [Example](#example)
- [Result](#result)
- [Datasets](#datasets)
- [Contact](#contact)

## Introduction

CAM-Net identifies an optimal consortium for a target microbe, representing its most stable and ecologically meaningful neighborhood rather than a collection of isolated pairwise links.

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
3.conda create -n camnet python=3.10
4.conda activate camnet
5.pip install cam_net-1.0-cp310-cp310-linux_x86_64.whl
```

## Example

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

## Result

| Output file |                           Content                            |
| :---------: | :----------------------------------------------------------: |
| summary.csv | 1. the name of the target microbe you input<br />2. optimal consortium of target microbe<br />3. *R* values of the predicted target microbe from the optimal consortium |
|  edges.csv  |                  network edges and weights                   |

## Datasets

All data supporting the findings of this study are derived from publicly available sources. Specifically, microbiome datasets and their source are hosted on the [Microbiome Search Engine](http://bioinfo-ai.cn/) (MSE) [1] platform. Detailed information about the dataset can be found at here: https://github.com/qdu-bioinfo/CAM-Net/tree/main/input.

<<<<<<< HEAD
|                         **Dataset**                          | **#  of samples** | **#  of studies** |        **Type**        |
| :----------------------------------------------------------: | :---------------: | :---------------: | :--------------------: |
| [Asia_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_WGS.7z) |      *n*=961      |      *n*=11       |    Metagenomic WGS     |
| [Australia_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Australia_WGS.7z) |      *n*=397      |       *n*=3       |    Metagenomic WGS     |
| [Europe_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_WGS.7z) |     *n*=2,547     |      *n*=20       |    Metagenomic WGS     |
| [North America_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/North%20America_WGS.7z) |     *n*=5,045     |      *n*=21       |    Metagenomic WGS     |
| [Asia_16S](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_16S.7z) |    *n*=10,223     |      *n*=18       | 16S rRNA gene amplicon |
| [Europe_16S](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_16S.7z) |     *n*=6,377     |      *n*=28       | 16S rRNA gene amplicon |
=======
|      Dataset      |                             Link                             |
| :---------------: | :----------------------------------------------------------: |
|     [Asia_WGS](https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_WGS.7z)      | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_WGS.7z |
|   Australia_WGS   | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Australia_WGS.7z |
|    Europe_WGS     | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_WGS.7z |
| North America_WGS | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/North%20America_WGS.7z |
|     Asia_16S      | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Asia_16S.7z |
|    Europe_16S     | https://github.com/qdu-bioinfo/CAM-Net/blob/main/input/Europe_16S.7z |
>>>>>>> 2c4d2f33a9f6fed43036db73e65440a93d39bae0

[1] Jing et al. *mSystems*. 2021

## Contact

All problems please contact CAM-Net development team: **Dr. Su, Xiaoquan**  Email: [**suxq@qdu.edu.cn**](mailto:suxq@qdu.edu.cn)
