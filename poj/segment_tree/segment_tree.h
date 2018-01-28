#ifndef DOG_SEGMENT_TREE_H_
#define DOG_SEGMENT_TREE_H_
#include "../wheel.h"
#include <bitset>
using std::bitset;

// NIL should be identity of moniod
#ifndef NIL
typedef int T;
#define FUNC(a, b) ((a) + (b))
#define NIL 0
#define INIT 1
#endif

class SegmentTree {
public:
  SegmentTree(int length) {
    int bsize = 1;
    layers_ = 0;
    for (bsize = 1; bsize < length; bsize <<= 1) {
      ++layers_;
    }
    data.reserve(bsize * 2);
    data.resize(bsize, NIL);
    data.resize(bsize+ length, INIT);
    data.resize(bsize * 2 , NIL);
    dirty_flag.resize(bsize * 2, false);
    this->length_ = length;
    this->bsize_ = bsize;
    fast_init();
    // data[1] = INIT;
    // dirty_flag[1] = true;
  }

  void fast_init() {
    int bsize = this->bsize_;
    int length = this->length_;
    dirty_flag.clear();
    dirty_flag.resize(bsize_ * 2, false);
    while (bsize >>= 1) {
      length >>= 1;
      for (int i = 0; i < length; ++i) {
        int base = bsize + i;
        data[base] = FUNC(data[2 * base], data[2 * base + 1]);
      }
    }
  }
  void reach(int index) {
    for (int offset = layers_; offset > 1; offset--) {
      int i = index >> offset;
      int bsize = bsize_ >> offset;
      int k = bsize + i;
      if (dirty_flag[k]) {
        data[k * 2] = data[k];
        data[k * 2 + 1] = data[k];
        dirty_flag[k] = false;
        dirty_flag[k * 2] = true;
        dirty_flag[k * 2 + 1] = true;
      }
    }
  }
  void raw_update(int i, T value) {
    int bsize = this->bsize_;
    data[bsize + i] = value;
  }

  void update(int i, T value) {
    reach(i);
    int bsize = this->bsize_;
    data[bsize + i] = value;
    while (bsize >>= 1) {
      i >>= 1;
      int base = bsize + i;
      data[base] = FUNC(data[2 * base], data[2 * base + 1]);
    }
  }

  const T &operator[](int index) { return data[this->bsize_ + index]; }
  void range_update(int beg, int end, T value) {
    int bsize = this->bsize_;
    if (beg == end) {
      return;
    }
    reach(beg);
    --end;
    if (beg == end) {
      update(beg, value);
      return;
    }
    reach(end);
    data[bsize + beg] = value;
    data[bsize + end] = value;
    // T left_sum = data[bsize + beg];
    // T right_sum = data[bsize + end];

    while (end - beg != 1) {
      if (!(beg & 1)) {
        data[bsize + beg + 1] = value;
        dirty_flag[bsize + beg + 1] = true;
        // left_sum = FUNC(left_sum, data[bsize + beg + 1]);
      }
      if (end & 1) {
        data[bsize + end - 1] = value;
        dirty_flag[bsize + end - 1] = true;
        // right_sum = FUNC(data[bsize + end - 1], right_sum);
      }
      beg >>= 1;
      end >>= 1;
      bsize >>= 1;
      int base1 = bsize + beg;
      int base2 = bsize + end;
      data[base1] = FUNC(data[base1 * 2], data[base1 * 2 + 1]);
      data[base2] = FUNC(data[base2 * 2], data[base2 * 2 + 1]);
    }
    while (bsize >>= 1) {
      beg >>= 1;
      end >>= 1;
      int base = bsize + beg;
      data[base] = FUNC(data[2 * base], data[2 * base + 1]);
      base = bsize + end;
      data[base] = FUNC(data[2 * base], data[2 * base + 1]);
    }

    return; /// FUNC(left_sum, right_sum);
  }

  T reduce(int beg, int end) {
    int bsize = this->bsize_;
    if (beg == end) {
      return NIL;
    }
    --end;
    reach(beg);
    if (beg == end) {
      return data[bsize + beg];
    }
    reach(end);
    T left_sum = data[bsize + beg];
    T right_sum = data[bsize + end];
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
  void log() {
    for (int i = 0; i < bsize_ + length_; ++i) {
      cerr << i % 10 << " ";
    }
    cerr << endl;
    for (int i = 0; i < bsize_ + length_; ++i) {
      cerr << data[i] << " ";
    }
    cerr << endl;
    for (int i = 0; i < bsize_ + length_; ++i) {
      cerr << dirty_flag[i] << " ";
    }
    cerr << endl;
    cerr << endl;
  }

private:
  // data and operation locatio
  vector<T> data;
  vector<bool> dirty_flag;
  int bsize_;
  int layers_;
  int length_;
};
#endif