#include "Thorup.h"
#include <climits>
#include <iostream>

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


void Thorup::FindComp(int v, short* is_in_comp) {
  is_in_comp[v] = 1;
  for(auto i: input_graf[v]) {
    if(!is_in_comp[i.vertex]) {
      FindComp(i.vertex, is_in_comp);
    }
  }
}


struct Edge {
  int first_vertex;
  int second_vertex;
  long long length;
  Edge() = default;
  Edge(int first_vertex, int second_vertex, long long length) : first_vertex(first_vertex), second_vertex(second_vertex), length(length) {}
};


vector<Edge>* SortEdges(vector<Edge>& edges, int max_length) {
 auto for_sort = new vector<Edge>[max_length + 1];

 for(auto edge: edges) {
   for_sort[edge.length].push_back(edge);
 }

 vector<Edge>* sort_edges = new vector<Edge>;

 for(int length = 0; length <= max_length; ++length) {
   for(auto edge: for_sort[length]) {
     sort_edges->push_back(edge);
   }
 }

 delete[] for_sort;
 return sort_edges;
}


struct SNMForMST {
  int to;
  int size;
  SNMForMST() : size(1) {};
};


int FindVertexInSNM(int v, SNMForMST snm[]) {
  if(snm[v].to == v) {
    return v;
  }
  snm[v].to = FindVertexInSNM(snm[v].to, snm);
  return snm[v].to;
}


int MergeInSNM(int first_vertex, int second_vertex, SNMForMST snm[]) {

  first_vertex = FindVertexInSNM(first_vertex, snm);
  second_vertex = FindVertexInSNM(second_vertex, snm);

  if(first_vertex == second_vertex) {
    return 0;
  }

  if(snm[first_vertex].size > snm[second_vertex].size) {
    std::swap(first_vertex, second_vertex);
  }

  snm[second_vertex].size += snm[first_vertex].size;
  snm[first_vertex].to = second_vertex;

  return 1;
}


vector<Edge>* FindMST(vector<Edge>& edges, int vertex_number, int max_length) {
  auto sort_edges = SortEdges(edges, max_length);

  auto snm = new SNMForMST[vertex_number];

  for(int i = 0; i < vertex_number; ++i) {
    snm[i].to = i;
  }

  auto mst = new vector<Edge>;

  for(auto edge: *sort_edges) {
    if(MergeInSNM(edge.first_vertex, edge.second_vertex, snm)) {
      mst->push_back(edge);
    }
  }

  delete sort_edges;
  delete[] snm;
  return mst;
}


struct TreeNode {
  int level = 0;
  TreeNode* child = nullptr;
  TreeNode* last_child = nullptr;
  TreeNode* next = nullptr;
  int vertex_id = -1;
  int start_time = -1;
  int end_time = -1;
  //buckets
  TreeNode() {};
  TreeNode(int vertex) : vertex_id(vertex) {}
};


