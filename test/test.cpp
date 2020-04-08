#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <SPFA.h>
#include <chrono>
#include <AStar.h>
#include <AStarWithFibonacciHeap.h>
#include "DijkstraWithHeap.h"
#include "DijkstraWithFibonacciHeap.h"
#include "BellmanFord.h"
#include "DijkstraWithHeap.h"

using std::cout;
using std::endl;
using std::pair;

const int TEST_QUANTITY = 10;
const int MAP_SIZE = 50;
int N = 2000;
int m = 2e5;

TEST(SpeedTest, RandomDirectedGraph) {

  long long dijkstra_with_heap_time = 0;
  long long dijkstra_with_fibonacci_heap_time = 0;
  long long bellman_ford_time = 0;
  long long spfa_time = 0;

  for(int id = 0; id < TEST_QUANTITY - 1; ++id) {

    std::mt19937 generate_random(id);

    vector<pair<pair<int, int>, long long>> v;

    const int MAX_LENGTH = 1e6;

    for (int i = 0; i < m; ++i) {
      int s = (generate_random() % N + N) % N;
      int e = (generate_random() % N + N) % N;
      int l = (generate_random() % MAX_LENGTH + MAX_LENGTH ) % MAX_LENGTH + 1;
      v.push_back({{s, e}, l});
    }

    long long ans = -1;

    SSSP* sssp = nullptr;
    long long* timer = nullptr;
    for (int index = 0; index < 4; ++index) {
      switch (index) {
        case 0:
          sssp = new DijkstraWithHeap();
          timer = &dijkstra_with_heap_time;
          break;
        case 1:
          sssp = new DijkstraWithFibonacciHeap();
          timer = &dijkstra_with_fibonacci_heap_time;
          break;
        case 2:
          sssp = new BellmanFord();
          timer = &bellman_ford_time;
          break;
        case 3:
          sssp = new SPFA();
          timer = &spfa_time;
          break;
      }
      sssp->InitByEdgesDirected(N, v);
      std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
      long long newans = sssp->Do(0, N - 1);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      *timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
      if(ans != -1) {
        EXPECT_EQ(ans, newans);
      }
      ans = newans;
      delete sssp;
    }
  }

  cout << "DijkstraWithHeap         :" << double(dijkstra_with_heap_time) / TEST_QUANTITY << '\n';
  cout << "DijkstraWithFibonacciHeap:" << double(dijkstra_with_fibonacci_heap_time) / TEST_QUANTITY << '\n';
  cout << "BellmanFord              :" << double(bellman_ford_time) / TEST_QUANTITY << '\n';
  cout << "SPFA                     :" << double(spfa_time) / TEST_QUANTITY << '\n';
}

TEST(SpeedTest, RandomUndirectedGraph) {

  long long dijkstra_with_heap_time = 0;
  long long dijkstra_with_fibonacci_heap_time = 0;
  long long bellman_ford_time = 0;
  long long spfa_time = 0;

  for(int id = 0; id < TEST_QUANTITY - 1; ++id) {

    std::mt19937 generate_random(id);

    vector<pair<pair<int, int>, long long>> v;

    const int MAX_LENGTH = 1e4;

    for (int i = 0; i < m; ++i) {
      int s = (generate_random() % N + N) % N;
      int e = (generate_random() % N + N) % N;
      int l = (generate_random() % MAX_LENGTH + MAX_LENGTH ) % MAX_LENGTH + 1;
      v.push_back({{s, e}, l});
    }

    long long ans = -1;

    SSSP* sssp = nullptr;
    long long* timer = nullptr;
    for (int index = 0; index < 4; ++index) {
      switch (index) {
        case 0:
          sssp = new DijkstraWithHeap();
          timer = &dijkstra_with_heap_time;
          break;
        case 1:
          sssp = new DijkstraWithFibonacciHeap();
          timer = &dijkstra_with_fibonacci_heap_time;
          break;
        case 2:
          sssp = new BellmanFord();
          timer = &bellman_ford_time;
          break;
        case 3:
          sssp = new SPFA();
          timer = &spfa_time;
          break;
      }
      sssp->InitByEdgesUndirected(N, v);
      std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
      long long newans = sssp->Do(0, N - 1);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      *timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
      if(ans != -1) {
        EXPECT_EQ(ans, newans);
      }
      ans = newans;
      delete sssp;
    }
  }

  cout << "DijkstraWithHeap         :" << double(dijkstra_with_heap_time) / TEST_QUANTITY << '\n';
  cout << "DijkstraWithFibonacciHeap:" << double(dijkstra_with_fibonacci_heap_time) / TEST_QUANTITY << '\n';
  cout << "BellmanFord              :" << double(bellman_ford_time) / TEST_QUANTITY << '\n';
  cout << "SPFA                     :" << double(spfa_time) / TEST_QUANTITY << '\n';\
}


