
#include "grafo.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <unordered_map>
#include <set>
#include "Dijkstra.h"
#include "Floyd.h"
#include "math.h"

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

    if (n != nullptr){
        mapa[id] = n;
        nosGrafo.push_back(n);
    }
        
}

void Grafo::addAresta(int id1, int id2, float peso)
{
    if (!(this->direcionado))
    {
        if (auxAddAresta(id1, id2, peso))
        {
            mapa.at(id1)->addGrau();
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

//Escreve no arquivo 'arquivoSaida' de formato .dot o Grafo 'G' de nome 'nome',
//onde 'arquivoSaida', 'G', e 'nome' são passados por parâmetro
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

//Encontra, através do algoritmo de Kruskal, a arvore geradora mínima de um subconjunto de vertices e
//escreve esta no arquivo 'arquivo' com formato .dot
//Recebe como parâmetro o número de vértices contidos no subconjunto (num_vert), o subconjunto de vértices
//(subConj_vertices[]) e o nome do arquivo em que se deseja salvar a arvore gerada
void Grafo::arvoreMinimaKruskal(int num_vert, int subConj_vertices[], string arquivo)
{
    if (direcionado)
    {
        cout << "Erro: Grafo direcionado" << endl;
        return;
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
            return;
        }
    }

    Grafo *arvMinimaKruskal = new Grafo(false);
    arvMinimaKruskal->setOrdem(num_vert);
    arvMinimaKruskal->setPesoAresta(true);

    if (num_vert == 1)
    {
        arvMinimaKruskal->addNo(subArvores[0]->id);
        ofstream saida;
        saida.open(arquivo, ios::out);
        if (saida.is_open())
        {
            No *v = arvMinimaKruskal->primeiroNo;
            saida << "graph "
                  << "Kruskal"
                  << "{" << endl;
            saida << v->id;
            saida << endl;
            saida << "}" << endl;
            saida.close();
        }
        else
        {
            cout << "Erro ao abrir o arquivo " << arquivo << endl;
        }
        return;
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

    cout << endl << "Arvore Geradora Minima - Kruskal";

    arvMinimaKruskal->printGrafo();

    cout << endl << "Obs: A Arvore Geradora Minima obtida atraves do algoritmo de Kruskal foi salva em " << arquivo << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ordena um vetor de aresta com base no peso dessas 
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Encontra, através do algoritmo de Prim, a arvore geradora mínima de um subconjunto de vertices e
//escreve esta no arquivo 'arquivo' com formato .dot
//Recebe como parâmetro o número de vértices contidos no subconjunto (num_vert), o subconjunto de vértices
//(subConj_vertices[]) e o nome do arquivo em que se deseja salvar a arvore gerada
void Grafo::arvoreMinimaPrim(int num_vert, int subConj_vertices[], string arquivo)
{

    if (direcionado)
    {
        cout << "Erro: Grafo direcionado" << endl;
        return;
    }

    Grafo *arvMinimaPrim = new Grafo(false);
    arvMinimaPrim->setOrdem(num_vert);
    arvMinimaPrim->setPesoAresta(true);

    if (num_vert == 0)
    {
        arvMinimaPrim->escreveArquivoDot(*arvMinimaPrim, arquivo, "Prim");
        cout << "A Arvore Geradora Minima obtida atraves do algoritmo de Prim foi salva em " << arquivo << endl;
        return;
    }

    No *subArvores[num_vert];
    Aresta arestas[arestas_inseridas];
    int cont = 0;

    for (int i = 0; i < num_vert; i++)
    {
        try
        {
            subArvores[i] = mapa.at(subConj_vertices[i]);
        }
        catch (const out_of_range &oor)
        {
            cout << "Erro: Nao existe vertice de id " << subConj_vertices[i] << " no grafo" << endl;
            return;
        }
    }

    if (num_vert == 1)
    {
        arvMinimaPrim->addNo(subArvores[0]->id);
        ofstream saida;
        saida.open(arquivo, ios::out);
        if (saida.is_open())
        {
            No *v = arvMinimaPrim->primeiroNo;
            saida << "graph "
                  << "Prim"
                  << "{" << endl;
            saida << v->id;
            saida << endl;
            saida << "}" << endl;
            saida.close();
            cout << "A Arvore Geradora Minima obtida atraves do algoritmo de Prim foi salva em " << arquivo << endl;
        }
        else
        {
            cout << "Erro ao abrir o arquivo " << arquivo << endl;
        }
        return;
    }

    Aresta *menorPeso = NULL;
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

                    if (menorPeso == NULL)
                    {
                        menorPeso = &arestas[cont];
                    }
                    else
                    {
                        if (menorPeso->peso >= arestas[cont].peso)
                        {
                            menorPeso = &arestas[cont];
                        }
                    }
                    cont++;
                }
            }
            a = a->proxAresta;
        }
    }

    int tamListaArestas = cont;

    arvMinimaPrim->addNo(menorPeso->id_origem);
    arvMinimaPrim->addNo(menorPeso->id);
    arvMinimaPrim->addAresta(menorPeso->id_origem, menorPeso->id, menorPeso->peso);

    int custo[num_vert + 1];
    int prox[num_vert];

    custo[num_vert] = INT_MAX;

    int indMenor = num_vert;

    for (int i = 0; i < num_vert; i++)
    {
        int peso1 = getPeso(arestas, subArvores[i]->id, menorPeso->id, tamListaArestas);
        int peso2 = getPeso(arestas, subArvores[i]->id, menorPeso->id_origem, tamListaArestas);
        if (peso1 == 0 || peso2 == 0)
        {
            prox[i] = 0;
            custo[i] = 0;
        }
        else if (peso1 < peso2)
        {
            custo[i] = peso1;
            prox[i] = menorPeso->id;
        }
        else
        {
            custo[i] = peso2;
            prox[i] = menorPeso->id_origem;
        }
        if (custo[i] != 0 && custo[i] <= custo[indMenor])
        {
            indMenor = i;
        }
    }

    int cont_vert = 0;

    while (cont_vert < num_vert - 2)
    {

        menorPeso->id = subArvores[indMenor]->id;
        menorPeso->id_origem = prox[indMenor];
        menorPeso->peso = custo[indMenor];

        arvMinimaPrim->addNo(menorPeso->id_origem);
        arvMinimaPrim->addNo(menorPeso->id);
        arvMinimaPrim->addAresta(menorPeso->id_origem, menorPeso->id, menorPeso->peso);

        prox[indMenor] = 0;
        custo[indMenor] = 0;
        indMenor = num_vert;

        for (int i = 0; i < num_vert; i++)
        {
            int peso = getPeso(arestas, subArvores[i]->id, menorPeso->id, tamListaArestas);
            if (prox[i] != 0 && custo[i] > peso)
            {
                prox[i] = menorPeso->id;
                custo[i] = peso;
            }
            if (custo[i] != 0 && custo[i] <= custo[indMenor])
                indMenor = i;
        }
        cont_vert++;
    }

    arvMinimaPrim->escreveArquivoDot(*arvMinimaPrim, arquivo, "Prim");

    cout << endl << "Arvore Geradora Minima - Prim:";

    arvMinimaPrim->printGrafo();

    cout << endl << "Obs: A Arvore Geradora Minima obtida atraves do algoritmo de Prim foi salva em " << arquivo << endl;
}

