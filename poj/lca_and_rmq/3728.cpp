#include "../wheel.h"
struct Data {
  int ancestor;
  int max;
  int min;
  int up_gap;
  int down_gap;
  Data(int loc, int value)
      : ancestor(loc), max(value), min(value), up_gap(0), down_gap(0) {}
  Data append_up(const Data &v) const {
    Data tmp(v.ancestor, 0);
    tmp.max = std::max(max, v.max);
    tmp.min = std::min(min, v.min);
    tmp.up_gap = std::max(std::max(tmp.up_gap, up_gap), max - v.min);
    tmp.down_gap = std::max(std::max(tmp.down_gap, down_gap), v.max - min);
  }
  int blend_dest(const Data &v) {
    return std::max(std::max(up_gap, v.down_gap), max - v.min);
  }
};
struct Vertex {
  int ancestor;
	int price;
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
    dfs(graph, source, -1);
  }
  void operator()(Graph &graph) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      graph[i].discover_time = -1;
    }
    timestamp = 0;
    for (int source = 0; source < (int)graph.size(); ++source) {
      depth = -1;
      dfs(graph, source, -1);
    }
  }

private:
  void dfs(Graph &graph, int source, int parent) {
    ++depth;
    if (graph[source].discover_time == -1) {
      Vertex &vertex = graph[source];
      vertex.discover_time = timestamp++;
      vertex.depth = depth;
      {
				Data acc = Data(parent, vertex.price);
				vertex.jmpTable.push_back(acc);
				// [beg 2^k] = [beg 2^--k] * [beg double 2^--k]
				int cur_beg = acc.ancestor;
				int k = 0; 
				while(cur_beg - (1 << k) >= 0){
					acc = acc.append_up(graph[cur_beg].jmpTable[k]);
					vertex.jmpTable.push_back(acc);
					++k;
					cur_beg = acc.ancestor;
				}
			}
      for (int i = 0; i < (int)vertex.neighbors.size(); ++i) {
        dfs(graph, vertex.neighbors[i], source);
      }
      vertex.finish_time = timestamp;
    }
    --depth;
  }

private:
  int depth;
  int timestamp;
};

int main(){
	
}