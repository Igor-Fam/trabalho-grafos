#ifndef NODE_H
#define NODE_H

#include "aresta.h"
#include "grafo.h"
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <list>
#include <math.h>

using namespace std;

class Grafo;
class Aresta;

class No
{
private:
    int id;
    int id_insercao;
    int grau;
    int grauEntrada;
    int grauSaida;
    float peso;
    Aresta *primeiraAresta;
    No *proxNo;
    bool noExiste(int id);
    friend class Grafo;
    friend class Aresta;

public:
    
    list<int> ListAnt;
    list<int> ListAdj;

    No(int id, int id_insercao, float peso = 0);
    No(){};
    ~No(){};
    bool addAresta(int id1, int id2, int arestas_inseridas, float peso = 0);
    No *addNo(int id, int &vert_inseridos, float peso = 0);
    int getGrau() { return grau; }
    int getId() {return id;}
    void addGrau() { grau++; }
    Aresta *retornaArestas();
    int getGrauEntrada() { return grauEntrada; }
    void addGrauEntrada() { grauEntrada++; }
    int getGrauSaida() { return grauSaida; }
    void addGrauSaida() { grauSaida++; }
    void printArestas();
    void fechoTransitivoDireto(set<int> *ftd, Grafo *g);
    bool fechoTransitivoIndireto(int id, Grafo *g, set<int> *fti);
    bool fechoTransitivoIndireto(int id, Grafo *g, set<int> *fti, set<int> *nosVisitados);
    void printArestasArquivoDot(ofstream saida);
    void adicionaAdjacencia(int id_alvo);
    void PreencheDist( unsigned int dist[], int tam , Grafo* g);
};

#endif