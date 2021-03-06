#include <cassert>
#include <vector>
using std::vector;
#define clz(x) __builtin_clz(x)
#define ctz(x) __builtin_ctz(x)

#ifndef NIL
typedef long long T;
#define NIL 0
#define FUNC(a, b) ((a) + (b))
#endif

class MonoidTree {
public:
  MonoidTree(int length) {
    int bsize;
    layer_count = 1;
    for (bsize = 1; bsize < length; bsize <<= 1) {
      layer_count++;
    }
    this->length_ = length;
    raw_data.resize(length, NIL);
    begin_data.resize(layer_count, vector<T>(length, NIL));
    end_data.resize(layer_count, vector<T>(length + 1, NIL));
  }

  void raw_update(int index, T k) { raw_data[index] = k; }

  void fast_init() {
    for (int layer = 0; layer < layer_count; ++layer) {
      int step = 1 << layer;
      int index = 0;
      for (; index < this->length_; index += step) {
        T acc = NIL;
        int end_index = std::min(index + step, this->length_);
        for (int i = end_index; i-- > index;) {
          acc = FUNC(raw_data[i], acc);
          begin_data[layer][i] = acc;
        }
        acc = NIL;
        end_index = std::min(index + step, this->length_);
        for (int i = index; i < end_index; ++i) {
          end_data[layer][i] = acc;
          acc = FUNC(acc, raw_data[i]);
        }
        if (end_index < index + step) {
          end_data[layer][end_index] = acc;
        }
      }
    }
  }

  T &operator[](int index) { return raw_data[index]; }

  T reduce(int beg, int end) {
    if (beg == end) {
      return NIL;
    }
    assert(beg < end);
    // find stand in [begin, end)
    int layer = 31 - clz(beg ^ end);
    T left = begin_data[layer][beg];
    T right = end_data[layer][end];
    return FUNC(left, right);
  }

private:
  vector<T> raw_data;
  vector<vector<T> /**/> begin_data;
  vector<vector<T> /**/> end_data;
  int layer_count;
  // int bsize_;
  int length_;
};
