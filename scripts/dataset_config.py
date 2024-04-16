class Astro:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 256
        self.r = 0.66
        self.name = 'astro1m'
        self.k=100
        
class BigANN:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 128
        self.r = 0.66
        self.name = 'bigann'
        self.k=100
        
class Deep:
    def __init__(self):
        self.n = 1000000
        self.qn = 200
        self.d = 256
        self.r = 0.66
        self.name = 'deep'
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
        
class Text:
    def __init__(self):
        self.n = 1000000
        self.qn = 100
        self.d = 200
        self.r = 0.66
        self.name = 'text-to-image'
        self.k=100
        
class Uqv:
    def __init__(self):
        self.n = 1000000
        self.qn = 10000
        self.d = 256
        self.r = 0.66
        self.name = 'uqv'
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