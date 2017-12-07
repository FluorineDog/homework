#undef DOG_DEBUG
#include <stdarg.h>
#include <stdio.h>

namespace dog_util {
class InputStream {
public:
  void redirect(const char *filename) {
#ifdef DOG_DEBUG
    freopen(filename, "r", stdin);
#endif
  }

  // easy to make mistake
  // if insist, use getchar() instead
  /* InputStream &operator<<(char &k) { scanf("%c", k); } */

  // better
  InputStream &operator<<(char &k) {
    char buf[2];
    scanf("%s", buf);
    k = buf[0];
    return *this;
  }

  InputStream &operator>>(int &k) {
    scanf("%d", &k);
    return *this;
  }
  InputStream &operator>>(long long &k) {
    scanf("%lld", &k);
    return *this;
  }
  InputStream &operator>>(unsigned &k) {
    scanf("%u", &k);
    return *this;
  }
  InputStream &operator>>(unsigned long long &k) {
    scanf("%llu", &k);
    return *this;
  }
  InputStream &operator>>(char *str) {
    scanf("%s", str);
    return *this;
  }
  InputStream &operator>>(double &k) {
    scanf("%f", k);
    return *this;
  }
} cin;

class OutputStream {
public:
  OutputStream &operator<<(char k) {
    printf("%c", k);
    return *this;
  }
  OutputStream &operator<<(int k) {
    printf("%d", k);
    return *this;
  }
  OutputStream &operator<<(long long k) {
    printf("%lld", k);
    return *this;
  }
  OutputStream &operator<<(unsigned k) {
    printf("%u", k);
    return *this;
  }
  OutputStream &operator<<(unsigned long long k) {
    printf("%llu", k);
    return *this;
  }
  OutputStream &operator<<(const char *str) {
    printf("%s", str);
    return *this;
  }
  OutputStream &operator<<(double k) {
    printf("%f", k);
    return *this;
  }
} cout;

class DebugStream {
public:
  int errprintf(const char *str, ...) {
#ifdef DOG_DEBUG
    va_list argptr;
    va_start(argptr, str);
    vfprintf(stderr, str, argptr);
    va_end(argptr);
#endif
  }
  DebugStream &operator<<(char k) {
    errprintf("%c", k);
    return *this;
  }
  DebugStream &operator<<(int k) {
    errprintf("%d", k);
    return *this;
  }
  DebugStream &operator<<(long long k) {
    errprintf("%lld", k);
    return *this;
  }
  DebugStream &operator<<(unsigned k) {
    errprintf("%u", k);
    return *this;
  }
  DebugStream &operator<<(unsigned long long k) {
    errprintf("%llu", k);
    return *this;
  }
  DebugStream &operator<<(const char *str) {
    errprintf("%s", str);
    return *this;
  }
  DebugStream &operator<<(double k) {
    errprintf("%f", k);
    return *this;
  }
} cerr;
const char *endl = "\n";
}
using dog_util::cin;
using dog_util::cout;
using dog_util::cerr;
using dog_util::endl;
typedef long long ll;
typedef long long ull;

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
  int lie_count = 0;
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
