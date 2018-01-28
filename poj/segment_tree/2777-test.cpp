#include <iostream>
typedef int T;
#define FUNC(a, b) ((a) | (b))
#define NIL 0
#define INIT 1
#include "segment_tree.h"
#include "../fenwick_tree/fenwick.h"

inline int numberOfSetBits(unsigned i) {
  // Java: use >>> instead of >>
  // C or C++: use uint32_t
  i = i - ((i >> 1) & 0x55555555);
  i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
  return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
void workload() {
  int L, T, O;
  if (scanf("%d%d%d", &L, &T, &O) != 3) {
    exit(0);
  }
  Fenwick tree(L);
  // tree.log();
  while (O-- > 0) {
    char ch;
    cin >> ch;
    int a, b, color;
    if (ch == 'C') {
      cin >> a >> b >> color;
      int c = std::min(a, b);
      int d = std::max(a, b);
      for (int i = c - 1; i < d; ++i) {
        tree.update(i, 1 << (color - 1));
      }
      // tree.log();
    } else {
      cin >> a >> b;
      int c = std::min(a, b);
      int d = std::max(a, b);
      int color = tree.reduce(c - 1, d);
      // tree.log();
      cout << numberOfSetBits(color) << endl;
    }
  }
}
int main() {
  cin.redirect("data.in");
  while (true)
    workload();
}