TreeNode* ConstructTree(vector<Edge> &edges, int vertex_number, int max_length) {
  auto mst = FindMST(edges, vertex_number, max_length);
  auto snm = new SNMForMST[vertex_number];
  for(int i = 0; i < vertex_number; ++i) {
    snm[i].to = i;
  }
  auto nodes = new TreeNode*[vertex_number];

  for(int i = 0; i < vertex_number; ++i) {
    nodes[i] = new TreeNode(i);
  }

  int current_level = 1;
  int current_max_length = 2;

  for(int i = 0; i < mst->size(); ++current_level) {
    while (i < mst->size() && mst->at(i).length < current_max_length) {
      
      int first_vertex = mst->at(i).first_vertex;
      int second_vertex = mst->at(i).second_vertex;

      auto first_node_vertex_w = nodes[FindVertexInSNM(first_vertex, snm)];
      auto second_node_vertex_w = nodes[FindVertexInSNM(second_vertex, snm)];

      if(nodes[FindVertexInSNM(second_vertex, snm)]->level == current_level) {
        std::swap(first_vertex, second_vertex);
      }
      
      if(nodes[FindVertexInSNM(first_vertex, snm)]->level == current_level) {
        if(nodes[FindVertexInSNM(second_vertex, snm)]->level == current_level) {
          auto first_node_vertex = nodes[FindVertexInSNM(first_vertex, snm)];
          auto second_node_vertex = nodes[FindVertexInSNM(second_vertex, snm)];
          first_node_vertex->last_child->next = second_node_vertex->child; 
          first_node_vertex->last_child = second_node_vertex->last_child;
          delete second_node_vertex;
          nodes[FindVertexInSNM(second_vertex, snm)] = first_node_vertex;
          MergeInSNM(first_vertex, second_vertex, snm);
        }
        else {
          auto first_node_vertex = nodes[FindVertexInSNM(first_vertex, snm)];
          auto second_node_vertex = nodes[FindVertexInSNM(second_vertex, snm)];
          first_node_vertex->last_child->next = second_node_vertex;
          first_node_vertex->last_child = second_node_vertex;
          nodes[FindVertexInSNM(second_vertex, snm)] = first_node_vertex;
          MergeInSNM(first_vertex, second_vertex, snm);
        }
      }
      else {
        auto new_node = new TreeNode();
        new_node->level = current_level;
        new_node->child = nodes[FindVertexInSNM(first_vertex, snm)];
        new_node->child->next = nodes[FindVertexInSNM(second_vertex, snm)];
        new_node->last_child = new_node->child->next;
        nodes[FindVertexInSNM(first_vertex, snm)] = new_node;
        nodes[FindVertexInSNM(second_vertex, snm)] = new_node;
        MergeInSNM(first_vertex, second_vertex, snm);
      }
      
      auto watch = nodes[FindVertexInSNM(first_vertex, snm)];

      ++i;
    }


    current_max_length *= 2;
  }

  auto root = nodes[FindVertexInSNM(0, snm)];

  delete mst;
  delete[] snm;
  delete[] nodes;
  return root;
}


void DFSTiming(TreeNode* node, int& time, vector<int>& time_to) {
  if(node->vertex_id != -1) {
    node->start_time = time;
    node->end_time = time;
    time_to[node->vertex_id] = time;
    ++time;
    return;
  }
  node->start_time = time;

  for(auto children = node->child; children != nullptr; children = children->next) {
    DFSTiming(children, time, time_to);
  }

  node->end_time = time - 1;
}


struct SegmentTreeNode {
  long long min;
  SegmentTreeNode* left;
  SegmentTreeNode* right;
  SegmentTreeNode(long long min):  min(min), left(nullptr), right(nullptr) {};
  SegmentTreeNode(SegmentTreeNode* left, SegmentTreeNode* right, long long min): min(min), left(left), right(right) {};
  void Update(int l, int r, int index, long long new_value);
  long long Min(int l, int r, int tl, int tr);
};


void SegmentTreeNode::Update(int l, int r, int index, long long new_value) {
  if(l == r) {
    this->min = new_value;
    return;
  }
  int mid = (l + r) / 2;

  if(index <= mid) {
    left->Update(l, mid, index, new_value);
  }
  else {
    right->Update(mid + 1, r, index, new_value);
  }
  min = std::min(left->min, right->min);
}


long long SegmentTreeNode::Min(int l, int r, int find_l, int find_r) {
  if(find_l > find_r) {
    return LONG_MAX;
  }
  if(l == find_l && r == find_r) {
    return min;
  }

  int mid = (l + r) / 2;
  return std::min(left->Min(l, mid, find_l, std::min(mid, find_r)), right->Min(mid + 1, r, std::max(find_l, mid + 1), find_r));
}


SegmentTreeNode* ConstructSegmentTree(int l, int r) {
  if(l == r) {
    return new SegmentTreeNode(LONG_MAX);
  }
  return new SegmentTreeNode(ConstructSegmentTree(l, (l + r)/2), ConstructSegmentTree((l + r)/2 + 1, r), LONG_MAX);
}

long long two_in[60] = {};

