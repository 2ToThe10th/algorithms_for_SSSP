#ifndef SSSP_SRC_ASTARWITHFIBONACCIHEAP_H_
#define SSSP_SRC_ASTARWITHFIBONACCIHEAP_H_

#include <queue>
#include "SSSP.h"

using std::vector;
using std::pair;
using std::priority_queue;

class AStarWithFibonacciHeap: public SSSP {
 private:

  struct Vertex {
    int vertex;
    long long distance;
    Vertex(int vertex, long long distance): vertex(vertex), distance(distance) {};
    const bool operator<(Vertex other) const {
      return distance > other.distance;
    }
  };

  struct ExpextedVertex {
    int vertex;
    long long distance;
    long long expected_distance;
    ExpextedVertex(int vertex, long long distance, long long expected_distance): vertex(vertex), distance(distance), expected_distance(expected_distance) {};
    const bool operator<(ExpextedVertex other) const {
      return expected_distance > other.expected_distance;
    }
  };

  vector<int> x;
  vector<int> y;
  vector<vector<Vertex>> graf;
 public:
  void InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;
  void InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) override;
  AStarWithFibonacciHeap(int n, int* x_from, int* y_from);

  long long Do(int start_vertex, int end_vertex) override;
};

#endif //SSSP_SRC_ASTARWITHFIBONACCIHEAP_H_