TEST(SpeedTest, RandomCityDirectedGraph) {

  long long dijkstra_with_heap_time = 0;
  long long dijkstra_with_fibonacci_heap_time = 0;
  long long a_star_time = 0;
  long long a_star_with_fibonacci_time = 0;
  long long bellman_ford_time = 0;
  long long spfa_time = 0;

  for(int id = 0; id < TEST_QUANTITY - 1; ++id) {

    std::mt19937 generate_random(id);

    vector<pair<pair<int, int>, long long>> v;

    auto x = new int[N];
    vector<int> x_col[MAP_SIZE];
    auto y = new int[N];
    vector<int> y_col[MAP_SIZE];

    for(int i = 0; i < N; ++i) {
      x[i] = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      y[i] = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      x_col[x[i]].push_back(i);
      y_col[y[i]].push_back(i);
    }

    for (int i = 0; i < m; ++i) {
      int col = -1;
      while(col == -1 or x_col[col].size() < 2) {
        col = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      }
      int s = (generate_random() % x_col[col].size() + x_col[col].size()) % x_col[col].size();
      int e = s;
      while(e == s) {
        e = (generate_random() % x_col[col].size() + x_col[col].size()) % x_col[col].size();
      }
      v.push_back({{x_col[col][s], x_col[col][e]}, std::abs(y[x_col[col][s]] - y[x_col[col][e]])});
      col = -1;
      while(col == -1 or y_col[col].size() < 2) {
        col = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      }
      s = (generate_random() % y_col[col].size() + y_col[col].size()) % y_col[col].size();
      e = s;
      while(e == s) {
        e = (generate_random() % y_col[col].size() + y_col[col].size()) % y_col[col].size();
      }
      v.push_back({{y_col[col][s], y_col[col][e]}, std::abs(x[y_col[col][s]] - x[y_col[col][e]])});
    }

    long long ans = -1;

    SSSP* sssp = nullptr;
    long long* timer = nullptr;
    for (int index = 0; index < 6; ++index) {
      switch (index) {
        case 0:
          sssp = new DijkstraWithHeap();
          timer = &dijkstra_with_heap_time;
          break;
        case 1:
          sssp = new DijkstraWithFibonacciHeap();
          timer = &dijkstra_with_fibonacci_heap_time;
          break;
        case 2:
          sssp = new AStar(N, x, y);
          timer = &a_star_time;
          break;
        case 3:
          sssp = new AStarWithFibonacciHeap(N, x, y);
          timer = &a_star_with_fibonacci_time;
          break;
        case 4:
          sssp = new BellmanFord();
          timer = &bellman_ford_time;
          break;
        case 5:
          sssp = new SPFA();
          timer = &spfa_time;
          break;
      }
      sssp->InitByEdgesDirected(N, v);
      std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
      long long newans = sssp->Do(0, N - 1);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      *timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
      if(ans != -1) {
        EXPECT_EQ(ans, newans);
      }
      ans = newans;
      delete sssp;
    }

    delete[] x;
    delete[] y;
  }

  cout << "DijkstraWithHeap         :" << double(dijkstra_with_heap_time) / TEST_QUANTITY << '\n';
  cout << "DijkstraWithFibonacciHeap:" << double(dijkstra_with_fibonacci_heap_time) / TEST_QUANTITY << '\n';
  cout << "AStar                    :" << double(a_star_time) / TEST_QUANTITY << '\n';
  cout << "AStarWithFibonacciHeap   :" << double(a_star_with_fibonacci_time) / TEST_QUANTITY << '\n';
  cout << "BellmanFord              :" << double(bellman_ford_time) / TEST_QUANTITY << '\n';
  cout << "SPFA                     :" << double(spfa_time) / TEST_QUANTITY << '\n';
}


