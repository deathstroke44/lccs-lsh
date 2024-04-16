from dataset_config import *
from method_config import LCCS
import os
import sys
from run_ground_truth import run_ground_truth
from run_time_recall import run_alg

os.chdir('/data/kabir/similarity-search/models/lccs-lsh/build')
if __name__ == '__main__':
    run_alg([LCCS()], [Sift()], 'l2')
    run_alg([LCCS()], [Sald()], 'l2')
    run_alg([LCCS()], [WordToVec()], 'l2')