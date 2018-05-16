#include <random>
#include "EnemyTable.h"
#include "TabuTenure.h"
#include "graph.h"
// class based -> function based

class TabuSearch {
 public:
  void init(const Graph& graph, int color_count);
  void shift(int vertex_id, int color);
  std::tuple<int, int> pick_move(int iter) const;

 private:
  Graph graph;
  vector<int> color_set;
  EnemyTable enemy_table;
  static std::default_random_engine e;
  TabuTenure tenure;
  int color_count;
  int curr_cost;
  int hist_cost;
};

inline void TabuSearch::init(const Graph& graph, int color_count) {
  // this->graph = graph;
  enemy_table.initBy(graph, color_set);
}

inline void TabuSearch::shift(int vertex_id, int new_color) {
  int old_color = color_set[vertex_id];
  // update enemy_table
  for (auto victim_id : graph.edges(vertex_id)) {
    enemy_table(victim_id, old_color)--;
    enemy_table(victim_id, new_color)++;
  }
  // update total_cost
  this->curr_cost +=
      enemy_table(vertex_id, new_color) - enemy_table(vertex_id, old_color);
}

std::tuple<int, int> TabuSearch::pick_move(int iter) const {
  tuple<int, int> tabuBest;
  int tabuDiff = inf;
  tuple<int, int> legalBest;
  int legalDiff = inf;
  int rd = e();
  for (auto v_id : graph.vertex_ids(rd)) {
    int old_color = color_set[v_id];
    if (enemy_table(v_id, old_color) == 0) {
      continue;
    }
    int old_enemy = enemy_table(v_id, old_color);
    int rd = e();
    for (auto color : Range(color_count, rd)) {
      if (color == old_color) continue;
      bool is_legal = tenure.test(v_id, color, iter);
      int diff = enemy_table(v_id, color) - old_enemy;
      auto new_entry = std::make_tuple(v_id, color);

      if (is_legal && diff < legalDiff) {
        legalBest = new_entry;
        legalDiff = diff;
      } else if (!is_legal && diff < tabuDiff) {
        tabuBest = new_entry;
        tabuDiff = diff;
      }
    }
  }

  if (curr_cost + tabuDiff < hist_cost && tabuDiff < legalDiff) {
    return tabuBest;
  } else {
    return legalBest;
  }
}
