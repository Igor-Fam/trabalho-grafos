#ifndef CLUSTER_H
#define CLUSTER_H

#include "no.h"

using namespace std;

class No;
class Aresta;

class Cluster
{
private:
    list<No*> nos;
    list<Aresta*> arestas;
    //No* noInicial;
    //Aresta* listaArestas;
    //int* vertices;
    double pesoVertices;
    float pesoArestas;
    float limiteInferior;
    float limiteSuperior;
public:
    Cluster(){}
    Cluster(int noInicial_, Grafo* g, float limiteInferior, float limiteSuperior);

    double getPesoVertices() { return pesoVertices; }
    void setPesoVertices(double pesoVertices_) { pesoVertices = pesoVertices_; }

    float getPesoArestas() { return pesoArestas; }
    void setPesoArestas(float pesoArestas_) { pesoArestas = pesoArestas_; }

    float getLimiteInferior() { return limiteInferior; }
    void setLimiteInferior(float limiteInferior) { this->limiteInferior = limiteInferior; }

    float getLimiteSuperior() { return limiteSuperior; }
    void setLimiteSuperior(float limiteSuperior) { this->limiteSuperior = limiteSuperior; }

    list<No*> getNos(){return nos;}
    list<Aresta*> getArestas(){return arestas;}

    void addNo(No *v){nos.push_back(v);}
    void addAresta(Aresta *a){arestas.push_back(a);}
};

#endif