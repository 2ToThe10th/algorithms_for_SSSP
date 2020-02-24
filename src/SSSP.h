#ifndef SSSP_SRC_SSSP_H_
#define SSSP_SRC_SSSP_H_

#include <vector>
#include <algorithm>

class SSSP {
 public:
  SSSP() = default;
  virtual ~SSSP() = default;
  virtual void InitByEdgesDirected(int n, std::vector<std::pair<std::pair<int, int>, long long>> vector_of_edges) = 0;
  virtual void InitByEdgesUndirected(int n, std::vector<std::pair<std::pair<int, int>, long long>> vector_of_edges) = 0;
  virtual long long Do(int start_vertex, int end_vertex) = 0;
};

#endif //SSSP_SRC_SSSP_H_
