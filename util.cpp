#include "util.h"

using namespace std;

// -----------------------------------------------------------------------------
int ResultComp(						// compare function for qsort (ascending)
	const void *e1,						// 1st element
	const void *e2)						// 2nd element
{
	int ret = 0;
	Result *item1 = (Result*) e1;
	Result *item2 = (Result*) e2;

	if (item1->key_ < item2->key_) {
		ret = -1;
	} 
	else if (item1->key_ > item2->key_) {
		ret = 1;
	} 
	else {
		if (item1->id_ < item2->id_) ret = -1;
		else if (item1->id_ > item2->id_) ret = 1;
	}
	return ret;
}

// -----------------------------------------------------------------------------
int ResultCompDesc(					// compare function for qsort (descending)
	const void *e1,						// 1st element
	const void *e2)						// 2nd element
{
	int ret = 0;
	Result *item1 = (Result*) e1;
	Result *item2 = (Result*) e2;

	if (item1->key_ < item2->key_) {
		ret = 1;
	} 
	else if (item1->key_ > item2->key_) {
		ret = -1;
	} 
	else {
		if (item1->id_ < item2->id_) ret = -1;
		else if (item1->id_ > item2->id_) ret = 1;
	}
	return ret;
}

// -----------------------------------------------------------------------------
void create_dir(					// create dir if the path exists
	char *path)							// input path
{
	int len = (int) strlen(path);
	for (int i = 0; i < len; ++i) {
		if (path[i] == '/') {
			char ch = path[i + 1];
			path[i + 1] = '\0';
									// check whether the directory exists
			int ret = access(path, F_OK);
			if (ret != 0) {			// create the directory
				ret = mkdir(path, 0755);
				if (ret != 0) {
					printf("Could not create directory %s\n", path);
				}
			}
			path[i + 1] = ch;
		}
	}
}

template<class DType>
void readFVecsFromExternal(const char* filepath, DType **data, int N, int maxRow=-1) {
  FILE *infile = fopen(filepath, "rb");
  if (infile == NULL) {
    std::cout << "File not found" << std::endl;
    return;
  }
  
  int rowCt = 0;
  int dimen;
  while (true) {
    if (fread(&dimen, sizeof(int), 1, infile) == 0) {
      break;
    }
    if (dimen != N) {
      std::cout << "N and actual dimension mismatch" << std::endl;
      return;
    }
    std::vector<DType> v(dimen);
    if(fread(v.data(), sizeof(DType), dimen, infile) == 0) {
      std::cout << "Error when reading" << std::endl;
    };
    
    for (int i=0; i<dimen; i++) {
      data[rowCt][i]= v[i];
    }

    rowCt++;
    
    if (maxRow != -1 && rowCt >= maxRow) {
      break;
    }
  }
  // std::cout<<"Row count test: "<<rowCt<<std::endl;

  if (fclose(infile)) {
    std::cout << "Could not close data file" << std::endl;
  }
}

// -----------------------------------------------------------------------------
int read_data(						// read data/query set from disk
	int   n,							// number of data/query objects
	int   d,			 				// dimensionality
	const char *fname,					// address of data/query set
	float **data)						// data/query objects (return)
{
	readFVecsFromExternal<float>(fname, data, d, n);
	return 0;
}

// -----------------------------------------------------------------------------
int read_data_binary(						// read data/query set from disk
	int   n,							// number of data/query objects
	int   d,			 				// dimensionality
	const char *fname,					// address of data/query set
	float **data)						// data/query objects (return)
{
	FILE *fp = fopen(fname, "rb");
	if (!fp) {
		printf("Could not open %s\n", fname);
		return 1;
	}

	int i   = 0;
	while (!feof(fp) && i < n) {
		assert(fread(data[i], sizeof(float), d, fp) == d);
		++i;
	}
	fclose(fp);

	return 0;
}

// -----------------------------------------------------------------------------
int read_ground_truth(				// read ground truth results from disk
	int qn,								// number of query objects
	const char *fname,					// address of truth set
	Result **R)							// ground truth results (return)
{
	FILE *fp = fopen(fname, "r");
	if (!fp) {
		printf("Could not open %s\n", fname);
		return 1;
	}

	int tmp1 = -1;
	int tmp2 = -1;
	assert(fscanf(fp, "%d %d\n", &tmp1, &tmp2) == 2);
	assert(tmp2 == MAXK);

	for (int i = 0; i < qn; ++i) {
		for (int j = 0; j < MAXK; ++j) {
			assert(fscanf(fp, "%d %f ", &R[i][j].id_, &R[i][j].key_) == 2);
		}
	}
	fclose(fp);

	return 0;
}

