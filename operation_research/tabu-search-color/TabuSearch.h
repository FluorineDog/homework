#include <cassert>
#include <functional>
#include <random>
#include "EnemyTable.h"
#include "TabuTenure.h"
#include "graph.h"
// class based -> function based

class TabuSearch {
 public:
  TabuSearch(const Graph& graph, int color_count)
      : graph(graph), color_count(color_count) {
    e.seed(67);
    for (auto& c : colors) {
      c = e() % color_count;
    }
    init();
  }
  TabuSearch(const Graph& graph, int color_count, vector<int>&& colors,
             uint_fast32_t seed)
      : graph(graph), color_count(color_count) {
    e.seed(seed);
    this->colors = std::move(colors);
    init();
  }
  void acceptConfig(vector<int>&& colors) {
    this->colors = std::move(colors);
    init();
  }
  void init();
  int shift(int vertex_id, int color);
  void tabu(int vertex_id, int color, int ddl);
  std::tuple<int, int> pick_move(int iter) const;
  int getCurrentCost() const { return curr_cost; }

  int getHistoryCost() const { return hist_cost; }

 private:
  const Graph& graph;
  const int color_count;
  vector<int> colors;
  EnemyTable enemy_table;
  TabuTenure tenure;
  int curr_cost;
  int hist_cost;

  static vector<int> GPX(const TabuSearch& ts1, const TabuSearch& ts2,
                         std::default_random_engine& e);

  static TabuSearch newChild(const TabuSearch& ts1, const TabuSearch& ts2,
                             std::default_random_engine& e) {
    auto&& result = GPX(ts1, ts2, e);
    return TabuSearch(ts1.graph, ts1.color_count, std::move(result), e());
  }

 private:
  mutable std::default_random_engine e;
};

void TabuSearch::tabu(int vertex_id, int color, int ddl) {
  tenure.tabu(vertex_id, color, ddl);
}

inline void TabuSearch::init() {
  // this->graph = graph;
  hist_cost = curr_cost = enemy_table.initBy(graph, colors);
  tenure.init(graph, color_count);
}

inline int TabuSearch::shift(int vertex_id, int new_color) {
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
  // assert(enemy_table.check(graph, colors, curr_cost));
  return old_color;
}

std::tuple<int, int> TabuSearch::pick_move(int iter) const {
  tuple<int, int> tabuBest;
  int tabuDiff = INF;
  tuple<int, int> legalBest;
  int legalDiff = INF;
  int rd = e();
  // int legalCount = 0;
  // int tabuCount = 0;
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
      // if (is_legal) {
      //   if (diff < legalDiff) {
      //     legalCount = 1;
      //     legalBest = new_entry;
      //     legalDiff = diff;
      //   } else if (diff == legalDiff) {
      //     legalCount++;
      //     if (e() % legalCount == 0) {
      //       legalDiff = diff;
      //     }
      //   }
      // } else {
      //   if (diff < tabuDiff) {
      //     tabuCount = 1;
      //     tabuBest = new_entry;
      //     tabuDiff = diff;
      //   } else if (diff == tabuDiff) {
      //     tabuCount++;
      //     if (e() % tabuCount == 0) {
      //       tabuBest = new_entry;
      //     }
      //   }
      // }
    }
  }

  if (curr_cost + tabuDiff < hist_cost && tabuDiff < legalDiff) {
    return tabuBest;
  } else {
    return legalBest;
  }
}

inline vector<int> TabuSearch::GPX(  //
    const TabuSearch& ts1,           //
    const TabuSearch& ts2,           //
    std::default_random_engine& e    //
) {
#define static
  std::reference_wrapper<const vector<int>>  //
      replica[] = {ts1.colors, ts2.colors};
  int vertex_count = replica[0].get().size();
  int color_count = ts1.color_count;

  vector<int> result(vertex_count);
  for (auto& c : result) {
    c = e() % color_count;
  }

  static vector<int> color_begs[2];
  color_begs[0].clear();
  color_begs[1].clear();

  static vector<int> color_cnts[2];
  color_cnts[0].clear();
  color_cnts[1].clear();
  color_cnts[0].resize(color_count, 0);
  color_cnts[1].resize(color_count, 0);

  static vector<std::pair<int, int>> vertex_collection[2];
  vertex_collection[0].clear();
  vertex_collection[1].clear();
  // vector<int> sheet[2];
  vector<bool> vertex_deleted;
  vertex_deleted.resize(vertex_count, false);
  for (auto main_id : Range(2)) {
    auto& vc = vertex_collection[main_id];
    for (auto v_id : Range(vertex_count)) {
      int color = replica[main_id].get()[v_id];
      vc.emplace_back(color, v_id);
    }
    std::sort(vc.begin(), vc.end());
    int acc = 0;
    for (auto [color, _] : vertex_collection[main_id]) {
      int fin = color_cnts[main_id][color]++;
      if (fin == 0) {
        color_begs[main_id].push_back(acc);
      }
      acc++;
    }
    color_begs[main_id].push_back(acc);
  }

  // for (auto main_id : Range(2)) {
  //   for (auto v_id : Range(vertex_count)) {
  //     int color = replica[main_id].get()[v_id];
  //     // sheet[main_id][color]++;
  //     auto& [vertex_count, vertex_set] = sheet[main_id][color];
  //     vertex_count++;
  //     vertex_set.insert(v_id);
  //   }
  // }

  static std::stack<pair<int, int>> records;
  assert((int)records.size() == 0);

  for (auto iter : Range(color_count)) {
    int main_id = iter % 2;
    int sub_id = 1 - main_id;
    int main_color = INF;
    int main_count = -1;
    // find max color
    for (auto color : Range(color_count, e())) {
      auto count = color_cnts[main_id][color];
      if (count > main_count) {
        main_color = color;
        main_count = count;
      }
    }
    records.emplace(main_id, main_color);
    // maintain main color_cnts
    color_cnts[main_id][main_color] = 0;
    // maintain deleted_table & sub color_cnts
    int beg = color_begs[main_id][main_color];
    int end = color_begs[main_id][main_color + 1];
    for (int i = beg; i < end; ++i) {
      auto [_, v_id] = vertex_collection[main_id][i];
      if (!vertex_deleted[v_id]) {
        int sub_color = replica[sub_id].get()[v_id];
        --color_cnts[sub_id][sub_color];
        vertex_deleted[v_id] = true;
      }
    }
  }
  assert((int)records.size() == color_count);
  int iter = 0;
  while (!records.empty()) {
    auto [main_id, main_color] = records.top();
    records.pop();
    int beg = color_begs[main_id][main_color];
    int end = color_begs[main_id][main_color + 1];
    for (int i = beg; i < end; ++i) {
      auto [_, v_id] = vertex_collection[main_id][i];
      result[v_id] = iter;
    }
    ++iter;
  }
  return result;
}
#undef static