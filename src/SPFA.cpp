#include "SPFA.h"
#include <climits>

void SPFA::InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  graf.resize(n);
  for(auto edge: vector_of_edges) {
    graf[edge.first.first].push_back(Vertex(edge.first.second, edge.second));
  }
}


void SPFA::InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  graf.resize(2*n);
  for(auto edge: vector_of_edges) {
    graf[edge.first.first].push_back(Vertex(edge.first.second, edge.second));
    graf[edge.first.second].push_back(Vertex(edge.first.first, edge.second));
  }
}


long long SPFA::Do(int start_vertex, int end_vertex) {
  auto distance = new long long[graf.size()];
  auto is_in_queue = new char[graf.size()];

  for(unsigned int i = 0; i < graf.size(); ++i) {
    distance[i] = LONG_MAX;
    is_in_queue[i] = 0;
  }

  distance[start_vertex] = 0;
  is_in_queue[start_vertex] = 1;

  auto queue = new std::queue<int>();
  queue->push(start_vertex);

  while(!queue->empty()) {
    int vertex = queue->front();
    queue->pop();
    for(auto neighbors: graf[vertex]) {
      if(distance[vertex] + neighbors.distance < distance[neighbors.vertex]) {
        distance[neighbors.vertex] = distance[vertex] + neighbors.distance;
        if(is_in_queue[neighbors.vertex] == 0) {
          queue->push(neighbors.vertex);
          is_in_queue[neighbors.vertex] = 1;
        }
      }
    }
    is_in_queue[vertex] = 0;
  }

  long long ret = distance[end_vertex];
  delete queue;
  delete[] distance;
  delete[] is_in_queue;
  return ret;
}
