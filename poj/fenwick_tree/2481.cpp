#include <algorithm>
// x_count && x_sum
#define T int
#define INIT 0
#define NIL 0
#define FUNC(a, b) (a + b)
#include "fenwick.h"

const int RANGE = 100000+1;
void truck(){	
	int N;
	cin >> N;
	if(N == 0){
		exit(0);
	}
	vector<pair<int, pair<int, int> > > raw_data;
	raw_data.reserve(N);
	for(int i = 0; i < N; ++i){
		int beg, end;
		cin >> beg >> end;	
		raw_data.push_back(make_pair(beg, make_pair(end, i)));
	}
	std::sort(raw_data.begin(), raw_data.end());
	int last_beg = -1;
	int last_end = -1;
	int last_result = 0;
	Fenwick	table(RANGE);
	vector<int> results(N);
	for(int i = 0; i < N; ++i){
		int beg = raw_data[i].first;
		int end = raw_data[i].second.first;
		int index = raw_data[i].second.second;
		if(beg == last_beg && end == last_end){
			results[index] = last_result;
			table.update(end, table[end] + 1);
			continue;
		}
		last_beg = beg;
		last_end = end;
		last_result = table.reduce(end + 1, RANGE);
		results[index] = last_result;
		table.update(end, table[end] + 1);
	}
	for(int i = 0; i < N; ++i){
		cout << results[i] << " ";
	}
	cout << endl;
}

int main(){
	cin.redirect("data.in");
	while(true){
		truck();
	}
}