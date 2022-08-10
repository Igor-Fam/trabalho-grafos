/*
#include "guloso.h"
#include "cluster.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Guloso::Guloso(int numeroClusters, float limiteInferior, float limiteSuperior, int numeroVertices, Grafo *g, int numArestas)
{
    numVert = 0;
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    int *clusterVertice = new int[numeroVertices];
    for (int i = 0; i < numeroVertices; i++)
    {
        clusterVertice[i] = -1;
        idsInvalidos[i] = 0;
    }

    int idInvalidoCont = 0;

    for (int i = 0; i < numeroClusters; i++)
    {
        int idInvalido = 1;
        int idInicial;

        do
        {
            srand(time(0) * i ^ 3);
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];
        } while (idInvalido != 0 && idInvalidoCont < numeroVertices);

        if (idInvalido == 0)
        {
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

        idsInvalidos[idInicial] = 1;
        clusterVertice[idInicial] = i;
        clusters[i] = new Cluster(idInicial, g, limiteInferior, limiteSuperior);
        numVert++;
        float pesoIdInicial = g->getNo(idInicial)->getPeso();
        clusters[i]->setPesoVertices(pesoIdInicial);
        cout << "Cluster " << i << " Id Inicial " << clusters[i]->getNos().at(idInicial)->getId() << " Peso " << clusters[i]->getNos().at(idInicial)->getPeso() << endl;
    }

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices, idsInvalidos, idInvalidoCont);
}

Guloso::Guloso(int numeroClusters, float limiteInferior[], float limiteSuperior[], int numeroVertices, Grafo *g, int numArestas)
{
    numVert = 0;
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    int *clusterVertice = new int[numeroVertices];

    for (int i = 0; i < numeroVertices; i++)
    {
        clusterVertice[i] = -1;
        idsInvalidos[i] = 0;
    }
    int idInvalidoCont = 0;
    for (int i = 0; i < numeroClusters; i++)
    {
        int idInvalido = 1;
        int idInicial;
        do
        {
            srand(time(0) * i ^ 3);
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];
        } while (idInvalido != 0 && idInvalidoCont < numeroVertices);

        if (idInvalido == 0)
        {
            idInvalidoCont++;
            g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont);
        }
        else
        {
            do
            {
                srand(time(NULL) * i);
                idInicial = rand() % numeroVertices;
                idInvalido = idsInvalidos[idInicial];
            } while (idInvalido == 1);
        }

        idsInvalidos[idInicial] = 1;
        clusterVertice[idInicial] = i;
        clusters[i] = new Cluster(idInicial, g, limiteInferior[i], limiteSuperior[i]);
        numVert++;
        float pesoIdInicial = g->getNo(idInicial)->getPeso();
        clusters[i]->setPesoVertices(pesoIdInicial);
        cout << "Cluster " << i << " Id Inicial " << clusters[i]->getNos().at(idInicial)->getId() << " Peso " << clusters[i]->getNos().at(idInicial)->getPeso() << endl;
    }

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices, idsInvalidos, idInvalidoCont);
}

void Guloso::preencheClusters(int *clusterVertice, int numeroVertices, int *idsInvalidos, int idInvalidoCont)
{
    int *arestaValida = new int[this->numArestas];
    int *clusterRecebeuAresta = new int[this->numClusters];

    for (int j = 0; j < this->numArestas; j++)
    {
        arestaValida[j] = 0;
    }

    for (int i = 0; i < this->numClusters; i++)
    {
        clusterRecebeuAresta[i] = 0;
    }

    int numArestasInvalidas = 0;

    do
    {

        for (int i = 0; i < this->numClusters; i++)
        {

            cout << "Cluster " << i << endl;

            Aresta *entraClusterI = NULL;
            bool encerraDoWhile = false;

            do
            {

                int pesoVertice = 0;

                for (int j = 0; j < this->numArestas; j++)
                {

                    Aresta a = this->candidatos[j];

                    if (clusterVertice[a.getId()] != -1 && clusterVertice[a.getId_origem()] != -1 && clusterVertice[a.getId()] != clusterVertice[a.getId_origem()])
                    {
                        arestaValida[j] = 1;
                        numArestasInvalidas += 1;
                        continue;
                    }

                    if (arestaValida[j] == 0 && clusterVertice[a.getId_origem()] == i && ((clusterVertice[a.getId()] == -1 && g->getNo(a.getId())->getPeso() + clusters[i]->getPesoVertices() < clusters[i]->getLimiteSuperior()) || clusterVertice[a.getId()] == i))
                    {
                        if (entraClusterI != NULL && clusterVertice[a.getId()] == -1 && clusters[i]->getPesoVertices() < clusters[i]->getLimiteInferior() && pesoVertice < g->getNo(a.getId())->getPeso())
                        {
                            delete entraClusterI;
                        }
                        if (clusterVertice[a.getId()] == -1)
                        {
                            pesoVertice = g->getNo(a.getId())->getPeso();
                        }
                        if (entraClusterI == NULL)
                        {
                            entraClusterI = new Aresta(a.getId_origem(), a.getId(), j, a.getPeso());
                        }
                    }
                    else if (arestaValida[j] == 0 && clusterVertice[a.getId()] == i && ((clusterVertice[a.getId_origem()] == -1 && g->getNo(a.getId_origem())->getPeso() + clusters[i]->getPesoVertices() < clusters[i]->getLimiteSuperior()) || clusterVertice[a.getId_origem()] == i))
                    {
                        if (entraClusterI != NULL && clusterVertice[a.getId_origem()] == -1 && clusters[i]->getPesoVertices() < clusters[i]->getLimiteInferior() && pesoVertice < g->getNo(a.getId_origem())->getPeso())
                        {
                            delete entraClusterI;
                            entraClusterI = new Aresta(a.getId_origem(), a.getId(), j, a.getPeso());
                        }
                        if (clusterVertice[a.getId_origem()] == -1)
                        {
                            pesoVertice = g->getNo(a.getId_origem())->getPeso();
                        }
                        if (entraClusterI == NULL)
                        {
                            entraClusterI = new Aresta(a.getId_origem(), a.getId(), j, a.getPeso());
                        }
                    }
                }

                if (entraClusterI != NULL)
                {
                    cout << "Entrou na solução" << endl;
                    cout << "Id Origem " << entraClusterI->getId_origem() << " "
                         << "Id " << entraClusterI->getId() << " "
                         << "Peso " << entraClusterI->getPeso() << endl;
                    try
                    {
                        clusters[i]->getNos().at(entraClusterI->getId());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addNo(g->getNo(entraClusterI->getId()));
                        clusters[i]->setPesoVertices(g->getNo(entraClusterI->getId())->getPeso());
                        clusterVertice[entraClusterI->getId()] = i;
                        numVert += 1;
                        idsInvalidos[entraClusterI->getId()] = 1;
                        idInvalidoCont += 1;
                    }

                    try
                    {
                        clusters[i]->getNos().at(entraClusterI->getId_origem());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addNo(g->getNo(entraClusterI->getId_origem()));
                        clusters[i]->setPesoVertices(g->getNo(entraClusterI->getId_origem())->getPeso());
                        clusterVertice[entraClusterI->getId_origem()] = i;
                        numVert += 1;
                        idsInvalidos[entraClusterI->getId_origem()] = 1;
                        idInvalidoCont += 1;
                    }

                    try
                    {
                        clusters[i]->getArestas().at(entraClusterI->getIdAresta());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addAresta(entraClusterI);
                        clusters[i]->setPesoArestas(entraClusterI->getPeso());
                        numArestasInvalidas += 1;
                        arestaValida[entraClusterI->getIdAresta()] = 1;
                        clusterRecebeuAresta[i] = 1;
                    }
                }
                else
                {
                    cout << "Procurando novo id inicial para o cluster" << endl;
                    int idInvalido = 1;
                    int idInicial;

                    for (int l = 0; l < numeroVertices; l++)
                    {
                        if (idsInvalidos[l] == 0)
                        {
                            if (g->getNo(l)->getPeso() + clusters[i]->getPesoVertices() <= clusters[i]->getLimiteSuperior())
                            {
                                idInvalido = 0;
                                idInicial = l;
                                break;
                            }
                        }
                    }

                    if (idInvalido == 0)
                    {
                        idInvalidoCont += 1;
                        g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont);
                    }
                    else
                    {
                        for (int l = 0; l < numeroVertices; l++)
                        {
                            if (idsInvalidos[l] != 1)
                            {
                                if (g->getNo(l)->getPeso() + clusters[i]->getPesoVertices() <= clusters[i]->getLimiteSuperior())
                                {
                                    idInvalido = 0;
                                    idInicial = l;
                                    break;
                                }
                            }
                        }
                    }

                    if (idInvalido == 0)
                    {
                        idsInvalidos[idInicial] = 1;
                        clusterVertice[idInicial] = i;
                        clusters[i]->addNo(g->getNo(idInicial));
                        clusters[i]->setPesoVertices(g->getNo(idInicial)->getPeso());
                        numVert += 1;
                    }

                    if (idInvalido != 0)
                    {
                        encerraDoWhile = true;
                    }
                }

            } while (entraClusterI == NULL && encerraDoWhile == false);
        }
    } while (numArestasInvalidas < numArestas && numVert < numeroVertices);

    for (int i = 0; i < this->numClusters; i++)
    {
        cout << "Peso Cluster Vertice " << clusters[i]->getPesoVertices() << endl;
        cout << "Vertices" << endl;
        unordered_map<int, No *> aux = clusters[i]->getNos();
        auto k = aux.begin();
        while (k != aux.end())
        {
            cout << k->first << " ";
            ++k;
        }
        cout << endl;
        cout << "Arestas" << endl;
        unordered_map<int, Aresta *> aux2 = clusters[i]->getArestas();
        auto m = aux2.begin();
        while (m != aux2.end())
        {
            cout << m->second->getId_origem() << " " << m->second->getId() << " " << m->second->getPeso() << endl;
            ++m;
        }
        cout << endl;
    }
}
*/

