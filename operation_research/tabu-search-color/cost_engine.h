#pragma once
#include "enemy_table.h"
#include "tabu_table.h"
#include <random>
class CostEngine {
 public:
  CostEngine(const Graph& graph) : graph(graph), enemyTable(this->graph) {}

  // shift data and calculate new coflicts involved
  void shift(int vertex_id, int new_color, stack<int>& affected) {
    enemyTable.shift(vertex_id, new_color, affected);
    graph[vertex_id].color = new_color;
  }

  // calculate best 
  // int pick_move(stack<int>& affected, std::default_random_engine& e) const{
  //   auto rd = e();
  //   while(!affected.empty()){
  //     int v_id = affected.top();
  //     Vertex v = graph[v_id];
  //     affected.pop();
  //     enemyTable(v_id, c.color);
  //   }
  // }
  int tabu();
  const Graph& get_graph() { return graph; }
  bool search(std::default_random_engine& e) {
    // using set
    int color_count = graph.get_color_count();
    int vertex_count = graph.size();
    for (size_t i = 0; i < 10000000UL; ++i) {
      int vertex_id = e() % vertex_count;
      int color = e() % color_count;
      this->shift(vertex_id, color);
    }
    return enemyTable.check();
  }

 private:
  Graph graph;
  EnemyTable enemyTable;
  TabuTable tabuTable;
};