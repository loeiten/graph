#include <boost/test/unit_test.hpp>

#include "graph/graph.hxx"

BOOST_AUTO_TEST_SUITE(CyclicCheckSimple)

BOOST_AUTO_TEST_CASE(cyclic_check_simple) {
  Graph g;
  g.AddEdge(0, 1);

  BOOST_TEST(!g.IsCyclic());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(CyclicCheckChains)

BOOST_AUTO_TEST_CASE(cyclic_check_di_chain) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(!g.IsCyclic());
}

BOOST_AUTO_TEST_CASE(cyclic_check_chain) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(!g.IsCyclic());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(CyclicCheckVs)

BOOST_AUTO_TEST_CASE(cyclic_check_di_v) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  BOOST_TEST(!g.IsCyclic());
}

BOOST_AUTO_TEST_CASE(cyclic_check_v) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  BOOST_TEST(!g.IsCyclic());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(CyclicCheckAcyclic)

BOOST_AUTO_TEST_CASE(cyclic_check_dag) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  g.AddDiEdge(1, 3);
  g.AddDiEdge(1, 4);

  g.AddDiEdge(2, 5);
  g.AddDiEdge(2, 6);
  g.AddDiEdge(2, 7);

  BOOST_TEST(!g.IsCyclic());
}

BOOST_AUTO_TEST_CASE(cyclic_check_ag) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  g.AddEdge(1, 3);
  g.AddEdge(1, 4);

  g.AddEdge(2, 5);
  g.AddEdge(2, 6);
  g.AddEdge(2, 7);

  BOOST_TEST(!g.IsCyclic());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(CyclicCheckCyclic)

BOOST_AUTO_TEST_CASE(cyclic_check_dcg) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(1, 2);
  g.AddDiEdge(2, 0);

  BOOST_TEST(g.IsCyclic());
}

BOOST_AUTO_TEST_CASE(cyclic_check_cg) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  BOOST_TEST(g.IsCyclic());
}

BOOST_AUTO_TEST_CASE(cyclic_check_cg_big) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  g.AddEdge(0, 3);
  g.AddEdge(3, 2);

  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 3);

  BOOST_TEST(g.IsCyclic());
}

BOOST_AUTO_TEST_SUITE_END()