#include "guloso.h"
#include "cluster.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Guloso::Guloso(int numeroClusters, float limiteInferior, float limiteSuperior, int numeroVertices, Grafo *g, int numArestas)
{
    numVert = 0;
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    int *clusterVertice = new int[numeroVertices];
    for (int i = 0; i < numeroVertices; i++)
    {
        clusterVertice[i] = -1;
        idsInvalidos[i] = -1;
    }

    int idInvalidoCont = 0;

    for (int i = 0; i < numeroClusters; i++)
    {
        int idInvalido = 1;
        int idInicial;

        do
        {
            srand(time(0) * i ^ 3);
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];
        } while (idInvalido != -1 && idInvalidoCont < numeroVertices);

        if (idInvalido == -1)
        {
            idInvalidoCont++;
            g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont, idInicial);
        }
        else
        {
            do
            {
                srand(time(0));
                idInicial = rand() % numeroVertices;
                idInvalido = idsInvalidos[idInicial];
            } while (idInvalido == -3);
        }

        idsInvalidos[idInicial] = -3;
        clusterVertice[idInicial] = i;
        clusters[i] = new Cluster(idInicial, g, limiteInferior, limiteSuperior);
        numVert++;
        float pesoIdInicial = g->getNo(idInicial)->getPeso();
        clusters[i]->setPesoVertices(pesoIdInicial);
        cout << "Cluster " << i << " Id Inicial " << clusters[i]->getNos().at(idInicial)->getId() << " Peso " << clusters[i]->getNos().at(idInicial)->getPeso() << endl;
    }

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices, idsInvalidos, idInvalidoCont);
}

