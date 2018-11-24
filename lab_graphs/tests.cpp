/**
 * @file tests.cpp
 * Contains code to test the functions in GraphTools.
 *
 * Written for CS 225 Spring 2011
 * @author Sean Massung
 *
 * Updated Spring 2012
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "graph.h"
#include "premade_graphs.cpp"
#include "graph_tools.h"

using std::vector;
using std::string;
using std::cerr;
using std::cout;
using std::endl;

/**
 * Show how to use the GraphTools tester.
 * @param programName - the name to display in the usage text
 */
void error(string programName)
{
    cerr << "\nusage: " << programName << " testType graphType" << endl
         << "\ttestType can be \"weight\", \"path\", or \"mst\"" << endl
         << "\tfor map graphs, graphType can be \"us\", \"europe\", or \"japan\"" << endl
         << "\tfor random graphs, graphType can be \"random\" and you can specify" << endl
         << "\t  the number of vertices and a random seed if wanted." << endl << endl
         << "example: test finding minimum weight on a graph of Europe:" << endl
         << "\t" << programName << " weight europe" << endl << endl
         << "example: test minimal spanning tree on a random graph:" << endl
         << "\t" << programName << " mst random" << endl << endl
         << "example: test shortest path on a random graph with 8 vertices and seed 777:" << endl
         << "\t" << programName << " path random 8 777" << endl << endl;
}

/**
 * Tests GraphTools::findMinWeight.
 * @param graph - the graph to run the test on
 * @param fileName- the prefix for the filename to save the graph
 */
void testMinWeight(Graph* graph, string fileName)
{
    int weight = GraphTools::findMinWeight(*graph);
    graph->savePNG("min-weight-" + fileName);
    graph->print();
    cout << "Minimum weight: " << weight << endl;
}

/**
 * Tests GraphTools::findShortestPath.
 * @param graph - the graph to run the test on
 * @param start - the vertex to find a path from
 * @param end - the vertex to find a path to
 * @param fileName- the prefix for the filename to save the graph
 */
void testShortestPath(Graph* graph, Vertex start, Vertex end, string fileName)
{
    int pathSize = GraphTools::findShortestPath(*graph, start, end);
    graph->savePNG("shortest-path-" + fileName);
    graph->print();
    cout << "Shortest path from " << start << " to " << end << ": " << pathSize
         << (pathSize == 1 ? " edge." : " edges.") << endl;
}

/**
 * Tests GraphTools::findMST.
 * @param graph - the graph to run the test on
 * @param fileName- the prefix for the filename to save the graph
 */
void testKruskal(Graph* graph, string fileName)
{
    GraphTools::findMST(*graph);
    graph->savePNG("kruskal-" + fileName);
    graph->print();
}

/**
 * Parses command line arguments and runs the appropriate test.
 */
int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 5) {
        error(argv[0]);
        return 1;
    }

    string test(argv[1]);
    string type(argv[2]);

    bool weighted = (test != "path");
    int numVertices = 9; // default for random graphs
    unsigned int seed;
    Graph* graph;

    // deduce graph type

    if (type == "us")
        graph = new Graph(PremadeGraphs::createUSMap(weighted));
    else if (type == "europe"){
        graph = new Graph(PremadeGraphs::createEuropeMap(weighted));
    }
    else if (type == "japan")
        graph = new Graph(PremadeGraphs::createJapanMap(weighted));
    else if (type == "random" && argc == 5) {
        std::istringstream(argv[3]) >> numVertices;
        std::istringstream(argv[4]) >> seed;
        graph = new Graph(weighted, numVertices, seed);
    } else if (type == "random" && argc == 3){
        graph = new Graph(weighted, 9, 777);
    }
    else
        error(argv[0]);

    // run appropriate test

    if (test == "weight")
        testMinWeight(graph, type);
    else if (test == "path" && type != "random") {
        Vertex start;
        Vertex end;
        if (type == "us")
        {
             start = "KansasCity";
             end = "WashingtonDC";
        }
        else if (type == "europe")
            {
                 start = "London";
                 end =  "Prague";
            }
        else if (type == "japan")
            {
                 start = "Nagoya";
                 end = "Hitachinaka";
            } 
        testShortestPath(graph, start, end, type);
    }
    else if (test == "path" && type == "random")
        {
            if (numVertices> 3)
                testShortestPath(graph,"0" , to_string(numVertices-2), type);
            else
                testShortestPath(graph,"0" , to_string(numVertices-1), type);
        }
    else if (test == "kruskal"){
        testKruskal(graph, type);
    }
    else {
        error(argv[0]);
        delete graph;
        return 1;
    }

    cout << "Tested " << test << " using graph " << type << endl;
    delete graph;
    return 0;
}
