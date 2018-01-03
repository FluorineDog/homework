#include "../wheel.h"
struct Data{
	int ancestor;
	int max;
	int min;
	int up_gap;
	int down_gap; 
	Data(int loc, int value):ancestor(loc), max(value), min(value), up_gap(0), down_gap(0){
		
	}
	Data append_up(Data& v){
		Data tmp(v.ancestor, 0);
		tmp.max = std::max(max, v.max);
		tmp.min = std::min(min, v.min);
		tmp.up_gap = std::max(std::max(tmp.up_gap, up_gap), max-v.min);
		tmp.down_gap = std::max(std::max(tmp.down_gap,down_gap), v.max-min);
	}
};
struct Vertex {
  // int ancestor;
  // int ancestor_depth;
	int depth;
	vector<Data> jmpTable;
  int discover_time;
  int finish_time;
  vector<int> neighbors;
};

typedef vector<Vertex> Graph;
class DFS {
public:
  DFS() {}
  void operator()(Graph &graph, int source) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      graph[i].discover_time = -1;
    }
    timestamp = 0;
    depth = -1;
    dfs(graph, source);
  }
  void operator()(Graph &graph) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      graph[i].discover_time = -1;
    }
    timestamp = 0;
    for (int source = 0; source < (int)graph.size(); ++source) {
      depth = -1;
      dfs(graph, source);
    }
  }

private:
  void dfs(Graph &graph, int source) {
    ++depth;
    if (graph[source].discover_time == -1) {
      Vertex &vertex = graph[source];
      vertex.discover_time = timestamp++;
			vertex.depth = 
      for (int i = 0; i < (int)vertex.neighbors.size(); ++i) {
        dfs(graph, vertex.neighbors[i]);
      }
      vertex.finish_time = timestamp;
    }
    --depth;
  }

private:
  int depth;
  int timestamp;
};
