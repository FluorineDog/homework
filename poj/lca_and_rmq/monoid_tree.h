#include <vector>
using std::vector;
#define clz(x) __builtin_clz(x)
#define ctz(x) __builtin_ctz(x)

typedef double T;
#define NIL 0
#define func(a, b) ((a) + (b))
class MonoidTree {
public:
  MonoidTree(int length) {
    int bsize;
    layer_count = 1;
    for (bsize = 1; bsize < length; bsize <<= 1) {
      layer_count++;
    }
    bsize_ = bsize;
    // int leading_zeros = clz(size - 1);
    // layer_count = 32 - leading_zeros;
    data.resize(layer_count, vector<T>(bsize, NIL));
  }

  T raw_update(int index, T k) { data[0][index] = k; }

  void fast_init() {
    const vector<T> &raw_data = data[0];
    for (int layer = 1; layer < layer_count; ++layer) {
      int step = 1 << layer;
      int mask = 1 << layer - 1;
      int decision_bit = 1 << (layer - 1);
      // need [beg, stand)
      // 			[stand, end)
      for (int stand = 0; stand < bsize_; stand += step) {
        // [beg, stand + step)
        // from [old_stand, stand + step) to what the fuck
        // <== XXXX1-XXXY0
        int old_stand = stand + decision_bit;
        T right = data[layer - 1][old_stand];
        for (int i = old_stand; i-- > stand;) {
          right = func(raw_data[i], right);
          data[layer][i] = right;
        }
        // [stand, end)
        // from [stand, old_stand) to what the fuck
        // <== XXXX1-XXXY0
        T left = data[layer][stand];
        for (int i = old_stand; i < stand + step; ++i) {
          data[layer][i] = left;
          left = func(left, raw_data[i]);
        }
      }
    }
  }

  T reduce(int beg, int end) {
    if(beg == end){
      return NIL;
    }
    int base = beg ^ end;
    int lz = clz(base);
    int stand = 1 << (32 - lz);
    int left_lz = clz(stand - beg);
    int right_lz = clz(end - stand);
    
  }

private:
  vector<vector<T> /**/> data;
  int layer_count;
  int bsize_;
};
