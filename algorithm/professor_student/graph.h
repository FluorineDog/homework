#include <vector>
#include <limits>
#include <iostream>

constexpr int inf = std::numeric_limits<int>::max() / 4;
enum class color_t{black, white};
struct Edge{
	Edge(int to = -1, Edge* next = nullptr, int flow_capacity = 0)
		:to(to), next(next), flow_capacity(flow_capacity) {}
	int to;
	Edge* next;
	// any attached data to edges
	int flow_capacity;
};

struct Vertex{
	Vertex(int from = -1):from(from), edges(nullptr){}
	int from;
	Edge* edges;
	// any attached data to vertex
	color_t color;
	int discover_time;
	int parent;
	int finish_time;
	int flowing;
	//int scc_index;
};

struct Graph 
	:public std::vector<Vertex>
{
	Graph(int size = 0)
		:vector(size)
	{
		for(int i = 0; i<this->size(); ++i){
			(*this)[i].from = i; 
		}
	}
	Graph& operator=(const Graph&) = delete;
	Graph(const Graph&) = delete;
	Graph& operator=(Graph&& graph){
		vector<Vertex>(*this) = std::move(graph);
		graph.clear();
		return *this;
	}
	Graph(Graph&& graph):
		vector(std::move(graph))
	{
		graph.clear();
	}
	~Graph();
	void showGraph();
};

inline void add_edge(Graph& graph, int from, int to, int flow_capacity = 0){
	graph[from].edges = new Edge(to, graph[from].edges, flow_capacity);  
}

#define FOR_EDGE(edge, vertex) \
for(Edge* edge = vertex.edges;\
edge != nullptr;\
edge = edge->next)


inline Graph transpose(Graph& graph){
	Graph result(graph.size());
	for(auto vertex:graph){
		FOR_EDGE(edge, vertex) {
			add_edge(result, edge->to, vertex.from);
		}
	}
	return result;
}

inline void clear_graph(Graph& graph){
	for(auto& vertex: graph){
		auto edge = vertex.edges;
		while(edge){
			auto next = edge->next;
			delete edge;
			edge = next;
		}
		vertex.edges = nullptr;
	}
}

inline Graph::~Graph(){
	clear_graph(*this);
}
// 
// void breath_first_search(Graph& graph, int source);
// void depth_first_search(Graph& graph);
// std::vector<int> topological_sort(Graph& graph);
// std::pair<Graph, std::vector<int>> strong_connected_component(Graph& graph);
// void test_skeleton(Graph&);