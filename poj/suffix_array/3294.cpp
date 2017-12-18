#include "sa_is.h"
#include <map>
#include "../fenwick_tree/fenwick.h"

void workload() {
  int N;
  cin >> N;
  char buffer[1001];
  vector<int> raw_str;
  raw_str.reserve(1001 * 100);
	char_t seperator = 27;
	map<int, int> string_ids;
  for (int i = 0; i < N; ++i) {
		string_ids[raw_str.size()] = i;	
    while (true) {
      char ch = getchar();
			if(!ch || ch == '\n'){
				break;
			}
			raw_str.push_back(ch - 'a');
    }
		raw_str.push_back(seperator++);
  }
	vector<int> sa = suffix_array_construct_helper(raw_str, seperator);	
	for(int beg = 0; beg < raw_str.size(); ++beg){
		int beg_index = sa[beg];	
		string_ids.lower_bound(beg_index);
	}
}

int main() {
  while (true) {
    workload();
  }
}