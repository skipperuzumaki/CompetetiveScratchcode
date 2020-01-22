#include <list> 
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>

using namespace std;

class Graph // TODO add jhonsons algo to replace floyd warshall
{
private:
	//For Kruskals
	class subset
	{
	public:
		int parent;
		int rank;
	}; 
	int find(subset subsets[], int i)
	{
		if (subsets[i].parent != i) {
			subsets[i].parent = find(subsets, subsets[i].parent);
		}
		return subsets[i].parent;
	} 
	void Union(subset subsets[], int x, int y)
	{
		int xroot = find(subsets, x);
		int yroot = find(subsets, y);
		if (subsets[xroot].rank < subsets[yroot].rank) {
			subsets[xroot].parent = yroot;
		}
		else if (subsets[xroot].rank > subsets[yroot].rank) {
			subsets[yroot].parent = xroot;
		}
		else
		{
			subsets[yroot].parent = xroot;
			subsets[xroot].rank++;
		}
	}
public:
	class Edge {
	public:
		int source;
		int dest;
		int weight;
		Edge operator =(const Edge& rhs) {
			source = rhs.source;
			dest = rhs.dest;
			weight = rhs.weight;
			return *this;
		}
		bool operator <(const Edge& rhs){
			return weight < rhs.weight;
		}
	};
	bool EgComp(const Edge* a, const Edge* b)
	{
		return a->weight > b->weight;
	}
private:
	// INT_MAX = Infinite for our purposes
	int V;
	list<int>* adj;
	vector<vector<int>> DistMat;
	vector<vector<int>> DjMat;
	vector<Edge> Edges;
	void DFSUtil(int v, bool visited[],vector<int>& ret);
	void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);
	void APUtil(int u, bool visited[], int disc[], int low[], int parent[], vector<bool>& ap, vector<pair<int,int>>& bridge);
	int minDistance(vector<int> dist, bool sptSet[]);
public:
	Graph(int V);
	void addEdge(int v, int w, int l = 0);
	vector<int> BFS(int s);
	vector<int> DFS(int v);
	stack<int> topologicalSort();
	pair<vector<bool>,vector<pair<int,int>>> ArticulationPoints();
	vector<int> dijkstra(int src);
	vector<vector<int>> floydWarshall();
	vector<Edge> Kruskal();
};

void Graph::DFSUtil(int v, bool visited[], vector<int>& ret)
{
	visited[v] = true;
	ret.push_back(v);
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		if (!visited[*i]) {
			DFSUtil(*i, visited, ret);
		}
	}
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
	visited[v] = true;
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		if (!visited[*i]) {
			topologicalSortUtil(*i, visited, Stack);
		}
	}
	Stack.push(v);
}

void Graph::APUtil(int u, bool visited[], int disc[], int low[], int parent[], vector<bool>& ap, vector<pair<int, int>>& bridge)
{
	static int time = 0;
	int children = 0;
	visited[u] = true;
	disc[u] = low[u] = ++time;
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;
		if (!visited[v])
		{
			children++;
			parent[v] = u;
			APUtil(v, visited, disc, low, parent, ap, bridge);
			low[u] = min(low[u], low[v]);
			if (parent[u] == -1 && children > 1) {
				ap[u] = true;
			}
			if (parent[u] != -1 && low[v] >= disc[u]) {
				ap[u] = true;
			}
			if (low[v] > disc[u]) {
				auto p = make_pair(u, v);
				bridge.push_back(p);
			}
		}
		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}
}

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
	vector<int> temp;
	for (int i = 0; i < V; i++) {
		temp.push_back(INT_MAX);
	}
	for (int i = 0; i < V; i++) {
		DistMat.push_back(temp);
		DjMat.push_back(temp);
	}
}

void Graph::addEdge(int v, int w,int l)
{
	adj[v].push_back(w);
	DistMat[v][w] = l;
	DjMat[v][w] = l;
	DjMat[w][v] = l;
	Edge e;
	e.source = v;
	e.dest = w;
	e.weight = l;
	Edges.push_back(e);
	
}

vector<int> Graph::BFS(int s)
{
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}
	list<int> queue;
	visited[s] = true;
	queue.push_back(s);
	list<int>::iterator i;
	vector<int> ret;
	while (!queue.empty())
	{
		s = queue.front();
		ret.push_back(s);
		queue.pop_front();
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
	return ret;
}

vector<int> Graph::DFS(int v)
{
	vector<int> ret;
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}
	DFSUtil(v, visited,ret);
	return ret;
}

stack<int> Graph::topologicalSort()
{
	stack<int> res;
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < V; i++) {
		if (visited[i] == false) {
			topologicalSortUtil(i, visited, res);
		}
	}
	return res;
}

pair<vector<bool>,vector<pair<int,int>>> Graph::ArticulationPoints()
{
	vector<bool> ap(V,false);
	vector<pair<int, int>> bridge;
	bool* visited = new bool[V];
	int* disc = new int[V];
	int* low = new int[V];
	int* parent = new int[V];

	// Initialize parent and visited, and ap(articulation point) arrays 
	for (int i = 0; i < V; i++)
	{
		parent[i] = -1;
		visited[i] = false;
		ap[i] = false;
	}

	// Call the recursive helper function to find articulation points 
	// in DFS tree rooted with vertex 'i' 
	for (int i = 0; i < V; i++) {
		if (visited[i] == false) {
			APUtil(i, visited, disc, low, parent, ap, bridge);
		}
	}
	auto p = make_pair(ap, bridge);
	return p;
}

int Graph::minDistance(vector<int> dist, bool sptSet[])
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v], min_index = v;
		}
	}
	return min_index;
}

vector<int> Graph::dijkstra(int src)
{
	vector<int> dist = vector<int>(V);
	bool* sptSet = new bool[V];
	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX, sptSet[i] = false;
	}
	dist[src] = 0;
	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(dist, sptSet);
		sptSet[u] = true; 
		for (int v = 0; v < V; v++)
			if (!sptSet[v] && DistMat[u][v] && dist[u] != INT_MAX
				&& dist[u] + DistMat[u][v] < dist[v])
				dist[v] = dist[u] + DistMat[u][v];
	}
	return dist;
}

inline vector<vector<int>> Graph::floydWarshall()
{
	vector<vector<int>> dist = DistMat;
	int i, j, k;
	for (k = 0; k < V; k++)
	{ 
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	return dist;
}

vector<Graph::Edge> Graph::Kruskal()
{
	vector<Edge> result(V);
	int e = 0; 
	int i = 0;  
	sort(Edges.begin(), Edges.end());

	// Allocate memory for creating V ssubsets  
	subset* subsets = new subset[(V * sizeof(subset))];

	// Create V subsets with single elements  
	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	// Number of edges to be taken is equal to V-1  
	while (e < V - 1 && i < Edges.size())
	{
		// Step 2: Pick the smallest edge. And increment  
		// the index for next iteration  
		Edge next_edge = Edges[i++];

		int x = find(subsets, next_edge.source);
		int y = find(subsets, next_edge.dest);

		// If including this edge does't cause cycle,  
		// include it in result and increment the index  
		// of result for next edge  
		if (x != y)
		{
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
		// Else discard the next_edge  
	}

	return result;
}
