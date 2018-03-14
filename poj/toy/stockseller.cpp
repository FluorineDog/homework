#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <cassert>
using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;
using ll = std::pair<long long, int>;
using std::make_pair;

int main() {
	int N;
	priority_queue<ll, std::vector<ll>, std::greater<ll>> data;
	auto inf = std::numeric_limits<long long>::max() / 4;
	// cout << "s = " << s << endl;
	data.push(make_pair(inf, -1));
	data.push(make_pair(inf, -1));
	// cout << "s = " << data.top() << endl;
	std::cin >> N;
	long long sum = 0;
	std::vector<int> day(N, 0);
	for (int i = 0; i < N; ++i) {
		ll x;
		std::cin >> x.first;
		x.second = i;
		ll k = data.top();
		if (x > data.top()) {
			sum += (x.first - data.top().first);
			data.pop();
			data.push(x);
		}
		data.push(x);
	}
	int left = data.size() - 1;
	std::vector<long long> waster;
	while (data.top().first != inf) {
		auto p = data.top();
		data.pop();
		if(data.top() == p){
			data.pop();
		}
		else{
			waster.push_back(p.first);
		}
	}
	// for(auto x: waster){
	// 	cout << x << ' ';
	// }
	// cout << endl;
	assert(data.size() == 2);
	for(int i = 0; i < waster.size() / 2; ++i){
		sum += waster[i];
	}
	for(int i = waster.size() / 2; i < waster.size(); ++i){
		sum -= waster[i];
	}
	std::cout << sum << std::endl;
	return 0;
}
