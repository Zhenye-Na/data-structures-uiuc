/**
 * @file demo.cpp
 *
 * This file shows how the Graph class can be used.
 * Feel free to play around in this area!
 *
 * @author Sean Massung
 * @date Spring 2011
 *
 * Updated by Sean Massung for Spring 2012
 */

#include <iostream>
#include <string>
#include "graph.h"
#include "premade_graphs.cpp"

using std::string;
using std::cout;
using std::endl;

/**
 * Draws the three example graphs with weights.
 * All graphs saved as PNGs are in lab12/images/.
 */
void createPremadeGraphs()
{
    Graph us = PremadeGraphs::createUSMap(true);
    Graph europe = PremadeGraphs::createEuropeMap(true);
    Graph japan = PremadeGraphs::createJapanMap(true);

    // save PNGs
    us.savePNG("united-states-mst");
    europe.savePNG("europe");
    japan.savePNG("japan");

    // print to terminal
    cout << "\nDisplaying a graph of Europe...\n\n";
    europe.print();
}

/**
 * Create the US map without weights.
 */
void createUnweightedUS()
{
    Graph us_uw = PremadeGraphs::createUSMap(false);
    us_uw.savePNG("us-unweighted");
}

/**
 * Create and print a random weighted graph with
 *  9 vertices and random seed 777.
 */
void createRandomGraph()
{
    cout << "\nDisplaying a random graph...\n\n";
    Graph graph(true, 9, 777);
    graph.print();
    graph.savePNG("random-demo-graph");
}

/**
 * Build a graph by manually inserting vertices.
 */
void buildGraph()
{
    cout << "Displaying a manually created graph...\n\n";
    Graph graph(true);
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertEdge("A", "B");
    graph.insertEdge("A", "C");
    graph.setEdgeWeight("A", "B", 7);
    graph.setEdgeWeight("A", "C", 11);
    graph.setEdgeLabel("A", "C", "AN EDGE");
    graph.savePNG("built-graph");
    graph.print();
}

/**
 * Run all the different examples.
 */
int main()
{
    createPremadeGraphs();
    createUnweightedUS();
    createRandomGraph();
    buildGraph();
    return 0;
}
