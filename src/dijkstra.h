#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "grafo.h"
#include "no.h"
#include <list>
#include "math.h"
#include <vector>

class Dijkstra
{
private:
    list<int> caminho;
    list<No *> abertos;
    void menorDist(Grafo *g, int nofinal);        // busca vertice aberto com menor custo salvo
    void criaCaminho(int no, int ant[], int noI); // Busca nos predecessores para fazer o caminho

public:
    vector<int> visitados;
    vector<float> dist;
    Dijkstra(Grafo *g);
    ~Dijkstra();
    list<int> caminhoMinimo(Grafo *g, int noI, int noAlvo); // base do algoritimo
    void imprime();
    void limpaVisitados();
};

#endif // DIJKSTRA_H_INCLUDED