#pragma once
#include <engine.h>
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
    for (auto& v : graph) {
      v.color = e() % color_count;
    }

    for (int i = 0; i < 100000; ++i) {
      int vertex_id = e() % graph.size();
      int color = e() % color_count;
      this->shift(vertex_id, color);
    }
    return enemyTable.check();
  }

 private:
  Graph graph;
  EnemyTable enemyTable;
};