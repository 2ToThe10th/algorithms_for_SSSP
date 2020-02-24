#ifndef SSSP_SRC_SPFA_H_
#define SSSP_SRC_SPFA_H_

#include <queue>
#include "SSSP.h"

using std::vector;
using std::pair;

class SPFA: public SSSP {
 private:

  struct Vertex {
    int vertex;
    long long distance;
    Vertex(int vertex, int distance): vertex(vertex), distance(distance) {};
    const bool operator<(Vertex other) const {
      return distance > other.distance;
    }
  };

  vector<vector<Vertex>> graf;
 public:
  void InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;
  void InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;

  long long Do(int start_vertex, int end_vertex) override;
};

#endif //SSSP_SRC_SPFA_H_
