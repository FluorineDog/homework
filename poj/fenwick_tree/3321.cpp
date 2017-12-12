#include "fenwick.h"
#define nullptr 0

struct Edge {
  int to;
  Edge *next;
  Edge(int to, Edge *next) : to(to), next(next) {}
};

struct Vertex {
  int from;
  Edge *edges;
  bool visited;
  int range_id;
  int range_begin;
  Vertex(int from = -1) : from(from), edges(nullptr), visited(false) {}
  void insert_new_edge(int dest) { edges = new Edge(dest, edges); }
};
typedef vector<Vertex> Graph;

static int index = 0;
void dfs(Graph &graph, int vertex_id) {
  Vertex &vertex = graph[vertex_id];
  vertex.range_begin = index;
  vertex.visited = true;
  for (Edge *iter = vertex.edges; iter; iter = iter->next) {
    if (graph[iter->to].visited) {
      continue;
    }
    dfs(graph, iter->to);
  }
  vertex.range_id = index++;
}

int main() {
	int N;
	cin.redirect("data.in");
  cin >> N;
  Graph graph;
  graph.resize(N);
  for (int i = 0; i < N; ++i) {
    graph[i] = i;
  }

  for (int i = 0; i < N - 1; ++i) {
    int a, b;
		cin >> a >> b;
		--a;
		--b;
    graph[a].insert_new_edge(b);
    graph[b].insert_new_edge(a);
  }
	dfs(graph, 0);
  int K;
	cin >> K;
	Fenwick table(N);
  while (K-- > 0) {
		char op;
		int vertex_id;
		cin >> op >> vertex_id;
		--vertex_id;
		switch(op){
		case 'C':{
			int id = graph[vertex_id].range_id;
			table.update(id, !table[id]);
		}
		break;
		case 'Q':{
			int begin = graph[vertex_id].range_begin;
			int end = graph[vertex_id].range_id + 1;
			cout << table.reduce(begin, end) << endl;
		}
		break;
		default:
			poj_throw();
		}

  }
}
