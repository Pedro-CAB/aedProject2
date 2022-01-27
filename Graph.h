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

using namespace std;

class Graph {

    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        int dist;
        int idLine;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        int pred;       //Predecessor
        int idStop;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    map<string,int> StopIds;
    map<string,int> LineIds;

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);

    // Depth-First Search: example implementation
    void dfs(int v);

    // Breadth-First Search: example implementation
    void bfs(int v);

};


#endif //AED2122_TRABALHO2_GRAPH_H
