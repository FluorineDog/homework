#include "TabuSearch.h"
#ifndef STRIP
#define STRIP 100000
#endif

#ifndef POPULATION
#define POPULATION 5
#endif

static std::default_random_engine e(67);
int localSearch(TabuSearch& engine, int iterBase);
int main(int argc, char* argv[]) {
  int preset_color_count;
  if (argc >= 3) {
    cin.redirect(argv[1]);
    preset_color_count = strtol(argv[2], nullptr, 10);
  } else {
    cin.redirect("data/DSJC500.5.col");
    preset_color_count = 49;
  }

  if (argc >= 4) {
    e.seed(strtol(argv[3], nullptr, 10));
  }

  char ch;
  int vertex_count, edge_count;
  while (true) {
    cin >> ch;
    if (ch == 'c') {
      // commnets
      cin.skipline();
    } else if (ch == 'p') {
      // presentation
      char tmp[20];
      cin >> tmp >> vertex_count >> edge_count;
      break;
    } else {
      cout << "edge info not found" << endl;
      exit(-1);
      // assert(false);
    }
  }

  Graph graph(vertex_count, edge_count * 2);
  for (int i = 0; i < edge_count; ++i) {
    while (getchar() != 'e') {
    }
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    graph.add_edge(from, to);
    graph.add_edge(to, from);
  }
  graph = graph.optimize();
  cout << "searching " << preset_color_count << endl;

  vector<TabuSearch> citizens;
  for (int i = 0; i < POPULATION; ++i) {
    citizens.emplace_back(graph, preset_color_count, i);
  }

  // TabuSearch engine(graph, preset_color_count);
  for (int iter = 0; iter < 1000000000; iter += STRIP) {
    int best[2] = {INF, INF}, worst = 0;
    int bestID[2] = {-1, -1}, worstID = -1;
    for (auto ctz_id : Range(POPULATION)) {
      auto& ctz = citizens[ctz_id];
      cout << ctz_id;
      int cost = localSearch(ctz, iter);
      if (cost < best[1]) {
        best[1] = cost;
        bestID[1] = ctz_id;
      }
      if (best[1] < best[0]) {
        std::swap(best[1], best[0]);
        std::swap(bestID[1], bestID[0]);
      }
      if (cost >= worst) {
        worst = cost;
        worstID = ctz_id;
      }
    }
    auto& ctz1 = citizens[bestID[0]];
    auto& ctz2 = citizens[bestID[1]];
    citizens[worstID].acceptConfig(std::move(TabuSearch::GPX(ctz1, ctz2, e)));
  }
  return 0;
}

int localSearch(TabuSearch& engine, int iterBase) {
  int best = INF;
  for (int iterI = 0; iterI < STRIP; ++iterI) {
    auto iter = iterBase + iterI;
    auto [v, c] = engine.pick_move(iter);
    int old_color = engine.shift(v, c);
    int cost = engine.getCurrentCost();
    best = std::min(cost, best);
    engine.tabu(v, old_color, iter + e() % 10 + cost);
    if (cost == 0) {
      cout                                     //
          << "iterBase: " << iterBase << endl  //
          << "iterI: " << iterI << endl        //
          << "success " << endl;
      exit(0);
    }
  }
  cout                                     //
      << "<=>" << best                     //
      << "<=>" << engine.getHistoryCost()  //
      << endl;
  return best;
}
