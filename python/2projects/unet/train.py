import os
import argparse
import numpy as np
import matplotlib.pyplot as plt

import torch
import torch.nn as nn
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SumamryWriter

from torchvision import transforms, datasets

from model import UNet



parser = argparse.ArgumentParser(description="Train the UNet",
                                 formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("--lr", default=1e-3, type=float, dest="lr")
parser.add_argument("--batch_size", default=4, type=int, dest="batch_size")
parser.add_argument("--num_epoch", default=100, type=int, dest="num_epoch")

parser.add_argument("--data_dir", default="./datasets", type=str, dest="data_dir")
parser.add_argument("--ckpt_dir", default="./checkpoint", type=str, dest="ckpt_dir")
parser.add_argument("--log_dir", default="./log", type=str, dest="log_dir")
parser.add_argument("--result_dir", default="./result", type=str, dest="result_dir")

parser.add_argument("--mode", default="train", type=str, dest="mode")
parser.add_argument("--train_continue", default="off", type=str, dest="train_continue")

args = parser.parse_args()



lr = args.lr
batch_size = args.batch_size
num_epoch = args.num_epoch


data_dir = args.data_dir
ckpt_dir = args.ckpt_dir
log_dir = args.log_dir
result_dir = args.result_dir


mode = args.mode
train_continue = args.train_continue


device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')





