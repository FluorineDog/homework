#include "sa_is.h"

void workload() {
  vector<int> raw_str;
  cin.getstring(raw_str);
  if (raw_str[0] == '.') {
    exit(0);
  }
  vector<int> sa = suffix_array_construct_helper(raw_str, 128);
  int N = raw_str.size();
  int sa_i_0;
  for (sa_i_0 = 0; sa_i_0 < N; ++sa_i_0) {
    if (sa[sa_i_0] == 0)
      break;
  }
  if (sa_i_0 == 0 || N % sa[sa_i_0 - 1] != 0 ) {
    cout << 1 << endl;
    return;
  }
  for (int i = sa[sa_i_0 - 1], j = 0; i < N; ++i, ++j) {
    if (raw_str[i] != raw_str[j]) {
      cout << 1 << endl;
      return;
    }
  }
  cout << N / sa[sa_i_0 - 1] << endl;
  return;
}

int main() {
  cin.redirect("data.in");
  while (true) {
    workload();
  }
}
