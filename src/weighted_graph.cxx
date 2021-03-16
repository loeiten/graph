#include "graph/weighted_graph.hxx"

#include <limits>
#include <map>
#include <set>
#include <utility>

using std::make_pair;
using std::map;
using std::numeric_limits;
using std::set;

void WeightedGraph::AddEdge(int from_node, int to_node, double weight) {
  adjacency_map[from_node].push_back(to_node);
  adjacency_map[to_node].push_back(from_node);

  edge_weight[make_pair(from_node, to_node)] = weight;
  edge_weight[make_pair(to_node, from_node)] = weight;

  nodes.insert(from_node);
  nodes.insert(to_node);
}

void WeightedGraph::AddDiEdge(int from_node, int to_node, double weight) {
  adjacency_map[from_node].push_back(to_node);

  edge_weight[make_pair(from_node, to_node)] = weight;

  nodes.insert(from_node);
  nodes.insert(to_node);
}

int WeightedGraph::GetNodeWithMinDist(
    const set<int>& remaining_nodes,
    const map<int, double>& distance_to_node) const {
  double min_dist = numeric_limits<double>::infinity();
  double cur_dist = numeric_limits<double>::infinity();
  int node_with_lowest_distance = numeric_limits<int>::max();

  for (const auto& node : remaining_nodes) {
    cur_dist = distance_to_node.at(node);
    if (cur_dist <= min_dist) {
      node_with_lowest_distance = node;
      min_dist = cur_dist;
    }
  }
  return node_with_lowest_distance;
}

double WeightedGraph::Distance(int from, int to) const {
  // Fill the set of remaining_nodes, distance_to_node and prev_node
  set<int> remaining_nodes = nodes;
  map<int, double> distance_to_node;
  map<int, int> prev_node;
  double new_distance;  // Initialize new distanace
  for (const auto& cur_node : nodes) {
    distance_to_node[cur_node] = numeric_limits<double>::infinity();
    prev_node[cur_node] = numeric_limits<int>::max();
  }

  // The distance from a node to itself is 0
  distance_to_node[from] = 0.0;

  while (!remaining_nodes.empty()) {
    int cur_node = GetNodeWithMinDist(remaining_nodes, distance_to_node);

    remaining_nodes.erase(cur_node);

    if (cur_node == to) {
      return distance_to_node[cur_node];
    }

    if (adjacency_map.find(cur_node) == adjacency_map.end()) {
      // If the node has no connections we continue (as it has been erased from
      // the set another node will come out of GetNodeWithMinDist)
      continue;
    }

    for (const auto& neighbour_node : adjacency_map.at(cur_node)) {
      if (remaining_nodes.find(neighbour_node) == remaining_nodes.end()) {
        // Node already has a shortest path
        continue;
      }
      new_distance = distance_to_node.at(cur_node) +
                     edge_weight.at(make_pair(cur_node, neighbour_node));
      if (new_distance < distance_to_node.at(neighbour_node)) {
        distance_to_node.at(neighbour_node) = new_distance;
        prev_node.at(neighbour_node) = cur_node;
      }
    }
  }

  return -1.0;
}
