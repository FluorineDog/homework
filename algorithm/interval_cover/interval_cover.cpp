#include "interval_cover.h"
double interval_cover(vector<Data> courses) {
  std::sort(courses.begin(), courses.end(),
            [](Data a, Data b) { return get<1>(a) < get<1>(b); });
  //
  // endtime ==> value
  std::map<double, double> table;
  table[std::numeric_limits<double>::min()] = 0;
  table[std::numeric_limits<double>::max()] =
      std::numeric_limits<double>::max();
  //
  double max = 0;
  for (auto t : courses) {
    auto beg_time = get<0>(t);
    auto end_time = get<1>(t);
    auto value = get<2>(t);
    auto iter = table.upper_bound(beg_time);
    --iter;
    if (iter->second + value > max) {
      max = iter->second + value;
      table[end_time] = max;
    }
	}
	return max;
}
