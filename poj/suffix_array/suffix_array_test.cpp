
#include <gtest/gtest.h>

#include "sa_is.h"

#include <string>
using std::string;
using std::vector;

void show_f(vector<int> res, const char *str) {
  // for (auto x : res) {
    // cout << x << " ";
    // printf("%2d ", x);
  // }
  // cout << "--" << str << endl;
}

#define show(res) show_f(res, #res);
TEST(suffix_array, test1) {
  string s = "1234543212346432123474321234543216345432";
  // string s = "23145";
  vector<int> fuck;
  // for (auto ch : s) {
    // fuck.push_back(ch - '1');
  // }
  // auto final = suffix_array_construct_helper(fuck, 26);

  // for(auto x:res){
  // cout << x << " ";
  // }
  // show(fuck);
  {
    vector<int> ids;
    for (int i = 0; i < (int)fuck.size(); ++i) {
      ids.push_back(i);
    }
    show(ids);
  }
  // show(final);
}
