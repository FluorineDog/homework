#ifndef DOG_FENWICK_TREE_H_
#define DOG_FENWICK_TREE_H_
#include "../wheel.h"

// NIL should be identity of moniod
#ifndef T
#define T int
#define FUNC(a, b) ((a) + (b))
#define NIL 0
#define INIT 0
#endif

class Fenwick {
public:
  Fenwick(int length) {
    int bsize = 1;

    for (bsize = 1; bsize < length; bsize <<= 1) {
    }
    data.reserve(bsize * 2);
    data.resize(bsize, NIL);
    data.resize(bsize + length, INIT);
    this->length_ = length;
    this->bsize_ = bsize;
    fast_init();
  }

  void fast_init(){
    int bsize = this->bsize_;
    int length = this->length_;
    while (bsize >>= 1) {
      length >>= 1;
      for (int i = 0; i < length; ++i) {
        int base = bsize + i;
        data[base] = FUNC(data[2 * base], data[2 * base + 1]);
      }
    }
  }

  void raw_update(int i, T value) {
    int bsize = this->bsize_;
    data[bsize + i] = value;
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

#undef T
#undef FUNC
#undef NIL 
#undef INIT

#endif