#include "guloso.h"
#include "cluster.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

using relogio_t = std::chrono::high_resolution_clock;
using tempo_t = relogio_t::time_point;
using namespace std;

Guloso::Guloso(int numeroClusters, float limiteInferior, float limiteSuperior, int numeroVertices, Grafo *g, int numArestas, string nomeArquivo)
{
    tempo_t start = relogio_t::now();
    numVert = 0;
    vertCont = new int[numeroVertices];
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    int *clusterVertice = new int[numeroVertices];
    int *idsInvalidosCluster = new int[numeroVertices];

    for (int i = 0; i < numeroVertices; i++)
    {
        clusterVertice[i] = -1;
        idsInvalidos[i] = -1;
        vertCont[i] = -1;
    }

    int idInvalidoCont = 0;

    for (int i = 0; i < numeroClusters; i++)
    {
        for (int j = 0; j < numeroVertices; j++)
        {
            idsInvalidosCluster[j] = 0;
        }

        int idInvalido = 1;
        int idInicial;
        int idsInvalidosClusterCont = 0;

        do
        {
            srand(time(0) * i ^ 3);
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];

            if (idInvalido == -1 && g->getNo(idInicial)->getPeso() > limiteSuperior)
            {
                idInvalido = -3;
                if (idsInvalidosCluster[idInicial] == 0)
                {
                    idsInvalidosClusterCont += 1;
                    idsInvalidosCluster[idInicial] = 1;
                }
            }
            else
            {
                if (idInvalido == -3)
                {
                    if (idsInvalidosCluster[idInicial] == 0)
                    {
                        idsInvalidosClusterCont += 1;
                        idsInvalidosCluster[idInicial] = 1;
                    }
                }
            }

        } while (idInvalido != -1 && idInvalidoCont < numeroVertices && idsInvalidosClusterCont < numeroVertices);

        if (idInvalido == -1)
        {
            idInvalidoCont++;
            g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont, idInicial);
        }
        else if (idInvalidoCont >= numeroVertices)
        {
            do
            {
                srand(time(0));
                idInicial = rand() % numeroVertices;
                idInvalido = idsInvalidos[idInicial];

                if (idInvalido != -3 && g->getNo(idInicial)->getPeso() > limiteSuperior)
                {
                    idInvalido = -3;
                    if (idsInvalidosCluster[idInicial] == 0)
                    {
                        idsInvalidosClusterCont += 1;
                        idsInvalidosCluster[idInicial] = 1;
                    }
                }
                else
                {
                    if (idInvalido == -3)
                    {
                        if (idsInvalidosCluster[idInicial] == 0)
                        {
                            idsInvalidosClusterCont += 1;
                            idsInvalidosCluster[idInicial] = 1;
                        }
                    }
                }

            } while (idInvalido == -3 && idsInvalidosClusterCont < numeroVertices);
        }

        if (idsInvalidosClusterCont < numeroVertices)
        {
            idsInvalidos[idInicial] = -3;
            vertCont[idInicial] = 0;
            clusterVertice[idInicial] = i;
            clusters[i] = new Cluster(idInicial, g, limiteInferior, limiteSuperior);
            numVert++;
            float pesoIdInicial = g->getNo(idInicial)->getPeso();
            clusters[i]->setPesoVertices(pesoIdInicial);
        }
    }

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices, idsInvalidos, idInvalidoCont, nomeArquivo, start);
}

