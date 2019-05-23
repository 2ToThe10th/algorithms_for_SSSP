#ifndef SSSP_SRC_THORUP_H_
#define SSSP_SRC_THORUP_H_

#include "SSSP.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;

class Thorup: public SSSP {
 private:
  struct Vertex {
    int vertex;
    long long distance;
    Vertex(int vertex, long long distance): vertex(vertex), distance(distance) {};
    const bool operator<(Vertex other) const {
      return distance > other.distance;
    }
  };

  void FindComp(int v, char* is_in_comp);

  vector<vector<Vertex>> input_graf;
 public:
  void InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;
  void InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;

  long long Do(int start_vertex, int end_vertex) override;
};

#endif //SSSP_SRC_THORUP_H_
