#include "Thorup.h"
#include <climits>


void Thorup::InitByEdgesDirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  throw "Thorup could not work with directed graph";
}


void Thorup::InitByEdgesUndirected(int n, vector<pair<pair<int, int>, long long>> vector_of_edges) {
  input_graf.resize(n);
  for(auto edge: vector_of_edges) {
    input_graf[edge.first.first].push_back(Vertex(edge.first.second, edge.second));
    input_graf[edge.first.second].push_back(Vertex(edge.first.first, edge.second));
  }
}


void Thorup::FindComp(int v, char* is_in_comp) {
  is_in_comp[v] = 1;
  for(auto i: input_graf[v]) {
    if(!is_in_comp[i.vertex]) {
      FindComp(i.vertex, is_in_comp);
    }
  }
}


long long Thorup::Do(int start_vertex, int end_vertex) {
  auto is_in_comp = new char[input_graf.size()];

  FindComp(start_vertex, is_in_comp);

  if(!is_in_comp[end_vertex]) {
    return LONG_MAX;
  }

  int n_count = 0;

  auto new_index = new int[input_graf.size()];

  for(unsigned int i = 0; i < input_graf.size(); ++i) {
    if(is_in_comp[i]) {
      new_index[i] = n_count;
      ++n_count;
    }
  }

  vector<vector<Vertex>> graf(n_count);

  int j = 0;

  for(unsigned int i = 0; i < input_graf.size(); ++i) {
    if(is_in_comp[i]) {

      for(auto vertex: input_graf[i]) {
        if(is_in_comp[vertex.vertex]) {
          graf[j].push_back(Vertex(new_index[vertex.vertex], vertex.distance));
        }
      }

      ++j;
    }
  }

  start_vertex = new_index[start_vertex];
  end_vertex = new_index[end_vertex];

  delete[] is_in_comp;
  delete[] new_index;

  //main code

  return 0;
}
