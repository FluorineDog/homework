#pragma once
#include <random>
#include "enemy_table.h"
#include "tabu_table.h"

inline void update_max(bool en, tuple<int, int, int>& dest, tuple<int, int, int> src){
  if(en && std::get<0>(src) > std::get<0>(dest)){
    dest = src;
  }
}

class CostEngine {
 public:
  CostEngine(const Graph& graph) : graph(graph), enemyTable(this->graph) {}

  // shift data and calculate new coflicts involved
  void shift(int vertex_id, int new_color) {
    enemyTable.shift(vertex_id, new_color);
    graph[vertex_id].color = new_color;
  }

  // calculate best
  int pick_move(int iter) const {
    //    v_id, color, cost
    tuple<int, int, int> legal_best = {-inf, 0, 0};
    tuple<int, int, int> overall_best = {-inf, 0, 0};
    for (int v_id : graph.vertex_ids()) {
      auto v = graph[v_id];
      int potential = enemyTable(v_id, v.color);
      if (potential == 0) {
        continue;
      }
      for(int color = 0; color < graph.get_color_count(); ++color){
        if(color == v.color) continue;
        int improve = potential - enemyTable(v_id, color);
        bool valid = tabuTable.test(v_id, color, iter);
        auto new_entry = std::make_tuple(improve, v_id, color);
        update_max(valid, legal_best, new_entry);
        update_max(true, overall_best, new_entry);
      }
    }
  }
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
  TabuTable tabuTable;
};