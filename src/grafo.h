#ifndef GRAPH_H
#define GRAPH_H

#include "no.h"
#include <unordered_map>

using namespace std;

class Grafo
{
private:
    bool direcionado;
    No* primeiroNo;
    unordered_map <int, No*> mapa;
    bool noExiste(int id);
public:
    Grafo(){ primeiroNo = nullptr; direcionado = false;};
    Grafo(bool direcionado){ primeiroNo = nullptr; this->direcionado = direcionado;};
    ~Grafo(){};
    bool auxAddAresta(int id1, int id2, float peso = 0);
    void addAresta(int id1, int id2, float peso = 0);
    No* auxAddNo(int id, float peso = 0);
    void addNo(int id, float peso = 0);
    void printGrafo();
    void printGrau(int id);
};

#endif