#pragma once
#include <queue>
#include <stack>
#include "wheel.h"
struct Vertex {
  int edge_beg;
  // int color;
  Vertex() : edge_beg(0) {}
};

struct Edge {
  int next;
  int to;  // vertex
  Edge(int next, int to) : next(next), to(to) {}
  int dest() { return to; }
};

class Range {
 public:
  Range(int size, int rd = 0) : size(size), offset(rd % size) {}
  struct Iterator {
    Iterator(int id, int size) : id(id), size(size) {}
    Iterator& operator++() {
      id++;
      return *this;
    }
    bool operator!=(int sz) { return id != sz; }
    int operator*() { return id >= size ? id - size : id; }
    int id;
    int size;
  };
  Iterator begin() { return Iterator(offset, size); }
  int end() { return offset + size; }

 private:
  int size;
  int offset;
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
  void set_color_count(int count) { color_count = count; }

  int get_color_count() const { return color_count; }

 private:
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

 public:
  Range vertex_ids(int rd = 0) const { return Range((int)size(), rd); }
  Edges edges(int beg) const { return Edges(*this, beg); }

 private:
  Edge edge_begin_id(int id) const { return get_edge((*this)[id].edge_beg); }
  Edge edge_begin(const Vertex& v) const { return get_edge(v.edge_beg); }
  Edge edge_next(const Edge& e) const { return get_edge(e.next); }
  bool edge_valid(const Edge& e) const { return e.next != -1; }

 private:
  vector<Edge> m_edges;
  int color_count;
};

// #include <set>
// Graph GTX(Graph&& a, Graph& b) {
//   int count = a.get_color_count();
//   std::vector<std::set<int>> vec_color_a(count);
//   std::vector<std::set<int>> vec_color_b(count);
//   std::set<std::pair<int, int>> big_a;
//   std::set<std::pair<int, int>> big_b;

//   for (auto v_id : a.vertex_ids()) {
//     vec_color_a[a[v_id].color].insert(v_id);
//   }

//   for (auto v_id : b.vertex_ids()) {
//     vec_color_b[b[v_id].color].insert(v_id);
//   }

//   for (auto iter : Range(count)) {
//     auto& s1 = vec_color_a[iter];
//     big_a.insert(std::make_pair(s1.size(), iter));
//     auto& s2 = vec_color_b[iter];
//     big_b.insert(std::make_pair(s2.size(), iter));
//   }

//   std::stack<std::set<int>> record;
//   for (int iter : Range(count)) {
//     auto [sz, id] = *--big_a.end();
//     big_a.erase(std::make_pair(sz, id));
//     auto& s = vec_color_a[id];
//     for (auto v_id : s) {
//       auto color = b[v_id].color;
//       auto& affected_set = vec_color_b[color];
//       int affected_size = affected_set.size();
//       affected_set.erase(color);
//       big_b.erase(std::make_pair(affected_size, color));
//       big_b.insert(std::make_pair(affected_size - 1, color));
//     }
//     record.emplace(std::move(s));
//     s.clear();
//     std::swap(big_a, big_b);
//     std::swap(vec_color_a, vec_color_b);
//     std::swap(a, b);
//   }
//   if (count % 2 == 1) {
//     std::swap(a, b);
//   }

//   Graph res = std::move(a);
//   int color = 0;
//   while (!record.empty()) {
//     for (auto x : record.top()) {
//       res[x].color = color;
//     }
//     color++;
//     record.pop();
//   }
//   return res;
// }