//Função utilizada pela função arvoreMinimaPrim(int num_vert, int subConj_vertices[], string arquivo) para calcular
//dados dois vértices o peso, se existir, da aresta entre eles. Caso não exista, o peso entre elas é tido como infinito
//(INT_MAX)
//Recebe como parâmetro um vetor com todas as arestas de interesse (arestas[]), o id dos vértices (id1 e id2), para os 
//quais se quer verificar o peso da aresta e o tamanho da lista de arestas(tamListaArestas)
int Grafo::getPeso(Aresta arestas[], int id1, int id2, int tamListaArestas)
{
    if (id1 == id2)
        return 0;
    for (int j = 0; j < tamListaArestas; j++)
    {
        if (arestas[j].id_origem == id1 && arestas[j].id == id2)
        {
            return arestas[j].peso;
        }
        else if (arestas[j].id_origem == id2 && arestas[j].id == id1)
        {
            return arestas[j].peso;
        }
    }
    return INT_MAX;
}

//Calcula o coeficiente de agrupamento local de um vértice.
//Recebe como parâmetro o id do vértice(id_vert)
float Grafo::coefAgrupLocal(int id_vert){
    No *v;
    try {
        v = mapa.at(id_vert);
    } catch (const out_of_range &oor){
        cout << "Erro: Nao existe vertice de id " << id_vert << " no grafo" << endl;
        return -1.f;
    }
    int numArestasTot;
    int num_vAdj;
    if (direcionado) {
        num_vAdj = v->getGrauEntrada() + v->getGrauSaida();
        numArestasTot = (num_vAdj - 1) * num_vAdj;
    }
    else {
        num_vAdj = v->getGrau();
        numArestasTot = (num_vAdj - 1) * num_vAdj / 2;
    }

    Aresta *a = v->primeiraAresta;
    int id_vAdj [num_vAdj];

    int i = 0;

    while (a != NULL) {
        id_vAdj[i] = a->id;
        a = a->proxAresta;
        i++;
    }

    int numArestasExist = 0;

    for (int i = 0; i < num_vAdj; i++){
        No *adj = mapa.at(id_vAdj[i]);
        a = adj->primeiraAresta;
        while (a != NULL) {
            for (int j = 0; j < num_vAdj; j++){
                if (i != j && a->id != id_vert && a->id == id_vAdj[j]){
                    numArestasExist ++;
                }
            }
            a = a->proxAresta;
        }
    }   

    if (!direcionado) {
        numArestasExist /= 2;
    }

    if (numArestasTot == 0){
        /*
        cout << "Erro: o vertice de id " << id_vert << " possui um unico vertice adjacente. Portanto, nao foi possivel " << 
        "calcular o coeficiente de agrupamento deste (divisao por zero)" << endl;
        */
       return 0.f;
    }
    return float(numArestasExist)/numArestasTot;
}

