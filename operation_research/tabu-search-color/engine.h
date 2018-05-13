#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <vector>
#include "graph.h"
using std::make_tuple;
using std::map;
using std::pair;
using std::set;
using std::tuple;
using std::vector;
#include "heap_del.h"
constexpr int inf = std::numeric_limits<int> / 4;



class EnemyTable : vector<int> {
 public:
  EnemyTable(int vertex_count, int color_count) : vector(vertex_count) {}
  int& operator()(int vertex_id, int color_id) {
    return (*this)[color_id * vertex_count + vertex_count];
  }
  void init(const Graph graph){
    for(int from = 0; from < graph.size(); ++from){
      for()
    } 
  }
 private:
  int vertex_count;
  int color_count;
}

class CostEngine {
 public:
 private:
  vector<int> enemyTable;
};