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
    m_edges.reserve(E + 1);
    m_edges.push_back(Edge(-1, -1));
  }

  void add_edge(int from, int to) {
    int pre_beg = operator[](from).edge_beg;
    operator[](from).edge_beg = m_edges.size();
    m_edges.push_back(Edge(pre_beg, to));
  }

  Edge get_edge(int edge_id) const { return m_edges[edge_id]; }
  int get_edge_count() const { return m_edges.size() - 1; }

  Graph optimize() const {
    const Graph& g(*this);
    Graph g_tmp(this->size(), get_edge_count());
    for (auto from : g.vertex_ids()) {
      for (auto to : g.edges(from)) {
        g_tmp.add_edge(from, to);
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
      // bool operator==(const Iterator& other) const { return !(*this !=
      // other); } bool operator!=(const Iterator& other) const {
      //   return edge.next != -1;
      // }
      bool operator!=(int other) const { return edge.next != other; }

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
    // Iterator end() const { return Iterator(graph, graph.edge_begin_id(0)); }
    static constexpr int end() { return -1; }

   private:
    const Graph& graph;
    int beg;
  };

  class VertexIds {
   public:
    VertexIds(int size) : size(size) {}
    struct Iterator {
      Iterator(int id) : id(id) {}
      Iterator& operator++() {
        id++;
        return *this;
      }
      bool operator!=(int sz) { return id != sz; }
      int operator*() { return id; }
      int id;
    };
    static Iterator begin() { return 0; }
    int end() { return size; }

   private:
    int size;
  };

  VertexIds vertex_ids() const { return VertexIds((int)size()); }
  Edges edges(int beg) const { return Edges(*this, beg); }

 private:
  Edge edge_begin_id(int id) const { return get_edge((*this)[id].edge_beg); }
  Edge edge_begin(const Vertex& v) const { return get_edge(v.edge_beg); }
  Edge edge_next(const Edge& e) const { return get_edge(e.next); }
  bool edge_valid(const Edge& e) const { return e.next != -1; }

 private:
  vector<Edge> m_edges;
};
