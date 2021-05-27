import os
import numpy as np

import torch
import torch.nn as nn
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SumamryWriter

from torchvision import transforms, datasets



lr = 1e-3
batch_size = 4
num_epoch = 100

