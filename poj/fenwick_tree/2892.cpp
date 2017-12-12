#include <algorithm>
// left_most destroyed, right_most destroyed
#include <limits>
int inf = std::numeric_limits<int>::max() / 4;
#define T pair<int, int>
#define INIT make_pair(inf, -inf)
#define NIL make_pair(inf, -inf)
#define FUNC(a, b) make_pair(std::min(a.first, b.first), std::max(a.second, b.second))
#include "fenwick.h"
#include <stack>
using std::stack;
int main() {
  int N, K;
  cin >> N, K;
  Fenwick village_record(20000 + 1);
  ll sum = 0;
  for (int i = 0; i < N; ++i) {
    pair<int, int> left_data = village_record.reduce(0, x);
    int left_count = left_data.first;
    int left_sum = left_data.second;
    sum += vol * (left_count * x - left_sum);

    pair<int, int> left_data = village_record.reduce(0, x);
    int right_count = right_data.first;
    int right_sum = right_data.second;
    sum += vol * (right_sum - right_count * x);

    x_record.update(x, make_pair(1, x));
	}
	cout << sum << endl;
}