#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

class Graph
{
private:
    bool isDirected;
    Node* firstNode;
    bool nodeExists(int id);
public:
    Graph(){ firstNode = nullptr; };
    ~Graph(){};
    void addEdge(int id1, int id2, float weight = 0);
    void addNode(int id, float weight = 0);
    void printGraph();
};

#endif