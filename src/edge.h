#ifndef EDGE_H
#define EDGE_H

class Edge{
    private:
        int id;
        Edge* nextEdge;
        float weight;
        friend class Node;
        
    public:
        Edge(int id, float weight = 0);
        Edge(){};
        ~Edge(){};
        void addEdge(int id, float weight = 0);
        void printList();
};


#endif