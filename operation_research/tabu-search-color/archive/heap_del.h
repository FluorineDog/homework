#ifndef DOG_HEAP_DEL_H_
#define DOG_HEAP_DEL_H_
#include <queue>

// using T = int;

template <typename T>
class MinHeapDel {
 public:
  void push(T v) { data.push(std::make_pair(v, 1)); }
  void erase(T v) { data.push(std::make_pair(v, -1)); }
  T pop() {
    int acc = 0;
    while (true) {
      auto[v, id] = data.top();
      data.pop();
      acc += id;
      if (acc >= 0) {
        return v;
      }
    }
  }

 private:
  std::priority_queue<std::pair<T, int>, std::greater<std::pair<T, int>>> data;
};

template <typename T>
class MaxHeapDel {
 public:
  void push(T v) { data.push(std::make_pair(v, -1)); }
  void erase(T v) { data.push(std::make_pair(v, 1)); }
  T top() {
    int acc = 0;
    while (true) {
      auto[v, id] = data.top();
      acc += id;
      if (acc <= 0) {
        return v;
      }
      data.pop();
    }
  }
 private:
  std::priority_queue<std::pair<T, int>>> data;
};

#endif  // DOG_HEAP_DEL_H_
