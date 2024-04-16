class Astro:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 256
        self.r = 0.66
        self.name = 'astro1m'
        self.k=100
        
class Audio:
    def __init__(self):
        self.n = 53387
        self.qn = 200
        self.d = 192
        self.r = 0.66
        self.name = 'audio'
        self.k=20
        
class BigANN:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 128
        self.r = 0.66
        self.name = 'bigann'
        self.k=100
        
class Cifar:
    def __init__(self):
        self.n = 50000
        self.qn = 200
        self.d = 512
        self.r = 0.66
        self.name = 'cifar'
        self.k=20
        
class Crawl:
    def __init__(self):
        self.n = 1989995
        self.qn = 10000
        self.d = 300
        self.r = 0.66
        self.name = 'crawl'
        self.k=100
        
class Deep:
    def __init__(self):
        self.n = 1000000
        self.qn = 200
        self.d = 256
        self.r = 0.66
        self.name = 'deep'
        self.k=20
        
class Enron:
    def __init__(self):
        self.n = 94987
        self.qn = 200
        self.d = 1369
        self.r = 0.66
        self.name = 'enron'
        self.k=20
        


        
class Gist:
    def __init__(self):
        self.n = 1000000
        self.qn = 1000
        self.d = 960
        self.r = 0.66
        self.name = 'gist'
        self.k=100

class Glove:
    def __init__(self):
        self.n = 1192514
        self.qn = 200
        self.d  = 100
        self.name = 'glove'
        self.r =  0.66
        self.k=20

class ImageNet:
    def __init__(self):
        self.n = 2340373
        self.qn = 200
        self.d  = 150
        self.name = 'imageNet'
        self.r =  0.66
        self.k=20

class LastFm:
    def __init__(self):
        self.n = 292385
        self.qn = 100
        self.d  = 65
        self.name = 'lastfm'
        self.r =  0.66
        self.k=100


class MNIST:
    def __init__(self):
        self.n = 69000
        self.qn = 200
        self.d = 784
        self.r = 0.66
        self.name = 'MNIST'
        self.k=20
        
        
class MovieLens:
    def __init__(self):
        self.n = 10677
        self.qn = 1000
        self.d  = 150
        self.r = 0.66
        self.name = 'movielens'
        self.k=100
        
class Msong:
    def __init__(self):
        self.n = 992272
        self.qn = 200
        self.d  = 420
        self.r = 0.66
        self.name = 'millionSong'
        self.k=20

class NUSW:
    def __init__(self):
        self.n = 268643
        self.qn = 200
        self.d = 500
        self.r = 0.66
        self.name = 'nuswide'
        self.k=20

class Notre:
    def __init__(self):
        self.n = 332668
        self.qn = 200
        self.d = 128
        self.r = 0.66
        self.name = 'notre'
        self.k=20
        
class Netflix:
    def __init__(self):
        self.n = 17770
        self.qn = 1000
        self.d = 300
        self.r = 0.66
        self.name = 'netflix'
        self.k=100

class NyTimes:
    def __init__(self):
        self.n = 290000
        self.qn = 100
        self.d  = 256
        self.name = 'nytimes'
        self.r =  0.66
        self.k=100

class Random:
    def __init__(self):
        self.n = 1000000
        self.qn = 200
        self.d  = 100
        self.name = 'random'
        self.r =  0.66
        self.k=20
        
class Sald:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 128
        self.r = 0.66
        self.name = 'sald1m'
        self.k=100
        
class Seismic:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 256
        self.r = 0.66
        self.name = 'seismic1m'
        self.k=100
        
class Sift:
    def __init__(self):
        self.n = 1000000
        self.qn = 10000
        self.d = 128
        self.r = 0.66
        self.name = 'sift'
        self.k=100
        
class Space:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 100
        self.r = 0.66
        self.name = 'space1V'
        self.k=100
        
class Sun:
    def __init__(self):
        self.n = 79106
        self.qn = 200
        self.d = 512
        self.r = 0.66
        self.name = 'sun'
        self.k=20
        
class Text:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 200
        self.r = 0.66
        self.name = 'text-to-image'
        self.k=100
        
class Ukbench:
    def __init__(self):
        self.n = 1097907
        self.qn = 200
        self.d = 128
        self.r = 0.66
        self.name = 'ukbench'
        self.k=20
        
class Uqv:
    def __init__(self):
        self.n = 1000000
        self.qn = 10000
        self.d = 256
        self.r = 0.66
        self.name = 'uqv'
        self.k=100
        
class Tiny:
    def __init__(self):
        self.n = 5000000
        self.qn = 1000
        self.d = 384
        self.r = 0.66
        self.name = 'tiny5m'
        self.k=100
        
class Trevi:
    def __init__(self):
        self.n = 99900
        self.qn = 200
        self.d = 4096
        self.r = 0.66
        self.name = 'trevi'
        self.k=20
        


        
class Yahoo:
    def __init__(self):
        self.n = 136736
        self.qn = 100
        self.d = 300
        self.r = 0.66
        self.name = 'yahoomusic'
        self.k=100
        


        
class WordToVec:
    def __init__(self):
        self.n = 1000000
        self.qn = 1000
        self.d = 300
        self.r = 0.66
        self.name = 'word2vec'
        self.k=100