// -----------------------------------------------------------------------------
int read_ground_truthV2(				// read ground truth results from disk
	int qn,
	int d,								// number of query objects
	const char *fname,					// address of truth set
	Result **R,
	float **data,
	float **query)							// ground truth results (return)
{
	FILE *infile = fopen(fname, "rb");
	if (infile == NULL) {
		std::cout << "File not found" << std::endl;
		return 1;
	}
	
	int rowCt = 0;
	int dimen;
	while (true) {
		if (fread(&dimen, sizeof(int), 1, infile) == 0) {
			break;
		}
		if (dimen != MAXK) {
			std::cout << "N and actual dimension mismatch" << std::endl;
			return 1;
		}
		std::vector<int> v(MAXK);
		if(fread(v.data(), sizeof(int), dimen, infile) == 0) {
			std::cout << "Error when reading" << std::endl;
		};
		
		for (int i=0; i<MAXK; i++) {
			R[rowCt][i].id_ = v[i]+1;
			R[rowCt][i].key_ = calc_l2_dist(d, query[rowCt], data[v[i]]);
		}

		rowCt++;
		
		if (qn != -1 && rowCt >= qn) {
			break;
		}
	}
	// std::cout<<"Row count test: "<<rowCt<<std::endl;

	if (fclose(infile)) {
		std::cout << "Could not close data file" << std::endl;
		return 1;
	}
	return 0;
}

void normalize(
	int dim, 
	float * p
)
{
	double norm = sqrt(calc_inner_product(dim, p, p));
	if(norm < 1e-9) {
		return ;
	}
	for(int i=0;i<dim;i++){
		p[i] /= norm;
	}
}

// -----------------------------------------------------------------------------
float calc_angle(				// calc angle
	int   dim,							// dimension
	const float *p1,					// 1st point
	const float *p2)					// 2nd point
{
	return acos(calc_cosangle(dim, p1, p2));
}

// -----------------------------------------------------------------------------
float calc_angle_normalized(				// calc angle
	int   dim,							// dimension
	const float *p1,					// 1st point
	const float *p2)					// 2nd point
{
	return acos(calc_inner_product(dim, p1, p2));
}

// -----------------------------------------------------------------------------
float calc_cosangle(				// calc cos(angle)
	int   dim,							// dimension
	const float *p1,					// 1st point
	const float *p2)					// 2nd point
{
	double ret = 0.0f;
	double norm0 = 0., norm1 = 0.;
	for (int i = 0; i < dim; ++i) {
		ret += (p1[i] * p2[i]);
		norm0 += p1[i] * p1[i];
		norm1 += p2[i] * p2[i];
	}
	if(norm0==0 || norm1==0){
		return 0;
	}
	return ret/sqrt(norm0*norm1);
}

// // -----------------------------------------------------------------------------
// float calc_l2_sqr(					// calc L2 square distance
// 	int   dim,							// dimension
// 	const float *p1,					// 1st point
// 	const float *p2)					// 2nd point
// {
// 	float diff = 0.0f;
// 	float ret  = 0.0f;
// 	for (int i = 0; i < dim; ++i) {
// 		diff = p1[i] - p2[i];
// 		ret += diff * diff;
// 	}
// 	return ret;
// }

// -----------------------------------------------------------------------------
float calc_lp_dist(					// calc L_{p} norm
	int   dim,							// dimension
	float p,							// the p value of Lp norm, p in (0,2]
	const float *vec1,					// 1st point
	const float *vec2)					// 2nd point
{
	if (fabs(p - 0.f) < FLOATZERO) {
		return calc_l0_dist(dim, vec1, vec2);
	}
	else {
		return calc_lp_dist_p(dim, p, vec1, vec2);
	}
}
// -----------------------------------------------------------------------------
float calc_recall(					// calc recall (percentage)
	int   k,							// top-k value
	const Result *R,					// ground truth results 
	MaxK_List *list)					// results returned by algorithms
{
	int cnt=0;
	for(int i=0;i<k;i++) {
		for(int j=0;j<k;j++) {
			if (list->ith_id(i) == R[j].id_-1) {
				cnt++;
				break;
			}
		}
	}
	return (cnt) * 100.0f / k;
}

