//
// Created by Utilizador on 24/01/2022.
//

#ifndef AED2122_TRABALHO2_GRAPH_H
#define AED2122_TRABALHO2_GRAPH_H

#include <vector>
#include <map>
#include <list>
#include <queue>
#include <iostream>

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Graph {

    struct Weight{
        float dist;
        int zone_change;
    };

    struct Edge {
        int dest;   // Destination node
        string line;
        Weight weight;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        string name;
        string zone;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    public: vector<Node> nodes; // The list of nodes being represented

    void dijkstra(int s);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, Weight weight);

    void bfs(int v);

    void dfs(int v);

    // ----- Functions to implement in this class -----
    float dijkstra_distance(int a, int b);
    list<int> dijkstra_path_dist(int a, int b);
    void dijkstra_dist(int a);

    void dijkstra_zone_change(int s);

};


#endif //AED2122_TRABALHO2_GRAPH_H
