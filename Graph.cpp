//
// Created by Utilizador on 24/01/2022.
//

#include "Graph.h"
#define INF (INT_MAX/2)

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, Weight weight, string line) {

    if (src<0 || src>n || dest<0 || dest>n) return;
    //cout<< "+ ";
    nodes[src].adj.push_back({dest, line, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, line, weight});
}

void Graph::addNode(int src, string name, string zone){
    nodes[src].name = name;
    nodes[src].zone = zone;
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Depth-First Search
void Graph::bfs(int v) {
    for (int i=0; i<=n; i++) nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist+1;
                nodes[w].pred = u;
            }
        }
    }
}

list<int> Graph::bfs_path(int v, int b){
    bfs(v);
    list<int> path;

    path.push_back(b);
    int i = b;
    while (i != v) {
        i = nodes[i].pred;
        path.push_front(i);
    }

    cout << path.size();
    return path;
}

float Graph::dijkstra_distance(int a, int b) {
    dijkstra_dist(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

list<int> Graph::dijkstra_path_dist(int a, int b) {
    dijkstra_dist(a);
    list<int> path;
    cout << " this happened!"<< endl;
    if (nodes[b].dist == INF) return path;

    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

list<int> Graph::dijkstra_path_zone(int a, int b) {
    dijkstra_zone_change(a);
    list<int> path;

    if (nodes[b].dist == INF) return path;
    cout << " this happened!"<< endl;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

// Dijkstra in O(|E| log |V|) using only the MinHeap that was given to you
void Graph::dijkstra_dist(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=0; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        /*if (nodes[u].dist == INF) {
            cout << "Stop " << u << " with dist = " << nodes[u].dist << endl;
        }
        cout << nodes[u].adj.size() <<endl;*/
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight.dist;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                //cout << w << " ";
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }
}

void Graph::dijkstra_zone_change(int s){
    MinHeap<int, int> q(n, -1);
    for (int v=0; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        //cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight.zone_change;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }
}
