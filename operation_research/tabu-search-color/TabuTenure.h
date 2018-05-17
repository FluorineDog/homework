#pragma once
#include <cassert>
#include "graph.h"

class TabuTenure {
 public:
  static constexpr int MAX_COLOR_COUNT = 61;
  TabuTenure() = default;
  void init(const Graph& graph, int color_count) {
    assert(color_count<= MAX_COLOR_COUNT);
    deadline_vec.clear();
    deadline_vec.resize(graph.size() * MAX_COLOR_COUNT , 0);
  }
  void tabu(int vertex_id, int color, int deadline) {
    // deadline_vec()
    table(vertex_id, color) = deadline;
  }

  bool test(int vertex_id, int color, int iter) const {
    return table(vertex_id, color) < iter;
  }

 private:
  int& table(int vertex_id, int color) {
    return deadline_vec[vertex_id * MAX_COLOR_COUNT + color];
  }

  const int& table(int vertex_id, int color) const {
    return deadline_vec[vertex_id * MAX_COLOR_COUNT + color];
  }
  vector<int> deadline_vec;
};