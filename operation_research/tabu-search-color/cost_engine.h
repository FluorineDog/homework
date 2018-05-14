#pragma once
#include "enemy_table.h"
#include <random>
class CostEngine {
 public:
  CostEngine(const Graph& graph) : graph(graph), enemyTable(this->graph) {}

  void shift(int vertex_id, int new_color) {
    enemyTable.shift(vertex_id, new_color);
    graph[vertex_id].color = new_color;
  }

  int pick_legal_move();
  int pick_forbidden_move();
  int tabu();
  const Graph& get_graph() { return graph; }
  bool search(std::default_random_engine& e) {
    // using set
    int color_count = graph.get_color_count();
    int vertex_count = graph.size();
    for (size_t i = 0; i < 10000000UL; ++i) {
      int vertex_id = e() % vertex_count;
      int color = e() % color_count;
      this->shift(vertex_id, color);
    }
    return enemyTable.check();
  }

 private:
  Graph graph;
  EnemyTable enemyTable;
};