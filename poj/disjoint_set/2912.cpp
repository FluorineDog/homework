#include "../wheel.h"

struct Data {
  int i;
  int type;
  Data(int i_ = -1, int type_ = -1) : i(i_), type(type_) {}
};

Data find(vector<Data> &fa, int i) {
  Data &self = fa[i];
  int old_type = self.type;
  if (self.i != i) {
    self = find(fa, self.i);
    self.type += old_type;
    self.type %= 3;
  }
  return self;
}
bool insert(vector<Data> &fa, int X, int Y, int op) {
  Data xd = find(fa, X);
  Data yd = find(fa, Y);
  if (xd.i != yd.i) {
    fa[yd.i] = Data(xd.i, (op + 3 - yd.type + xd.type) % 3);
    return true;
  }
  if ((yd.type - xd.type + 3) % 3 != op) {
    return false;
  }
}

void truck() {
  int N, K;
  cin >> N >> K;
  vector<Data> fa_base(N);
  for (int i = 0; i < fa_base.size(); ++i) {
    fa_base[i] = Data(i, 0);
  }

  vector<pair<bool, vector<Data>>> ignore_table(N, make_pair(true, fa_base));
  int lie_count = 0;
  int who = -1;
  int first_encounter = -1;

  for (int line = 0; line < K; line++) {
    int X, Y;
    char op;
    cin >> X >> op >> Y;
    switch (op) {
    case '=':
      op = 0;
      break;
    case '<':
      op = 1;
      break;
    case '>':
      op = 2;
      break;
    default:
      poj_throw();
    }
    int candidate = N;
    int i = 0;
    // change to linked list?
    for (i = 0; i < N; ++i) {
      bool valid = ignore_table[i].first;
      vector<Data> &fa = ignore_table[i].second;
      if (!valid || i == X || i == Y) {
        continue;
      }
      bool status = insert(fa, X, Y, op);
      if (status) {
        candidate--;
        ignore_table[i].first = false;
        if (candidate == 1) {
          who = i;
          first_encounter = line + 1;
        }
        if (candidate == 0) {
          cout << "Impossible" << endl;
          break;
        }
      }
    }
  }
  if (candidate == 2) {
    cout << "Can not determine";
	}
	
  while (int i = 0; i < N; ++i) {
  }
}

int main() {}