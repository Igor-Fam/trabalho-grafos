#ifndef GRAPH_H
#define GRAPH_H

#include "no.h"
#include <unordered_map>

using namespace std;

class No;
class Aresta;

class Grafo
{
private:
    bool direcionado;
    bool peso_aresta;
    int ordem;
    int vert_inseridos;
    int arestas_inseridas;
    No *primeiroNo;
    unordered_map<int, No *> mapa;
    bool noExiste(int id);
    friend class Aresta;
    void QuickSort(Aresta arestas[], int p, int q);
    int particionamento(Aresta arestas[], int p, int q);
    void troca(Aresta *a, Aresta *b);

public:
    Grafo()
    {
        primeiroNo = nullptr;
        direcionado = false;
        vert_inseridos = 0;
        arestas_inseridas = 0;
    };
    Grafo(bool direcionado)
    {
        primeiroNo = nullptr;
        this->direcionado = direcionado;
        vert_inseridos = 0;
        arestas_inseridas = 0;
    };
    ~Grafo(){};
    bool auxAddAresta(int id1, int id2, float peso = 0);
    void addAresta(int id1, int id2, float peso = 0);
    No *auxAddNo(int id, float peso = 0);
    void addNo(int id, float peso = 0);
    void printGrafo();
    void printGrau(int id);
    void fechoTransitivoDireto(int id);
    void fechoTransitivoIndireto(int id);
    void setOrdem(int ordemGrafo) { ordem = ordemGrafo; };
    int getVert_inseridos() { return vert_inseridos; };
    void escreveArquivoDot(Grafo G, string arquivoSaida, string nome);
    void setPesoAresta(bool pesoAresta) { this->peso_aresta = pesoAresta; };
    void arvoreMinimaKruskal(int num_vert, int subConj_vertices[], string arquivo);
};

#endif