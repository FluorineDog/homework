#include <algorithm>
#undef min
#undef max
#define T int
#define NIL (1 << 29)
#define INIT (1 << 29)
#define FUNC(a, b) std::min(a, b)
#include "../fenwick_tree/fenwick.h"
#include "sa_is.h"
#include <map>

void height_helper(Fenwick &tree, const vector<char_t> &raw_str,
                   const vector<int> &sa, const vector<int> &rank) {
  // height[i] = h[SA[i]] = LCS(SA[i], SA[i-1]);
  int N = raw_str.size();
  // s_i => sa_i
  int height = 0;
  for (int s_i = 0; s_i < N; ++s_i) {
    int sa_i = rank[s_i];
    int last_sa_i = sa_i - 1;
    if (sa_i > 0) {
      int last_s_i = sa[last_sa_i];
      int offset = 0;
      while (true) {
        char_t left = raw_str[s_i + offset];
        char_t right = raw_str[last_s_i + offset];
        if (left != right) {
          break;
        }
        ++height;
      }
    }
    tree.raw_update(sa_i, height);
    if (height) {
      --height;
    }
  }
  tree.fast_init();
}

void workload() {
  int string_count;
  cin >> string_count;

  // char buffer[1001];
  vector<int> raw_str;
  raw_str.reserve(1001 * 100);
  char_t seperator = 27;
  vector<int> str_ids;
  // s_index => string_id
  str_ids.reserve(1001 * 100);
  bool flag_first = true;
  for (int i = 0; i < string_count; ++i) {
    while (true) {
      char ch = getchar();
      if (!ch || ch == '\n') {
        if (!flag_first) {
          break;
        }
        flag_first = false;
      }
      raw_str.push_back(ch - 'a');
      str_ids.push_back(i);
    }
    raw_str.push_back(seperator++);
    str_ids.push_back(i);
  }
  vector<int> sa = suffix_array_construct_helper(raw_str, seperator);
  int N = raw_str.size();
  Fenwick tree(N);
  vector<int> rank(N);
  for (int i = 0; i < N; ++i) {
    rank[sa[i]] = i;
  }
  height_helper(tree, raw_str, sa, rank);
  // map<int, int> known_strings;
  vector<int> known_strings(100);
  int known_id_count = 0;
  // range [sa_i - 1, sa_end)
  int sa_end = 1;
  vector<int> max_s_ids;
  int max_height;
  for (int sa_i = 1; sa_i < N;) {
    while (known_id_count < (N + 1) / 2) {
      int s_index = sa[sa_end];
      int current_str_id = str_ids[s_index];
      int tmp = ++known_strings[current_str_id];
      if (tmp == 1) {
        ++known_id_count;
      }
      ++sa_end;
    }
    int height = tree.reduce(sa_i, sa_end);
    if (max_height <= height) {
      if (max_height < height) {
        max_s_ids.clear();
        max_height = height;
      }
      // guarantee to be not the same
      if (tree.reduce(max_s_ids.back(), sa_i) < height) {
        max_s_ids.push_back(sa[sa_i]);
      }
    }

    if (sa_end >= N) {
      break;
    }
  }
  if (max_height == 0) {
    cout << "?" << endl;
    return;
  }
  for (int i = 0; i < (int)max_s_ids.size(); ++i) {
    int beg = max_s_ids[i]; 
    for(int k = 0; k < max_height; ++k){
      cout << raw_str[beg + k];      
    }
    cout << endl;
  }
}

int main() {
  cin.redirect("data.in");
  while (true) {
    workload();
  }
}
