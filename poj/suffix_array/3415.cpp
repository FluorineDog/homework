#define HEIGHT_ARRAY

// #define DOG_ENABLE_HEIGHT_TREE
#include "sa_is.h"
#include <iostream>
#include <stack>
#include <string>
struct Data {
  ull a_count;
  ull b_count;
  Data operator+(const Data &x) {
    return Data(a_count + x.a_count, b_count + x.b_count);
  }
  Data(ull a = 0, ull b = 0) : a_count(a), b_count(b) {}
};

void workload() {
  // std::string a, b;
  int K;
  std::cin >> K;
  if (K == 0) {
    exit(0);
  }
  // std::cin >> a >> b;
  static vector<char_t> raw_str(2 * 100000 + 2);
  raw_str.clear();
  // size_t total_size = a.size() + b.size() + 2;
  // raw_str.reserve(total_size);
  // for (size_t i = 0; i < a.size(); ++i) {
  // raw_str.push_back(a[i]);
  // }
  cin.getstring(raw_str);
  raw_str.push_back('#');
  int a_size = raw_str.size();
  cin.getstring(raw_str);
  raw_str.push_back('$');
  size_t total_size = raw_str.size();

  vector<int> sa = suffix_array_construct_helper(raw_str, 128);
  // Fenwick height(total_size);
  vector<int> rank = get_rank(total_size, sa);
  vector<int> height = get_height(raw_str, sa, rank);
  vector<Data> record(a_size);
  ull sum = 0;
  int last_height = 0;
  for (size_t sa_i = 0; sa_i < total_size; ++sa_i) {
    int cur_height = sa_i == total_size - 1 ? 0 : height[sa_i];
    // cout << cur_height;
    if (cur_height >= last_height) {
      last_height = cur_height;
      Data &ref = record[cur_height];
      if (sa[sa_i] < a_size) {
        ref.a_count++;
      } else {
        ref.b_count++;
      }
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
  // cout << endl;
  std::cout << sum << std::endl;
}
int main() {
  cin.redirect("data.in");
  while (true) {
    workload();
  }
}
