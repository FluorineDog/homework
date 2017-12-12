#include "../wheel.h"

struct Data {
  int i;
  int type;
  Data(int i_ = -1, int type_ = -1) : i(i_), type(type_) {}
};

Data find(map<int, Data> &fa, int i) {
  if (fa.find(i) == fa.end()) {
    // fake init
    fa[i] = Data(i, 0);
  }
  Data &self = fa[i];
  int old_type = self.type;
  if (self.i != i) {
    self = find(fa, self.i);
    self.type += old_type;
    self.type %= 2;
  }
  return self;
}
void log(map<int, Data> &fa) {
#ifdef DOG_DEBUG
  typedef map<int, Data>::iterator Iter;
  for (Iter iter = fa.begin(); iter != fa.end(); ++iter) {
    cerr << "{" << iter->first << "->" << iter->second.i << "("
         << iter->second.type << ")}";
  }
  cerr << endl;
#endif
}

int main() {
  int N, K;
  cin >> N >> K;
  map<int, Data> fa;
  for (int index = 0; index < K; ++index) {
    int X, Y;
    char buf[10];
    cin >> X >> Y >> buf;
    int op = buf[0] == 'e' ? 0 : 1;
    --X;
    --Y;
    ++Y;
    log(fa);
    Data xd = find(fa, X);
    log(fa);
    Data yd = find(fa, Y);
    log(fa);
    cerr << "----------" << endl;
    if (xd.i != yd.i) {
      fa[yd.i] = Data(xd.i, (op + 2 - yd.type + xd.type) % 2);
      continue;
    }
    if ((yd.type - xd.type + 2) % 2 != op) {
      cout << index << endl;
      return 0;
    }
  }
  cout << K << endl;
}
