#include "graph.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

constexpr int reserved_vertex = 2;
// constexpr int reserved_stu = 100 + reserved_vertex;
// constexpr int reserved_prof = 30 + reserved_stu;
constexpr int stu_max = 100;
constexpr int prof_max = 20;
constexpr int time_max = 30;
constexpr int reserved_stu_time = 30 * 100 + reserved_vertex;
constexpr int reserved_prof_time = 30 * 20 + reserved_stu_time;
constexpr int src = 0;
constexpr int dest = 1;

int breath_first_search(Graph &graph, int source) {
  auto black = color_t::black;
  auto white = color_t::white;
  for (auto &vertex : graph) {
    vertex.color = white;
    vertex.discover_time = inf;
    vertex.flowing = -1;
  }
  queue<int> qq;
  graph[source].color = black;
  graph[source].discover_time = 0;
  graph[source].parent = -1;
  graph[source].flowing = inf;
  qq.push(source);
  while (qq.size()) {
    auto &vertex = graph[qq.front()];
    qq.pop();

    if (vertex.from == dest) {
      // found
      auto final_flow = vertex.flowing; 
      int tail = vertex.from;
      while (tail != source) {
        auto& vertex = graph[tail];
        auto& parent = graph[vertex.parent];

        FOR_EDGE(edge, parent){
          if(edge->to == vertex.from){
            // assert(edge->flow_capacity == 1);
            edge->flow_capacity -= final_flow;
            break;
          }
        }
        FOR_EDGE(edge, vertex){
          if(edge->to == parent.from){
            // assert(edge->flow_capacity == 0);
            edge->flow_capacity += final_flow;
            break;
          }
        }
        tail = parent.from;
      }
      return final_flow;
    }
    // cerr << "v-" << vertex.from << endl;
    FOR_EDGE(edge, vertex) {
      // cerr<<"\t-->" << edge->to << endl;
      // assuming have no edge
      if (edge->flow_capacity == 0) {
        continue;
      }
      auto &next_v = graph[edge->to];
      if (next_v.color == white) {
        next_v.color = black;
        next_v.discover_time = vertex.discover_time + 1;
        next_v.parent = vertex.from;
        next_v.flowing = std::min(edge->flow_capacity, vertex.flowing);
        qq.push(edge->to);
      }
    }
  }
  return 0;
}

int main() {
  // entry, stu, pro, time
  int P, student_count, professor_count, time_count;
  while(cin >> P){
  cin >> student_count >> professor_count >> time_count;
  vector<tuple<int, int, int>> data_sheet;
  map<int, int> stu_time_set;
  map<int, int> prof_time_set;
  while (P-- > 0) {
    int stu, prof, time;
    cin >> stu >> prof >> time;
    data_sheet.emplace_back(--stu, --prof, --time);
  }
  // auto stu_id = [](int stu) { return stu; };
  // auto prof_id = [](int prof) { return prof + reserved_stu; };
  auto stu_id = [](int stu) { return src; };
  auto prof_id = [](int prof) { return dest; };
  auto stu_time_id = [](int stu, int time) {
    return stu * time_max + time + reserved_vertex;
  };
  auto prof_time_id = [](int prof, int time) {
    return prof * time_max + time + reserved_stu_time;
  };

  Graph graph(reserved_prof_time);
  for (int stu = 0; stu < student_count; ++stu) {
    // add_edge(graph, src, stu_id(stu), inf);
    // add_edge(graph, stu_id(stu), src, 0);
    for (int time = 0; time < time_count; ++time) {
      add_edge(graph, stu_id(stu), stu_time_id(stu, time), 1);
      add_edge(graph, stu_time_id(stu, time), stu_id(stu), 0);
      // add_edge(graph, stu_id(stu), stu_time_id(stu, time), 1);
      // add_edge(graph, stu_time_id(stu, time), stu_id(stu), 0);
    }
  }

  for (int prof = 0; prof < professor_count; ++prof) {
    // add_edge(graph, dest, prof_id(prof), 0);
    // add_edge(graph, prof_id(prof), dest, inf);
    for (int time = 0; time < time_count; ++time) {
      add_edge(graph, prof_id(prof), prof_time_id(prof, time), 0);
      add_edge(graph, prof_time_id(prof, time), prof_id(prof), 1);
    }
  }

  for (auto[stu, prof, time] : data_sheet) {
    add_edge(graph, stu_time_id(stu, time), prof_time_id(prof, time), 1);
    add_edge(graph, prof_time_id(prof, time), stu_time_id(stu, time), 0);
  }
  
  int max_flow = 0;
  while(true){
    auto flow = breath_first_search(graph, src);
    if(flow == 0){
      break;
    }
    max_flow += flow;
  }
  cout << max_flow << endl;
  }
}
