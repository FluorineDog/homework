#include <algorithm>
#undef min
#undef max
// #define T int
// #define NIL (1 << 29)
// #define INIT (1 << 29)
// #define FUNC(a, b) std::min(a, b)
// #include "../fenwick_tree/fenwick.h"
#define DOG_ENABLE_HEIGHT_ARRAY
#include "sa_is.h"
#include <map>


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
  vector<int> rank = get_rank(N, sa);

  // show_id(raw_str.size());
  // show(raw_str);
  // show(str_ids);
  // show(sa);
  // show(rank);
  height_helper(tree, raw_str, sa, rank);
  // map<int, int> known_strings;
  vector<int> known_strings(string_count);
  int known_id_count = 0;
  // range [sa_i - 1, sa_end)
  vector<int> max_sa_ids;
  int max_height = 0;

  int sa_end = 0;
  for (int sa_i = 0; sa_i < N;) {
    for (; sa_end < N && known_id_count < (string_count + 2) / 2; ++sa_end) {
      int s_index = sa[sa_end];
      int current_str_id = str_ids[s_index];
      int tmp = ++known_strings[current_str_id];
      if (tmp == 1) {
        ++known_id_count;
      }
    }
    if(known_id_count < (string_count + 2) / 2){
      break;
    }
    int height = tree.reduce(sa_i, sa_end - 1);
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
    if (sa_end >= N) {
      break;
    }
    {
      int s_index = sa[sa_i];
      int current_str_id = str_ids[s_index];
      int tmp = --known_strings[current_str_id];
      if (tmp == 0) {
        --known_id_count;
      }
      ++sa_i;
    }
  }
  if (max_height == 0) {
    cout << "?" << endl << endl;
    return;
  }
  for (int i = 0; i < (int)max_sa_ids.size(); ++i) {
    int beg = sa[max_sa_ids[i]];
    for (int k = 0; k < max_height; ++k) {
      cout << (char)(raw_str[beg + k] + 'a');
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  cin.redirect("data.in");
  while (true) {
    workload();
  }
}
