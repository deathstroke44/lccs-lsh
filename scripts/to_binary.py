import csv
import struct
import numpy as np

dataset_path = '/data/kabir/similarity-search/dataset/'

def to_binary(dataset_name):
    inDataFilename = dataset_path+'%s/%s.ds'%(dataset_name, dataset_name)
    inQueryFilename = dataset_path+'%s/%s.q'%(dataset_name, dataset_name)
    outDataFilename = dataset_path+'%s/%s.dsb'%(dataset_name, dataset_name)
    outQueryFilename = dataset_path+'%s/%s.qb'%(dataset_name, dataset_name)

    print(dataset_name)
    with open(inDataFilename, 'r') as fin, open(outDataFilename, 'wb') as fout:
        reader = csv.reader(fin, delimiter=' ')
        
        for row in reader:
            # print(row)
            x = [float(ri) for ri in row[1:] if ri!='' ]

            fout.write(struct.pack('f'*len(x), *x))          
    with open(inQueryFilename, 'r') as fin, open(outQueryFilename, 'wb') as fout:
        reader = csv.reader(fin, delimiter=' ')
        
        for row in reader:
            # print(row)
            x = [float(ri) for ri in row[1:] if ri!='' ]

            fout.write(struct.pack('f'*len(x), *x))           


# to_binary('Mnist')
to_binary('Sift')
# to_binary('Gist')
# to_binary('Mnist784')
# to_binary('glove')
# to_binary('Trevi')