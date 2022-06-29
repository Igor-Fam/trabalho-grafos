#ifndef EDGE_H
#define EDGE_H

class Aresta{
    private:
        int id;
        Aresta* proxAresta;
        float peso;
        friend class No;
        
    public:
        Aresta(int id, float peso = 0);
        Aresta(){};
        ~Aresta(){};
        void addAresta(int id, float peso = 0);
        void printList();
};


#endif