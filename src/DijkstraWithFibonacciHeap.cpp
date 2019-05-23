#include "DijkstraWithFibonacciHeap.h"
#include <climits>
#include <boost/heap/fibonacci_heap.hpp>


void DijkstraWithFibonacciHeap::InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  graf.resize(n);
  for(auto edge: vector_of_edges) {
    graf[edge.first.first].push_back(Vertex(edge.first.second, edge.second));
  }
}


void DijkstraWithFibonacciHeap::InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  graf.resize(2*n);
  for(auto edge: vector_of_edges) {
    graf[edge.first.first].push_back(Vertex(edge.first.second, edge.second));
    graf[edge.first.second].push_back(Vertex(edge.first.first, edge.second));
  }
}


long long DijkstraWithFibonacciHeap::Do(int start_vertex, int end_vertex) {
  auto distance = new long long[graf.size()];

  for(unsigned int i = 0; i < graf.size(); ++i) {
    distance[i] = LONG_MAX;
  }

  auto queue = new boost::heap::fibonacci_heap<Vertex>;
  queue->push(Vertex(start_vertex, 0));

  while(!queue->empty()) {
    Vertex top = queue->top();
    queue->pop();
    if(top.distance >= distance[top.vertex]) {
      continue;
    }
    distance[top.vertex] = top.distance;

    if(top.vertex == end_vertex) {
      break;
    }

    for(auto child: graf[top.vertex]) {
      if(distance[child.vertex] > distance[top.vertex]) {
        queue->push(Vertex(child.vertex, top.distance + child.distance));
      }
    }

  }

  long long ret = distance[end_vertex];
  delete queue;
  delete[] distance;
  return ret;
}