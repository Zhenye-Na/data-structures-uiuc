#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "catchlib.h"

#include "../graph.h"
#include "../graph_tools.h"
#include <iostream>
#include <string>

using namespace std;

TEST_CASE("minWeight_OneEdge_ReturnValue", "[weight=5]") {
     Graph graph(true, 13, 1234);
     int minWeight = GraphTools::findMinWeight(graph);
     REQUIRE(minWeight == 69);
}

TEST_CASE("minWeight_OneEdge_EdgeLabel", "[weight=5]") {
    Graph graph(true, 13, 1234);
    GraphTools::findMinWeight(graph); // ignore return value
    REQUIRE(graph.getEdgeLabel("0", "5") == "MIN");
}

TEST_CASE("minWeight_MultiEdge_ReturnValue", "[weight=10]") {
    Graph graph(true, 12, 29347);
    int minWeight = GraphTools::findMinWeight(graph);
    REQUIRE(minWeight == 34);
}

TEST_CASE("minWeight_MultiEdge_EdgeLabels", "[weight=10]") {
    Graph graph(true, 12, 29347);
    GraphTools::findMinWeight(graph); // ignore return value
    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());
    vector<Edge>::iterator nonMinEdge;
    vector<Edge>::iterator minEdge = edges.begin();
    
    CHECK(minEdge->getLabel() == "MIN");
    for(nonMinEdge = edges.begin() + 1; nonMinEdge != edges.end(); ++nonMinEdge)
    {
        if (nonMinEdge->getLabel() == "")
	    FAIL("Did not label edges.");
	else
      CHECK(nonMinEdge->getLabel() != "MIN");
    }
}

TEST_CASE("minPath_OneEdge_ReturnValue", "[weight=5]")
{
    Graph graph(false, 2, 756);
    REQUIRE(GraphTools::findShortestPath(graph, "0", "1") == 1);
}

//  minPath - one edge - edge label
TEST_CASE("minPath_OneEdge_EdgeLabel", "[weight=5]")
{
    Graph graph(false, 2, 756);
    GraphTools::findShortestPath(graph, "0", "1"); // ignore return value
    REQUIRE(graph.getEdgeLabel("0", "1") == "MINPATH");
}

//  minPath - multiple edges - return value
TEST_CASE("minPath_MultiEdge_ReturnValue", "[weight=10]")
{
    // there is only one minpath for this graph from 6 to 4:
    //  edges (6,9) (9,3) (3,8) (8,4): 6 -> 9 -> 3 -> 8 -> 4
    Graph graph(false, 10, 324621);
    REQUIRE(GraphTools::findShortestPath(graph, "6", "4") == 4);
}

bool edge_is( Edge & e, unsigned s, unsigned d ) {
    return (e.source == to_string(s) && e.dest == to_string(d)) || (e.dest == to_string(s) && e.source == to_string(d));
    }

//  minPath - multiple edges - edge labels

TEST_CASE("minPath_MultiEdge_EdgeLabels", "[weight = 10]")
{
    // there is only one minpath for this graph from 6 to 4:
    Graph graph(false, 10, 10);
    GraphTools::findShortestPath(graph, "0", "9"); // ignore return value
    vector<Edge> edges = graph.getEdges();
    vector<Edge>::iterator edge;
    for(edge = edges.begin(); edge != edges.end(); ++edge)
    {
        if(!edge_is(*edge, 9, 1) && !edge_is(*edge, 1, 0))
            REQUIRE(edge->getLabel() != "MINPATH");
        else
            REQUIRE(edge->getLabel() == "MINPATH");
    }
    }

//  Test Kruskal's

bool edge_eq( Edge & e, unsigned s, unsigned d ) {
    return (e.source == to_string(s) && e.dest == to_string(d)) || (e.dest == to_string(s) && e.source == to_string(d));
    }

TEST_CASE("kruskal_all", "[weight = 15]")
{
    // there are no duplicate weights in this graph
    //  (i.e., there is only one solution)
    Graph graph(true, 10, 61);
    GraphTools::findMST(graph);
    vector<Edge> edges = graph.getEdges();
    vector<Edge>::iterator edge;
    for(edge = edges.begin(); edge != edges.end(); ++edge)
    {
        // if the edge is NOT in the MST
        if( edge_eq(*edge, 6, 9) || edge_eq(*edge, 9, 5) ||
            edge_eq(*edge, 5, 8) || edge_eq(*edge, 8, 9)
          )
        {
            if (edge->getLabel() == "MST") 
		FAIL("labeled \"MST\" on non-MST edge");
	}
        else if(edge->getLabel() != "MST")
        {
            // this is *is* on the MST
	    FAIL("did not label \"MST\" on minimum spanning tree edge");
        }
    }
}

