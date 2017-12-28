#define DOG_ENABLE_HEIGHT_TREE
#include "sa_is.h"
#include <cassert>
#include <stack>
using std::swap;
struct Height_reduce {
  Height_reduce(const Fenwick &height, const vector<int> &rank):ref_height(height), ref_rank(rank) {}
  const Fenwick &ref_height;
  const vector<int> &ref_rank;
  int operator()(int str_a, int str_b) {
    int sa = ref_rank[str_a];
    int sb = ref_rank[str_b];
    if (sa > sb)
      swap(sa, sb);
    return ref_height.reduce(sa, sb);
  }
};

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
  Fenwick height(N - 1);
  height_helper(height, raw_str, sa, rank);
  Height_reduce height_reduce(height, rank);
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

  // search all L
  // common multiple
  int max_multiple = 1;
  vector<pair<int, int> /**/> record;
  record.reserve(N / 2);

  for (int L = 1; L <= N / 2; ++L) {
    for (int str_i = 0; str_i < N - L;) {
      int hi = height_reduce(str_i, str_i + L);
      int remains = L - hi % L;
      int multiple = hi / L;
      if (str_i > remains && remains != L) {
        int try_i = str_i - remains;
        int try_hi = height_reduce(try_i, try_i + L);
        if (try_hi >= hi + remains) {
          str_i = str_i - remains;
          hi = try_hi;
          ++multiple;
          assert(multiple == hi / L);
        } else {
          str_i = str_i + L - remains;
        }
      } else {
        str_i = str_i + L - remains;
      }

      if (multiple >= max_multiple) {
        if (multiple > max_multiple) {
          record.clear();
        }
        int next_i = str_i + L * multiple + L;
        do {
          record.push_back(make_pair(str_i, L));
        } while (str_i-- > 0 &&
                 height_reduce(str_i, str_i + L) >= multiple * L);
        str_i = next_i;

      } else {
        str_i += hi + L; // you have to consider
      }
    }
  }
  for (size_t i = 0; i < record.size(); ++i) {
    cout << "(" << record[i].first << ", " << record[i].second << ") ";
  }
  // ull sum = 0;
  // int last_height = 0;
  cout << endl;
}

int main() {
  cin.redirect("data.in");
  int case_num = 1;
  while (true) {
    workload(case_num++);
  }
}
