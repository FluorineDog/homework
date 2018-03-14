// #include "../wheel.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using std::make_pair;
using std::priority_queue;
using std::vector;
// NIL should be identity of moniod
// sum, max_depth
constexpr auto inf = std::numeric_limits<int>::max() / 4;
using Data = std::pair<int, int>;
Data dog_sum(Data data1, Data data2) {
	if(data1.second == inf){
		return data2;
	}
	else if(data2.second == inf){
		return data1;
	}
	auto[sum1, depth1] = data1;
	auto[sum2, depth2] = data2;
	int sum = sum1 + sum2;
	int depth = std::min(depth1, depth2 + sum1);
	return make_pair(sum, depth);
}

typedef Data T;
#define FUNC(a, b) dog_sum((a), (b))
#define NIL make_pair(0, inf)
#define INIT make_pair(1, 1)
#define FILP make_pair(-1, -1)
using ll = long long;

#include "../fenwick_tree/fenwick.h"
// using std::cout;
// using std::endl;

int main() {
	//
	// Fenwick_tree
	int N;
	cin >> N;
	Fenwick lookup(N);
	vector<std::pair<ll, int>> record;
	lookup.fast_init();
	for (int i = 0; i < N; ++i) {
		ll x;
		cin >> x;
		record.push_back(make_pair(x, i));
	}
	ll sum = 0;
	std::sort(record.begin(), record.end());
	vector<int> answer(N);
	vector<int> acc(N);
	{
		auto info = lookup.reduce(0, N);
		cout << info.first << "# ";
	}
	for (int index = N; --index > 0;) {
		auto[value, select_i] = record[index];
		lookup.update(select_i, FILP);
		auto info = lookup.reduce(0, N);
		if (info.second < 0) {
			sum -= value;
			lookup.update(select_i, INIT);
			answer[select_i] = value;
			acc[select_i] = 1;
		} else {
			answer[select_i] = value;
			acc[select_i] = -1;
			sum += value;
		}
		info = lookup.reduce(0, N);
		cout << info.first << "$ ";
	}
	int tmp = 0;
	for(int i = 0; i < N; ++i){
		tmp += acc[i];
		acc[i] = tmp;
	}
	for(int i = 0; i < N; ++i){
		cout << answer[i] << "(" << acc[i] << ") ";
	}
	cout << sum << endl;
}