Guloso::Guloso(int numeroClusters, float limiteInferior[], float limiteSuperior[], int numeroVertices, Grafo *g, int numArestas, string nomeArquivo)
{
    tempo_t start = relogio_t::now();
    numVert = 0;
    vertCont = new int[numeroVertices];
    clusters = new Cluster *[numeroClusters];
    int *idsInvalidos = new int[numeroVertices];
    int *clusterVertice = new int[numeroVertices];
    int *idsInvalidosCluster = new int[numeroVertices];

    for (int i = 0; i < numeroVertices; i++)
    {
        clusterVertice[i] = -1;
        idsInvalidos[i] = -1;
        vertCont[i] = -1;
    }

    int idInvalidoCont = 0;

    for (int i = 0; i < numeroClusters; i++)
    {
        for (int j = 0; j < numeroVertices; j++)
        {
            idsInvalidosCluster[j] = 0;
        }

        int idInvalido = 1;
        int idInicial;
        int idsInvalidosClusterCont = 0;

        do
        {
            srand(time(0) * i ^ 3);
            idInicial = rand() % numeroVertices;
            idInvalido = idsInvalidos[idInicial];

            if (idInvalido == -1 && g->getNo(idInicial)->getPeso() > limiteSuperior[i])
            {
                idInvalido = -3;
                if (idsInvalidosCluster[idInicial] == 0)
                {
                    idsInvalidosClusterCont += 1;
                    idsInvalidosCluster[idInicial] = 1;
                }
            }
            else
            {
                if (idInvalido == -3)
                {
                    if (idsInvalidosCluster[idInicial] == 0)
                    {
                        idsInvalidosClusterCont += 1;
                        idsInvalidosCluster[idInicial] = 1;
                    }
                }
            }

        } while (idInvalido != -1 && idInvalidoCont < numeroVertices && idsInvalidosClusterCont < numeroVertices);

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

                if (idInvalido != -3 && g->getNo(idInicial)->getPeso() > limiteSuperior[i])
                {
                    idInvalido = -3;
                    if (idsInvalidosCluster[idInicial] == 0)
                    {
                        idsInvalidosClusterCont += 1;
                        idsInvalidosCluster[idInicial] = 1;
                    }
                }
                else
                {
                    if (idInvalido == -3)
                    {
                        if (idsInvalidosCluster[idInicial] == 0)
                        {
                            idsInvalidosClusterCont += 1;
                            idsInvalidosCluster[idInicial] = 1;
                        }
                    }
                }

            } while (idInvalido == -3 && idsInvalidosClusterCont < numeroVertices);
        }

        if (idsInvalidosClusterCont < numeroVertices)
        {
            idsInvalidos[idInicial] = -3;
            vertCont[idInicial] = 0;
            clusterVertice[idInicial] = i;
            clusters[i] = new Cluster(idInicial, g, limiteInferior[i], limiteSuperior[i]);
            numVert++;
            float pesoIdInicial = g->getNo(idInicial)->getPeso();
            clusters[i]->setPesoVertices(pesoIdInicial);
        }
    }

    this->candidatos = g->getArestas(numArestas);
    this->numArestas = numArestas;
    this->numClusters = numeroClusters;
    this->g = g;

    preencheClusters(clusterVertice, numeroVertices, idsInvalidos, idInvalidoCont, nomeArquivo, start);
}