int Visit(TreeNode* node, vector<vector<Thorup::Vertex>>& graf, SegmentTreeNode* root, vector<long long>& d, vector<int>& time_to) {

  if(node->vertex_id != -1) {

    for(auto to: graf[node->vertex_id]) {
      if(d[to.vertex] > d[node->vertex_id] + to.distance) {
        d[to.vertex] = d[node->vertex_id] + to.distance;
        root->Update(0, graf.size() - 1, time_to[to.vertex], d[to.vertex]);
      }
    }
    //std::cout << "Updated " << node->vertex_id << ' ' << d[node->vertex_id] << std::endl;

    if(node->vertex_id == 3)
    {
      int g = 4;
    }

    root->Update(0, graf.size() - 1, time_to[node->vertex_id], LONG_MAX);

    return 1;
  }

  bool used_circle = true;
  TreeNode* last_node;

  while(used_circle) {

    used_circle = false;
    last_node = nullptr;

    long long mint = LONG_MAX;

    for(auto children = node->child; children != nullptr; children = children->next) {
      mint = std::min(root->Min(0, graf.size() - 1, children->start_time, children->end_time), mint);
    }

    for(auto children = node->child; children != nullptr; children = children->next) {
      //std::cout << mint << std::endl;
      //std::cout << children->start_time << ' ' << children->end_time << ' ' << children->vertex_id << std::endl;
      //std::cout << root->Min(0, graf.size() - 1, children->start_time, children->end_time) << std::endl;
      //std::cout << (root->Min(0, graf.size() - 1, children->start_time, children->end_time) >> (node->level - 1)) << std::endl;
      if((root->Min(0, graf.size() - 1, children->start_time, children->end_time) == mint)) {
        if(Visit(children, graf, root, d, time_to)) {

          if(last_node == nullptr) {
            node->child = children->next;
          }
          else {
            last_node->next = children->next;
          }

          if(node->last_child == children) {
            node->last_child = last_node;
            if(last_node != nullptr) {
              node->last_child->next = nullptr;
            }
          }

          //std::cout << "to_delete " << children->start_time << ' ' << children->end_time << ' ' << children->vertex_id << std::endl;

          delete children;
          if(last_node != nullptr) {
            children = last_node;
          }
          else {
            used_circle = true;
            break;
          }

        } else {
          last_node = children;
        }

      }
      else {
        last_node = children;
      }
    }

    if(node->child == nullptr) {
      return 1;
    }

  }

  return 0;
}


long long Thorup::Do(int start_vertex, int end_vertex) {

  //prepare graph
  auto is_in_comp = new short[input_graf.size()];

  for(int i = 0; i < input_graf.size(); ++i) {
    is_in_comp[i] = 0;
  }

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
  vector<Edge> edges;

  int j = 0;

  int max_length = 0;

  for(unsigned int i = 0; i < input_graf.size(); ++i) {
    if(is_in_comp[i]) {

      for(auto vertex: input_graf[i]) {
        if(is_in_comp[vertex.vertex]) {
          graf[j].push_back(Vertex(new_index[vertex.vertex], vertex.distance));
          if(i < vertex.vertex) {
            edges.push_back(Edge(new_index[i], new_index[vertex.vertex], vertex.distance));
            max_length = std::max<int>(max_length, vertex.distance);
          }
        }
      }

      ++j;
    }
  }

  start_vertex = new_index[start_vertex];
  end_vertex = new_index[end_vertex];

  delete[] is_in_comp;
  is_in_comp = nullptr;
  delete[] new_index;
  new_index = nullptr;

  //main code

  auto tree_root = ConstructTree(edges, graf.size(), max_length);

  int time = 0;
  vector<int> time_to;
  time_to.resize(graf.size());
  DFSTiming(tree_root, time, time_to);

  auto segment_tree = ConstructSegmentTree(0, graf.size() - 1);

  vector<long long> d;
  d.resize(graf.size());
  for(int i = 0; i < d.size(); ++i) {
    d[i] = LONG_MAX;
  }

  d[start_vertex] = 0;

  segment_tree->Update(0, graf.size() - 1, time_to[start_vertex], 0);

  two_in[0] = 1;

  for(int i = 1; i < 60; ++i) {
    two_in[i] = two_in[i - 1] * 2;
  }

  while(segment_tree->min != LONG_MAX) {

    Visit(tree_root, graf, segment_tree, d, time_to);

  }

  return d[end_vertex];
}
