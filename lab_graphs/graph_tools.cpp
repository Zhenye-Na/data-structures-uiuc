/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    queue<Vertex> traverse;
    int minWeight = INT_MAX;

    for (size_t i = 0; i < vertices.size(); i++)
        graph.setVertexLabel(vertices[i], "UNEXPLORED");

    for (size_t i = 0; i < edges.size(); i++)
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");

    Vertex v = graph.getStartingVertex();

    if (graph.getVertexLabel(v) == "UNEXPLORED") {
        graph.setVertexLabel(v, "VISITED");
        traverse.push(v);

        while (!traverse.empty()) {
            v = traverse.front();
            traverse.pop();

            vector<Vertex> adj = graph.getAdjacent(v);
            for (size_t i = 0; i < adj.size(); i++) {
                Vertex n = adj[i];

                if (graph.getVertexLabel(n) == "UNEXPLORED") {
                    graph.setEdgeLabel(v, n, "DISCOVERY");

                    if (graph.getEdgeWeight(v, n) < minWeight)
                        minWeight = graph.getEdgeWeight(v, n);

                    graph.setVertexLabel(n, "VISITED");
                    traverse.push(n);
                } else if (graph.getEdgeLabel(v, n) == "UNEXPLORED") {
                    if (graph.getEdgeWeight(v, n) < minWeight)
                        minWeight = graph.getEdgeWeight(v, n);

                    graph.setEdgeLabel(v, n, "CROSS");
                }
            }
        }
    }

    Edge e;
    for (size_t i = 0; i < edges.size(); i++) {
        e = edges[i];
        if (graph.getEdgeWeight(edges[i].source, edges[i].dest) == minWeight)
            break;
    }

    graph.setEdgeLabel(e.source, e.dest, "MIN");
    return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    queue<Vertex> traverse;
    unordered_map<Vertex, Vertex> parent;
    parent[start] = start;

    for (size_t i = 0; i < vertices.size(); i++)
        graph.setVertexLabel(vertices[i], "UNEXPLORED");

    for (size_t i = 0; i < edges.size(); i++)
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");

    Vertex v = start;

    if (graph.getVertexLabel(v) == "UNEXPLORED") {
        graph.setVertexLabel(v, "VISITED");
        traverse.push(v);

        while (!traverse.empty()) {
            v = traverse.front();
            traverse.pop();

            vector<Vertex> adj = graph.getAdjacent(v);
            for (size_t i = 0; i < adj.size(); i++) {
                Vertex n = adj[i];

                if (graph.getVertexLabel(n) == "UNEXPLORED") {
                    graph.setEdgeLabel(v, n, "DISCOVERY");

                    graph.setVertexLabel(n, "VISITED");
                    traverse.push(n);

                    parent[n] = v;
                } else if (graph.getEdgeLabel(v, n) == "UNEXPLORED")
                    graph.setEdgeLabel(v, n, "CROSS");

            }
        }
    }

    v = end;
    int dist = 0;

    while (v != start) {
        graph.setEdgeLabel(v, parent[v], "MINPATH");
        dist++;
        v = parent[v];
    }
    return dist;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    unordered_map<Vertex, int> map;
    DisjointSets dset;
    Vertex s, d;
    Edge e;

    std::sort(edges.begin(), edges.end());
    for (size_t i = 0; i < vertices.size(); i++)
        map[vertices[i]] = i;

    dset.addelements(vertices.size());

    for (size_t i = 0; i < edges.size(); i++) {
        e = edges[i];
        s = e.source;
        d = e.dest;

        if (dset.find(map[s]) != dset.find(map[d])) {
            dset.setunion(map[s], map[d]);
            graph.setEdgeLabel(s, d, "MST");
        }
    }
}
