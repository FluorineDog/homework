#define HEIGHT_ARRAY

#define 
#include "sa_is.h"
#include <iostream>
#include <string>
int main() {
	std::string a, b;
	int K;
	std::cin >> K >> a >> b;
	vector<char_t> raw_str;
	raw_str.reserve(a.size() + b.size() + 2);
	for(size_t i = 0; i < a.size(); ++i){
		raw_str.push_back(a[i]);
	}
	raw_str.push_back('#');
	for(size_t i = 0; i < b.size(); ++i){
		raw_str.push_back(b[i]);
	}
	raw_str.push_back('$');
	vector<int> sa = suffix_array_construct_helper(raw_str, 128);
	Fenwick height(a.size() + b.size() + 2);
	height_helper(height,)
}