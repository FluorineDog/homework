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
constexpr auto INF = std::numeric_limits<int>::max() / 4;
using Data = std::pair<int, int>;
Data dog_sum(Data data1, Data data2) {
	auto[sum1, depth1] = data1;
	auto[sum2, depth2] = data2;
	int sum = sum1 + sum2;
	int depth = std::min(depth1, sum1 + depth2);
	return make_pair(sum, depth);
}

typedef Data T;
#define FUNC(a, b) dog_sum((a), (b))
#define NIL make_pair(0, 0)
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
	// cin.redirect("toy/stock/1.in");

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
	// vector<int> answer(N);
	// vector<int> acc(N);
	// {
	// 	auto[sum, dep] = dog_sum(make_pair(-2, -2), make_pair(0, -1));
	// 	cout << sum << "&&" << dep << "# " << endl;
	// }
	for (int index = N; index-- > 0;) {
		auto[value, select_i] = record[index];
		lookup.update(select_i, FILP);
		auto info = lookup.reduce(0, N);
		if (info.second < 0) {
			sum -= value;
			lookup.update(select_i, INIT);
			// answer[select_i] = value;
			// acc[select_i] = 1;
		} else {
			// answer[select_i] = value;
			// acc[select_i] = -1;
			sum += value;
		}
		info = lookup.reduce(0, N);
		// cout << info.first << "$ ";
	}
	cout << sum << endl;
	// int tmp = 0;
	// for(int i = 0; i < N; ++i){
	// 	cout << acc[i] << "*" << i << "  ";
	// }
	// for (int i = 0; i < N; ++i) {
	// 	tmp += acc[i];
	// 	acc[i] = tmp;
	// }
	// cout << endl;
	// int multi = 1;
	// for (int i = 172 + 256; i != 0; i >>= 1) {
	// 	{
	// 		int k = i ;
	// 		auto[sum, dep] = lookup[k - 256];
	// 		k -= 256 / multi;
	// 		auto true_min = *std::min_element(acc.begin() + multi * k,
	// 																		 acc.begin() + std::min(N, multi * (k + 1))) - (k?acc[multi*k-1]:0);
	// 		cout << sum << "(" << dep << ")[" << k << "]{" << true_min << "} ";
	// 	}

	// 	if(i != 1) {
	// 		int k = i^1 ;
	// 		auto[sum, dep] = lookup[k - 256];
	// 		k -= 256 / multi;
	// 		auto true_min = *std::min_element(acc.begin() + multi * k,
	// 																		 acc.begin() + std::min(multi * (k + 1), N)) - (k?acc[multi*k-1]:0);
	// 		cout << sum << "(" << dep << ")[" << k << "]{" << true_min << "} ";
	// 	}

	// 	multi *=2;
	// 	cout << "==>" << (i >> 1) << endl;
	// }
}

// (a1, a2)
// (b1, b2)
// (c1, c2)
// (a1 + b1 + b1, std::min(a1+b2, a2), a1+b1+c2)

// (a1, a2)
// (b1, b2)
// (c1, c2)
// (a1 + b1 + c1, a2 , a1 + std::min(b1 + c2, b2))