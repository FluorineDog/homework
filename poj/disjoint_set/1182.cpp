#include <stdio.h>
namespace dog_util {
class InputStream {
public:
  void redirect(const char *filename) {
#ifdef DEBUG
    //"disjoint_set/1733.in"
    freopen(filename, "r", stdin);
#endif
  }

  InputStream &operator>>(int &k) { scanf("%d", &k); }
  InputStream &operator>>(long long &k) { scanf("%lld", &k); }
  InputStream &operator>>(unsigned &k) { scanf("%u", &k); }
  InputStream &operator>>(unsigned long long &k) { scanf("%llu", &k); }
  InputStream &operator>>(char *str) { scanf("%s", str); }
} cin;

class OutputStream {
public:
  OutputStream &operator<<(int k) { printf("%d", k); }
  OutputStream &operator<<(long long k) { printf("%lld", k); }
  OutputStream &operator<<(unsigned k) { printf("%u", k); }
  OutputStream &operator<<(unsigned long long k) { printf("%llu", k); }
  OutputStream &operator<<(const char *str) { printf("%s", str); }
} cout;

class DebugStream {
public:
  int errprintf(const char *str, ...) {
#ifdef DEBUG
    fprintf(stderr, str, va_list);
#endif
  }
  DebugStream &operator<<(int k) { errprintf("%d", k); }
  DebugStream &operator<<(long long k) { errprintf("%lld", k); }
  DebugStream &operator<<(unsigned k) { errprintf("%u", k); }
  DebugStream &operator<<(unsigned long long k) { errprintf("%llu", k); }
  DebugStream &operator<<(const char *str) { errprintf("%s", str); }
} cerr;
const char *endl = "\n";
}
typedef long long ll;
typedef long long ull;
using dog_util::cin;
using dog_util::cout;
using dog_util::cerr;
using dog_util::endl;

#include <map>
#include <set>
#include <stdio.h>
#include <vector>
using std::vector;
using std::pair;
using std::set;
using std::map;
using std::make_pair;

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

int main() {
  int N, K;
  cin >> N >> K;
  vector<Data> fa(N);
  for (int i = 0; i < fa.size(); ++i) {
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
    auto status = insert(fa, X, Y, op);
    if (!status) {
      ++lie_count;
    }
  }
  cout << lie_count << endl;
}
