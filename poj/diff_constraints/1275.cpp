#define HIGH_IO_PERFORMANCE
#include "graph.h"

bool check(int total, const vector<int> &require,
           const vector<int> &applicant) {
  // acc[t] = [0, t)
  // acc[0] = 0
  // acc[24] = total
  // acc[t + 1] - require[t] > acc[t - 7]
  // acc[t - 24] == -total + acc[0]
  // acc[t + 1] < applicant[t] + acc[t]
  Graph graph(25);
  for (int t = 0; t < 7; t++) {
    graph.add_edge(t + 1, t - 7 + 24, total - require[t]);
  }
  for (int t = 7; t < 24; t++) {
    graph.add_edge(t + 1, t - 7, -require[t]);
  }
  for (int t = 0; t < 24; t++) {
    graph.add_edge(t, t + 1, applicant[t]);
		graph.add_edge(t+1, t, 0);
  }
	graph.add_edge(0, 24, total);
	graph.add_edge(24, 0, -total);
  bool fuck = graph.spfa(0);
  // if (total == 3) {
    // for (int i = 0; i < 25; ++i) {
      // cout << graph[i].value << "*" << graph[i].visited << endl;
    // }
  // }
  return fuck;
}

void workload() {
  vector<int> require(24);
  for (int i = 0; i < 24; ++i) {
    cin >> require[i];
  }
  int apply_num;
  cin >> apply_num;
  vector<int> applicant(24, 0);
  for (int i = 0; i < apply_num; ++i) {
    int id;
    cin >> id;
    applicant[id]++;
  }
  int beg = 0;
  int end = apply_num + 1;
  while (beg != end) {
    int mid = (beg + end) / 2;
    if (check(mid, require, applicant)) {
      end = mid;
    } else {
      beg = mid + 1;
    }
  }
  // int k0 = check(0, require, applicant);
  // int k1 = check(1, require, applicant);
  // int k2 = check(2, require, applicant);
  // int k3 = check(3, require, applicant);
  // cerr << k1 + k2 + k3 + k0;
  if (beg == apply_num + 1) {
    cout << "No Solution\n";
  } else {
    cout << beg << endl;
  }
}

int main() {
  cin.redirect("data.in");
  int case_num;
  cin >> case_num;
  while (case_num-- > 0) {
    workload();
  }
}
