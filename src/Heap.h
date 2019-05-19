#ifndef SSSP_SRC_HEAP_H_
#define SSSP_SRC_HEAP_H_

#include <vector>
#include <algorithm>

class Heap {
 public:
  Heap() = default;
  virtual ~Heap() = default;
  virtual void InitByEdges(int n, std::vector<std::pair<std::pair<int, int>, long long>> vector_of_edges) = 0;
  virtual long long Do(int start_vertex, int end_vertex) = 0;
};

#endif //SSSP_SRC_HEAP_H_
