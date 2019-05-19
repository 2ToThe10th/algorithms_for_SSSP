#include "BellmanFord.h"
#include <climits>


void BellmanFord::InitByEdges(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  number_of_vertex = n;
  for(auto edge: vector_of_edges) {
    edges.push_back(Edge(edge.first.first, edge.first.second, edge.second));
  }
}


long long BellmanFord::Do(int start_vertex, int end_vertex) {
  auto distance = new long long[number_of_vertex];

  for(int i = 0; i < number_of_vertex; ++i) {
    distance[i] = LONG_MAX;
  }

  distance[start_vertex] = 0;

  bool is_change = true;

  while(is_change) {
    is_change = false;
    for(auto edge: edges) {
      if(distance[edge.start_vertex] != LONG_MAX && distance[edge.start_vertex] + edge.length < distance[edge.end_vertex]) {
        is_change = true;
        distance[edge.end_vertex] = distance[edge.start_vertex] + edge.length;
      }
    }
  }

  long long ret = distance[end_vertex];
  delete[] distance;
  return ret;
}
