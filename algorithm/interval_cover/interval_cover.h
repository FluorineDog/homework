#ifndef DOG_INTERVAL_COVEL_H_
#define DOG_INTERVAL_COVEL_H_

#include <algorithm>
#include <map>
#include <tuple>
#include <vector>
using std::tuple;
using std::vector;
using std::get;

// begin, end, value
using Data = tuple<double, double, double>;

double interval_cover(vector<Data>         kmcourses);

#endif // DOG_INTERVAL_COVEL_H_