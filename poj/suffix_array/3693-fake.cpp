#include "sa_is.h"
#include <stack>
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

Func::T Func::NIL = make_pair(make_pair(-1, -1), -1);
#include "../fenwick_tree/fenwick_template.h"

void workload(int case_num) {
  static vector<int> raw_str(100001);
  raw_str.clear();
  cin.getstring(raw_str);
  raw_str.push_back(127);
  if (raw_str[0] == '#') {
    exit(0);
  }
  int N = raw_str.size();
  vector<int> sa = suffix_array_construct_helper(raw_str, 128);
  vector<int> rank = get_rank(N, sa);
  vector<int> height = get_height(raw_str, sa, rank);

  // int location = 0;
  // int length = 0;
  // int multiple = 0;
  // for (int sa_i = 0; sa_i < N - 1; ++sa_i) {
  //   int h = height[sa_i];
  //   int delta = std::abs(sa[sa_i] - sa[sa_i + 1]);
  //   int new_mul = h / delta + 1;
  //   if (new_mul > multiple) {
  //     multiple = new_mul;
  //     length = h / delta * delta + delta;
  //     location = std::min(sa[sa_i], sa[sa_i + 1]);
  //   }
  // }
  Fenwick<Func::T, Func::NIL, Func::NIL, Func> tree(N);
  for(int i = 0; i < N; ++i){
    // tree.raw_update(i, );
  }
  std::stack<pair<int, int> /**/> record;
  ull sum = 0;
  int last_height = 0;
  for (size_t sa_i = 0; sa_i < N - 1; ++sa_i) {
    int cur_height = sa_i == N - 1 ? 0 : height[sa_i];
    int str_i = sa[sa_i];
    // cout << cur_height;
    if (cur_height >= last_height) {
      last_height = cur_height;
      record.push(make_pair(str_i, cur_height));
      // tree.update(str_i, Func::gen(str_i));
      // Data &ref = record[cur_height];
      // if (sa[sa_i] < a_size) {
      // ref.a_count++;
      // } else {
      // ref.b_count++;
      // }
    } else {
      Data leak;
      if (sa[sa_i] < a_size) {
        leak.a_count++;
      } else {
        leak.b_count++;
      }
      for (int h = last_height; h > cur_height; --h) {
        leak = leak + record[h];
        record[h] = Data();
        if (h >= K) {
          sum += leak.a_count * leak.b_count;
        }
      }
      last_height = cur_height;
      record[cur_height] = record[cur_height] + leak;
    }
  }
  cout << "Case " << case_num << ": ";
  int str_i = location;
  for (int i = str_i; i < str_i + length; ++i) {
    cout << (char)raw_str[i];
  }
  cout << endl;
}

int main() {
  cin.redirect("data.in");
  int case_num = 1;
  while (true) {
    workload(case_num++);
  }
}
