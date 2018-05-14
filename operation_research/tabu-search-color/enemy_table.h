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

constexpr int inf = std::numeric_limits<int>::max() / 4;

class EnemyTable {
 public:
  // EnemyTable() = default;
  EnemyTable(const Graph& graph) : graph(graph) {
    init();
  }
  int& operator()(int vertex_id, int color_id) {
    return table(vertex_id, color_id);
  }
  void init() {
    m_table.clear();
    this->vertex_count = graph.size();
    // TODO 
    int color_count = graph.get_color_count();
    m_table.resize(vertex_count * color_count, 0);
    int cost = 0;
    for (auto from : graph.vertex_ids()) {
      auto v = graph[from];
      for (auto to : graph.edges(from)) {
        table(to, v.color)++;
        cost++;
      }
    }
    total_cost = cost / 2;
  }

  void shift(int vertex_id, int new_color) {
    auto& v = graph[vertex_id];
    auto old_color = v.color;
    for (auto victim_id : graph.edges(vertex_id)) {
      table(victim_id, old_color)--;
      table(victim_id, new_color)++;
    }
  }
  bool check() {
    Graph g = graph;
    EnemyTable eng(g);
    bool tableEq = eng.m_table == this->m_table;
    bool costEq = eng.total_cost == this->total_cost;
    return tableEq && costEq;
  }
 private:
  int& table(int vertex_id, int color_id) {
    // vertex_count
    // used for cache
    return m_table[color_id * vertex_count + vertex_id];
  }
  const Graph& graph;
  vector<int> m_table;
  int total_cost;
  int vertex_count;
};

