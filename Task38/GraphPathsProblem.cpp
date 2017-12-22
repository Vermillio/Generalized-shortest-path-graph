#include "GraphPathsProblem.h"
#include <set>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

void Print(Path printable)
{
	cout << "Distance: " << printable.length << endl;
	cout << "Path: { ";
	for (auto it : printable.chain)
		cout << it.first << "-" << it.second << " ";
	cout << "}" << endl;
}

void Print(vector<Path> printable)
{
	int i = 0;
	for (auto it1 : printable)
	{
		cout << "Path " << i << ": " << endl;
		cout << "Distance: " << it1.length << endl;
		cout << "Path: { ";
		for (auto it2 : it1.chain)
			cout << it2.first << "-" << it2.second << " ";
		cout << "}" << endl;
	}
}

void Graph::RunDemo()
{
	vector<vector<Edge>> input;
	int v, e, w;
	cout << "Enter vertices: " << endl;
	while (cin >> v)
	{
		cout << "Enter edges and weights: " << endl;
		while (cin >> e && cin >> w)
		{
			graph.resize(max((int)graph.size(), max(e, v) + 1));
			graph[v].push_back({ e, w });
			cout << endl;
		}
		fflush(stdin);
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	fflush(stdin);
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	int src, dest;
	cout << "Enter source: " << endl;
	cin >> src;
	cout << "Enter destination: " << endl;
	cin >> dest;

	Path shortest = FindShortest(src, dest);
	cout << "<<SHORTEST>>" << endl;
	Print(shortest);

	cout << "<<ALL PATHS WITH NO OVERLAPPING EDGES>>";
	vector<Path> NoE = FindPathsNoOverlEdges(src, dest);
	Print(NoE);

	cout << "<<ALL PATHS WITH NO OVERLAPPING VERTEXES>>";
	vector<Path> NoV = FindPathsNoOverlEdges(src, dest);
	Print(NoV);
}

Path Graph::FindShortest(int source, int dest)
{
	vector<int> min_distance(graph.size(), INT_MAX);
	min_distance[source] = 0;
	Path Shortest;
	set<pair<int, int>> active_vertices;
	active_vertices.insert( { 0, source } );
	Shortest.chain.insert({ 0, source });
	int i = 0;
	while (!Shortest.chain.empty())
	{
		int where = active_vertices.begin()->second;
		
		if (where == dest)
		{
			i++;
			Shortest.chain.insert({ i, where });
			Shortest.length = min_distance[where];
			return Shortest;
		}
		
		active_vertices.erase(active_vertices.begin());
		
		for (auto ed : graph[where])
			if (min_distance[ed.to] > min_distance[where] + ed.weight) 
			{
				active_vertices.erase({ min_distance[ed.to], ed.to });
				Shortest.chain.erase({ i, ed.to });
				min_distance[ed.to] = min_distance[where] + ed.weight;
				active_vertices.insert({min_distance[ed.to], ed.to });
				i++;
				Shortest.chain.insert({ i, ed.to });

			}
	}
	return Path({ 0, {} }); //path doesn't exist
}

void Graph::remove(Path removable_item)
{
	for (auto it : removable_item.chain)
		graph[it.first].erase(graph[it.first].begin() + it.second);
}

void Graph::remove_all(Path removable_item)
{
	for (auto it : removable_item.chain)
		graph[it.first].erase(graph[it.first].begin(), graph[it.first].end());
}

vector<Path> Graph::FindPathsNoOverlVertices(int source, int dest)
{
	Graph graph_copy(graph);
	vector<Path> solution;
	Path current;
	while (true)
	{
		current = graph_copy.FindShortest(source, dest);
		if (current.length == 0 && current.chain.empty())
			return solution;
		solution.push_back(current);
		graph_copy.remove_all(*(solution.end() - 1));
	}
	return solution;
}

vector<Path> Graph::FindPathsNoOverlEdges(int source, int dest)
{
	Graph graph_copy(graph);
	vector<Path> solution;
	Path current;
	while (true)
	{
		current = graph_copy.FindShortest(source, dest);
		if (current.length == 0 && current.chain.empty())
			return solution;
		solution.push_back(current);
		graph_copy.remove(*(solution.end() - 1));
	}
	return solution;
}

