#ifndef DOG_SA_IS_H_
#define DOG_SA_IS_H_
#include "../wheel.h"
#include <stdint.h>
#include <string>

typedef int char_t;
// void checker(const vector<char_t> &raw_str, const vector<int> &sa) {
//   for (int i = 0; i < (int)raw_str.size() - 1; ++i) {
//     int s_i = sa[i] - 1;
//     int s_i_next = sa[i + 1] - 1;
//     while (raw_str[++s_i] == raw_str[++s_i_next])
//       ;
//     if (raw_str[s_i] > raw_str[s_i_next]) {
//       cout << "fuck" << endl;
//     };
//   }
// }
inline vector<int> get_rank(int N, const vector<int> sa) {
  vector<int> rank(N);
  for (int i = 0; i < N; ++i) {
    rank[sa[i]] = i;
  }
  return rank;
}

#ifdef DOG_ENABLE_HEIGHT_TREE
#define T int
#define NIL (1 << 29)
#define INIT (1 << 29)
#define FUNC(a, b) std::min(a, b)
#include "../fenwick_tree/fenwick.h"

void height_helper(Fenwick &tree, const vector<char_t> &raw_str,
                   const vector<int> &sa, const vector<int> &rank) {
  // height[i] = h[SA[i]] = LCS(SA[i], SA[i-1]);
  int N = raw_str.size();
  // s_i => sa_i
  int height = 0;
  for (int s_i = 0; s_i < N; ++s_i) {
    int sa_i = rank[s_i];
    if (sa_i > 0) {
      int last_sa_i = sa_i - 1;
      int last_s_i = sa[last_sa_i];
      while (true) {
        char_t left = raw_str[s_i + height];
        char_t right = raw_str[last_s_i + height];
        if (left != right) {
          break;
        }
        ++height;
      }
      tree.raw_update(last_sa_i, height);
    }
    if (height) {
      --height;
    }
  }
  tree.fast_init();
}
#else
vector<int> get_height(const vector<char_t> &raw_str, const vector<int> &sa,
                       const vector<int> &rank) {
  // height[i] = h[SA[i]] = LCS(SA[i], SA[i-1]);
  int N = raw_str.size();
  vector<int> result(N - 1);
  // s_i => sa_i
  int height = 0;
  for (int s_i = 0; s_i < N; ++s_i) {
    int sa_i = rank[s_i];
    if (sa_i > 0) {
      int last_sa_i = sa_i - 1;
      int last_s_i = sa[last_sa_i];
      while (true) {
        char_t left = raw_str[s_i + height];
        char_t right = raw_str[last_s_i + height];
        if (left != right) {
          break;
        }
        ++height;
      }
      result[last_sa_i] = height;
    }
    if (height) {
      --height;
    }
  }
  return result;
}
#endif

inline void induction(int N, const vector<char_t> &raw_str,
                      const vector<bool> &is_s_types,
                      const vector<int> &alphabet_offsets, vector<int> &sa) {
  // section 2: sort LCM substrings
  vector<int> bucket_begins = alphabet_offsets;
  {
    // overkill
    // since we kill $
    // do it
    int old_offset = N;
    char_t ch = raw_str[old_offset - 1];
    int index = bucket_begins[ch]++;
    sa[index] = old_offset - 1;
  }
  for (int i = 0; i < N; ++i) {
    int old_offset = sa[i];
    if (old_offset <= 0 || is_s_types[old_offset - 1]) {
      continue;
    }
    char_t ch = raw_str[old_offset - 1];
    int index = bucket_begins[ch]++;
    sa[index] = old_offset - 1;
  }
  vector<int> bucket_ends = alphabet_offsets;
  for (int i = N; i-- > 0;) {
    int old_offset = sa[i];
    if (old_offset <= 0 || !is_s_types[old_offset - 1]) {
      continue;
    }
    char_t ch = raw_str[old_offset - 1];
    int index = --bucket_ends[ch + 1];
    sa[index] = old_offset - 1;
  }
}

