#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> used;

const int INF = numeric_limits<int>::max();//Бесконечность
struct Edge
{
	int destination;
	int weight;
};

void Dikstra(vector<vector<Edge>>& graph, int source, vector<int>& distance)
{
	int n = graph.size();
	vector < bool > visited(n,false);
	distance.assign(n, INF);
	distance[source] = 0;
	// Поиск кратчайших путей
	for (int i = 0; i < n - 1; i++)
	{
		int minDistance = INF;
		int minVert = -1;
		// Находим вершину с наименьшим расстоянием среди непосещенных вершин
		for (int v = 0; v < n; v++)
		{
			if (!visited[v] && distance[v] < minDistance)
			{
				minDistance = distance[v];
				minVert = v;
			}
		}
		visited[minVert] = true;
		for (Edge& edge : graph[minVert])
		{
			int v = edge.destination;
			int weight = edge.weight;
			if (!visited[v] && distance[minVert] != INF && distance[minVert] + weight < distance[v])
			{
				distance[v] = distance[minVert] + weight; // Обновляем расстояния до смежных вершин
			}
		}
	}
}

void main()
{
	setlocale(LC_ALL, "rus");
	vector<vector<Edge>> graph(9);
	graph[0].push_back({ 1,7 });
	graph[0].push_back({ 2,10 });
	graph[1].push_back({ 0,7 });
	graph[1].push_back({ 6,27 });
	graph[1].push_back({ 5 ,9 });
	graph[2].push_back({ 0,10 });
	graph[2].push_back({ 5,8 });
	graph[2].push_back({ 4,31 });
	graph[3].push_back({ 4,32 });
	graph[3].push_back({ 7,17 });
	graph[3].push_back({ 8,21 });
	graph[4].push_back({ 2,31 });
	graph[4].push_back({ 3,32 });
	graph[5].push_back({ 2,8 });
	graph[5].push_back({ 1,9 });
	graph[5].push_back({ 7,11 });
	graph[6].push_back({ 1,27 });
	graph[6].push_back({ 8,15 });
	graph[7].push_back({ 5,11 });
	graph[7].push_back({ 3,17 });
	graph[7].push_back({ 8,15 });
	graph[8].push_back({ 3,21 });
	graph[8].push_back({ 7,15 });
	graph[8].push_back({ 6,15 });
	int start = 5;
	vector<int> distance(9);
	Dikstra(graph, start, distance);
	for (int i = 0; i < 9; ++i) {
		cout << "Расстояние от вершины " << start << " до " << i << ": " << distance[i] << endl;
	}
}