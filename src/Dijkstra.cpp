#include "dijkstra.h"
#include "grafo.h"
#include "no.h"
#include <iostream>
#include <limits.h>
#include <list>
#include <math.h>

using namespace std;
Dijkstra::Dijkstra(Grafo *g)
{
    for (int i = 0; i <= g->getOrdem(); i++)
    {
        // cout<< "o i eh: "<<i << endl;
        dist.push_back(INFINITY);
        visitados.push_back(-1);
    }
    // cout << "terminei aqui"<<endl;
    for (auto i = g->nosGrafo.begin(); i != g->nosGrafo.end(); i++)
    {
        No *aux = *i;
        abertos.push_back(aux);
    }
}

Dijkstra::~Dijkstra() {}

list<int> Dijkstra::caminhoMinimo(Grafo *g, int noI, int noAlvo)
{
    No *noInicial = g->procurarNo(noI);
    this->dist.at(noI) = 0;
    No *auxremove = noInicial;
    int contador = 0;
    int salvaindice = 99999999;
    for (auto j = abertos.begin(); j != abertos.end(); j++)
    {
        abertos.remove(auxremove);
        for (auto i = auxremove->ListAdj.begin(); i != auxremove->ListAdj.end(); i++)
        {
            for (auto k = g->arestasGrafo.begin(); k != g->arestasGrafo.end(); k++)
            {
                Aresta *auxAresta = *k;
                if (auxAresta != nullptr)
                {
                    if (auxAresta->getIdOrigem() == auxremove->getId() && auxAresta->getId() == *i)
                    {
                        if (dist.at(auxremove->getId()) + auxAresta->getPeso() < dist.at(*i))
                        {
                            dist.at(*i) = dist.at(auxremove->getId()) + auxAresta->getPeso();
                            if (contador == 0)
                            {
                                if (dist.at(*i) < salvaindice)
                                {
                                    salvaindice = *i;
                                }
                                contador++;
                            }
                            else
                            {
                                if (dist.at(*i) < dist.at(salvaindice))
                                {
                                    salvaindice = *i;
                                }
                            }
                        }
                        else
                        {
                            salvaindice = *i;
                        }
                    }
                }
            }
        }
        auxremove = g->procurarNo(salvaindice);
    }
    menorDist(g, noAlvo);
    return this->caminho;
}

void Dijkstra::menorDist(Grafo *g, int nofinal)
{
    No *id = g->procurarNo(nofinal);
    int menor = this->dist.at(id->getId());
    int salvaindiceMenor;
    caminho.push_front(id->getId());
    limpaVisitados();
    visitados[id->getId()] = dist[id->getId()];
    while (dist.at(id->getId()) != 0)
    {
        // cout<< "id :" << id->getId()<< " distancia: "<< dist[id->getId()]<<endl;
        for (auto x = id->ListAdj.begin(); x != id->ListAdj.end(); x++)
        {
            if (visitados[*x] == -1)
            {
                int auxiliardox = *x;
                Aresta *auxaresta = g->existeAresta(auxiliardox, id->getId());
                if (auxaresta != nullptr)
                {
                    if ((dist.at(auxiliardox) < menor) && dist.at(auxiliardox) != 0)
                    {
                        menor = dist.at(auxiliardox);
                        salvaindiceMenor = auxiliardox;
                    }
                    else if (dist.at(id->getId()) == (auxaresta->getPeso()))
                    {
                        menor = dist.at(auxiliardox);
                        salvaindiceMenor = auxiliardox;
                    }
                }
            }
        }
        caminho.push_front(salvaindiceMenor);
        id = g->procurarNo(salvaindiceMenor);
        visitados[id->getId()] = dist[id->getId()];
    }
}
void Dijkstra::criaCaminho(int noA, int ant[], int noI)
{
    if (noA != noI)
    {
        caminho.push_front(noA);
        int aux = ant[noA];
        criaCaminho(aux, ant, noI);
    }
    else
        caminho.push_front(noI);
}

void Dijkstra::imprime()
{
    for (auto i = caminho.begin(); i != caminho.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;
}

void Dijkstra::limpaVisitados()
{
    for (int i = 0; i < visitados.size(); i++)
    {
        visitados.at(i) = -1;
    }
}