TEST(SpeedTest, RandomCityUndirectedGraph) {

  long long dijkstra_with_heap_time = 0;
  long long dijkstra_with_fibonacci_heap_time = 0;
  long long a_star_time = 0;
  long long a_star_with_fibonacci_time = 0;
  long long bellman_ford_time = 0;
  long long spfa_time = 0;

  for(int id = 0; id < TEST_QUANTITY; ++id) {

    std::mt19937 generate_random(id);

    vector<pair<pair<int, int>, long long>> v;

    auto x = new int[N];
    vector<int> x_col[MAP_SIZE];
    auto y = new int[N];
    vector<int> y_col[MAP_SIZE];

    for(int i = 0; i < N; ++i) {
      x[i] = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      y[i] = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      x_col[x[i]].push_back(i);
      y_col[y[i]].push_back(i);
    }

    for (int i = 0; i < m; ++i) {
      int col = -1;
      while(col == -1 or x_col[col].size() < 2) {
        col = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      }
      int s = (generate_random() % x_col[col].size() + x_col[col].size()) % x_col[col].size();
      int e = s;
      while(e == s) {
        e = (generate_random() % x_col[col].size() + x_col[col].size()) % x_col[col].size();
      }
      v.push_back({{x_col[col][s], x_col[col][e]}, std::abs(y[x_col[col][s]] - y[x_col[col][e]])});
      col = -1;
      while(col == -1 or y_col[col].size() < 2) {
        col = (generate_random() % MAP_SIZE + MAP_SIZE) % MAP_SIZE;
      }
      s = (generate_random() % y_col[col].size() + y_col[col].size()) % y_col[col].size();
      e = s;
      while(e == s) {
        e = (generate_random() % y_col[col].size() + y_col[col].size()) % y_col[col].size();
      }
      v.push_back({{y_col[col][s], y_col[col][e]}, std::abs(x[y_col[col][s]] - x[y_col[col][e]])});
    }

    long long ans = -1;

    SSSP* sssp = nullptr;
    long long* timer = nullptr;
    for (int index = 0; index < 6; ++index) {
      switch (index) {
        case 0:
          sssp = new DijkstraWithHeap();
          timer = &dijkstra_with_heap_time;
          break;
        case 1:
          sssp = new DijkstraWithFibonacciHeap();
          timer = &dijkstra_with_fibonacci_heap_time;
          break;
        case 2:
          sssp = new AStar(N, x, y);
          timer = &a_star_time;
          break;
        case 3:
          sssp = new AStarWithFibonacciHeap(N, x, y);
          timer = &a_star_with_fibonacci_time;
          break;
        case 4:
          sssp = new BellmanFord();
          timer = &bellman_ford_time;
          break;
        case 5:
          sssp = new SPFA();
          timer = &spfa_time;
          break;
      }
      sssp->InitByEdgesUndirected(N, v);
      std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
      long long newans = sssp->Do(0, N - 1);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      *timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
      if(ans != -1) {
        EXPECT_EQ(ans, newans);
      }
      ans = newans;
      delete sssp;
    }

    delete[] x;
    delete[] y;
  }

  cout << "DijkstraWithHeap         :" << double(dijkstra_with_heap_time) / TEST_QUANTITY << '\n';
  cout << "DijkstraWithFibonacciHeap:" << double(dijkstra_with_fibonacci_heap_time) / TEST_QUANTITY << '\n';
  cout << "AStar                    :" << double(a_star_time) / TEST_QUANTITY << '\n';
  cout << "AStarWithFibonacciHeap   :" << double(a_star_with_fibonacci_time) / TEST_QUANTITY << '\n';
  cout << "BellmanFord              :" << double(bellman_ford_time) / TEST_QUANTITY << '\n';
  cout << "SPFA                     :" << double(spfa_time) / TEST_QUANTITY << '\n';
}
