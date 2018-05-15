#pragma once
#include <random>
#include "enemy_table.h"
#include "tabu_table.h"

struct Movement {
  Movement(int value, int v_id, int color)
      : value(value), v_id(v_id), color(color) {}
  int value;
  int v_id;
  int color;
};

inline void update_max(bool en, Movement& dest, Movement& src) {
  if (en && src.value > dest.value) {
    dest = src;
  }
}

class CostEngine {
 public:
  CostEngine(const Graph& graph) : graph(graph), enemyTable(this->graph), tabuTable(graph) {}

  // shift data and calculate new coflicts involved
  void shift(int vertex_id, int new_color) {
    enemyTable.shift(vertex_id, new_color);
    graph[vertex_id].color = new_color;
  }

  int tabu(int vertex_id, int color, int iter, int step) { 
    tabuTable.tabu(vertex_id, color, iter + step);
  }
  // calculate best
  std::tuple<Movement, Movement> pick_move(int iter) const {
    //    v_id, color, cost
    Movement legal_best(-inf, 0, 0);
    Movement overall_best(-inf, 0, 0);
    for (int v_id : graph.vertex_ids()) {
      auto v = graph[v_id];
      int potential = enemyTable(v_id, v.color);
      if (potential == 0) {
        continue;
      }
      for (int color = 0; color < graph.get_color_count(); ++color) {
        if (color == v.color) continue;
        int improve = potential - enemyTable(v_id, color);
        bool valid = tabuTable.test(v_id, color, iter);
        Movement new_entry(improve, v_id, color);
        update_max(valid, legal_best, new_entry);
        update_max(true, overall_best, new_entry);
      }
    }
    return make_tuple(legal_best, overall_best);
  }

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