Guloso::Guloso(int numeroClusters, float limiteInferior[], float limiteSuperior[], int numeroVertices, Grafo *g, int numArestas)
{
    numVert = 0;
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    int *clusterVertice = new int[numeroVertices];

    for (int i = 0; i < numeroVertices; i++)
    {
        clusterVertice[i] = -1;
        idsInvalidos[i] = -1;
    }
     
    int idInvalidoCont = 0;
    
    for (int i = 0; i < numeroClusters; i++)
    {
        int idInvalido = 1;
        int idInicial;
        do
        {
            srand(time(0) * i ^ 3);
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];
        } while (idInvalido != -1 && idInvalidoCont < numeroVertices);

        if (idInvalido == -1)
        {
            idInvalidoCont++;
            g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont, idInicial);
        }
        else
        {
            do
            {
                srand(time(NULL) * i);
                idInicial = rand() % numeroVertices;
                idInvalido = idsInvalidos[idInicial];
            } while (idInvalido == -3);
        }

        idsInvalidos[idInicial] = -3;
        clusterVertice[idInicial] = i;
        clusters[i] = new Cluster(idInicial, g, limiteInferior[i], limiteSuperior[i]);
        numVert++;
        float pesoIdInicial = g->getNo(idInicial)->getPeso();
        clusters[i]->setPesoVertices(pesoIdInicial);
        cout << "Cluster " << i << " Id Inicial " << clusters[i]->getNos().at(idInicial)->getId() << " Peso " << clusters[i]->getNos().at(idInicial)->getPeso() << endl;
    }

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices, idsInvalidos, idInvalidoCont);
}

