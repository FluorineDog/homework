#include "../wheel.h"
#include <cstdint>
#include <iostream>
void show(vector<int> res) {
  for (auto x : res) {
    // cout << x << " ";
    printf("%2d ", x);
  }
  cout << endl;
}
// $ is \0 for us
typedef int char_t;
vector<int> suffix_array_construct_helper(const vector<char_t> &raw_str,
                                          int alphabet_size) {

  const int N = raw_str.size();
  vector<bool> is_s_types(N);
  vector<int> alphabet_offsets(alphabet_size + 1, 0);
  // section 0: calculate s/l types
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
  sas[0].resize(N, -1);
  sas[1].resize(N, -1);
  // charter one: contruct pesudo-sorted suffix
  for (int instance = 0; instance < 2; ++instance) {
    vector<int> &sa = sas[instance];
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
        // insert them to bucket unordered
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
  show(sas[0]);
  show(sas[1]);
  show(raw_str);
  {
    vector<int> ids;
    for (int i = 0; i < N; ++i) {
      ids.push_back(i);
    }
    show(ids);
  }
  return sas[0];
  // // charter two: recursive sort
  // // section 4: construct new string
  // for (int i = 1; i < raw_str.size(); ++i) {
  //   if (!(is_s_types[i] && !is_s_types[i - 1])) {
  //     continue;
  //   }
  //   char_t ch = raw_str[i];
  // }

  // section 4
}

void suffix_array(const vector<int> &S) {}
