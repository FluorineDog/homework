#ifndef DOG_FENWICK_TREE_TEMPLATE_H_
#define DOG_FENWICK_TREE_TEMPLATE_H_
#include "../wheel.h"

struct Func {
  // closest functor
  typedef pair<pair<int, int>, int> T;
  T operator()(T a, T b) {
    if (a.second == 0) {
      return b;
    } else if (b.second == -1) {
      return a;
    }
    int min = b.first.first - a.first.second;
    min = std::min(min, a.second);
    min = std::min(min, b.second);
    return make_pair(make_pair(a.first.first, b.first.second), min);
  }
  static T NIL;
  static T gen(int loc) {
    return make_pair(make_pair(loc, loc), INT32_MAX / 4);
  }
};

// NIL should be identity of moniod
template<typename T, T NIL, T INIT, typename FUNC>
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
        data[base] = FUNC()(data[2 * base], data[2 * base + 1]);
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

#endif