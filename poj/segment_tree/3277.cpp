#define HIGH_IO_PERFORMANCE
#include "../wheel.h"
#include <queue>
int main() {
  cin.redirect("data.in");
  int N;
  cin >> N;
  // height, case, int
  typedef std::pair<int, int> T;
  vector<pair<int, T> /**/> data;
	data.reserve(N * 2);
  for (int i = 0; i < N; ++i) {
    int beg, end, height;
    cin >> beg >> end >> height;
    if (beg == end) {
      continue;
    }
    data.push_back(make_pair(beg, make_pair(height, -1)));
    data.push_back(make_pair(end, make_pair(height, 1)));
  }
  std::sort(data.begin(), data.end());
  std::priority_queue<T, std::vector<T>, std::less<T> /**/> buildings;
  buildings.push(make_pair(0, -1));
	int current_beg = -1;
	ull sum_area = 0;
  for (int i = 0; i < (int)data.size(); ++i) {
		pair<int, T> instance = data[i];
		sum_area += (ull)(instance.first - current_beg) * (ull)buildings.top().first;
		current_beg = instance.first;
		buildings.push(instance.second);
    int record = 0;
    while (record != 0 || buildings.top().second == 1) {
      record += buildings.top().second;
      buildings.pop();
    }
  }
	cout << sum_area << endl;
  return 0;
}