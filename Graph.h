//
// Created by Utilizador on 24/01/2022.
//

#ifndef AED2122_TRABALHO2_GRAPH_H
#define AED2122_TRABALHO2_GRAPH_H

#include <vector>
#include <map>
#include <list>
#include <algorithm>
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
        int dest;
        string line;
        Weight weight;
    };

    struct Node {
        list<Edge> adj;
        float dist;
        int pred;
        bool visited;
        string name;
        string zone;
    };

    int n;
    bool hasDir;
    public: vector<Node> nodes;

    void dijkstra(int s);

public:
    Graph(int nodes, bool dir = false);

    Graph();

    void addEdge(int src, int dest, Weight weight, string line);

    void addNode(int src, string name, string zone);

    void bfs(int v);
    list<int> bfs_path(int v, int b);

    void dfs(int v);
    float dijkstra_distance(int a, int b);
    list<int> dijkstra_path_dist(int a, int b);
    list<int> dijkstra_path_zone(int a, int b);
    void dijkstra_dist(int a);
    void dijkstra_zone_change(int s);

};


#endif //AED2122_TRABALHO2_GRAPH_H
