//
// Created by Utilizador on 24/01/2022.
//

#include "Graph.h"
#define INF (INT_MAX/2)

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

void Graph::addEdge(int src, int dest, Weight weight, string line) {

    if (src<0 || src>n || dest<0 || dest>n) return;
    nodes[src].adj.push_back({dest, line, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, line, weight});
}

void Graph::addNode(int src, string name, string zone){
    nodes[src].name = name;
    nodes[src].zone = zone;
}

void Graph::dfs(int v) {
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

/**
 * Esta função permite fazer a pesquisa em largura no graph, pelo que permite aceder ao menor número
 * de paragens em que o utilizador tem que passar para chegar ao destino
 * @param v nó de origem
 * @return
 *
 * Complexidade temporal: O(|V| + |E|), sendo V -> número de nós e E -> número de arestas
 */
void Graph::bfs(int v) {
    for (int i=0; i<=n; i++) nodes[i].visited = false;
    queue<int> q;
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].visited = true;

    while (!q.empty()) {
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

/**
 * Esta função guarda o caminho do nó inicial até ao final de acordo com o número de paragens
 * @param v nó de origem
 * @param b nó de chegada
 * @return list<int> retorna a lista com os nós que pertencem ao caminho entre v e b
 *
 * Complexidade temporal: igual à do bfs()
 */
list<int> Graph::bfs_path(int v, int b){
    bfs(v);
    list<int> path;

    path.push_back(b);
    int i = b;
    while (i != v) {
        i = nodes[i].pred;
        path.push_front(i);
    }

    return path;
}

/**
 * Esta função retorna o caminho entre o nó inicial e final
 * @param a nó de origem
 * @param b nó de chegada
 * @return list<int> retorna uma lista com o caminho de menor distância entre a e b
 *
 * Complexidade temporal: igual à do dijkstra_dist()
 */
list<int> Graph::dijkstra_path_dist(int a, int b) {
    dijkstra_dist(a);
    list<int> path;
    if (nodes[b].dist == INF) return path;

    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

/**
 * Esta função retorna o caminho entre o nó inicial e o final de acordo com o menor número de vezes
 * em que há mudança de zona
 * @param a nó de origem
 * @param b nó de chegada
 * @return list<int> retorna uma lista com o caminho onde há menos mudanças de zona entre a e b
 *
 * Complexidade temporal: igual à do dijkstra_zone_change()
 */
list<int> Graph::dijkstra_path_zone(int a, int b) {
    dijkstra_zone_change(a);
    list<int> path;

    if (nodes[b].dist == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

/**
 * Esta função calcula a menor distância entre os nós do graph
 * @param s nó de origem
 * @return
 *
 * Complexidade temporal: O(|E| log|V|), sendo E -> número de arestas V -> número de nós, usando as
 * MinHeaps
 */
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
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight.dist;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }
}

/**
 * Esta função calcula o menor número de vezes que se muda de zona entre todos os nós
 * @param s nó de origem
 * @return
 *
 * Complexidade temporal: O(|E| log|V|), igual ao dijkstra_dist()
 */
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
