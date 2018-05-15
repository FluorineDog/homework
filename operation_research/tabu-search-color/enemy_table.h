#pragma once
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <vector>
#include "graph.h"
using std::make_tuple;
using std::map;
using std::pair;
using std::set;
using std::tuple;
using std::vector;
// #include "heap_del.h"

constexpr int get2shift(int N) {
  int zeros = __builtin_clz(N - 1);
  return 32 - zeros;
}

constexpr int inf = std::numeric_limits<int>::max() / 4;

class EnemyTable {
 public:
  // EnemyTable() = default;
  EnemyTable(const Graph& graph) : graph(graph) { init(); }
  EnemyTable(const EnemyTable&) = delete;
  EnemyTable(EnemyTable&&) = delete;
  const int& operator()(int vertex_id, int color_id) const {
    return table(vertex_id, color_id);
  }
  void init() {
    m_table.clear();
    int v_count = graph.size();
    this->vertex_shift = get2shift(v_count);
    // TODO
    int color_count = graph.get_color_count();
    m_table.resize((1 << vertex_shift) * color_count, 0);
    int cost = 0;
    for (auto from : graph.vertex_ids()) {
      auto v = graph[from];
      for (auto to : graph.edges(from)) {
        table(to, v.color)++;
        if (v.color == graph[to].color) cost++;
      }
    }
    total_cost = cost / 2;
  }

  int get_cost() const { return total_cost; }

  void shift(int vertex_id, int new_color) {
    auto& v = graph[vertex_id];
    auto old_color = v.color;
    this->total_cost +=
        table(vertex_id, new_color) - table(vertex_id, old_color);
    for (auto victim_id : graph.edges(vertex_id)) {
      int new_gen = table(victim_id, old_color)--;
      int old_die = table(victim_id, new_color)++;
    }
  }
  bool check() const {
    Graph g = graph;
    EnemyTable eng(g);
    bool tableEq = eng.m_table == this->m_table;
    bool costEq = eng.total_cost == this->total_cost;
    return tableEq && costEq;
  }

 private:
  const int& table(int vertex_id, int color_id) const {
    // vertex_count
    // used for cache
    return m_table[(color_id << vertex_shift) | vertex_id];
  }

  int& table(int vertex_id, int color_id) {
    // vertex_count
    // used for cache
    return m_table[(color_id << vertex_shift) | vertex_id];
  }
  const Graph& graph;
  vector<int> m_table;
  int total_cost;
  int vertex_shift;
};