#include "matrix_chain.h"

T matrix_chain(const vector<T> &mat) {
  // DP[beg, end) = DP[beg, k) + DP[k, end) + vbeg * vk * vend
  auto size = mat.size() - 1;
  // delta * beg -> cost
  auto update = [](T &acc, T v) { acc = std::min(acc, v); };
  vector<vector<T>> DP(size + 1,
                       vector<T>(size + 1, std::numeric_limits<T>::max() / 10));
  DP[1] = vector<T>(size, 0);
  for (size_t delta = 2; delta <= size; ++delta) {
    for (size_t beg = 0; beg + delta < size + 1; ++beg) {
      size_t end = beg + delta;
      for (size_t k = beg + 1; k < end; ++k) {
        update(DP[delta][beg],
               DP[k - beg][beg] + DP[end - k][k] +
                   mat[beg] * mat[end] * mat[k]);
      }
    }
  }
  return DP[size][0];
}
