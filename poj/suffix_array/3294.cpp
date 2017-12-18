#include <algorithm>
#define private public
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
        ++offset;
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
  if (string_count <= 0) {
    exit(0);
  }

  char buffer[1001];
  vector<int> raw_str;
  raw_str.reserve(1001 * 100);
  char_t seperator = 27;
  vector<int> str_ids;
  // s_index => string_id
  str_ids.reserve(1001 * 100);
  for (int i = 0; i < string_count; ++i) {
    cin >> buffer;
    for (char *ptr = buffer; *ptr; ptr++) {
      raw_str.push_back(*ptr - 'a');
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

  show_id(raw_str.size());
  show(raw_str);
  show(sa);
  show(rank);
  height_helper(tree, raw_str, sa, rank);
  // map<int, int> known_strings;
  vector<int> known_strings(string_count);
  int known_id_count = 0;
  // range [sa_i - 1, sa_end)
  int sa_end = 1;
  vector<int> max_sa_ids;
  int max_height = -1;
  {
    int current_str_id = str_ids[sa[0]];
    known_strings[current_str_id]++;
    known_id_count++;
  }
  for (int sa_i = 0; sa_i < N;) {
    while (sa_end < N && known_id_count < (string_count + 1) / 2) {
      int s_index = sa[sa_end];
      int current_str_id = str_ids[s_index];
      int tmp = ++known_strings[current_str_id];
      if (tmp == 1) {
        ++known_id_count;
      }
      ++sa_end;
    }

    if (sa_end >= N) {
      break;
    }

    int height = tree.reduce(sa_i, sa_end);
    if (max_height <= height) {
      if (max_height < height) {
        max_sa_ids.clear();
        max_height = height;
      }
      // guarantee to be not the same
      if (max_sa_ids.empty() || tree.reduce(max_sa_ids.back(), sa_i) < height) {
        max_sa_ids.push_back(sa_i);
      }
    }
    {
      int s_index = sa[sa_i + 1];
      int current_str_id = str_ids[s_index];
      int tmp = --known_strings[current_str_id];
      if (tmp == 0) {
        --known_id_count;
      }
      ++sa_i;
    }
  }
  if (max_height == 0) {
    cout << "?" << endl;
    return;
  }
  for (int i = 0; i < (int)max_sa_ids.size(); ++i) {
    int beg = sa[max_sa_ids[i]];
    for (int k = 0; k < max_height; ++k) {
      cout << raw_str[beg + k] + 'a';
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
