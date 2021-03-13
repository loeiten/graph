#include <boost/test/unit_test.hpp>
#include <exception>
#include <list>

#include "graph/graph.hxx"

using std::list;
using std::out_of_range;

BOOST_AUTO_TEST_SUITE(CreateGraph)

BOOST_AUTO_TEST_CASE(simple_edge) {
  Graph g;
  g.AddEdge(0, 1);
  BOOST_TEST(g.GetAdjacencyList(0) == list<int>{1});
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(Chains)

BOOST_AUTO_TEST_CASE(di_chain) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddEdge(1, 2);
  BOOST_TEST(g.GetAdjacencyList(0) == list<int>{1});
  BOOST_TEST(g.GetAdjacencyList(1) == list<int>{2});
  BOOST_TEST(g.GetAdjacencyList(2) == list<int>{1});
}

BOOST_AUTO_TEST_CASE(chain) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  BOOST_TEST(g.GetAdjacencyList(0) == list<int>{1});
  // NOTE: Extra parantheses needed for list initializer with several elements
  BOOST_TEST(g.GetAdjacencyList(1) == (list<int>{0, 2}));
  BOOST_TEST(g.GetAdjacencyList(2) == list<int>{1});
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(Vs)

BOOST_AUTO_TEST_CASE(di_v) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);
  BOOST_TEST(g.GetAdjacencyList(0) == (list<int>{1, 2}));
  // NOTE: 1 and 2 are leaf nodes, and are not pointing to anything
  BOOST_CHECK_THROW(g.GetAdjacencyList(1), out_of_range);
  BOOST_CHECK_THROW(g.GetAdjacencyList(2), out_of_range);
}

BOOST_AUTO_TEST_CASE(v) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  BOOST_TEST(g.GetAdjacencyList(0) == (list<int>{1, 2}));
  BOOST_TEST(g.GetAdjacencyList(1) == (list<int>{0}));
  BOOST_TEST(g.GetAdjacencyList(2) == (list<int>{0}));
}

BOOST_AUTO_TEST_SUITE_END()
