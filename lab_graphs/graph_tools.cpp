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
    /* Your code here! */
    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());
    int MIN = edges[0].weight;
    for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); it++) { // Traverse around all edges of graph
        if (it->weight == MIN)
            graph.setEdgeLabel(it->source, it->dest, "MIN"); //Label the minimum edge as "MIN".
        else 
            graph.setEdgeLabel(it->source, it->dest, "UNEXPLORED");
    }
    return MIN;
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
    /* Your code here! */
    unordered_map<Vertex, vector<Vertex>> parent;
    unordered_map<Vertex, int> dis;
    vector<Vertex> vertices = graph.getVertices();
    for (Vertex v : vertices) {
        parent[v] = vector<Vertex>();
        dis[v] = 32767; // Initialize two maps
    }
    dis[start] = 0; 
    queue<Vertex> BFS; // Use BFS/queue to do traversal
    BFS.push(start);
    while (BFS.size() != 0) { 
        Vertex curr = BFS.front();
        vector<Vertex> neighbors = graph.getAdjacent(curr); 
        for (Vertex v : neighbors) { // Add all adjacent vertexes
            if (dis[curr] + 1 < dis[v]) {
                BFS.push(v);
                dis[v] = dis[curr] + 1; //This is the shortest path in terms of edges
                parent[v].push_back(curr); // Update parent and distance of vertex
            }
            if (dis[curr] + 1 == dis[v]) { // Find all paths with min distance
                parent[v].push_back(curr);
            }
        }
        BFS.pop();
    }
    setMINPATH(graph, end, parent); // Label each edge "MINPATH" if it is part of the minimum path 
    return dis[end];
}

// Helper function for findShortestPath to set MINPATH
void GraphTools::setMINPATH(Graph& graph, Vertex end, unordered_map<Vertex, vector<Vertex>>& parent) {
    if (parent[end].empty()) return;
    for (Vertex p : parent[end]) {
        // Label each edge "MINPATH" if it is part of the minimum path 
        graph.setEdgeLabel(p, end, "MINPATH"); 
        setMINPATH(graph, p, parent);
    }
    return;
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
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end()); // sort edges for Kruskal's algorithm
    vector<Vertex> vertices = graph.getVertices();
    unordered_map<Vertex, int> nums; // map Vertex to its index in vertices
    for (int i = 0; i < (int)vertices.size(); i++) {nums[vertices[i]] = i;}
    DisjointSets* dsets = new DisjointSets();
    dsets->addelements(vertices.size());
    for (Edge edge : edges) {
        int a = nums[edge.source], b = nums[edge.dest];
        if (dsets->find(a) != dsets->find(b)) {
            dsets->setunion(a, b);
            graph.setEdgeLabel(edge.source, edge.dest, "MST");
            //Label the edges of a minimal spanning tree as "MST" in the graph.
        }
    }
}

