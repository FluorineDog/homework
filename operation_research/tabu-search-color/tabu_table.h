#pragma once
#include "graph.h"
class TabuTable {
 public:
  TabuTable(const Graph& graph) { init(graph); }
  void init(const Graph& graph) {
    deadline_vec.resize(graph.size() * graph.get_color_count());
    this->color_count = 0;
  }
  void tabu(int vertex_id, int color, int deadline) {
    // deadline_vec()
    table(vertex_id, color) = deadline;
  }

  bool test(int vertex_id, int color, int iter) const {
    return table(vertex_id, color) <= iter;
  }

 private:
  int& table(int vertex_id, int color) {
    return deadline_vec[vertex_id * color_count + color];
  }

  const int& table(int vertex_id, int color) const{
    return deadline_vec[vertex_id * color_count + color];
  }
  vector<int> deadline_vec;
  int color_count;
};