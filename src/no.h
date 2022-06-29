#ifndef NODE_H
#define NODE_H

#include "aresta.h"
#include <iostream>

using namespace std;

class No
{
private:
    int id;
    int grau;
    int grauEntrada;
    int grauSaida;
    float peso;
    Aresta* primeiraAresta;
    No* proxNo;
    bool noExiste(int id);
    friend class Grafo;

public:
    No(int id, float peso = 0);
    No(){};
    ~No(){};
    bool addAresta(int id1, int id2, float peso = 0);
    No* addNo(int id, float peso = 0);
    int getGrau(){ return grau; }
    void addGrau(){ grau++; }
    int getGrauEntrada(){ return grauEntrada; }
    void addGrauEntrada(){ grauEntrada++; }
    int getGrauSaida(){ return grauSaida; }
    void addGrauSaida(){ grauSaida++; }
    void printArestas();
};

#endif