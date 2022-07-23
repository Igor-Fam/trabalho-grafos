#ifndef EDGE_H
#define EDGE_H

#include <unordered_map>
#include <set>
#include "grafo.h"

using namespace std;

class Grafo;

class Aresta
{
private:
    int id_insercao;
    int id;
    int id_origem;
    Aresta *proxAresta;
    float peso;
    friend class No;
    friend class Grafo;

public:
    Aresta(int id,int id2, float peso);
    Aresta(int id, float peso = 0);
    Aresta(){};
    ~Aresta(){};
    void addAresta(int id, int arestas_inseridas,float peso = 0);
    void printList();
    void fechoTransitivoDireto(set<int> *ftd, Grafo *g);
    bool fechoTransitivoIndireto(int id, Grafo *g, set<int> *fti, set<int> *nosVisitados);
    void setId_insercao(int idInsercao) { this->id_insercao = idInsercao; };
    float getPeso(){return this->peso;};
    int getId(){return id;};
    int getIdOrigem() {return id_origem;};
};

#endif