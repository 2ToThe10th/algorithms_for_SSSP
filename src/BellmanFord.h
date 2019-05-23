#ifndef SSSP_SRC_BELLMANFORD_H_
#define SSSP_SRC_BELLMANFORD_H_

#include "SSSP.h"

using std::vector;
using std::pair;


class BellmanFord: public SSSP {
 private:
  struct Edge{
    int start_vertex;
    int end_vertex;
    int length;
    Edge(int start_vertex, int end_vertex, int length): start_vertex(start_vertex), end_vertex(end_vertex), length(length) {};
  };

  int number_of_vertex;
  vector<Edge> edges;
 public:
  void InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;
  void InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;

  long long Do(int start_vertex, int end_vertex) override;
};

#endif //SSSP_SRC_BELLMANFORD_H_
