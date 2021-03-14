#include <boost/test/unit_test.hpp>
#include <set>

#include "graph/graph.hxx"

using std::set;

BOOST_AUTO_TEST_SUITE(GetCyclesSimple)

BOOST_AUTO_TEST_CASE(get_cycles_simple) {
  Graph g;
  g.AddEdge(0, 1);
  BOOST_TEST(g.GetCycles() == set<set<int>>());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(GetCyclesChains)

BOOST_AUTO_TEST_CASE(get_cycles_di_chain) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(g.GetCycles() == set<set<int>>());
}

BOOST_AUTO_TEST_CASE(get_cycles_chain) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);

  BOOST_TEST(g.GetCycles() == set<set<int>>());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(GetCyclesVs)

BOOST_AUTO_TEST_CASE(get_cycles_di_v) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  BOOST_TEST(g.GetCycles() == set<set<int>>());
}

BOOST_AUTO_TEST_CASE(get_cycles_v) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  BOOST_TEST(g.GetCycles() == set<set<int>>());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(GetCyclesAcyclic)

BOOST_AUTO_TEST_CASE(get_cycles_dag) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(0, 2);

  g.AddDiEdge(1, 3);
  g.AddDiEdge(1, 4);

  g.AddDiEdge(2, 5);
  g.AddDiEdge(2, 6);
  g.AddDiEdge(2, 7);

  BOOST_TEST(g.GetCycles() == set<set<int>>());
}

BOOST_AUTO_TEST_CASE(get_cycles_ag) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);

  g.AddEdge(1, 3);
  g.AddEdge(1, 4);

  g.AddEdge(2, 5);
  g.AddEdge(2, 6);
  g.AddEdge(2, 7);

  BOOST_TEST(g.GetCycles() == set<set<int>>());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(GetCyclesCyclic)

BOOST_AUTO_TEST_CASE(get_cycles_dcg) {
  Graph g;
  g.AddDiEdge(0, 1);
  g.AddDiEdge(1, 2);
  g.AddDiEdge(2, 0);

  BOOST_TEST(g.GetCycles() == (set<set<int>>{set<int>{0, 1, 2}}));
}

BOOST_AUTO_TEST_CASE(get_cycles_cg) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  BOOST_TEST(g.GetCycles() == (set<set<int>>{set<int>{0, 1, 2}}));
}

// DELME
// FIXME: You are here: Also test cycle with leaf nodes
#include <iostream>
using std::cout;
using std::endl;

BOOST_AUTO_TEST_CASE(get_cycles_cg_big) {
  Graph g;
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);

  g.AddEdge(0, 3);
  g.AddEdge(3, 2);

  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 3);

  // DELME
  auto foo = g.GetCycles();
  for (const auto& cycle : foo) {
    cout << "{";
    for (const auto& node : cycle) {
      cout << node << ", ";
    }
    cout << "}" << endl;
  }

  BOOST_TEST(
      g.GetCycles() ==
      (set<set<int>>{set<int>{0, 1, 2}, set<int>{0, 1, 2, 3},
                     // set<int>{0, 1, 2, 3, 4, 5},  // 3 is a locus
                     // set<int>{0, 1, 2, 3, 5},  // Ends in a non-closed loop
                     set<int>{0, 2, 3},
                     // set<int>{0, 2, 3, 4, 5},  // 3 is a locus
                     // set<int>{0, 2, 3, 5},  // Ends in a non-closed loop
                     // set<int>{0, 3, 4, 5},  // Begins with a non-closed loop
                     // set<int>{2, 3, 4, 5},  // 3 is a locus
                     set<int>{3, 4, 5}}));
}

BOOST_AUTO_TEST_SUITE_END()
