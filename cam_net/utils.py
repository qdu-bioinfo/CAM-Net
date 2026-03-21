import random
import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.backends.backend_pdf import PdfPages

def set_seed(seed):
    random.seed(seed)
    np.random.seed(seed)
    os.environ['PYTHONHASHSEED'] = str(seed)

def pearson_r(y_true, y_pred):
    y_true = np.asarray(y_true, dtype=float)
    y_pred = np.asarray(y_pred, dtype=float)
    if np.all(y_true == y_true[0]) or np.all(y_pred == y_pred[0]):
        return 0.0
    r = np.corrcoef(y_true, y_pred)[0, 1]
    return 0.0 if np.isnan(r) else float(r)

def plot_prediction(y_true, y_pred, title, pdf):
    plt.figure(figsize=(6, 5))
    r = pearson_r(y_true, y_pred)
    sns.regplot(x=y_true, y=y_pred, scatter_kws={'alpha':0.6}, line_kws={'color':'red'})
    plt.title(f"{title}\n(Pearson r = {r:.4f})")
    plt.xlabel("True Abundance")
    plt.ylabel("Predicted Abundance")
    pdf.savefig()
    plt.close()