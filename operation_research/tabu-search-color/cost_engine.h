#pragma once
#include <algorithm>
#include <random>
#include "enemy_table.h"
#include "tabu_table.h"

struct Movement {
  Movement() = default;
  Movement(int value, int v_id, int color)
      : value(value), v_id(v_id), color(color) {}
  int value;
  int v_id;
  int color;
};

inline void update_max(bool en, Movement& dest, Movement& src, int& count,
                       std::default_random_engine& e) {
  // if (en && src.value - dest.value > 0) {
  // dest = src;
  // }
  if (en) {
    int diff = src.value - dest.value;
    if (diff == 0) {
      ++count;
      if (e() % count == 0) {
        dest = src;
      }
    } else if (diff > 0) {
      dest = src;
      count = 1;
    }
  }
}

class CostEngine {
 public:
  CostEngine(const Graph& graph)
      : graph(graph), enemyTable(this->graph), tabuTable(graph) {}

  // shift data and calculate new coflicts involved
  void shift(int vertex_id, int new_color) {
    enemyTable.shift(vertex_id, new_color);
    graph[vertex_id].color = new_color;
  }

  void tabu(int vertex_id, int color, int iter, int step) {
    tabuTable.tabu(vertex_id, color, iter + step);
  }
  // calculate best
  std::tuple<Movement, Movement> pick_move(int iter,
                                           std::default_random_engine& e,
                                           int heat = 0) const {
    //    v_id, color, cost
    Movement legal_best(-inf, 0, 0);
    Movement overall_best(-inf, 0, 0);
    int valid_count = 0;
    int overall_count = 0;
    for (int v_id : graph.vertex_ids(0)) {
      auto v = graph[v_id];
      int potential = enemyTable(v_id, v.color);
      if (potential == 0 && e() % 100) {
        continue;
      }
      for (auto color : Range(graph.get_color_count(), 0)) {
        if (color == v.color) continue;
        int improve = potential - enemyTable(v_id, color);
        bool valid = tabuTable.test(v_id, color, iter);
        Movement new_entry(improve, v_id, color);
        update_max(valid, legal_best, new_entry, valid_count, e);
        update_max(!valid, overall_best, new_entry, overall_count, e);
      }
    }
    // std::cout << legal_best.value << overall_best.value;
    return make_tuple(legal_best, overall_best);
  }

  const Graph& get_graph() { return graph; }
  bool search(std::default_random_engine& e) {
    // using set
    int color_count = graph.get_color_count();
    int vertex_count = graph.size();
    int history_best = enemyTable.get_cost();
    Graph hisGraph = graph;
    for (size_t i = 0; i < 100000000ULL; ++i) {
      Movement choose;
      int current = enemyTable.get_cost();
      if (current == 0) {
        cout << i << " iter" << endl;
        break;
      }
      auto [legal, overall] = pick_move(i, e);
      if (overall.value > legal.value &&
          current - overall.value < history_best) {
        choose = overall;
      } else {
        choose = legal;
      }
      if (current - choose.value < history_best) {
        history_best = current - choose.value;
        if (history_best < 20) {
          hisGraph = graph;
        }
      }
      this->shift(choose.v_id, choose.color);
      if (i % 100000UL == 0) {
        graph = GTX(std::move(graph), hisGraph);
        tabuTable.init(graph);
        enemyTable.init();
        cout << current << "(" << history_best << ") at" << i << endl;
      }
      current = enemyTable.get_cost();
      this->tabu(choose.v_id, graph[choose.v_id].color, i,
                 std::min(100, (int)(current + e() % 10)));
    }
    // for (auto v_id : graph.vertex_ids()) {
    //   auto& v = graph[v_id];
    //   cout << v_id + 1 << " " << v.color << endl;
    // }
    return true;
  }

 private:
  Graph graph;
  EnemyTable enemyTable;
  TabuTable tabuTable;
};