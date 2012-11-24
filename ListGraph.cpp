#include "Graph.h"
#include "ListGraph.h"

// Creates a default list graph
ListGraph::ListGraph(int numNodes){
	num_edges = 0;
	edgeList = std::vector<EList>();
	for(int i = 0; i < numNodes; i++){
		edgeList.push_back(EList(NULL));
	}
}

// A lovely destructor
ListGraph::~ListGraph(){
	for(int i = 0; i < edgeList.size(); i++){
		  edgeList.pop_back();
	}
}

// Adds a weighted edge between nodes u and v with the given weight
void ListGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){
	bool duplicate = false;
	if(u >= 0 && u < edgeList.size() && v >= 0 && v < edgeList.size() && u!= v && weight > 0){
		for(std::list<NWPair>::const_iterator i = edgeList.at(u).begin(); i != edgeList.at(u).end(); i++){
			if(i->first == v && i->second == weight){
				duplicate = true;
			}
		}
		if (!duplicate){
			edgeList.at(u).push_back(NWPair(v,weight));
			edgeList.at(v).push_back(NWPair(u,weight));
			num_edges++;
		}
	}
}

// Returns the weight of the edge between two nodes
EdgeWeight ListGraph::weight(NodeID u, NodeID v) const{
	if(u >= 0 && u < edgeList.size() && v >= 0 && v < edgeList.size()){
		for(std::list<NWPair>::const_iterator i = edgeList.at(u).begin(); i != edgeList.at(u).end(); i++){
			if(i -> first == v){
				return i -> second;
			}
		}
	}
	return 0;
}

// Returns a list of NodeID/EdgeWeight pairs adjacent to the edge
std::list<NWPair> ListGraph::getAdj(NodeID u) const{
	if(u >= 0 && u < edgeList.size()){
		return edgeList.at(u);
	}
}

// Returns the number of nodes neighboring node u
unsigned ListGraph::degree(NodeID u) const{
	if(u >= 0 && u < edgeList.size()){
		return getAdj(u).size();
	}
}

// Returns the number of nodes in the graph
unsigned ListGraph::size() const{
	return edgeList.size();
}

// Returns the number of edges in the graph
unsigned ListGraph::numEdges() const{
	return num_edges;
}