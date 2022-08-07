#ifndef GRAPH_H
#define GRAPH_H

#include "no.h"
#include <unordered_map>
#include <list>
#include <ostream>
#include <iostream>

using namespace std;

class No;
class Aresta;

class Grafo
{
private:
    bool direcionado;
    No* primeiroNo;
    unordered_map <int, No*> mapa;
    bool noExiste(int id);
    friend class Aresta;
public:
    Grafo(){ primeiroNo = nullptr; direcionado = false;};
    Grafo(bool direcionado){ primeiroNo = nullptr; this->direcionado = direcionado;};
    ~Grafo(){};
    bool auxAddAresta(int id1, int id2, float peso = 0);
    void addAresta(int id1, int id2, float peso = 0);
    No* auxAddNo(int id, float peso = 0);
    void addNo(int id, float peso = 0);
    No* getNo(int i){ return mapa[i]; }
    void printGrafo();
    void printGrau(int id);
    void fechoTransitivoDireto(int id);
    void fechoTransitivoIndireto(int id);
    void QuickSort(Aresta arestas[], int p, int q);
    int particionamento(Aresta arestas[], int p, int q);
    void troca(Aresta *a, Aresta *b);
    Aresta* getArestas(int numArestas);
    void imprimeMap(){
        auto i = mapa.begin();
        while(i != mapa.end())
        {
            cout << i->first << endl;
            ++i;
        }
    }
};

#endif