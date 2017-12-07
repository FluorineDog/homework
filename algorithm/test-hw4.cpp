#include <chrono>
#include <cstdio>
#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "matrix_chain/matrix_chain.h"
TEST(matrix_chain, test_small) {
  EXPECT_EQ(27, matrix_chain({3, 3, 3}));
  EXPECT_EQ(27 * 2, matrix_chain({3, 3, 3, 3}));
  EXPECT_EQ(9 * 2, matrix_chain({3, 1, 3, 3}));
  EXPECT_EQ(9 * 2, matrix_chain({3, 3, 1, 3}));
}
using std::cerr;
using std::cout;
using std::endl;

#include "string_match/string_match.h"
#include <fstream>
using namespace std;
TEST(matrix_chain, test2) {
  ios_base::sync_with_stdio(false);
  // timing
  std::ifstream fin("string_match/data/p1-in-big.txt");
  std::ifstream fin_std("string_match/data/p1-out-big.txt");
  using namespace chrono;
  high_resolution_clock::duration tot{};
  // capable of accepting multiple sets of input
  size_t nmat;
  while (fin >> nmat) {
    vector<long long> mats(nmat + 1);
    fin >> mats[0] >> mats[1];
    for (int i = 1; i < nmat; ++i) {
      long long dis;
      fin >> dis;
      fin >> mats[i + 1];
    }
    auto sta = high_resolution_clock::now();
    auto ans = matrix_chain(std::move(mats));
    auto fin = high_resolution_clock::now();

    long long standard;
    fin_std >> standard;
    EXPECT_EQ(standard, ans);
    tot += fin - sta;
  }
  cerr << "total time: ";
  cerr << duration_cast<microseconds>(tot).count() << " us" << endl;
}

TEST(string_match, test_small) {
  std::ifstream fin("string_match/data/p2-in.txt");
  std::ifstream fin_std("string_match/data/p2-out.txt");
  std::ios_base::sync_with_stdio(false);
  // timing
  using namespace std::chrono;
  high_resolution_clock::duration tot{};
  // capable of accepting multiple sets of input
  size_t nchset;
  while (fin >> nchset) {
    vector<uint32_t> delta(nchset);
    vector<vector<uint32_t>> alpha(nchset, vector<uint32_t>(nchset));
    for (uint32_t i = 0; i < nchset; ++i)
      fin >> delta[i];
    for (uint32_t i = 0; i < nchset; ++i)
      for (uint32_t j = 0; j < nchset; ++j)
        fin >> alpha[i][j];
    size_t ns1, ns2;
    fin >> ns1;
    vector<uint32_t> s1(ns1);
    for (uint32_t i = 0; i < ns1; ++i)
      fin >> s1[i];
    fin >> ns2;
    vector<uint32_t> s2(ns2);
    for (uint32_t i = 0; i < ns2; ++i)
      fin >> s2[i];
    auto ans = string_match_st(s1, s2, alpha, delta);
    auto ans2 = string_match_dp(s1, s2, alpha, delta);
    // cout << "minimum penalties: " << ans << endl << endl;
    T standard;
    fin_std >> standard;
    EXPECT_EQ(standard, ans);
    EXPECT_EQ(standard, ans2);
  }
  cerr << "total time: ";
  cerr << duration_cast<microseconds>(tot).count() << " us" << endl;
  // string_match_dp()
}

