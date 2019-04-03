#include "srp.h"

using namespace std;

SRP::SRP(int d, int K, int M)
    : dim(d)
    , K(K)
    , M(M)
    , p(K * M * d)
{
    assert(d > 0 && K > 0 && M > 0);

    std::normal_distribution<double> normalDistribution(0.);
    std::random_device rd;
    std::default_random_engine rng(rd());
    for (int i = 0; i < K * M * d; i++) {
        p[i] = normalDistribution(rng);
    }
}

SRP::~SRP()
{
}

std::vector<SigType> SRP::getSig(const Scalar* data)
{
    std::vector<SigType> ret(K);
    for (int i = 0; i < K; i++) {
        int sigi = 0;
        for (int j = 0; j < M; j++) {
            int idx = i * M * dim + j * dim;
            float sum = calc_inner_product(dim, &p[idx], data);
            if (sum >= 0) {
                sigi = (sigi << 1) + 1;
            } else {
                sigi = sigi << 1;
            }
        }
        ret[i] = sigi;
    }
    return ret;
}

SRPPair::SRPPair(int d, int K, int M)
    : dim(d)
    , K(K)
    , M(M)
{
    assert(d > 0 && K > 0 && M > 0);
    //let nHasher*(nHasher-1)/2 > K*M;
    nHasher = (int)(sqrt(2 * K * M) + 1.5);
    p.resize(nHasher * d);
    pairs.reserve(nHasher * (nHasher - 1) / 2);

    std::normal_distribution<double> normalDistribution(0.);
    std::random_device rd;
    std::default_random_engine rng(rd());
    for (int i = 0; i < nHasher; i++) {
        for (int j = 0; j < d; j++) {
            int idx = i * d + j;
            p[idx] = normalDistribution(rng);
        }
        double norm = sqrt(calc_inner_product(d, &p[i * d], &p[i * d]));
        for (int j = 0; j < d; j++) {
            int idx = i * d + j;
            p[idx] /= norm;
        }
    }

    for (int i = 0; i < nHasher; i++) {
        for (int j = i + 1; j < nHasher; j++) {
            pairs.emplace_back(i, j);
        }
    }
    random_shuffle(pairs.begin(), pairs.end());
}

SRPPair::~SRPPair()
{
}

std::vector<SigType> SRPPair::getSig(const Scalar* data)
{
    std::vector<Scalar> innerProduct(nHasher);
    for (int i = 0; i < nHasher; i++) {
        innerProduct[i] = calc_inner_product(dim, &p[i * dim], data);
    }

    std::vector<SigType> ret(K);
    for (int i = 0; i < K; i++) {
        int sigi = 0;
        for (int j = 0; j < M; j++) {
            int idx = i * M + j;
            int u = pairs[idx].first;
            int v = pairs[idx].second;
            sigi = (sigi << 1) ^ (innerProduct[u] < innerProduct[v]);
        }
        ret[i] = sigi;
    }
    return ret;
}