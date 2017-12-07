#include "string_match.h"
#include <algorithm>
#include <iostream>
using namespace std;

T string_match(dog_string s1, dog_string s2,
               const vector<vector<uint32_t>> &alpha,
               const vector<uint32_t> &delta);
T string_match_dp(dog_string s1, dog_string s2,
                  const vector<vector<uint32_t>> &alpha,
                  const vector<uint32_t> &delta);
T string_match_st(dog_string s1, dog_string s2,
                  const vector<vector<uint32_t>> &alpha,
                  const vector<uint32_t> &delta);

T string_match_dp(dog_string s1, dog_string s2,
                  const vector<vector<uint32_t>> &alpha,
                  const vector<uint32_t> &delta) {
  int fake;
  constexpr char HEAD = (char)0;
  s1.insert(s1.begin(), HEAD);
  s2.insert(s2.begin(), HEAD);

  vector<T> DPPrev(s2.size() + 1, inf);
  vector<T> DPCur(s2.size() + 1, inf);
  for (int i = 0; i < s1.size(); ++i) {
    for (int j = 0; j < s2.size(); ++j) {
      // DP[i][j] = max(DP[i-1][j]+delta[vi], detla[vj]+DP[i][j-1],
      // DP[i-1][j-1] + alpha[vi, vj])
      if (!i && !j) {
        DPCur[j] = 0;
        continue;
      }
      auto &x = DPCur[j];
      x = inf;
      if (j > 0) {
        x = std::min(x, DPCur[j - 1] + delta[s2[j]]);
      }
      if (i > 0) {
        x = std::min(x, DPPrev[j] + delta[s1[i]]);
      }
      if (i && j) {
        x = std::min(x, DPPrev[j - 1] + alpha[s1[i]][s2[j]]);
      }
      // DPCur[j] = std::min((j ? DPCur[j - 1] : inf) + delta[s2[j]],
      // (i ? DPPrev[j] : inf) + delta[s1[i]]);
      // DPCur[j] = std::min(DPCur[j],
      // (j && i ? DPPrev[j - 1] : inf) + alpha[s1[i]][s2[j]]);
    }
    DPPrev.swap(DPCur);
  }
  return DPPrev[s2.size() - 1];
}

#include "graph.h"
#include "min_bin_heap.h"
#include <set>
#define int size_t
T string_match_st(dog_string s1, dog_string s2,
                  const vector<vector<uint32_t>> &alpha,
                  const vector<uint32_t> &delta) {

  s1.insert(s1.begin(), 0);
  s2.insert(s2.begin(), 0);
  int fake;
  auto total_size = (s1.size() + 1) * (s2.size() + 1);
  Graph graph(total_size);
  auto vert = [stride = s2.size() + 1](int a, int b) { return a * stride + b; };

  for (int i = 0; i < s1.size(); ++i) {
    for (int j = 0; j < s2.size(); ++j) {
      if (j) {
        add_edge(graph, vert(i, j - 1), vert(i, j), delta[s2[j]]);
      }
      if (i) {
        add_edge(graph, vert(i - 1, j), vert(i, j), delta[s1[i]]);
      }
      if (i && j) {
        add_edge(graph, vert(i - 1, j - 1), vert(i, j), alpha[s1[i]][s2[j]]);
      }
    }
  }
  std::set<std::pair<uint32_t, int>> heap;
  std::vector<uint32_t> values(total_size);
  for (int i = 0; i < total_size; ++i) {
    heap.emplace(inf - i, i);
    values[i] = inf - i;
  }
  using std::make_pair;
#define DECREASE(i, x)                                                         \
  do {                                                                         \
    if (x < values[i]) {                                                       \
      heap.erase(make_pair(values[i], i));                                     \
      values[i] = (uint32_t)x;                                                 \
      heap.insert(make_pair(values[i], i));                                    \
    }                                                                          \
  } while (0)

  DECREASE(0, 0);
  while (heap.begin()->second != vert(s1.size() - 1, s2.size() - 1)) {
    auto[value, vertex_id] = *heap.begin();
    heap.erase(heap.begin());

    auto vertex = graph[vertex_id];
    FOR_EDGE(edge, vertex) {
      // relax
      DECREASE(edge->to, value + edge->value);
    }
  }
  return heap.begin()->first;
}
