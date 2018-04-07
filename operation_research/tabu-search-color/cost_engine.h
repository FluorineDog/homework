#include <algorithm>
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
#include "heap_del.h"

template <typename T, T value>
struct DefaultValue {
  T operator T() { return T; }
  DefaultedValue(T v = value) : v(value) {}

 private:
  T value;
};

class CostEngine {
 public:
  CostEngine(Graph& graph, int color_count)
      : graph(graph), color_count(color_count) {
    vertex_count = graph.size();
    init_table();
  }
  void init_table() {
    delta_table.clear();
    delta_table.resize(vertex_count * color_count, 0);
    for (int src_id = 0; src_id < vertex_count; ++src_id) {
      auto& src = graph[src_id];
      for (auto edge = graph.edge_begin(src); graph.edge_valid(edge);
           edge = graph.edge_next(edge)) {
        // for each edge
        auto& dest = graph[edge.to];
        // record if moved to here, how many enemies i will encounter
        get_delta(src_id, dest.color) += 1;
      }
    }
  }

  void tabu(int vertex, int color) {}

  void untabu(int vertex, int color) {}

  void shift(int vertex, int color) {
    int src_id = vertex;
    auto& src = graph[src_id];
    for (auto edge = graph.edge_begin(src); graph.edge_valid(edge);
         edge = graph.edge_next(edge)) {
      // update neighborhood value
    }
  }

  // value, vertex, color
  tuple<int, int, int> get_best_policy() {
    // i hate it;
    return global_heap()
  }

 private:
  int& get_delta(int vertex, int color) {
    // get unique table id for each <vertex, color>
    return delta_table[vertex * color_count + color];
  }

  int get_alter_cost(int vertex, int color) {
    int old_cost = get_delta(vertex, graph[vertex].color);
    int new_cost = get_delta(vertex, color);
    return new_cost - old_cost;
  }

  Graph& graph;
  int current_cost;
  int vertex_count;
  int color_count;
  // vertex -> color_delta
  // id -> color_delta
  vector<int> delta_table;
  // dirty, further opt is needed
  vector<MinHeapDel<tuple<int>>> vertex_heap;
  MinHeapDel<tuple<int>> global_heap;
  
};