TEST(string_match, test_dp2) {
  std::ifstream fin("string_match/data/p2-in-huge.txt");
  std::ifstream fin_std("string_match/data/p2-out-huge.txt");
  std::ios_base::sync_with_stdio(false);
  // timing
  using namespace std::chrono;
  high_resolution_clock::duration tot{};
  // capable of accepting multiple sets of input
  size_t nchset;
  while (fin >> nchset) {
    vector<uint32_t> delta(nchset);
    vector<vector<uint32_t>> alpha(nchset, vector<uint32_t>(nchset));
    for (uint32_t i = 0; i < nchset; ++i)
      fin >> delta[i];
    for (uint32_t i = 0; i < nchset; ++i)
      for (uint32_t j = 0; j < nchset; ++j)
        fin >> alpha[i][j];
    size_t ns1, ns2;
    fin >> ns1;
    vector<uint32_t> s1(ns1);
    for (uint32_t i = 0; i < ns1; ++i)
      fin >> s1[i];
    fin >> ns2;
    vector<uint32_t> s2(ns2);
    for (uint32_t i = 0; i < ns2; ++i)
      fin >> s2[i];
    auto sta = high_resolution_clock::now();
    auto ans = string_match_dp(s1, s2, alpha, delta);
    auto finish = high_resolution_clock::now();
    // cout << "minimum penalties: " << ans << endl << endl;
    T standard;
    fin_std >> standard;
    EXPECT_EQ(standard, ans);
    tot += finish - sta;
  }
  cerr << "total time: ";
  cerr << duration_cast<microseconds>(tot).count() << " us" << endl;
  // string_match_dp()
}

TEST(string_match, test_dp1) {
  std::ifstream fin("string_match/data/p2-in-big.txt");
  std::ifstream fin_std("string_match/data/p2-out-big.txt");
  std::ios_base::sync_with_stdio(false);
  // timing
  using namespace std::chrono;
  high_resolution_clock::duration tot{};
  // capable of accepting multiple sets of input
  size_t nchset;
  while (fin >> nchset) {
    vector<uint32_t> delta(nchset);
    vector<vector<uint32_t>> alpha(nchset, vector<uint32_t>(nchset));
    for (uint32_t i = 0; i < nchset; ++i)
      fin >> delta[i];
    for (uint32_t i = 0; i < nchset; ++i)
      for (uint32_t j = 0; j < nchset; ++j)
        fin >> alpha[i][j];
    size_t ns1, ns2;
    fin >> ns1;
    vector<uint32_t> s1(ns1);
    for (uint32_t i = 0; i < ns1; ++i)
      fin >> s1[i];
    fin >> ns2;
    vector<uint32_t> s2(ns2);
    for (uint32_t i = 0; i < ns2; ++i)
      fin >> s2[i];
    auto sta = high_resolution_clock::now();
    auto ans = string_match_dp(s1, s2, alpha, delta);
    auto finish = high_resolution_clock::now();
    // cout << "minimum penalties: " << ans << endl << endl;
    T standard;
    fin_std >> standard;
    EXPECT_EQ(standard, ans);
    tot += finish - sta;
  }
  cerr << "total time: ";
  cerr << duration_cast<microseconds>(tot).count() << " us" << endl;
  // string_match_dp()
}

TEST(string_match, test_st1) {
  std::ifstream fin("string_match/data/p2-in-big.txt");
  std::ifstream fin_std("string_match/data/p2-out-big.txt");
  std::ios_base::sync_with_stdio(false);
  // timing
  using namespace std::chrono;
  high_resolution_clock::duration tot{};
  // capable of accepting multiple sets of input
  size_t nchset;
  while (fin >> nchset) {
    vector<uint32_t> delta(nchset);
    vector<vector<uint32_t>> alpha(nchset, vector<uint32_t>(nchset));
    for (uint32_t i = 0; i < nchset; ++i)
      fin >> delta[i];
    for (uint32_t i = 0; i < nchset; ++i)
      for (uint32_t j = 0; j < nchset; ++j)
        fin >> alpha[i][j];
    size_t ns1, ns2;
    fin >> ns1;
    vector<uint32_t> s1(ns1);
    for (uint32_t i = 0; i < ns1; ++i)
      fin >> s1[i];
    fin >> ns2;
    vector<uint32_t> s2(ns2);
    for (uint32_t i = 0; i < ns2; ++i)
      fin >> s2[i];
    auto sta = high_resolution_clock::now();
    auto ans = string_match_st(s1, s2, alpha, delta);
    auto finish = high_resolution_clock::now();
    // cout << "minimum penalties: " << ans << endl << endl;
    T standard;
    fin_std >> standard;
    EXPECT_EQ(standard, ans);
    tot += finish - sta;
  }
  cerr << "total time: ";
  cerr << duration_cast<microseconds>(tot).count() << " us" << endl;
  // string_match_dp()
}