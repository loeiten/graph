#include <boost/test/unit_test.hpp>
#include <list>

#include "graph/graph.hxx"

using std::list;

BOOST_AUTO_TEST_SUITE(CreateGraph)

BOOST_AUTO_TEST_CASE(simple_edge) {
  Graph g;
  g.AddEdge(0, 2);
  BOOST_TEST(g.GetAdjacencyList(0) == list<int>{2});
}

BOOST_AUTO_TEST_SUITE_END()
