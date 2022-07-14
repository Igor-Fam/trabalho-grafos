#include "grafo.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>

using namespace std;

bool Grafo::noExiste(int id)
{
    return primeiroNo->noExiste(id);
}

No *Grafo::auxAddNo(int id, float peso)
{
    if (primeiroNo == nullptr)
    {
        No *newNo = new No(id, this->vert_inseridos, peso);
        primeiroNo = newNo;
        this->vert_inseridos += 1;
        return primeiroNo;
    }
    else if (primeiroNo->id == id)
    {
        // cout << "No ja existente!" << endl;
        return nullptr;
    }
    else if (id < primeiroNo->id)
    {
        No *newNo = new No(id, this->vert_inseridos, peso);
        newNo->proxNo = primeiroNo;
        primeiroNo = newNo;
        this->vert_inseridos += 1;
        return primeiroNo;
    }
    else
    {
        return primeiroNo->addNo(id, this->vert_inseridos, peso);
    }
}

void Grafo::addNo(int id, float peso)
{
    No *n = auxAddNo(id, peso);
    if (n != nullptr)
        mapa[id] = n;
}

void Grafo::addAresta(int id1, int id2, float peso)
{
    bool a_id1_id2 = true;
    if (!(this->direcionado))
    {
        if (auxAddAresta(id1, id2, peso))
        {
            mapa.at(id1)->addGrau();
            a_id1_id2 = false;
        }
        if (auxAddAresta(id2, id1, peso))
        {
            mapa.at(id2)->addGrau();
        }
    }
    else
    {
        auxAddAresta(id1, id2, peso);
        mapa.at(id1)->addGrauEntrada();
        mapa.at(id2)->addGrauSaida();
    }
    this->arestas_inseridas += 1;
}

bool Grafo::auxAddAresta(int id1, int id2, float peso)
{
    // cout << id1 << " " << id2 << " " << this->arestas_inseridas << endl;
    if (noExiste(id2))
        return primeiroNo->addAresta(id1, id2, this->arestas_inseridas, peso);
    else
        cout << "No " << id2 << " nao existe!" << endl;
    return false;
}

void Grafo::printGrafo()
{
    cout << endl;
    if (primeiroNo == nullptr)
        cout << "Grafo vazio!" << endl;
    else
        primeiroNo->printArestas();
}

void Grafo::printGrau(int id)
{
    cout << mapa.at(id)->getGrau() << endl
         << endl;
}

void Grafo::fechoTransitivoDireto(int id)
{
    if (!this->direcionado)
    {
        cout << "Grafo nao direcionado nao possui fecho transitivo direto!" << endl;
        return;
    }
    set<int> *ftd = new set<int>;
    No *n = mapa[id];
    n->fechoTransitivoDireto(ftd, this);
    cout << "Fecho transitivo direto: " << endl;
    for (int x : *ftd)
    {
        cout << x << " ";
    }
    cout << endl;

    delete ftd;
}

void Grafo::fechoTransitivoIndireto(int id)
{
    if (!this->direcionado)
    {
        cout << "Grafo nao direcionado nao possui fecho transitivo indireto!" << endl;
        return;
    }
    set<int> *fti = new set<int>;
    set<int> *nosVisitados = new set<int>;
    for (auto it : mapa)
    {
        *nosVisitados = {};
        // cout << endl << "* No " << it.first << ": " << endl;
        it.second->fechoTransitivoIndireto(id, this, fti, nosVisitados);
    }
    cout << "Fecho transitivo indireto: " << endl;
    for (int x : *fti)
    {
        cout << x << " ";
    }
    cout << endl;

    delete fti, nosVisitados;
}

void Grafo::escreveArquivoDot(Grafo G, string arquivoSaida, string nome)
{
    ofstream saida;
    saida.open(arquivoSaida, ios::out);

    No *v = primeiroNo;

    bool adicionado[arestas_inseridas];

    if (!direcionado)
        saida << "graph " << nome << "{" << endl;
    else
        saida << "digraph " << nome << "{" << endl;

    while (v != NULL)
    {
        Aresta *a = v->primeiraAresta;
        while (a != NULL)
        {
            if (adicionado[a->id_insercao] == false)
            {
                if (!direcionado)
                    saida << v->id << " -- " << a->id;
                else
                    saida << v->id << " -> " << a->id;

                if (peso_aresta)
                {
                    saida << " [label=" << a->peso << "]";
                }

                adicionado[a->id_insercao] = true;

                a = a->proxAresta;
                saida << endl;
            }
            else
                a = a->proxAresta;
        }
        v = v->proxNo;
    }
    saida << "}" << endl;
}

