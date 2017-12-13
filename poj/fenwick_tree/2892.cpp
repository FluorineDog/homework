#include <algorithm>
// left_most destroyed, right_most destroyed
#include <limits>
int inf = std::numeric_limits<int>::max() / 4;
#define T pair<int, int>
#define INIT make_pair(inf, -inf)
#define NIL make_pair(inf, -inf)
#define FUNC(a, b)                                                             \
  make_pair(std::min(a.first, b.first), std::max(a.second, b.second)) 

#include "fenwick.h"
#include <stack>
using std::stack;
int main() {
  cin.redirect("data.in");
  int N, K;
  cin >> N >> K;
  Fenwick village_record(N + 2);
  village_record.update(0, make_pair(0, 0));
  village_record.update(N + 1, make_pair(N + 1, N + 1));

  stack<int> destroyed_village;
  while (K-- > 0) {
    char op;
    cin >> op;
    switch (op) {
    case 'R': {
      int x = destroyed_village.top();
      destroyed_village.pop();
      village_record.update(x, NIL);
    } break;
    case 'D': {
      int x;
      cin >> x;
      destroyed_village.push(x);
      village_record.update(x, make_pair(x, x));
    } break;
    case 'Q': {
      int x;
      cin >> x;
      pair<int, int> left_data = village_record.reduce(0, x + 1);
      int left_destroyed = left_data.second;

      pair<int, int> right_data = village_record.reduce(x, N + 2);
      int right_destroyed = right_data.first;
      int count = right_destroyed - left_destroyed - 1;
      if (count < 0) {
        count = 0;
      }
      cout << count << endl;
    } break;
    }
  }
}
