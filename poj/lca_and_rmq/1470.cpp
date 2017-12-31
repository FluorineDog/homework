
#include "../fenwick_tree/fenwick_template.h"

struct Node{
		
	vector<int> edges;
};
int main() {
	int N;
	scanf("%d", &N);
	vector<Node> graph;
	Fenwick<> tree;
	for(int k = 0; k < N; ++k){
		int vertex;
		int edge_count;
		scanf("%d:(%d)", &vertex, &edge_count);
		--vertex;
		graph[vertex].edges.reserve(edge_count);
		for(int i = 0; i < edge_count; ++i){
			int edge;
			scanf("%d", &edge);
			--edge;
			graph[vertex].edges.push_back(edge);
		}	
	}
	int K;
	while(K-->0){
		
	}
}