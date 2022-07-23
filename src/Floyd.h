#ifndef FLOYD_H_INCLUDED
#define FLOYD_H_INCLUDED
#include "no.h"
#include "aresta.h"
#include "Grafo.h"
#include "math.h"

class Floyd{
    private:
    list<int> caminho;

    public:
    Floyd();
    ~Floyd();

    void caminhoMinimo(Grafo* g, int noI, int noAlvo);
};
#endif //FLOYD_H_INCLUDED
