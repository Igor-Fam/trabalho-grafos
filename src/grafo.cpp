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
    //cout << id1 << " " << id2 << " " << this->arestas_inseridas << endl;
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

    No* v = primeiroNo;

    bool adicionado[arestas_inseridas];

    if(!direcionado)
        saida << "graph " << nome << "{" << endl;
    else
        saida << "digraph " << nome << "{" << endl;
   
    while (v != NULL)
    {
        Aresta *a = v->primeiraAresta;
        while (a != NULL) {
        if(adicionado[a->id_insercao] == false)
            {
                if(!direcionado)
                    saida << v->id << " -- " <<  a->id;
                else
                    saida << v->id << " -> " <<  a->id;

                if(peso_aresta)
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