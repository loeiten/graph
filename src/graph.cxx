#include "graph/graph.hxx"

#include <algorithm>
#include <deque>
#include <iterator>
#include <set>

using std::back_inserter;
using std::deque;
using std::find;
using std::set;

void Graph::AddEdge(int from_node, int to_node) {
  adjacency_map[from_node].push_back(to_node);
  adjacency_map[to_node].push_back(from_node);
}

void Graph::AddDiEdge(int from_node, int to_node) {
  adjacency_map[from_node].push_back(to_node);
}

const list<int> Graph::GetAdjacencyList(int node) const {
  // NOTE: The operator[] on std::map is marked as non-const, and cannot be used
  // in a const, hence we use .at()
  return adjacency_map.at(node);
}

bool Graph::IsLeaf(int node) const {
  if (adjacency_map.find(node) == adjacency_map.end()) {
    return true;
  }
  return false;
}

list<int> Graph::DFS(int from) const {
  // NOTE: The following must only be declared once
  map<int, bool> visited_map;
  for (auto& cur_pair : adjacency_map) {
    visited_map[cur_pair.first] = false;
  }
  map<int, bool>* visited_map_ptr = &visited_map;

  // NOTE: We add the starting node
  list<int> result{from};
  list<int>* result_ptr = &result;

  DFSRecurser(from, visited_map_ptr, result_ptr);

  return result;
}

void Graph::DFSRecurser(int node, map<int, bool>* visited_map_ptr,
                        list<int>* result_ptr) const {
  // The node is now visited
  (*visited_map_ptr)[node] = true;

  // Leave if leaf node
  if (IsLeaf(node)) {
    return;
  }
  // Loop through all the adjacent nodes of the current node
  // Note operator[] is not supported for constant map
  for (const auto& neighbour_node : adjacency_map.at(node)) {
    // Check if the neighbour_node exists in the visited_map
    if (!(*visited_map_ptr)[neighbour_node]) {
      // If it is not visited, visit it

      result_ptr->push_back(neighbour_node);
      DFSRecurser(neighbour_node, visited_map_ptr, result_ptr);
    }
  }
}

list<int> Graph::BFS(int from) const {
  // NOTE: The following must only be declared once
  map<int, bool> visited_map;
  for (auto& cur_pair : adjacency_map) {
    visited_map[cur_pair.first] = false;
  }

  // NOTE: We add the starting node and mark it as visited
  list<int> result{from};
  visited_map[from] = true;
  deque<int> bfs_queue;
  bfs_queue.push_back(from);

  while (!bfs_queue.empty()) {
    int cur_node = bfs_queue.back();
    bfs_queue.pop_back();
    // Continue if leaf node
    if (IsLeaf(cur_node)) {
      continue;
    }
    for (const auto& neighbour_node : adjacency_map.at(cur_node)) {
      if (!visited_map[neighbour_node]) {
        visited_map[neighbour_node] = true;
        result.push_back(neighbour_node);
        bfs_queue.push_back(neighbour_node);
      }
    }
  }
  return result;
}

int Graph::Distance(int from, int to) const {
  int distance = 0;
  map<int, bool> visited_map;
  for (auto& cur_pair : adjacency_map) {
    visited_map[cur_pair.first] = false;
  }

  // NOTE: We add the starting node and mark it as visited
  visited_map[from] = true;
  deque<int> bfs_queue;
  bfs_queue.push_back(from);

  while (!bfs_queue.empty()) {
    int cur_node = bfs_queue.back();

    if (cur_node == to) {
      return distance;
    }

    bfs_queue.pop_back();
    // FIXME: You are here - in digraph a leaf is only pointing back at prev
    // Continue if leaf node
    if (IsLeaf(cur_node)) {
      continue;
    }

    // Increase the distance
    ++distance;

    for (const auto& neighbour_node : adjacency_map.at(cur_node)) {
      if (!visited_map[neighbour_node]) {
        visited_map[neighbour_node] = true;
        bfs_queue.push_back(neighbour_node);
      }
    }
  }
  return -1;
}

// NOTE: Some duplication of DFS, maybe better way to reuse code?
bool Graph::IsCyclic() const {
  // NOTE: The following must only be declared once
  map<int, bool> visited_map;
  for (auto& cur_pair : adjacency_map) {
    visited_map[cur_pair.first] = false;
  }
  map<int, bool>* visited_map_ptr = &visited_map;

  bool cyclic = false;
  bool* cyclic_ptr = &cyclic;

  CyclicRecurser((*adjacency_map.begin()).first, (*adjacency_map.begin()).first,
                 visited_map_ptr, cyclic_ptr);

  return cyclic;
}

