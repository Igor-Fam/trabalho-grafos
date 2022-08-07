#include "guloso.h"
#include "cluster.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Guloso::Guloso(int numeroClusters, float limiteInferior, float limiteSuperior, int numeroVertices, Grafo *g)
{
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    for (int i = 0; i < numeroVertices; i++)
    {
        idsInvalidos[i] = 0;
    }

    for (int i = 0; i < numeroClusters; i++)
    {
        int idInvalido = 1;
        int idInicial;
        int idInvalidoCont = 0;

        do
        {
            srand(time(0));
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];
        } while (idInvalido != 0 && idInvalidoCont < numeroVertices);

        if (idInvalido == 0)
        {
            idsInvalidos[idInicial] = 1;
            idInvalidoCont++;
            g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont);
        }
        else
        {
            do
            {
                srand(time(0));
                idInicial = rand() % numeroVertices;
                idInvalido = idsInvalidos[idInicial];
            } while (idInvalido == 1);
        }
        cout << "Cluster: " << i << " IdInicial: " << idInicial << endl;
        clusters[i] = new Cluster(idInicial, g, limiteInferior, limiteSuperior);
    }
}

Guloso::Guloso(int numeroClusters, float limiteInferior[], float limiteSuperior[], int numeroVertices, Grafo *g)
{
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    for (int i = 0; i < numeroVertices; i++)
    {
        idsInvalidos[i] = 0;
    }
    int idInvalidoCont = 0;
    for (int i = 0; i < numeroClusters; i++)
    {
        int idInvalido = 1;
        int idInicial;

        do
        {
            srand(time(0) * i);
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];
        } while (idInvalido != 0 && idInvalidoCont < numeroVertices);

        if (idInvalido == 0)
        {
            idsInvalidos[idInicial] = 1;
            idInvalidoCont++;
        }
        else
        {
            do
            {
                srand(time(NULL) * i);
                idInicial = rand() % numeroVertices;
                idInvalido = idsInvalidos[idInicial];
            } while (idInvalido == 1);

            idsInvalidos[idInicial] = 1;
        }

        g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont);
        cout << "Cluster: " << i << " IdInicial: " << idInicial << endl;
        clusters[i] = new Cluster(idInicial, g, limiteInferior[i], limiteSuperior[i]);
    }
}
