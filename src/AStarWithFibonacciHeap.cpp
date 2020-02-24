#include "AStarWithFibonacciHeap.h"
#include <climits>
#include <boost/heap/fibonacci_heap.hpp>


void AStarWithFibonacciHeap::InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  graf.resize(n);
  for(auto edge: vector_of_edges) {
    graf[edge.first.first].push_back(Vertex(edge.first.second, edge.second));
  }
}


void AStarWithFibonacciHeap::InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  graf.resize(n);
  for(auto edge: vector_of_edges) {
    graf[edge.first.first].push_back(Vertex(edge.first.second, edge.second));
    graf[edge.first.second].push_back(Vertex(edge.first.first, edge.second));
  }
}


long long AStarWithFibonacciHeap::Do(int start_vertex, int end_vertex) {
  auto distance = new long long[graf.size()];

  for(unsigned int i = 0; i < graf.size(); ++i) {
    distance[i] = LONG_MAX;
  }

  auto queue = new boost::heap::fibonacci_heap<ExpextedVertex>;
  queue->push(ExpextedVertex(start_vertex, 0, 0));

  while(!queue->empty()) {
    ExpextedVertex top = queue->top();
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
        queue->push(ExpextedVertex(child.vertex, top.distance + child.distance,
                                   top.distance + child.distance + std::abs(x[child.vertex] - x[end_vertex]) +std::abs(y[child.vertex] - y[end_vertex])));
      }
    }

  }

  long long ret = distance[end_vertex];
  delete queue;
  delete[] distance;
  return ret;
}
AStarWithFibonacciHeap::AStarWithFibonacciHeap(int n, int *x_from, int *y_from) {
  x.resize(n);
  y.resize(n);
  for(int i = 0; i < n; ++i) {
    x[i] = x_from[i];
    y[i] = y_from[i];
  }
}
