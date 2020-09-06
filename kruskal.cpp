#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
 
#define edge pair<int,int>
 
class Graph {
private:
    vector<pair<int, edge> > G; // graph
    vector<pair<int, edge> > T; // mst
    int *parent; //указатель на массив родителей (корневых вершин)
    int V; // number of vertices/nodes in graph
public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void printT();
    void printG();
};
Graph::Graph(int V) {
    parent = new int[V];
 
    //i 0 1 2 3 4 5
    //parent[i] 0 1 2 3 4 5
    for (int i = 0; i < V; i++)
        parent[i] = i;
 
    G.clear();
    T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent
        return find_set(parent[i]);
}
 
void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}
void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end()); // increasing weight
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]); // add to tree
            union_set(uRep, vRep);
        }
    }
}
void Graph::printT() {
    cout << "Edge :" << " Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : "
                << T[i].first;
        cout << endl;
    }
}
void Graph::printG() {
    cout << "Edge :" << " Weight" << endl;
    for (int i = 0; i < G.size(); i++) {
        cout << G[i].second.first << " - " << G[i].second.second << " : "
                << G[i].first;
        cout << endl;
    }
}
int main() {
    int n;
     cout << "Write the number of the cities: "; 
     cin >> n; 
    //n = 1000;
    Graph g(n);
    std::srand(unsigned(std::time(0)));
    for (int i=0;i<n;i++) {
        for (int j=i;j<n;j++) {
            if (i!=j) {
            int way = rand()%200;
                g.AddWeightedEdge(i,j,way);
                g.AddWeightedEdge(j,i,way);
        }
    }
}   
    cout << endl;
    cout << "Initial graph:" <<endl;
    g.printG();
    g.kruskal();
    cout << endl;
    cout << "Minimum spanning tree:" << endl;
    g.printT();
    return 0;
}
