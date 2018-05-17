#define private public
#include "TabuSearch.h"
#include "graph.h"
int main() {
  Graph graph(10);
  vector<int> c1{
      0, 0, 0, 1, 1, 1, 1, 2, 2, 2,
  };
  //  A  B  C  D  E  F  G  H  I  J
  vector<int> c2{
      1, 2, 0, 0, 0, 1, 0, 2, 1, 2,
  };
  TabuSearch pp1(graph, 3, std::move(c1), 0);
  TabuSearch pp2(graph, 3, std::move(c2), 0);
  std::default_random_engine e;
  auto child = TabuSearch::newChild(pp1, pp2, e);
  cout <<  "A  B  C  D  E  F  G  H  I  J" << endl;
  for(auto x : child.colors){
    cout << x << "  ";
  }
  cout << endl;
  return 0;
}