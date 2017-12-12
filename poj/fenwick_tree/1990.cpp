#include <algorithm>
// x_count && x_sum
#define T pair<int, int>
#define INIT make_pair(0, 0)
#define NIL make_pair(0, 0)
#define FUNC(a, b) make_pair(a.first + b.first, a.second + b.second)
#include "fenwick.h"

int main() {
  int N;
  cin >> N;
  // vol, x
  vector<pair<int, int> > cow_table;
  cow_table.reserve(N);
  for (int i = 0; i < N; ++i) {
    int vol, x;
    cin >> vol >> x;
    cow_table.push_back(make_pair(vol, x));
  }
  std::sort(cow_table.begin(), cow_table.end());
  Fenwick x_record(20000 + 1);
  ll sum = 0;
  for (int i = 0; i < N; ++i) {
    ll vol = cow_table[i].first;
    int x = cow_table[i].second;
    pair<int, int> left_data = x_record.reduce(0, x);
    int left_count = left_data.first;
    int left_sum = left_data.second;
    sum += vol * (left_count * x - left_sum);

    pair<int, int> right_data = x_record.reduce(x+1, 20001);
    int right_count = right_data.first;
    int right_sum = right_data.second;
    sum += vol * (right_sum - right_count * x);

    x_record.update(x, make_pair(1, x));
	}
	cout << sum << endl;
}