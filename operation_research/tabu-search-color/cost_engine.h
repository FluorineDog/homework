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
#include "heap_del.h"
constexpr int inf = std::numeric_limits<int> / 4;

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
        current_cost++;
      }
    }
    best_shift.resize(vertex_count);
    for (int id = 0; i < vertex_count; ++id) {
      update_best_shift(id);
      global_heap.push();
    }
    assert(current_cost % 2 == 0);
    current_cost /= 2;
  }

  void tabu(int vertex, int color) {}

  void untabu(int vertex, int color) {}

  void shift(int vertex, int color) {
    int src_id = vertex;
    assert(src.color == dest.color);
    auto& src = graph[src_id];
    for (auto edge = graph.edge_begin(src); graph.edge_valid(edge);
         edge = graph.edge_next(edge)) {
      // update neighborhood value
      int dest_id = edge.to;
      auto& dest = graph[dest_id];
      int& from_color_cost = get_delta(dest_id, src.color);
      int& to_color_cost = get_delta(dest_id, dest.color);
      // ready to update data
      bool update_flag = false;
      auto[best_cost, best_color] = best_shift[dest_id];
      assert(best_cost <= from_color_cost);
      assert(best_cost <= to_color_cost);
      if (best_cost == from_color_cost) {
        // possible similiar one
        update_flag = true;
      }
      ++from_color_cost;
      if (best_cost == to_color_cost) {
        // override
        update_flag = true;
      }
      --to_color_cost;
      dest.color = color;
      if (update_flag) {
        int old = best_shift[dest];
        update_best_shift(dest);
        global_heap.erase();
      }
    }
  }

  // value, vertex, color
  tuple<int, int, int> get_best_policy() {
    // i hate it;
    return global_heap.top();
  }

  bool check() {
    Graph g = graph;
    CostEngine eng(g, color_count);
    assert(std::equal(delta_table.begin(), delta_table.end(),
                      g.delta_table.begin()));
    assert(
        std::equal(best_shift.begin(), best_shift.end(), g.best_shift.begin()));
    int conflict = 0;
    for (int id = 0; id < vertex; ++id) {
      auto& src = graph[id];

      for (auto edge = graph.edge_begin(src); graph.edge_valid(edge);
           edge = graph.edge_next(edge)) {
        //
        auto& dest = graph[edge.to];
        conflict += (src.color == dest.color) ? 1 : 0;
      }
    }
    assert(conflict % 2 == 0);
    conflict /= 2;
    assert(conflict == g.current_cost)
  }

 private:
  // find the minimal cost, store to best_cost shift
  void update_best_shift(int vertex) {
    int min = inf;
    for (int color = 0; color < color_count; ++color) {
      // we shall trust compiler
      min = std::min(get_delta(vertex, color), min);
    }
    best_shift[vertex] = min;
  }

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

  // id<vertex, color> -> cost
  int current_cost;
  vector<int> delta_table;
  // dirty, further opt is needed
  // maybe brute force vector can be better
  // if not, change will be issued later
  // vector<MinHeapDel<tuple<int, int>>> vertex_heap;
  // vertex * (cost -> color)
  vector<tuple<int, int>> best_shift;
  // cost -> vertex * color
  MinHeapDel<tuple<int, int, int>> global_heap;
  int vertex_count;
  int color_count;
};
