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

class EnemyTable : vector<int> {
 public:
  // EnemyTable() = default;
  EnemyTable(const Graph& graph, int color_count) : graph(graph) {
    init(color_count);
  }

  int& operator()(int vertex_id, int color_id) {
    return table(vertex_id, color_id);
  }
  void init(int color_count) {
    auto& table = *this;
    this->clear();
    this->vertex_count = graph.size();
    this->color_count;
    this->resize(vertex_count * color_count, 0);
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
    auto& table = *this;
    auto& v = graph[vertex_id];
    auto origin_color = v.color;
    for (auto victim_id : graph.edges(vertex_id)) {
      table(victim_id, origin_color)--;
      table(victim_id, new_color)++;
    }
  }

 private:
  int table(int vertex_id, int color_id) {
    return (*this)[color_id * vertex_count + vertex_count];
  }
  Graph& graph;
  int total_cost;
  int vertex_count;
  int color_count;
};

class CostEngine {
 public:
 private:
  vector<int> enemyTable;
};
