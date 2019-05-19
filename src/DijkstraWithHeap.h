#ifndef SSSP_SRC_DIJKSTRAWITHHEAP_H_
#define SSSP_SRC_DIJKSTRAWITHHEAP_H_

#include <queue>
#include "Heap.h"

using std::vector;
using std::pair;
using std::priority_queue;

class DijkstraWithHeap: public Heap {
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
  void InitByEdges(int n, vector<pair<pair<int, int>, long long>> vector_of_edges);

  long long Do(int start_vertex, int end_vertex);
};

#endif //SSSP_SRC_DIJKSTRAWITHHEAP_H_