void Graph::CyclicRecurser(int node, int prev_node,
                           map<int, bool>* visited_map_ptr,
                           bool* cyclic_ptr) const {
  if (*cyclic_ptr) {
    // Cycle found, no need to continue
    return;
  }
  // The node is now visited
  (*visited_map_ptr)[node] = true;

  // Leave if leaf node
  if (IsLeaf(node)) {
    return;
  }
  // Loop through all the adjacent nodes of the current node
  for (const auto& neighbour_node : adjacency_map.at(node)) {
    // Check if the neighbour_node exists in the visited_map
    if (!(*visited_map_ptr)[neighbour_node]) {
      // If it is not visited, visit it
      CyclicRecurser(neighbour_node, node, visited_map_ptr, cyclic_ptr);
    } else if (neighbour_node != prev_node) {
      // Need to check if we just came from the node (in that case it has of
      // course been visited)

      // Cycle found, no need to continue
      *cyclic_ptr = true;
      return;
    }
  }
}

// NOTE: Some duplication of IsCyclic, maybe better way to reuse code?
set<set<int>> Graph::GetCycles() const {
  // NOTE: The following must only be declared once
  map<int, bool> visited_map;
  for (auto& cur_pair : adjacency_map) {
    visited_map[cur_pair.first] = false;
  }
  map<int, bool>* visited_map_ptr = &visited_map;

  set<int> cycle_start;
  set<int>* cycle_start_ptr = &cycle_start;

  GetCyclcesRecurser((*adjacency_map.begin()).first,
                     (*adjacency_map.begin()).first, visited_map_ptr,
                     cycle_start_ptr);

  set<set<int>> cycles;
  set<set<int>>* cycles_ptr = &cycles;

  deque<int> visited;
  deque<int>* visited_ptr = &visited;

  for (const auto& start : cycle_start) {
    TraceCycle(start, start, visited_ptr, cycles_ptr);
  }

  return cycles;
}

void Graph::GetCyclcesRecurser(int node, int prev_node,
                               map<int, bool>* visited_map_ptr,
                               set<int>* cycle_start_ptr) const {
  // The node is now visited
  (*visited_map_ptr)[node] = true;

  // Leave if leaf node
  if (IsLeaf(node)) {
    return;
  }
  // Loop through all the adjacent nodes of the current node
  for (const auto& neighbour_node : adjacency_map.at(node)) {
    // Check if the neighbour_node exists in the visited_map
    if (!(*visited_map_ptr)[neighbour_node]) {
      // If it is not visited, visit it
      GetCyclcesRecurser(neighbour_node, node, visited_map_ptr,
                         cycle_start_ptr);
    } else if (neighbour_node != prev_node) {
      // Need to check if we just came from the node (in that case it has of
      // course been visited)

      // Cycle found, add to cycles start
      cycle_start_ptr->insert(neighbour_node);
    }
  }
}

void Graph::TraceCycle(int node, int prev_node, deque<int>* visited_ptr,
                       set<set<int>>* cycles_ptr) const {
  // Add current node to the deque
  visited_ptr->push_back(node);

  // Leave if leaf node
  if (IsLeaf(node)) {
    return;
  }
  // Loop through all the adjacent nodes of the current node
  for (const auto& neighbour_node : adjacency_map.at(node)) {
    // Check if the neighbour_node exists in the visited_map
    if (find(visited_ptr->cbegin(), visited_ptr->cend(), neighbour_node) ==
        visited_ptr->cend()) {
      // If it is not visited, visit it
      TraceCycle(neighbour_node, node, visited_ptr, cycles_ptr);
    } else if (neighbour_node != prev_node) {
      // Need to check if we just came from the node (in that case it has of
      // course been visited)

      // Cycle found, start by adding the node where the cycle was found
      set<int> cycle{neighbour_node};
      // Reverse traverse until the area of locus (i.e. the node where the
      // cycle was found)
      for (auto current_node_it = visited_ptr->rbegin();
           *current_node_it != neighbour_node; ++current_node_it) {
        cycle.insert(*current_node_it);
      }
      cycles_ptr->insert(cycle);
    }
  }

  // Nothing more interesting with the current node, pop from queue
  visited_ptr->pop_back();
}