void Guloso::preencheClusters(int *clusterVertice, int numeroVertices, int *idsInvalidos, int idInvalidoCont, string nomeArquivo, tempo_t start)
{
    int *arestaValida = new int[this->numArestas];
    int *clusterRecebeuAresta = new int[this->numClusters];
    vector<vector<int>> vertInvalidoParaClusters(numeroVertices, std::vector<int>(numClusters));

    for (int j = 0; j < this->numArestas; j++)
    {
        arestaValida[j] = 0;
    }

    for (int i = 0; i < this->numClusters; i++)
    {
        clusterRecebeuAresta[i] = 0;
    }

    for (int i = 0; i < numeroVertices; i++)
    {
        for (int j = 0; j < numClusters; j++)
        {
            vertInvalidoParaClusters[i][j] = 0;
        }
    }

    int numArestasInvalidas = 0;

    do
    {
        for (int i = 0; i < this->numClusters; i++)
        {
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

                        if (arestaValida[j] == 0)
                        {
                            arestaValida[j] = 1;
                            numArestasInvalidas += 1;
                        }

                        continue;
                    }

                    if (arestaValida[j] == 0 && clusterVertice[a.getId_origem()] == i && (clusterVertice[a.getId()] == -1 && g->getNo(a.getId())->getPeso() + clusters[i]->getPesoVertices() > clusters[i]->getLimiteSuperior()))
                    {

                        arestaValida[j] = 1;
                        numArestasInvalidas += 1;

                        if (vertInvalidoParaClusters[a.getId()][i] == 0)
                        {
                            vertInvalidoParaClusters[a.getId()][i] = 1;
                        }

                        continue;
                    }

                    else if (arestaValida[j] == 0 && clusterVertice[a.getId()] == i && ((clusterVertice[a.getId_origem()] == -1 && g->getNo(a.getId_origem())->getPeso() + clusters[i]->getPesoVertices() > clusters[i]->getLimiteSuperior())))
                    {

                        arestaValida[j] = 1;
                        numArestasInvalidas += 1;

                        if (vertInvalidoParaClusters[a.getId_origem()][i] == 0)
                        {
                            vertInvalidoParaClusters[a.getId_origem()][i] = 1;
                        }
                        continue;
                    }

                    if (arestaValida[j] == 0 && clusterVertice[a.getId_origem()] == i && ((clusterVertice[a.getId()] == -1 && g->getNo(a.getId())->getPeso() + clusters[i]->getPesoVertices() <= clusters[i]->getLimiteSuperior()) || clusterVertice[a.getId()] == i))
                    {
                        if (entraClusterI != NULL && clusterVertice[a.getId()] == -1 && clusters[i]->getPesoVertices() < clusters[i]->getLimiteInferior() && pesoVertice < g->getNo(a.getId())->getPeso())
                        {
                            entraClusterI = NULL;
                        }

                        if (entraClusterI == NULL && clusterVertice[a.getId()] == -1)
                        {
                            pesoVertice = g->getNo(a.getId())->getPeso();
                        }

                        if (entraClusterI == NULL)
                        {
                            entraClusterI = new Aresta(a.getId_origem(), a.getId(), j, a.getPeso());
                        }
                    }
                    else if (arestaValida[j] == 0 && clusterVertice[a.getId()] == i && ((clusterVertice[a.getId_origem()] == -1 && g->getNo(a.getId_origem())->getPeso() + clusters[i]->getPesoVertices() <= clusters[i]->getLimiteSuperior()) || clusterVertice[a.getId_origem()] == i))
                    {
                        if (entraClusterI != NULL && clusterVertice[a.getId_origem()] == -1 && clusters[i]->getPesoVertices() < clusters[i]->getLimiteInferior() && pesoVertice < g->getNo(a.getId_origem())->getPeso())
                        {
                            entraClusterI = NULL;
                        }

                        if (entraClusterI == NULL && clusterVertice[a.getId_origem()] == -1)
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
                    try
                    {
                        clusters[i]->getNos().at(entraClusterI->getId());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addNo(g->getNo(entraClusterI->getId()));
                        vertCont[entraClusterI->getId()] = 0;
                        clusters[i]->setPesoVertices(g->getNo(entraClusterI->getId())->getPeso());
                        clusterVertice[entraClusterI->getId()] = i;
                        numVert += 1;
                        idsInvalidos[entraClusterI->getId()] = -3;
                        idInvalidoCont += 1;
                        for (int v = 0; v < numClusters; v++)
                        {
                            if (v != i && vertInvalidoParaClusters[entraClusterI->getId()][v] == 0)
                            {
                                vertInvalidoParaClusters[entraClusterI->getId()][v] == 1;
                            }
                        }
                    }

                    try
                    {
                        clusters[i]->getNos().at(entraClusterI->getId_origem());
                    }
                    catch (const out_of_range &oor)
                    {
                        clusters[i]->addNo(g->getNo(entraClusterI->getId_origem()));
                        vertCont[entraClusterI->getId_origem()] = 0;
                        clusters[i]->setPesoVertices(g->getNo(entraClusterI->getId_origem())->getPeso());
                        clusterVertice[entraClusterI->getId_origem()] = i;
                        numVert += 1;
                        idsInvalidos[entraClusterI->getId_origem()] = -3;
                        idInvalidoCont += 1;
                        for (int v = 0; v < numClusters; v++)
                        {
                            if (v != i && vertInvalidoParaClusters[entraClusterI->getId_origem()][v] == 0)
                            {
                                vertInvalidoParaClusters[entraClusterI->getId_origem()][v] == 1;
                            }
                        }
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
                    int idInvalido = 1;
                    int idInicial;

                    for (int l = 0; l < numeroVertices; l++)
                    {
                        for (auto b = clusters[i]->getNos().begin(); b != clusters[i]->getNos().end(); b++)
                        {
                            if (idsInvalidos[l] != -3 && idsInvalidos[l] == b->first)
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
                        idInvalidoCont += 1;
                        g->getNo(idInicial)->getAdjacencias(idsInvalidos, &idInvalidoCont, idInicial);
                    }
                    else
                    {
                        for (int l = 0; l < numeroVertices; l++)
                        {
                            if (idsInvalidos[l] == -1)
                            {
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
                        vertCont[idInicial] = 0;
                    }
                    else
                    {
                        encerraDoWhile = true;
                        for (int v = 0; v < numeroVertices; v++)
                        {
                            if (clusterVertice[v] != i && vertInvalidoParaClusters[v][i] == 0)
                            {
                                vertInvalidoParaClusters[v][i] == 1;
                            }
                        }
                    }
                }

            } while (entraClusterI == NULL && encerraDoWhile == false);
        }

        for (int v = 0; v < numeroVertices; v++)
        {
            for (int w = 0; w < numClusters; w++)
            {
                if (clusterVertice[v] != -1 && clusterVertice[v] != w && vertInvalidoParaClusters[v][w] == 0)
                {
                    vertInvalidoParaClusters[v][w] == 1;
                }
            }
        }

        for (int v = 0; v < numeroVertices; v++)
        {
            bool vInvalido = false;
            for (int w = 0; w < numClusters; w++)
            {
                if (vertInvalidoParaClusters[v][w] == 0)
                {
                    vInvalido = true;
                }
            }

            if (vInvalido && vertCont[v] == -1)
            {
                // cout << "vertice nao entra em nenhum cluster: " << v << endl;
                numVert++;
            }
        }

    } while (numArestasInvalidas < numArestas || numVert < numeroVertices);

    tempo_t end = relogio_t::now();
    double delta = std::chrono::duration_cast<std::chrono::milliseconds>((end) - (start)).count();

    cout << endl
         << "Algoritmo Guloso" << endl;
    cout << "Qualidade: " << getQualidadeSolucao() << endl;
    cout << "Tempo de Processamento: " << delta << " ms" << endl;
    cout << "Solucao Viavel? " << boolalpha << verificaSolucaoViavel(numeroVertices) << endl
         << endl;

    salvaResultado(nomeArquivo);
}

bool Guloso::verificaSolucaoViavel(int numeroVertices)
{
    int verticeSol = 0;
    bool solViavel = true;
    for (int i = 0; i < this->numClusters; i++)
    {
        unordered_map<int, No *> vertices = clusters[i]->getNos();
        auto v = vertices.begin();
        while (v != vertices.end())
        {
            verticeSol += 1;
            ++v;
        }
        if (clusters[i]->getPesoVertices() < clusters[i]->getLimiteInferior() || clusters[i]->getPesoVertices() > clusters[i]->getLimiteSuperior())
        {
            solViavel = false;
        }
    }
    if (verticeSol < numeroVertices)
    {
        solViavel = false;
    }
    return solViavel;
}

double Guloso::getQualidadeSolucao()
{
    double pesoArestasTotal = 0;
    for (int i = 0; i < this->numClusters; i++)
    {
        pesoArestasTotal += clusters[i]->getPesoArestas();
    }
    return pesoArestasTotal;
}

void Guloso::salvaResultado(string nomeArquivo)
{
    ofstream arquivo;
    arquivo.open(nomeArquivo, ios::out);
    if (arquivo.is_open())
    {
        double pesoArestasTotal = 0;
        arquivo << "Algoritmo Guloso" << endl;
        for (int i = 0; i < numClusters; i++)
        {
            unordered_map<int, No *> vertices = clusters[i]->getNos();
            arquivo << "Cluster " << i << ": " << endl;
            arquivo << " -> Vertices: ";
            auto v = vertices.begin();
            while (v != vertices.end())
            {
                arquivo << v->first << " ";
                ++v;
            }
            arquivo << endl;
            arquivo << " -> Somatorio do peso das arestas: " << clusters[i]->getPesoArestas();
            arquivo << endl;
            pesoArestasTotal += clusters[i]->getPesoArestas();
        }
        arquivo << endl
                << "Qualidade Final da solucao: " << pesoArestasTotal << endl;
        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir arquivo de saida" << endl;
    }
}