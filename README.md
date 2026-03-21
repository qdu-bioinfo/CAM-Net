# CAM-Net

## Content

- [Introduction](#introduction)
- [Package requirement](#package-requirement)
- [Installation environment](#installation-environment)
- [Example](#example)
- [Result](#result)
- [Supplementary](#supplementary)
- [Contact](#contact)

## Introduction

CAM-Net can output the optimal consortium of the target microbe, which represents the closest group of the target microbe.

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

## Installation environment

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
here, "**-i**" represents the input abundance table CSV file, "**-t**" represents the name of the target microbe, and "**-o**" represents the output results folder.

```
cam-net -i example/example.csv -t s__Akkermansia_muciniphila -o results
```

## Result

The output file "**summary.csv**" will contain the following information: 1. Target microbe; 2. Optimal consortium of target microbe; 3. r-values of the predicted target microbe from the optimal consortium.

Additionally, the output file "**edges.csv**" will contain: network edges and weights.

## Supplementary

[**Real Dataset 1**](https://github.com/qdu-bioinfo/XX) contains 10,223 Asia and 6377 Europe 16S amplicon samples originating from Microbiome Search Engine (MSE).

[**Real Dataset 2**](https://github.com/qdu-bioinfo/XXXX) contains 961 Asia, 397 Australia, 2547 Europe and 5046 North America WGS Metagenome samples originating from Microbiome Search Engine (MSE).

## Contact

All problems please contact CAM-Net development team: **Dr. Su,Xiaoquan**  Email: [**suxq@qdu.edu.cn**](mailto:suxq@qdu.edu.cn)
