#pragma once
#include <queue>
#include <stack>
#include "wheel.h"
struct Vertex {
  int edge_beg;
  int color;
  Vertex() : edge_beg(0), color(-1) {}
};

struct Edge {
  int next;
  int to;  // vertex
  Edge(int next, int to) : next(next), to(to) {}
  int dest() { return to; }
};

class Graph : public vector<Vertex> {
 public:
  Graph(int V, int E = 0) {

    this->resize(V);
    edges.reserve(E + 1);
    edges.push_back(Edge(-1, -1));
  }

  void add_edge(int from, int to) {
    int pre_beg = operator[](from).edge_beg;
    operator[](from).edge_beg = edges.size();
    edges.push_back(Edge(pre_beg, to));
  }

  Edge get_edge(int edge_id) const { return edges[edge_id]; }
  int get_edge_count() const { return edges.size() - 1; }
  Graph optimize() const {
    const Graph& g(*this);
    Graph g_tmp(this->size(), get_edge_count());
    for (size_t from = 0; from < this->size(); ++from) {
      const Vertex& v = g[from];
      for (auto e = edge_begin(v); edge_valid(e); edge_next(e)) {
        g_tmp.add_edge(from, e.to);
      }
    }
    return g_tmp;
  }

  class Edges {
   public:
    class Iterator {
     public:
      Iterator(const Graph& graph, Edge edge) : edge(edge), graph(graph) {}
      int operator*() const { return edge.to; }

      bool operator==(const Iterator& other) const { return !(*this != other); }

      bool operator!=(const Iterator& other) const {
        return edge.next != other.edge.next;
      }

      Iterator operator++() {
        edge = graph.edge_next(edge);
        return *this;
      }

     private:
      Edge edge;
      const Graph& graph;
    };

    Edges(const Graph& graph, int beg) : graph(graph), beg(beg) {}
    Iterator begin() const { return Iterator(graph, graph.edge_begin_id(beg)); }
    Iterator end() const { return Iterator(graph, graph.edge_begin_id(0)); }

   private:
    const Graph& graph;
    int beg;
  };

  Edges get_edges(int beg) { return Edges(*this, beg); }
  Edge edge_begin_id(int id) const { return get_edge((*this)[id].edge_beg); }
  Edge edge_begin(const Vertex& v) const { return get_edge(v.edge_beg); }
  Edge edge_next(const Edge& e) const { return get_edge(e.next); }
  bool edge_valid(const Edge& e) const { return e.next != -1; }

 private:
  vector<Edge> edges;
};
