#include "Graph.h"
#include "MatrixGraph.h"

// Creates a matrix with all weights equal to 0
MatrixGraph::MatrixGraph(unsigned num_nodes){
	num_edges = 0;
	for(int i = 0; i < num_nodes; i++){
		M.push_back(*new std::vector<EdgeWeight>());
		for(int j = 0; j < num_nodes; j++){
			M[i].push_back(0);
		}
	}
}

// The destructor! Because these are important and stuff.
MatrixGraph::~MatrixGraph(){
	for(int i = 0; i < M.size(); i++){
		for(int j = 0; j < M.size(); j++){
			M[i].pop_back();
		}
	}
}

// Adds a weighted edge between nodes u and v with the given weight
void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){
	if(u >= 0 && u < M.size() && v >= 0 && v < M.size() && u!= v && M[u][v] == 0 && M[v][u] == 0 && weight > 0){
		M[u][v] = weight;
		M[v][u] = weight;
		num_edges++;
	}
}

// Returns the weight of the edge between two nodes
EdgeWeight MatrixGraph::weight(NodeID u, NodeID v) const{
	if(u >= 0 && u < M.size() && v >= 0 && v < M.size()){
		return M[u][v];
	}
	else
		return 0;
}

// Returns a list of NodeID/EdgeWeight pairs adjacent to the edge;
// logic seen in marcusrm's MatrixGraph.cpp
std::list<NWPair> MatrixGraph::getAdj(NodeID u) const{
	if(u >= 0 && u < M.size()){
		EList* neighbors = new EList;
		for(int i = 0; i < M[u].size(); i++){
			NWPair cur(i, M[u][i]);
			if(cur.second != 0)
				neighbors->push_back(cur);
		}

		return *neighbors;
	}
}

// Returns the number of nodes neighboring node u
unsigned MatrixGraph::degree(NodeID u) const{
	if(u >= 0 && u < M.size()){
		return getAdj(u).size();
	}
}

// Returns the number of nodes in the graph
unsigned MatrixGraph::size() const{
	return M.size();
}

// Returns the number of edges in the graph
unsigned MatrixGraph::numEdges() const{
	return num_edges;
}