void Guloso::preencheClusters(int *clusterVertice, int numeroVertices, int *idsInvalidos, int idInvalidoCont)
{
    int *arestaValida = new int[this->numArestas];
    int *clusterRecebeuAresta = new int[this->numClusters];

    for (int j = 0; j < this->numArestas; j++)
    {
        arestaValida[j] = 0;
    }

    for (int i = 0; i < this->numClusters; i++)
    {
        clusterRecebeuAresta[i] = 0;
    }

    int numArestasInvalidas = 0;

    do
    {

        for (int i = 0; i < this->numClusters; i++)
        {

            //cout << "Cluster " << i << endl;

            Aresta *entraClusterI = NULL;
            bool encerraDoWhile = false;

            do
            {

                int pesoVertice = 0;

                for (int j = 0; j < this->numArestas; j++)
                {

                    Aresta a = this->candidatos[j];

                    if (clusterVertice[a.getId()] != -1 && clusterVertice[a.getId_origem()] != -1 && clusterVertice[a.getId()] != clusterVertice[a.getId_origem()])
                    {
                        arestaValida[j] = 1;
                        numArestasInvalidas += 1;
                        continue;
                    }

                    if (arestaValida[j] == 0 && clusterVertice[a.getId_origem()] == i && ((clusterVertice[a.getId()] == -1 && g->getNo(a.getId())->getPeso() + clusters[i]->getPesoVertices() < clusters[i]->getLimiteSuperior()) || clusterVertice[a.getId()] == i))
                    {
                        if (entraClusterI != NULL && clusterVertice[a.getId()] == -1 && clusters[i]->getPesoVertices() < clusters[i]->getLimiteInferior() && pesoVertice < g->getNo(a.getId())->getPeso())
                        {
                            delete entraClusterI;
                        }
                        if (clusterVertice[a.getId()] == -1)
                        {
                            pesoVertice = g->getNo(a.getId())->getPeso();
                        }
                        if (entraClusterI == NULL)
                        {
                            entraClusterI = new Aresta(a.getId_origem(), a.getId(), j, a.getPeso());
                        }
                    }
                    else if (arestaValida[j] == 0 && clusterVertice[a.getId()] == i && ((clusterVertice[a.getId_origem()] == -1 && g->getNo(a.getId_origem())->getPeso() + clusters[i]->getPesoVertices() < clusters[i]->getLimiteSuperior()) || clusterVertice[a.getId_origem()] == i))
                    {
                        if (entraClusterI != NULL && clusterVertice[a.getId_origem()] == -1 && clusters[i]->getPesoVertices() < clusters[i]->getLimiteInferior() && pesoVertice < g->getNo(a.getId_origem())->getPeso())
                        {
                            delete entraClusterI;
                            entraClusterI = new Aresta(a.getId_origem(), a.getId(), j, a.getPeso());
                        }
                        if (clusterVertice[a.getId_origem()] == -1)
                        {
                            pesoVertice = g->getNo(a.getId_origem())->getPeso();
                        }
                        if (entraClusterI == NULL)
                        {
                            entraClusterI = new Aresta(a.getId_origem(), a.getId(), j, a.getPeso());
                        }
                    }
                }

                if (entraClusterI != NULL)
                {
                    /*cout << "Entrou na solução" << endl;
                    cout << "Id Origem " << entraClusterI->getId_origem() << " "
                         << "Id " << entraClusterI->getId() << " "
                         << "Peso " << entraClusterI->getPeso() << endl;*/
                    try
                    {
                        clusters[i]->getNos().at(entraClusterI->getId());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addNo(g->getNo(entraClusterI->getId()));
                        clusters[i]->setPesoVertices(g->getNo(entraClusterI->getId())->getPeso());
                        clusterVertice[entraClusterI->getId()] = i;
                        numVert += 1;
                        idsInvalidos[entraClusterI->getId()] = -3;
                        idInvalidoCont += 1;
                    }

                    try
                    {
                        clusters[i]->getNos().at(entraClusterI->getId_origem());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addNo(g->getNo(entraClusterI->getId_origem()));
                        clusters[i]->setPesoVertices(g->getNo(entraClusterI->getId_origem())->getPeso());
                        clusterVertice[entraClusterI->getId_origem()] = i;
                        numVert += 1;
                        idsInvalidos[entraClusterI->getId_origem()] = -3;
                        idInvalidoCont += 1;
                    }

                    try
                    {
                        clusters[i]->getArestas().at(entraClusterI->getIdAresta());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addAresta(entraClusterI);
                        clusters[i]->setPesoArestas(entraClusterI->getPeso());
                        numArestasInvalidas += 1;
                        arestaValida[entraClusterI->getIdAresta()] = 1;
                        clusterRecebeuAresta[i] = 1;
                    }
                }
                else
                {
                    //cout << "Procurando novo id inicial para o cluster" << endl;
                    int idInvalido = 1;
                    int idInicial;

                    for (int l = 0; l < numeroVertices; l++)
                    {
                        if (idsInvalidos[l] == i)
                        {
                            if (g->getNo(l)->getPeso() + clusters[i]->getPesoVertices() <= clusters[i]->getLimiteSuperior())
                            {
                                idInvalido = 0;
                                idInicial = l;
                                break;
                            }
                        }
                    }

                    if (idInvalido == 0)
                    {
                        idInvalidoCont += 1;
                        g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont, idInicial);
                    }
                    else
                    {
                        for (int l = 0; l < numeroVertices; l++)
                        {
                            if (idsInvalidos[l] == -1){
                                if (g->getNo(l)->getPeso() + clusters[i]->getPesoVertices() <= clusters[i]->getLimiteSuperior())
                                {
                                    idInvalido = 0;
                                    idInicial = l;
                                    break;
                                }
                            }
                            else if (idsInvalidos[l] != -3)
                            {
                                if (g->getNo(l)->getPeso() + clusters[i]->getPesoVertices() <= clusters[i]->getLimiteSuperior())
                                {
                                    idInvalido = 0;
                                    idInicial = l;
                                }
                            }
                        }
                    }

                    if (idInvalido == 0)
                    {
                        idsInvalidos[idInicial] = -3;
                        clusterVertice[idInicial] = i;
                        clusters[i]->addNo(g->getNo(idInicial));
                        clusters[i]->setPesoVertices(g->getNo(idInicial)->getPeso());
                        numVert += 1;
                    }

                    if (idInvalido != 0)
                    {
                        encerraDoWhile = true;
                    }
                }

            } while (entraClusterI == NULL && encerraDoWhile == false);
        }
    } while (numArestasInvalidas < numArestas && numVert < numeroVertices);

    for (int i = 0; i < this->numClusters; i++)
    {
        cout << "Peso total dos vertices do cluster: " << clusters[i]->getPesoVertices() << endl;
        cout << "Vertices" << endl;
        unordered_map<int, No *> aux = clusters[i]->getNos();
        auto k = aux.begin();
        while (k != aux.end())
        {
            cout << k->first << " ";
            ++k;
        }
        cout << endl;
        cout << "Arestas" << endl;
        unordered_map<int, Aresta *> aux2 = clusters[i]->getArestas();
        auto m = aux2.begin();
        while (m != aux2.end())
        {
            cout << m->second->getId_origem() << " " << m->second->getId() << " " << m->second->getPeso() << endl;
            ++m;
        }
        cout << endl;
    }
}