#include <iostream>
#include <vector>
#include <fstream>

bool hamiltonRecursiveAdjacent(int pos, const std::vector<std::vector<bool>>& adjMatrix, std::vector<int>& path, std::vector<bool>& visited)
{
	if (pos == adjMatrix.size()) return adjMatrix[path[pos - 1]][0];

	for (int v = 0; v < adjMatrix.size(); v++)
	{
		if (adjMatrix[path[pos - 1]][v] && !visited[v])
		{
			path[pos] = v;
			visited[v] = true;
			
			if (hamiltonRecursiveAdjacent(pos + 1, adjMatrix, path, visited)) return true;

			visited[v] = false;
		}
	}
	return false;
}

bool hamiltonRecursiveSuccession(int pos, const std::vector<std::vector<int>>& succList, std::vector<int>& path, std::vector<bool>& visited)
{
	if (pos == succList.size())
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

			if (hamiltonRecursiveSuccession(pos + 1, succList, path, visited)) return true;

			visited[v] = false;
		}
	}
	return false;
}

bool eulerRecursiveAdjacent(int pos, int E, std::vector<std::vector<bool>>& adjMatrix, std::vector<int>& path)
{
	if (pos == E + 1) return path[pos - 1] == 0;

	for (int v = 0; v < adjMatrix.size(); v++)
	{
		if (adjMatrix[path[pos - 1]][v])
		{
			path[pos] = v;

			adjMatrix[path[pos - 1]][v] = false;
			adjMatrix[v][path[pos - 1]] = false;

			if (eulerRecursiveAdjacent(pos + 1, E, adjMatrix, path)) return true;

			adjMatrix[path[pos - 1]][v] = true;
			adjMatrix[v][path[pos - 1]] = true;
		}
	}
	return false;
}

bool eulerRecursiveSuccession(int pos, int E, std::vector<std::vector<int>>& succList, std::vector<int>& path)
{
	if (pos == E + 1) return path[pos - 1] == 0;

	for (int& v : succList[path[pos - 1]])
	{
		if (v != -1)
		{
			int t = v;
			path[pos] = t;

			v = -1;

			if (eulerRecursiveSuccession(pos + 1, E, succList, path)) return true;
			v = t;
		}
	}
	return false;
}

void initHamiltonAdjacent(const std::vector<std::vector<bool>>& adjMatrix)
{
	std::vector<int> path(adjMatrix.size(), -1);
	std::vector<bool> visited(adjMatrix.size(), false);

	path[0] = 0;
	visited[0] = true;

	std::cout << "Hamilton macierz sasiedztwa: " << (hamiltonRecursiveAdjacent(1, adjMatrix, path, visited) ? "Jest cykl" : "Nie ma cyklu") << std::endl;
}

void initHamiltonSuccession(const std::vector<std::vector<int>>& succList)
{
	std::vector<int> path(succList.size(), -1);
	std::vector<bool> visited(succList.size(), false);

	path[0] = 0;
	visited[0] = true;

	std::cout << "Hamilton lista skierowana: " << (hamiltonRecursiveSuccession(1, succList, path, visited) ? "Jest cykl" : "Nie ma cyklu") << std::endl;
}

void initEulerAdjacent(int E, std::vector<std::vector<bool>> adjMatrix)
{
	std::vector<int> path(E + 1, -1);
	path[0] = 0;

	std::cout << "Euler macierz sasiedztwa: " << (eulerRecursiveAdjacent(1, E, adjMatrix, path) ? "Jest cykl" : "Nie ma cyklu") << std::endl;
}

void initEulerSuccession(int E, std::vector<std::vector<int>> succList)
{
	std::vector<int> path(E + 1, -1);
	path[0] = 0;

	std::cout << "Euler lista skierowana: " << (eulerRecursiveSuccession(1, E, succList, path) ? "Jest cykl" : "Nie ma cyklu") << std::endl;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

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

	initHamiltonAdjacent(adjMatrix);
	initHamiltonSuccession(succList);
	initEulerAdjacent(E,adjMatrix);
	initEulerSuccession(E, succList);
}