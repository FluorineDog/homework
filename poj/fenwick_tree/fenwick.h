#include "../wheel.h"

#ifndef T
#define T int
#define FUNC(a, b) ((a) + (b))
// NIL should be identity of moniod
// to be honest, it doesn't matter...
#define NIL 0
#define INIT 1
#endif

class Fenwick {
public:
  Fenwick(int length) {
    int bsize = 1;

    for (bsize = 1; bsize < length; bsize <<= 1) {
    }
    this->length_ = length;
    this->bsize_ = bsize;
    data.reserve(bsize * 2);
    data.resize(bsize, NIL);
    data.resize(bsize + length, INIT);
    while (bsize >>= 1) {
      length >>= 1;
      for (int i = 0; i < length; ++i) {
        int base = bsize + i;
        data[base] = FUNC(data[2 * base], data[2 * base + 1]);
      }
    }
  }

  void update(int i, T value) {
    int bsize = this->bsize_;
    data[bsize + i] = value;
    while (bsize >>= 1) {
      i >>= 1;
      int base = bsize + i;
      data[base] = FUNC(data[2 * base], data[2 * base + 1]);
    }
  }

  const T &operator[](int index) { return data[this->bsize_ + index]; }

  T reduce(int beg, int end) const {
    int bsize = this->bsize_;
    if (beg == end) {
      return NIL;
    }
    T left_sum = data[bsize + beg];
    T right_sum = NIL;
    while (end - beg != 1) {
      if (!(beg & 1)) {
        left_sum = FUNC(left_sum, data[bsize + beg + 1]);
      }
      if (end & 1) {
        right_sum = FUNC(data[bsize + end - 1], right_sum);
      }
      beg >>= 1;
      end >>= 1;
      bsize >>= 1;
    }
    return FUNC(left_sum, right_sum);
  }

private:
  vector<T> data;
  int bsize_;
  int length_;
};
