#include <iostream>
#include <vector>
#include <fstream>

bool hamiltonRecursiveAdjacent(int pos, int V, const std::vector<std::vector<bool>>& adjMatrix, std::vector<int>& path, std::vector<bool>& visited)
{
	if (pos == V)
	{
		if (adjMatrix[path[pos - 1]][0]) return true;
		return false;
	}

	for (int v = 0; v < V; v++)
	{
		if (adjMatrix[path[pos - 1]][v] && !visited[v])
		{
			path[pos] = v;
			visited[v] = true;
			
			if (hamiltonRecursiveAdjacent(pos + 1, V, adjMatrix, path, visited)) return true;

			visited[v] = false;
		}
	}
	return false;
}

bool hamiltonRecursiveSuccession(int pos, int V, const std::vector<std::vector<int>>& succList, std::vector<int>& path, std::vector<bool>& visited)
{
	if (pos == V)
	{
		for (int n : succList[path[pos - 1]])
		{
			if (n == 0) return true;
		}
		return false;
	}

	for (int v : succList[path[pos - 1]])
	{
		if (!visited[v])
		{
			path[pos] = v;
			visited[v] = true;

			if (hamiltonRecursiveSuccession(pos + 1, V, succList, path, visited)) return true;

			visited[v] = false;
		}
	}
	return false;
}

void initHamiltonAdjacent(int V, const std::vector<std::vector<bool>>& adjMatrix)
{
	std::vector<int> path(V, -1);
	std::vector<bool> visited(V, false);

	path[0] = 0;
	visited[0] = true;

	std::cout << "macierz sasiedztwa: " << (hamiltonRecursiveAdjacent(1, V, adjMatrix, path, visited) ? "Jest cykl" : "Nie ma cyklu");
}

void initHamiltonSuccession(int V, const std::vector<std::vector<int>>& succList)
{
	std::vector<int> path(V, -1);
	std::vector<bool> visited(V, false);

	path[0] = 0;
	visited[0] = true;

	std::cout << "skierowana lista: " << (hamiltonRecursiveSuccession(1, V, succList, path, visited) ? "Jest cykl" : "Nie ma cyklu") << std::endl;
}

int main()
{
	std::ifstream graphFile("graph.txt");

	int V, E;
	graphFile >> V >> E;

	std::vector<std::vector<bool>> adjMatrix(V, std::vector<bool>(V, false));
	std::vector<std::vector<int>> succList(V);
	
	for (int i = 0; i < E; i++)
	{
		int u, v;
		graphFile >> u >> v;

		adjMatrix[u][v] = true;
		adjMatrix[v][u] = true;

		succList[u].push_back(v);
	}

	initHamiltonAdjacent(V, adjMatrix);
	initHamiltonSuccession(V, succList);
}