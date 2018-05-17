#pragma once
#include <cassert>
#include "graph.h"

class TabuTenure {
 public:
  static constexpr int color_count = 61;
  TabuTenure() = default;
  void init(const Graph& graph) {
    assert(graph.get_color_count() <= color_count);
    deadline_vec.clear();
    deadline_vec.resize(graph.size() * color_count , 0);
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
    return deadline_vec[vertex_id * color_count + color];
  }

  const int& table(int vertex_id, int color) const {
    return deadline_vec[vertex_id * color_count + color];
  }
  vector<int> deadline_vec;
};