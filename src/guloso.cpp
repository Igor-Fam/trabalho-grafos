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

    for (int i = 0; i < numeroClusters; i++)
    {
        int idInvalido = 1;
        int idInicial;
        int idInvalidoCont = 0;

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
        cout << "Cluster: " << i << " IdInicial: " << idInicial << endl;
        clusters[i] = new Cluster(idInicial, g, limiteInferior, limiteSuperior);
        numVert++;
        float pesoIdInicial = g->getNo(idInicial)->getPeso();
        clusters[i]->setPesoVertices(clusters[i]->getPesoVertices() + pesoIdInicial);
    }

    delete[] idsInvalidos;

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices);
}

Guloso::Guloso(int numeroClusters, float limiteInferior[], float limiteSuperior[], int numeroVertices, Grafo *g, int numArestas)
{
    int numVert = 0;
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
        cout << "Cluster: " << i << " IdInicial: " << idInicial << endl;
        clusters[i] = new Cluster(idInicial, g, limiteInferior[i], limiteSuperior[i]);
        numVert++;
        // Precisa testar os limites ao inserir o primeiro vertice?
        float pesoIdInicial = g->getNo(idInicial)->getPeso();
        clusters[i]->setPesoVertices(clusters[i]->getPesoVertices() + pesoIdInicial);
    }

    delete[] idsInvalidos;

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices);
}

