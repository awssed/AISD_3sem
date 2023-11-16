#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define edge pair<int,int>

vector<pair<int, edge>> G; // graph
vector<pair<int, edge>> T; // mst
int V=8;
  int*  parent = new int[V];
void add(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}
bool compareSecondElement(const std::pair<int, edge>& a, const std::pair<int, edge>& b) {
    return a.first < b.first;
}
int findSet(int u) {
    if (parent[u]!=u) 
    {
        parent[u] = findSet(parent[u]);
    }
    return parent[u];
}

void unionSets(int u, int v) {
    for (int i = 0; i < V; i++) {
        if (parent[i] == v) {
            parent[i] = u;
        }
    }
}
void kraskal()
{
    sort(G.begin(), G.end(),compareSecondElement);
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < G.size(); i++) {
        int u = G[i].second.first;
        int v = G[i].second.second;
        int setU = findSet(u);
        int setV = findSet(v);
        if (setU != setV) {
            T.push_back(G[i]);
            unionSets(setU, setV);
        }
    }
}
void print() {
    cout << "Edge :" << " Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first + 1 << " - " << T[i].second.second + 1 << " : "
            << T[i].first;
        cout << endl;
    }
}
void main()
{
    add(0, 1, 2);
    add(0, 4, 2);
    add(0, 3, 8);
    add(1, 0, 2);
    add(1, 4, 5);
    add(1, 2, 3);
    add(2, 1, 3);
    add(2, 4, 12);
    add(2, 7, 7);
    add(3, 0, 8);

    add(3, 1, 10);
    add(3, 4, 14);
    add(3, 5, 3);
    add(4, 0, 2);
    add(4, 1, 5);
    add(4, 2, 12);
    add(4, 7, 8);
    add(4, 6, 4);
    add(4, 5, 11);
    add(4, 3, 14);
    add(5, 3, 3);
    add(5, 4, 11);
    add(5, 6, 6);
    add(6, 5, 6);
    add(6, 3, 1);
    add(6, 4, 4);
    add(6, 7, 9);
    add(7, 6, 9);
    add(7, 4, 8);
    add(7, 2, 7);
    kraskal();
    print();
}