void Grafo::arvoreMinimaKruskal(int num_vert, int subConj_vertices[], string arquivo)
{
    if (direcionado)
    {
        cout << "Erro: Grafo direcionado" << endl;
        exit(1);
    }

    No *subArvores[num_vert];
    int id_subArvores[ordem];
    Aresta arestas[arestas_inseridas];
    int cont = 0;

    for (int i = 0; i < num_vert; i++)
    {
        try
        {
            subArvores[i] = mapa.at(subConj_vertices[i]);
            id_subArvores[subArvores[i]->id_insercao] = subArvores[i]->id_insercao;
        }
        catch (const out_of_range &oor)
        {
            cout << "Erro: Nao existe vertice de id " << subConj_vertices[i] << " no grafo" << endl;
            exit(1);
        }
    }

    for (int i = 0; i < num_vert; i++)
    {
        Aresta *a = subArvores[i]->primeiraAresta;
        while (a != NULL)
        {
            for (int j = i + 1; j < num_vert; j++)
            {
                if (a->id == subArvores[j]->id)
                {
                    arestas[cont].id = subArvores[j]->id;
                    arestas[cont].id_origem = subArvores[i]->id;
                    arestas[cont].peso = a->peso;
                    cont++;
                }
            }
            a = a->proxAresta;
        }
    }

    QuickSort(arestas, 0, cont - 1);

    int tamListaArestas = cont;
    int cont_vert = 0;
    int cont_arestas = 0;
    Grafo *arvMinimaKruskal = new Grafo(false);
    arvMinimaKruskal->setOrdem(num_vert);
    arvMinimaKruskal->setPesoAresta(true);

    while (cont_vert < num_vert - 1 && tamListaArestas != 0)
    {
        Aresta a = arestas[cont_arestas];

        cont_arestas++;
        tamListaArestas--;

        int id1_insercao = mapa.at(a.id_origem)->id_insercao;
        int id2_insercao = mapa.at(a.id)->id_insercao;

        if (id_subArvores[id1_insercao] != id_subArvores[id2_insercao])
        {
            arvMinimaKruskal->addNo(a.id_origem);
            arvMinimaKruskal->addNo(a.id);
            arvMinimaKruskal->addAresta(a.id_origem, a.id, a.peso);

            int maior, menor;

            if (id_subArvores[id2_insercao] < id_subArvores[id1_insercao])
            {
                maior = id_subArvores[id1_insercao];
                menor = id_subArvores[id2_insercao];
                id_subArvores[id1_insercao] = id_subArvores[id2_insercao];
            }
            else
            {
                maior = id_subArvores[id2_insercao];
                menor = id_subArvores[id1_insercao];
                id_subArvores[id2_insercao] = id_subArvores[id1_insercao];
            }

            cont_vert++;

            for (int i = 0; i < num_vert; i++)
            {
                if (id_subArvores[i] == maior)
                    id_subArvores[i] = menor;
            }
        }
    }

    arvMinimaKruskal->escreveArquivoDot(*arvMinimaKruskal, arquivo, "Kruskal");

    cout << "A Arvore Geradora Minima obtida atraves do algoritmo de Kruskal foi salva em " << arquivo << endl;
}

void Grafo::QuickSort(Aresta arestas[], int p, int q)
{
    if (p < q)
    {
        int j = particionamento(arestas, p, q);
        QuickSort(arestas, p, j - 1);
        QuickSort(arestas, j + 1, q);
    }
}

int Grafo::particionamento(Aresta arestas[], int p, int q)
{
    int i = p - 1, j = q;
    int v = arestas[q].peso;

    while (1)
    {
        while (arestas[++i].peso < v)
            ;
        while (v < arestas[--j].peso)
        {
            if (j == p)
                break;
        }
        if (i >= j)
            break;
        troca(&arestas[i], &arestas[j]);
    }

    troca(&arestas[i], &arestas[q]);

    return i;
}

void Grafo::troca(Aresta *a, Aresta *b)
{
    Aresta aux = *a;
    *a = *b;
    *b = aux;
}