vector<int> suffix_array_construct_helper(const vector<char_t> &raw_str,
                                          int alphabet_size) {
  const int N = raw_str.size();
  if (N == 0) {
    return vector<int>();
  }
  vector<bool> is_s_types(N);
  vector<int> alphabet_offsets(alphabet_size + 1, 0);
  // chapter 0: calculate s/l types
  // count the charactor;
  {
    char_t last_ch = 0;
    bool last_s_type = false;
    for (int i = N; i-- > 0;) {
      char_t current_ch = raw_str[i];
      alphabet_offsets[current_ch]++;
      if (current_ch != last_ch) {
        last_s_type = current_ch < last_ch;
      }

      is_s_types[i] = last_s_type;
      last_ch = current_ch;
    }
    // sum up to get result
    int sum = 0;
    for (int i = 0; i < alphabet_size; ++i) {
      int k = alphabet_offsets[i];
      alphabet_offsets[i] = sum;
      sum += k;
    }
    alphabet_offsets[alphabet_size] = sum;
  }

  vector<int> sas[2];
  // mode 1 is the last step
  // mode 2 has recursize work to do
  int mode = 1;
  for (int i = 0; i < alphabet_size; ++i) {
    if (alphabet_offsets[i + 1] - alphabet_offsets[i] > 1) {
      mode = 2;
      break;
    }
  }
  // charter one: contruct pesudo-sorted suffix
  for (int instance = 0; instance < mode; ++instance) {
    vector<int> &sa = sas[instance];
    sa.resize(N + 1, -1);
    // section 1: find LCM charactor
    // ch => begin
    vector<int> bucket_begins = alphabet_offsets;
    vector<int> bucket_ends = alphabet_offsets;
    // ch => end, +1 for copy_free
    // find LCM character
    if (instance == 0) {
      for (int i = 1; i < (int)raw_str.size(); ++i) {
        // insert them to bucket unordered
        if (!(is_s_types[i] && !is_s_types[i - 1])) {
          continue;
        }
        char_t ch = raw_str[i];
        int offset = --bucket_ends[ch + 1];
        sa[offset] = i;
      }
    } else {
      for (int i = (int)raw_str.size(); i-- > 1;) {
        // insert them to bucket unordered, assuming inverse order
        if (!(is_s_types[i] && !is_s_types[i - 1])) {
          continue;
        }
        char_t ch = raw_str[i];
        int offset = --bucket_ends[ch + 1];
        sa[offset] = i;
      }
    }
    induction(N, raw_str, is_s_types, alphabet_offsets, sa);
  }
  if (mode == 1) {
    return sas[0];
  }

  // show(sas[0]);
  // show(sas[1]);

  // charter two: recursive sort
  {
    // section 4: construct new string to do recursive work
    vector<char_t> new_str(N, -1);
    char_t new_ch = 0;
    // use flag to make new_ch compact
    bool flag = false;
    int end_cond = sas[1][0];
    for (int i = 0; i < N; ++i) {
      int s_index = sas[0][i];
      if (s_index > 0 && is_s_types[s_index] && !is_s_types[s_index - 1]) {
        // LMS character
        new_str[s_index] = new_ch;
        // new_str.push_back(new_ch);
        flag = true;
      }
      if (s_index == end_cond) {
        if (flag)
          new_ch++;
        flag = false;
        end_cond = sas[1][i + 1];
      }
    }
    // new_str_index => old_str_index
    vector<int> mapping;
    int length = 0;
    for (int index = 0; index != N; ++index) {
      if (new_str[index] != -1) {
        new_str[length++] = new_str[index];
        mapping.push_back(index);
      }
    }
    new_str.resize(length);
    vector<int> well_ordered = suffix_array_construct_helper(new_str, new_ch);
    // section 5: do the final sort
    vector<int> bucket_ends = alphabet_offsets;
    vector<int> &sa = sas[0];
    sa.clear();
    sa.resize(N + 1, -1);
    for (int new_i = length; new_i-- > 0;) {
      int i = mapping[well_ordered[new_i]];
      char_t ch = raw_str[i];
      int offset = --bucket_ends[ch + 1];
      sa[offset] = i;
    }
    induction(N, raw_str, is_s_types, alphabet_offsets, sa);
    return sa;
  }
}

// void show_f(vector<int> res, const char *str) {
//   for (int i = 0; i < (int)res.size(); ++i) {
//     // cout << res[i] << " ";
//     printf("%2d ", res[i]);
//     if (i % 32 == 31) {
//       cout << "**" << i / 32 << endl;
//     }
//   }
//   cout << "--" << str << endl;
// }

// #define show(res) show_f(res, #res);

// void show_id(int n) {
//   vector<int> id_autogen;
//   for (int i = 0; i < n; ++i) {
//     id_autogen.push_back(i);
//   }
//   show(id_autogen);
// }

#endif