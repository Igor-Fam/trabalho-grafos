#ifndef NODE_H
#define NODE_H

#include "edge.h"

class Node
{
private:
    int id;
    float weight;
    Edge* firstEdge;
    Node* nextNode;
    bool nodeExists(int id);
    friend class Graph;

public:
    Node(int id, float weight = 0);
    Node(){};
    ~Node(){};
    void addEdge(int id1, int id2, float weight = 0);
    void addNode(int id, float weight = 0);
    void printEdgeList();
};

#endif