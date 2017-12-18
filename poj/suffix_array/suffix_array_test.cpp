
#include <gtest/gtest.h>

#include "sa_is.h"

#include <string>
using std::string;
using std::vector;
TEST(suffix_array, test1){
	string s = "12345432123454321234543212345432123454321";
	vector<int> fuck;
	for(auto ch:s){
		fuck.push_back(ch - '1');
	}
	auto res = suffix_array_construct_helper(fuck, 6);
	for(auto x:res){
		cout << x << " ";
	}
	cout << endl;
}