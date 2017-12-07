// #undef DOG_DEBUG
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
void poj_throw() {
  int *memory = new int[1UL << 31];
  memory = new int[1UL << 31];
  memory = new int[1UL << 31];
  memory = new int[1UL << 31];
}

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
using dog_util::poj_throw;
typedef long long ll;
typedef long long ull;

#include <algorithm>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>
using std::vector;
using std::pair;
using std::set;
using std::map;
using std::make_pair;
struct FUCK {
  int m[2];
  operator int *() { return m; }
  int &operator[](int i) { return m[i]; }
};

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
    self.type %= 2;
  }
  return self;
}
void log(vector<Data> &fa) {
#ifdef DOG_DEBUG
  typedef vector<Data>::iterator Iter;
  for (int i = 0; i < fa.size(); ++i) {
    cerr << "{" << i << "->" << fa[i].i << "(" << fa[i].type << ")}";
  }
  // for (Iter iter = fa.begin(); iter != fa.end(); ++iter) {
  // cerr << "{" << iter->first << "->" << iter->second.i << "("
  //  << iter->second.type << ")}";
  // }
  cerr << endl;
#endif
}

bool deal() {
  // while (true) {
  int K, divine, devilish;
  cin >> K >> divine >> devilish;
  int N = divine + devilish;
  if (K == 0 && N == 0) {
    return false;
  }
  vector<Data> fa(N);
  for (int i = 0; i < N; ++i) {
    fa[i] = Data(i, 0);
  }
  int lie_count = 0;
  for (int index = 0; index < K; ++index) {
    int X, Y;
    char buf[10];
    // cin >> X >> Y >> buf;
    scanf("%d%d%s", &X, &Y, buf);
    int op = buf[0] == 'y' ? 0 : 1;
    --X;
    --Y;
    Data xd = find(fa, X);
    Data yd = find(fa, Y);
    if (xd.i != yd.i) {
      fa[yd.i] = Data(xd.i, (op + 2 - yd.type + xd.type) % 2);
      continue;
    }
    // if ((yd.type - xd.type + 2) % 2 != op) {
    // cout << index << endl;
    // return 0;
    // }
  }
  log(fa);
  map<int, FUCK> table;
  for (int i = 0; i < fa.size(); ++i) {
    Data data = find(fa, i);
    int *tmp = table[data.i];
    tmp[data.type]++;
  }
  typedef map<int, FUCK>::iterator Iter;
  int relative_count = 0;
  for (Iter iter = table.begin(); iter != table.end(); ++iter) {
    // let (a, b)  ==> (a-b, 0), to pack problem
    // don't matter if a < b
    int *workload = iter->second;
    workload[0] -= workload[1];
    relative_count += workload[1];
    if (workload[0] == 0) {
      cerr << "fuck";
      cout << "no" << endl;
      return true;
    }
  }

  static vector<int> buffer(2200, 0);
  buffer.clear();
  buffer.resize(N + 1);
  static vector<pair<int, int> > parents(2200);
  parents.clear();
  parents.resize(N + 1, make_pair(-1, -1));
  buffer[relative_count] = 1;
  int upper = relative_count + 1;
  int lower = relative_count;
  for (Iter iter = table.begin(); iter != table.end(); ++iter) {
    int tag = iter->first;
    int delta = iter->second[0];
    if (delta > 0) {
      upper += delta;
      for (int i = upper - delta; i-- > lower;) {
        if (buffer[i] == 0)
          continue;
        if (buffer[i + delta] == 0) {
          parents[i + delta] = make_pair(i, tag);
        }
        buffer[i + delta] += buffer[i];
      }
    } else {
      lower += delta;
      for (int i = lower - delta; i < upper; ++i) {
        if (buffer[i] == 0)
          continue;
        if (buffer[i + delta] == 0) {
          parents[i + delta] = make_pair(i, tag);
        }
        buffer[i + delta] += buffer[i];
      }
    }
  }

  if (buffer[divine] != 1) {
    cerr << "fake" << buffer[divine];
    cout << "no" << endl;
    return true;
  }
  set<int> divine_0set;
  int index = divine;
  int dangerout_count = 0;
  while (index != relative_count) {
    pair<int, int> par = parents[index];
    divine_0set.insert(par.second);
    index = par.first;
    ++dangerout_count;
    if (dangerout_count > N + 1) {
      poj_throw();
    }
  }
  for (int i = 0; i < fa.size(); ++i) {
    int divine_type = divine_0set.find(fa[i].i) != divine_0set.end() ? 0 : 1;
    if (divine_type == fa[i].type) {
      cout << i + 1 << endl;
    }
  }
  cout << "end" << endl;
}

int main() {
  cin.redirect("data.in");
  while (deal())
    ;
  return 0;
}