// -----------------------------------------------------------------------------
float calc_recall(					// calc recall (percentage)
	int   k,							// top-k value
	const Result *R,					// ground truth results
	MinK_List *list)					// results returned by algorithms
{
	int i = list->size()-1;
	int last = k - 1;
	//loop until list->ithkey <= R[last].key
	while (i >= 0 && R[last].key_ - list->ith_key(i) < -FLOATZERO) {
		i--;
	}
	return (i + 1) * 100.0f / k;
}

// -----------------------------------------------------------------------------
int get_hits(						// get the number of hits between two ID list
	int   k,							// top-k value
	int   t,							// top-t value
	const Result *R,					// ground truth results 
	MaxK_List *list)					// results returned by algorithms
{
	int i = k - 1;
	int last = t - 1;
	while (i >= 0 && R[last].key_ - list->ith_key(i) > FLOATZERO) {
		i--;
	}
	return min(t, i + 1);
}

float calc_weighted_dist2(			// calc inner product
	int   dim,							// dimension
	const float *w,
	const float *p1,					// 1st point
	const float *p2)					// 2nd point
{
	double ret = 0.0f;
	for (int i = 0; i < dim; ++i) {
		ret += w[i]*(p1[i]-p2[i])*(p1[i]-p2[i]);
	}
	return ret;
}


int calc_hamming_dist(			// calc inner product
	int   dim,		
	const uint8_t *p1,					// 1st point
	const uint8_t *p2)					// 2nd point
{
	int tail = dim%8;
	int ret = 0;
	for(int i=0;i<tail;i++){
		ret += get_num_bits8(p1[i]^p2[i]);
	}
	ret += calc_hamming_dist(dim/8, (const uint64_t*)(p1+tail), (const uint64_t*)(p2+tail));
	return ret;
}

int calc_hamming_dist(			// calc inner product
	int   dim,		
	const uint64_t *p1,					// 1st point
	const uint64_t *p2)					// 2nd point
{
	int ret = 0;
	for(int i=0;i<dim;i++){
		ret += get_num_bits64(p1[i]^p2[i]);
	}
	return ret;
}

float calc_ratio(
	int k, 
	const Result *Rs, 
	MinK_List *list)
{
	if(list->size()<k){
		return sqrt(1e9);
	}
	double ret  = (list->ith_key(k-1)+1e-9) / (Rs[k-1].key_+1e-9);
	if(ret<0){
		ret = 1e9;
	} else if(ret<1){
		ret = 1/ret;
	}
	return sqrt(ret);
}
float calc_ratio(
	int k, 
	const Result *Rs, 
	MaxK_List *list)
{
	if(list->size()<k){
		return sqrt(1e9);
	}
	double ret  = (list->ith_key(k-1)+1e-9) / (Rs[k-1].key_+1e-9);
	if(ret<0){
		ret = 1e9;
	} else if(ret<1){
		ret = 1/ret;
	}
	return sqrt(ret);
}

const int PrefixTableSize = 1 << 16;
std::array<uint8_t, PrefixTableSize> _prefix_table;

bool init_prefix_table()
{
	for (int i = 0; i < PrefixTableSize; i++) {
		//calculate the prefix-1 of i, since it will be run only once, implement using stupid way
		_prefix_table[i] = 0;
		for (int j = 0; j < 16; j++) {
			int mask = 1 << (15 - j);
			if (i&mask) {
				_prefix_table[i]++;
			}
			else {
				break;
			}
		}
	}
	return true;
}

int get_num_prefix(uint16_t u)
{
	static bool initialized = init_prefix_table();
	return _prefix_table[u];
}

int get_num_prefix(uint32_t u)
{
	int a = get_num_prefix(uint16_t(u >> 16));
	if (a != 16) {
		return a;
	}
	int b = get_num_prefix(uint16_t(u & 0xffff));
	return a + b;
}

int get_num_prefix(uint64_t u)
{
	int a = get_num_prefix(uint16_t(u >> 48));
	if (a != 16) {
		return a;
	}
	int b = get_num_prefix(uint16_t((u >> 32) & 0xffff));
	if (b != 16) {
		return a + b;
	}
	int c = get_num_prefix(uint16_t((u >> 16) & 0xffff));
	if (c != 16) {
		return a + b + c;
	}
	int d = get_num_prefix(uint16_t(u & 0xffff));
	return a + b + c + d;
}
