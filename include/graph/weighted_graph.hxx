#ifndef INCLUDE_GRAPH_WEIGHTED_GRAPH_HXX_
#define INCLUDE_GRAPH_WEIGHTED_GRAPH_HXX_

#include <deque>
#include <list>
#include <map>
#include <set>
#include <utility>

#include "graph/graph.hxx"

using std::deque;
using std::list;
using std::map;
using std::pair;
using std::set;

/**
 * Class contiaining graph with weigths
 */
class WeightedGraph : public Graph {
 public:
  /**
   * Default constructor
   */
  WeightedGraph() {}

  /**
   * Connect two nodes in the graph in an undirected way
   *
   * \param from_node The node to create the edge from
   * \param to_node The node to create the edge to
   * \param weight The weight of the edge (both directions)
   */
  void AddEdge(int from_node, int to_node, double weight = 1.0);

  /**
   * Connect two nodes in the graph in a directed way
   *
   * \param from_node The node to create the edge from
   * \param to_node The node to create the edge to
   * \param weight The weight of the edge (one direction)
   */
  void AddDiEdge(int from_node, int to_node, double weight = 1.0);

  /**
   * Find shortest path in unweighted graph using Dijkstra's algorithm
   *
   * Returns inf if node is not found
   *
   * \param from Node to start the search from
   * \param to Node to end the search at
   * \return The distance between the input
   */
  double Distance(int from, int to) const;

 private:
  map<pair<int, int>, double> edge_weight; /**< The map of weights */
  set<int> nodes;                          /**< A set of all the nodes */

  /**
   * Return the node with the shortest distance
   *
   *
   * \param remaining_nodes Set of nodes which has not been returned from this
   * function \param distance_to_node Distance to nodes as measured from the
   * initial node \return The distance between the input
   */
  int GetNodeWithMinDist(const set<int>& remaining_nodes,
                         const map<int, double>& distance_to_node) const;
};

#endif  // INCLUDE_GRAPH_WEIGHTED_GRAPH_HXX_
