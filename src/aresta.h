#ifndef EDGE_H
#define EDGE_H

#include <unordered_map>
#include <set>
#include "grafo.h"

using namespace std;

class Grafo;

class Aresta{
    private:
        int id;
        int id_origem;
        Aresta* proxAresta;
        float peso;
        friend class No;
        friend class Grafo;
        
    public:
        Aresta(int id, float peso = 0);
        Aresta(int id_origem, int id, float peso = 0);
        Aresta(){};
        ~Aresta(){};
        void addAresta(int id, float peso = 0);
        void printList();
        void fechoTransitivoDireto(set<int>* ftd, Grafo* g);
        bool fechoTransitivoIndireto(int id, Grafo* g, set<int>* fti, set<int>* nosVisitados);
};


#endif