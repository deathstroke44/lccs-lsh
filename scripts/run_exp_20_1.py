from dataset_config import *
from method_config import LCCS
import os
import sys
from run_ground_truth import run_ground_truth
from run_time_recall import run_alg

os.chdir('/data/kabir/similarity-search/models/lccs-lsh-20/build')
if __name__ == '__main__':
    run_alg([LCCS()], [Deep()], 'l2')
    run_alg([LCCS()], [Glove()], 'l2')
    run_alg([LCCS()], [MNIST()], 'l2')
    run_alg([LCCS()], [Msong()], 'l2')
    run_alg([LCCS()], [NUSW()], 'l2')