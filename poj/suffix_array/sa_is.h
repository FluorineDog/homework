#include "../wheel.h"
#include <cstdint>
#include <iostream>
#include <string>

void show_f(vector<int> res, const char *str) {
  for (auto x : res) {
    // cout << x << " ";
    printf("%2d ", x);
  }
  cout << "--" << str << endl;
}

#define show(res) show_f(res, #res);
// $ is \0 for us
typedef int char_t;

inline void induction(int N, const vector<char_t> &raw_str,
                     const vector<int> &is_s_types,
                     const vector<int> &alphabet_offsets,
                     vector<int> &sa) {
  // section 2: sort LCM substrings

  auto bucket_begins = alphabet_offsets;
  auto bucket_ends = alphabet_offsets;
  {
    // overkill
    // since we kill $
    // do it
    int old_offset = N;
    char_t ch = raw_str[old_offset - 1];
    int index = bucket_begins[ch]++;
    sa[index] = old_offset - 1;
  }
  // show(sa);
  for (int i = 0; i < N; ++i) {
    int old_offset = sa[i];
    if (old_offset <= 0 || is_s_types[old_offset - 1]) {
      continue;
    }
    char_t ch = raw_str[old_offset - 1];
    int index = bucket_begins[ch]++;
    sa[index] = old_offset - 1;
  }
  // show(sa);
  bucket_ends = alphabet_offsets;
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
  show(raw_str);
  {
    vector<int> ids;
    for (int i = 0; i < N; ++i) {
      ids.push_back(i);
    }
    show(ids);
  }
  vector<bool> is_s_types(N);
  vector<int> alphabet_offsets(alphabet_size + 1, 0);
  // chapter 0: calculate s/l types
  // count the charactor;
  {
    char_t last_ch = '\0';
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
    if (alphabet_offsets[mode] > 1) {
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
    auto bucket_begins = alphabet_offsets;
    auto bucket_ends = alphabet_offsets;
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
    // show(sa);
    // section 2: sort LCM substrings
    {
      // overkill
      // since we kill $
      // do it
      int old_offset = N;
      char_t ch = raw_str[old_offset - 1];
      int index = bucket_begins[ch]++;
      sa[index] = old_offset - 1;
    }
    // show(sa);
    for (int i = 0; i < N; ++i) {
      int old_offset = sa[i];
      if (old_offset <= 0 || is_s_types[old_offset - 1]) {
        continue;
      }
      char_t ch = raw_str[old_offset - 1];
      int index = bucket_begins[ch]++;
      sa[index] = old_offset - 1;
    }
    // show(sa);
    bucket_ends = alphabet_offsets;
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
  if (mode == 1) {
    show(sas[0]);
    return sas[0];
  }

  // show(sas[0]);
  // show(sas[1]);

  // charter two: recursive sort
  // section 4: construct new string to do recursive work
  {

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
    cout << "------" << endl;
    show(new_str);
    show(mapping);
    vector<int> well_ordered = suffix_array_construct_helper(new_str, new_ch);
    cout << "****" << endl;
    show(well_ordered);
  }
  return {};
  // for (int i = 1; i < raw_str.size(); ++i) {
  //   }
  //   char_t ch = raw_str[i];
  // }

  // section 4
}

void suffix_array(const vector<int> &S) {}
