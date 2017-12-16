#include <algorithm>
#include <iostream>
// x_count && x_sum
#define T int
#define INIT 0
#define NIL 0
#define FUNC(a, b) (a + b)
#include "fenwick.h"

vector<pair<int, pair<int, int> > > raw_data;
const int RANGE = 100000 + 1;
vector<int> results;
bool truck() {
	int N;
	// cin >> N;
  scanf("%d", &N);
  if (N == 0) {
    return false;
  }
  raw_data.resize(N);
  for (int i = 0; i < N; ++i) {
    int beg, end;
		// cin >> beg >> end;
    scanf("%d%d", &beg, &end);
    raw_data[i] = make_pair(beg, make_pair(-end, i));
  }
  std::sort(raw_data.begin(), raw_data.end());
  int last_beg = -1;
  int last_end = -1;
  int last_result = 0;
  Fenwick table(RANGE);
  results.resize(N);
  for (int i = 0; i < N; ++i) {
    int beg = raw_data[i].first;
    int end = -raw_data[i].second.first;
    int index = raw_data[i].second.second;
    if (end == last_end && beg == last_beg) {
    	table.update(end, table[end] + 1);
      results[index] = last_result;
      continue;
    }
    last_beg = beg;
    last_end = end;
    last_result = table.reduce(end, RANGE);
   	table.update(end, table[end] + 1);
    results[index] = last_result;
  }
  for (int i = 0; i < N; ++i) {
    // cout << results[i] << " ";
    printf("%d ", results[i]);
  }
  printf("\n");
  return true;
}

int main() {
  raw_data.reserve(RANGE);
  std::ios::sync_with_stdio(false);
  cin.redirect("data.in");
  while (truck()) {
  }
}