//Calcula o coeficiente de agrupamento médio do grafo
float Grafo::coefAgrupMedio(){
    float somaCoef = 0;
    No *v = primeiroNo;
    bool erro = false;
    while (v != NULL){
        float c = coefAgrupLocal(v->id);
        if (c == -1){
            return -1.f;
        }
        somaCoef += c;
        v = v->proxNo;
    }
    return somaCoef/ordem;
}

No* Grafo::procurarNo(int id){
    for(auto i = nosGrafo.begin(); i != nosGrafo.end();i++){
        No* aux = *i;
        if(aux->getId() == id)
        return aux;
    }
    return nullptr;
}

Aresta* Grafo::existeAresta(int id ,int id_alvo){ // FUNCAO PARA ACHAR UMA ARESTA DADO DOIS VERTICES
    for (auto i = arestasGrafo.begin(); i != arestasGrafo.end(); i++){
        Aresta* verificador = *i; 
        if(verificador->getIdOrigem() == id && verificador->getId() == id_alvo){
            return verificador;
        }
    }
    //cout << "Nao existe essa aresta no grafo." << endl;
    return NULL;
}

list<int> Grafo::caminhoMinimoDijkstra(int ID1, int ID2){
    Dijkstra* aux = new Dijkstra(this);
    list<int> caminhoD = aux->caminhoMinimo(this, ID1, ID2);
    if(caminhoD.size()>0){
        cout << "Caminho minimo: ";
        for(auto i = caminhoD.begin(); i != caminhoD.end(); i++){
            cout << *i << " ";
        }
        cout << endl;
    }
    return caminhoD;
}
void Grafo::caminhoMinimoFloyd(int ID1, int ID2){
    Floyd aux;
    aux.caminhoMinimo(this, ID1, ID2);
}

