#include <random>
#include "EnemyTable.h"
#include "TabuTenure.h"
#include "graph.h"
#include <cassert>
// class based -> function based

class TabuSearch {
 public:
  TabuSearch(const Graph& graph, int color_count)
      : graph(graph), color_count(color_count) {
    init();
  }
  void init();
  void shift(int vertex_id, int color);
  std::tuple<int, int> pick_move(int iter) const;

 private:
  const Graph& graph;
  const int color_count;
  vector<int> colors;
  EnemyTable enemy_table;
  TabuTenure tenure;
  int curr_cost;
  int hist_cost;

 private:
  static std::default_random_engine e;
};

inline void TabuSearch::init() {
  // this->graph = graph;
  for (auto& c : colors) {
    c = e() % color_count;
  }
  hist_cost = curr_cost = enemy_table.initBy(graph, colors);
  tenure.init(graph);
}

inline void TabuSearch::shift(int vertex_id, int new_color) {
  int old_color = colors[vertex_id];
  // update enemy_table
  for (auto victim_id : graph.edges(vertex_id)) {
    enemy_table(victim_id, old_color)--;
    enemy_table(victim_id, new_color)++;
  }
  // update total_cost
  curr_cost +=
      enemy_table(vertex_id, new_color) - enemy_table(vertex_id, old_color);
  hist_cost = std::min(curr_cost, hist_cost);
  colors[vertex_id] = new_color;
  assert(enemy_table.check(graph, colors, curr_cost));
}

std::tuple<int, int> TabuSearch::pick_move(int iter) const {
  tuple<int, int> tabuBest;
  int tabuDiff = inf;
  tuple<int, int> legalBest;
  int legalDiff = inf;
  int rd = e();
  for (auto v_id : graph.vertex_ids(rd)) {
    int old_color = colors[v_id];
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
