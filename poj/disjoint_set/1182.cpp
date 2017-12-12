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
  return true;
}

int main() {
  int N, K;
  cin >> N >> K;
  vector<Data> fa(N);
  for (int i = 0; i < (int)fa.size(); ++i) {
    fa[i] = Data(i, 0);
  }

  int lie_count = 0;
  while (K-- > 0) {
    int op, X, Y;
    cin >> op >> X >> Y;
    --op;
    --X;
    --Y;
    if (X >= N || Y >= N) {
      ++lie_count;
      continue;
    }
    bool status = insert(fa, X, Y, op);
    if (!status) {
      ++lie_count;
    }
  }
  cout << lie_count << endl;
}
