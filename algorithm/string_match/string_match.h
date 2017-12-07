#ifndef STRING_MATCH_H_
#define STRING_MATCH_H_

#include <algorithm>
#include <map>
#include <tuple>
#include <vector>
using std::tuple;
using std::vector;
using std::get;
using std::map;

using dog_string = vector<uint32_t>;
using T = long long;
T string_match(dog_string s1, dog_string s2, const vector<vector<uint32_t>>& alpha, const vector<uint32_t>& delta);
T string_match_dp(dog_string s1, dog_string s2, const vector<vector<uint32_t>>& alpha, const vector<uint32_t>& delta);
T string_match_st(dog_string s1, dog_string s2, const vector<vector<uint32_t>>& alpha, const vector<uint32_t>& delta);
constexpr T inf = std::numeric_limits<T>::max()/8;

#endif