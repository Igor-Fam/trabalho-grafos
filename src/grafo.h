#ifndef GRAPH_H
#define GRAPH_H

#include "no.h"
#include "aresta.h"
#include <unordered_map>
#include <list>
#include "math.h"

using namespace std;

class Dijkstra;
class Floyd;

class No;
class Aresta;

class Grafo
{
private:
    bool direcionado;
    bool peso_aresta;
    int ordem;
    int vert_inseridos;
    int arestas_inseridas;
    No *primeiroNo;
    unordered_map<int, No *> mapa;
    bool noExiste(int id);
    friend class Aresta;

    //Ordena um vetor de aresta com base no peso dessas 
    void QuickSort(Aresta arestas[], int p, int q);
    int particionamento(Aresta arestas[], int p, int q);
    void troca(Aresta *a, Aresta *b);
    
    //Função utilizada pela função arvoreMinimaPrim(int num_vert, int subConj_vertices[], string arquivo) para calcular
    //dados dois vértices o peso, se existir, da aresta entre eles. Caso não exista, o peso entre elas é tido como infinito
    //(INT_MAX)
    int getPeso(Aresta arestas[], int id, int id_origem, int tamListaArestas);

public:

list<No*> nosGrafo;
list<Aresta*> arestasGrafo;
 
    Grafo()
    {
        primeiroNo = nullptr;
        direcionado = false;
        vert_inseridos = 0;
        arestas_inseridas = 0;
    };
    Grafo(bool direcionado)
    {
        primeiroNo = nullptr;
        this->direcionado = direcionado;
        vert_inseridos = 0;
        arestas_inseridas = 0;
    };

    ~Grafo(){};
    bool auxAddAresta(int id1, int id2, float peso = 0);
    void addAresta(int id1, int id2, float peso = 0);
    No *auxAddNo(int id, float peso = 0);
    void addNo(int id, float peso = 0);
    void printGrafo();
    void printGrau(int id);
    void fechoTransitivoDireto(int id);
    void fechoTransitivoIndireto(int id);
    void setOrdem(int ordemGrafo) { ordem = ordemGrafo; };
    int getOrdem(){return ordem;}
    int getVert_inseridos() { return vert_inseridos; };
    void setPesoAresta(bool pesoAresta) { this->peso_aresta = pesoAresta; };

    //Escreve no arquivo 'arquivoSaida' de formato .dot o Grafo 'G' de nome 'nome',
    //onde 'arquivoSaida', 'G', e 'nome' são passados por parâmetro
    void escreveArquivoDot(Grafo G, string arquivoSaida, string nome);

    //Encontra, através do algoritmo de Kruskal, a arvore geradora mínima de um subconjunto de vertices e
    //escreve esta no arquivo 'arquivo' com formato .dot
    void arvoreMinimaKruskal(int num_vert, int subConj_vertices[], string arquivo);

    //Encontra, através do algoritmo de Prim, a arvore geradora mínima de um subconjunto de vertices e
    //escreve esta no arquivo 'arquivo' com formato .dot
    void arvoreMinimaPrim(int num_vert, int subConj_vertices[], string arquivo);

    //Calcula o coeficiente de agrupamento local de um vértice.
    float coefAgrupLocal(int id_vert);

    //Calcula o coeficiente de agrupamento médio do grafo
    float coefAgrupMedio();
    No* procurarNo(int id);
    Aresta* existeAresta(int id, int id_alvo);
    list<int> caminhoMinimoDijkstra(int ID1, int ID2);
    void caminhoMinimoFloyd(int ID1, int ID2);
    void adicionaArestasGrafo(Aresta* novaAresta);
};

#endif