void Guloso::preencheClusters(int *clusterVertice, int numeroVertices)
{
    int numeroArestas = 0;
    int *arestasUtilizadas = new int[numArestas];
    for (int i = 0; i < numArestas; i++)
    {
        arestasUtilizadas[i] = 0;
    }
    while (numVert < numeroVertices && numeroArestas < numArestas)
    {
        int *clusterRecebeuAresta = new int[numClusters];
        for (int i = 0; i < numClusters; i++)
        {
            clusterRecebeuAresta[i] = 0;
        }

        for (int i = 0; i < this->numArestas; i++)
        {
            Aresta a = this->candidatos[i];

            cout << "Aresta analisada: " << a.getId_origem() << " " << a.getId() << endl;

            if (clusterVertice[a.getId()] != -1 && clusterVertice[a.getId_origem()] != -1 && clusterVertice[a.getId_origem()] != clusterVertice[a.getId()])
                numeroArestas++;

            if (clusterVertice[a.getId()] == -1 || clusterVertice[a.getId_origem()] == -1 || (clusterVertice[a.getId()] == clusterVertice[a.getId_origem()]))
            {
                for (int j = 0; j < this->numClusters; j++)
                {
                    if (clusterRecebeuAresta[j] == 0)
                    {
                        bool existeVertAdjCluster = false;
                        bool existeArestaEntreVertCluster = false;
                        No *v = NULL;
                        if (clusterVertice[a.getId_origem()] == j && clusterVertice[a.getId()] == -1)
                        {
                            int id = a.getId();
                            v = g->getNo(id);
                            existeVertAdjCluster = true;
                        }

                        else if (clusterVertice[a.getId()] == j && clusterVertice[a.getId_origem()] == -1)
                        {
                            int id = a.getId_origem();
                            v = g->getNo(id);
                            existeVertAdjCluster = true;
                        }

                        else if (clusterVertice[a.getId()] == j && clusterVertice[a.getId_origem()] == j && arestasUtilizadas[i] == 0)
                        {
                            existeArestaEntreVertCluster = true;
                        }

                        double pesoVertice;
                        double pesoVertCluster;

                        if (existeVertAdjCluster || existeArestaEntreVertCluster)
                        {
                            if (existeVertAdjCluster)
                            {
                                cout << "Entrou na solução 3" << endl;
                                //cout << a.getId_origem() << " " << a.getId() << " " << a.getPeso() << endl;
                                pesoVertice = v->getPeso();
                                pesoVertCluster = clusters[j]->getPesoVertices() + pesoVertice;
                                if (pesoVertCluster < clusters[j]->getLimiteSuperior())
                                {
                                    clusters[j]->addNo(v);
                                    clusters[j]->setPesoVertices(pesoVertCluster);
                                    clusterVertice[v->getId()] = j;
                                    numVert++;
                                }
                            }
                            cout << "Entrou na solução 4" << endl;
                            //cout << j << endl;
                            clusters[j]->addAresta(&(this->candidatos[i]));
                            arestasUtilizadas[i] = 1;
                            numeroArestas++;
                            clusters[j]->setPesoArestas(clusters[j]->getPesoArestas() + a.getPeso());
                            clusterRecebeuAresta[j] = 1;
                            break;
                        }
                    }
                }
            }
        }

        

        for (int i = 0; i < numClusters; i++)
        {
            if (clusterRecebeuAresta[i] == 0)
            {
                for (int j = 0; j < numArestas; j++)
                {
                    Aresta a = this->candidatos[j];
                    cout << "Aresta analisada: " << a.getId_origem() << " " << a.getId() << endl;
                    //cout << i << endl;

                    if (clusterVertice[a.getId()] != -1 && clusterVertice[a.getId_origem()] != -1 && clusterVertice[a.getId_origem()] != clusterVertice[a.getId()])
                        numeroArestas++;

                    if ((clusterVertice[a.getId_origem()] == -1 && clusterVertice[a.getId()] == -1) || (clusterVertice[a.getId()] == clusterVertice[a.getId_origem()] == i))
                    {
                        No *v1 = NULL;
                        No *v2 = NULL;
                        v1 = g->getNo(a.getId_origem());
                        v2 = g->getNo(a.getId());

                        //cout << clusterVertice[a.getId()] << " " << clusterVertice[a.getId_origem()] << endl;
                        if (clusterVertice[a.getId()] == clusterVertice[a.getId_origem()] == i && arestasUtilizadas[i] == 0)
                        {
                            cout << "Entrou na solução1" << endl;
                            numeroArestas++;
                            clusters[i]->addAresta(&(this->candidatos[j]));
                            arestasUtilizadas[j] == 1;
                            clusters[i]->setPesoArestas(clusters[i]->getPesoArestas() + a.getPeso());
                            clusterRecebeuAresta[i] = 1;
                            break;
                        }

                        else if (v1->getPeso() + v2->getPeso() + clusters[i]->getPesoVertices() < clusters[i]->getLimiteSuperior())
                        {
                            cout << "Entrou na solução2" << endl;
                            clusters[i]->addNo(v1);
                            clusters[i]->addNo(v2);
                            numeroArestas++;
                            clusters[i]->addAresta(&(this->candidatos[j]));
                            arestasUtilizadas[j] = 1;
                            clusters[i]->setPesoVertices(v1->getPeso() + v2->getPeso() + clusters[i]->getPesoVertices());
                            clusters[i]->setPesoArestas(clusters[i]->getPesoArestas() + a.getPeso());
                            clusterVertice[v1->getId()] = i;
                            clusterVertice[v2->getId()] = i;
                            clusterRecebeuAresta[i] = 1;
                            numVert++;
                            numVert++;
                            break;
                        }

                        
                        No *menor = NULL;
                        No *maior = NULL;
                        if (v1->getPeso() < v2->getPeso())
                        {
                            menor = v1;
                            maior = v2;
                        }
                        else
                        {
                            menor = v2;
                            maior = v1;
                        }

                        if (menor->getPeso() + clusters[i]->getPesoVertices() < clusters[i]->getLimiteSuperior())
                        {
                            clusters[i]->addNo(menor);
                            clusters[i]->setPesoVertices(menor->getPeso() + clusters[i]->getPesoVertices());
                            clusterVertice[menor->getId()] = i;
                            clusterRecebeuAresta[i] = 1;
                            numVert++;
                            break;
                        }

                        if (maior->getPeso() + clusters[i]->getPesoVertices() < clusters[i]->getLimiteSuperior())
                        {
                            clusters[i]->addNo(maior);
                            clusters[i]->setPesoVertices(maior->getPeso() + clusters[i]->getPesoVertices());
                            clusterVertice[maior->getId()] = i;
                            clusterRecebeuAresta[i] = 1;
                            numVert++;
                            break;
                        }
                    }
                }
            }
        }
    }

    cout << "Nv " << numVert << "NT " << numeroVertices << endl;
    cout << "Na " << numArestas << "AT " << this->numArestas << endl;

    cout << numClusters << endl;
    for (int i = 0; i < numClusters; i++)
    {
        cout << "Cluster " << i << endl;
        list<No *> aux = clusters[i]->getNos();
        auto j = aux.begin();
        while (j != aux.end())
        {
            cout << (*j)->getId() << " ";
            ++j;
        }
        cout << endl;
        list<Aresta *> auxA = clusters[i]->getArestas();
        auto k = auxA.begin();
        while (k != auxA.end())
        {
            cout << (*k)->getId_origem() << " " << (*k)->getId() << " " << (*k)->getPeso() << endl;
            ++k;
        }
    }
}