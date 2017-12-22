#pragma once

#include <vector>
#include <set>

using namespace std;

struct Path
{
	int length;
	set < pair<int, int> > chain;
};

struct Edge
{
	int to;
	int weight;
};



class Graph
{

	void remove(Path removable_item);
	void remove_all(Path removable_item);

	public:
		
		vector<vector<Edge>> graph;
		
		void RunDemo();
		Path FindShortest(int source, int dest);
		vector<Path> FindPathsNoOverlVertices(int source, int dest);
		vector<Path> FindPathsNoOverlEdges(int source, int dest);

		Graph() : graph({}) {};
		Graph(vector<vector<Edge>> x) : graph(x) {};
};