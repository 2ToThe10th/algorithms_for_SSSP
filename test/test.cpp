#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <SPFA.h>
#include <chrono>
#include "BellmanFord.h"
#include "DijkstraWithHeap.h"

using std::cout;
using std::endl;
using std::pair;

TEST(SpeedTest, RandomGraph) {

  long long dijkstra_with_heap_time = 0;
  long long bellman_ford_time = 0;
  long long spfa_time = 0;

  const int TEST_QUANTITY = 1e3;

  for(int id = 0; id < TEST_QUANTITY; ++id) {

    std::mt19937 generate_random(id);

    vector<pair<pair<int, int>, long long>> v;

    const int MAX_VERTEX = 1e4;
    const int MAX_EDGE = 1e6;
    const int MAX_LENGTH = 1e7;

    int n = (generate_random() % MAX_VERTEX + MAX_VERTEX) % MAX_VERTEX + 1;
    int m = (generate_random() % MAX_EDGE + MAX_EDGE) % MAX_EDGE;

    for (int i = 0; i < m; ++i) {
      int s = (generate_random() % n + n) % n;
      int e = (generate_random() % n + n) % n;
      int l = (generate_random() % MAX_LENGTH + MAX_LENGTH ) % MAX_LENGTH;
      v.push_back({{s, e}, l});
    }

    long long ans = -1;

    Heap* sssp = nullptr;
    long long* timer = nullptr;
    for (int index = 0; index < 3; ++index) {
      switch (index) {
        case 0:
          sssp = new DijkstraWithHeap();
          timer = &dijkstra_with_heap_time;
          break;
        case 1:
          sssp = new BellmanFord();
          timer = &bellman_ford_time;
          break;
        case 2:
          sssp = new SPFA();
          timer = &spfa_time;
          break;
      }
      sssp->InitByEdges(n, v);
      std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
      long long newans = sssp->Do(0, n - 1);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      *timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
      if(ans != -1) {
        EXPECT_EQ(ans, newans);
      }
      ans = newans;
      delete sssp;
    }
  }

  cout << "DijkstraWithHeap:" << double(dijkstra_with_heap_time) / TEST_QUANTITY << '\n';
  cout << "BellmanFord:     " << double(bellman_ford_time) / TEST_QUANTITY << '\n';
  cout << "SPFA:            " << double(spfa_time) / TEST_QUANTITY << '\n';
}