void Grafo::adicionaArestasGrafo(Aresta *novaAresta)
{
    arestasGrafo.push_back(novaAresta);
}

void Grafo::prof(int id, int visitado[], ofstream *saida)
{
    No *v = NULL;
    try
    {
        v = mapa.at(id);
    }
    catch (const out_of_range &oor)
    {
        cout << "Erro: Nao existe vertice de id " << id << " no grafo" << endl;
        return;
    }
    visitado[v->id_insercao] = 1;
    Aresta *a = v->primeiraAresta;
    while (a != NULL)
    {
        No *n = NULL;
        try
        {
            n = mapa.at(a->getId());
        }
        catch (const out_of_range &oor)
        {
            cout << "Erro: Nao existe vertice de id " << id << " no grafo" << endl;
            return;
        }
        if (visitado[n->id_insercao] == 0)
        {
            cout << "(" << id << "," << a->getId() << ") - Aresta" << endl;
            if (!direcionado)
                *saida << id << " -- " << a->getId();
            else
                *saida << id << " -> " << a->getId();

            if (peso_aresta)
            {
                *saida << " [label=" << a->getPeso() << "]";
            }
            *saida << endl;
            if (direcionado && existeAresta(a->getId(), id)){
                cout << "(" << id << "," << a->getId() << ") Aresta de Retorno " << endl;
                if (!direcionado)
                    *saida << a->getId() << " -- " << id << "[style=dotted]";
                else
                    *saida << a->getId() << " -> " << id << "[style=dotted]";                    
                if (peso_aresta)
                {
                    *saida << " [label=" << a->getPeso() << "]";
                }
                *saida << endl;
            }
            prof(a->getId(), visitado, saida);
        }
        else
        {
            if (visitado[n->id_insercao] == -1)
            {
                cout << "(" << id << "," << a->getId() << ") - Aresta de Retorno" << endl;
                if (!direcionado)
                    *saida << id << " -- " << a->getId() << "[style=dotted]";
                else
                    *saida << id << " -> " << a->getId() << "[style=dotted]";
                if (peso_aresta)
                {
                    *saida << " [label=" << a->getPeso() << "]";
                }
                *saida << endl;

                if (direcionado && existeAresta(a->getId(), id)){
                    cout << "(" << id << "," << a->getId() << ") Aresta de Retorno " << endl;
                    if (!direcionado)
                        *saida << a->getId() << " -- " << id << "[style=dotted]";
                    else
                        *saida << a->getId() << " -> " << id << "[style=dotted]";
                    if (peso_aresta)
                    {
                        *saida << " [label=" << a->getPeso() << "]";
                    }
                    *saida << endl;
                }
            }
        }
        a = a->proxAresta;
    }
    visitado[v->id_insercao] = -1;
}

void Grafo::buscaProf(int id, string arquivo)
{
    int visitado[ordem];
    for (int i = 0; i < ordem; i++)
    {
        visitado[i] = 0;
    }
    ofstream saida;
    saida.open(arquivo, ios::out);
    if (saida.is_open())
    {
        if (!direcionado)
            saida << "graph "
                  << "G"
                  << "{" << endl;
        else
            saida << "digraph "
                  << "G"
                  << "{" << endl;
        int i = 0;
        prof(id, visitado, &saida);
        for (No *v = primeiroNo; v != NULL; v = v->proxNo)
        {   
            if (visitado[i] == 0) {
                prof(v->getId(), visitado, &saida);
            }
            i++;
        }
        saida << "}" << endl;
        saida.close();
    }
    else
    {
        cout << "Erro ao abrir arquivo" << endl;
    }
}