//Graph header file

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

// A graph is a collection of nodes and edges, where each edge connects two nodes and has a weight (which can represent the strength of the connection between the nodes)
// It's a useful and flexible mathematical abstraction that can be used to model a wide variety of systems and relationships, such as social networks, transportation networks, and many other types of complex systems.

// define the structure for the graph(edges and nodes)


//Define the edges
struct Edge {
    int neighbor_index;// to keep track of which node this edge is connecting to
    float weight;// time distance in our case, but could be any measure of similarity or connection strength between the nodes
};

//Define the nodes
struct Node {
    float timestamp;// the timestamp of the onset in seconds, which will be used to determine the position of the node in the graph
    std::vector<float> chroma_vector;// the chroma vector associated with the onset, which will be used to calculate the weights of the edges connecting this node to other nodes in the graph
    std::vector<Edge> edges;
};

#endif // GRAPH_H