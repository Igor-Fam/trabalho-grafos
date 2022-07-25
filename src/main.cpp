#include <iostream>
#include <fstream>
#include <cstring>
#include <cfloat>
#include <unordered_map>
// #include "aresta.h"
// #include "no.h"
#include "grafo.h"
#include "math.h"

using namespace std;

void separaDadoArqEnt(string &str, int &parametro)
{
    int pos = str.find(' ');
    parametro = stoi(str.substr(0, pos));
    str.erase(0, pos + 1);
    return;
}

bool comparaStrings(const char *str1, const char *str2)
{
    if (strcmp(str1, str2) == 0)
        return true;
    return false;
}

void imprimeMenu(){
    cout << endl << "Escolha a funcionalidade desejada: " << endl
        << "1. Fecho Transitivo Direto" << endl
        << "2. Fecho Transitivo Indireto" << endl
        << "3. Coeficiente de Agrupamento Local de um Vertice" << endl
        << "4. Coeficiente de Agrupamento Medio do Grafo" << endl
        << "5. Caminho minimo entre dois vertices usando algoritmo de Djkstra" << endl
        << "6. Caminho minimo entre dois vertices usando algoritmo de Floyd" << endl
        << "7. Arvore Geradora Minima usando o algoritmo de Prim" << endl
        << "8. Arvore Geradora Minima usando o algoritmo de Kruskal" << endl
        << "9. Arvore dada pela ordem de caminhamento em profundidade" << endl
        << "10. Sair" << endl;
    return;
}

int leId(int indice){
    int id;
    if (indice == 0)
        cout << "Id do Vertice: ";
    else 
        cout << "Id do Vertice " << indice << ": ";
    cin >> id;
    return id;
}

int* leIds(int &num_vert){
    cout << "Numero de Vertices: ";
    cin >> num_vert;

    int *subConj_vertices = new int [num_vert];

    for (int i = 0; i < num_vert; i++)
    {
        subConj_vertices[i] = leId(i + 1);
    }
    return subConj_vertices;
}

int main(int argc, char **argv)
{

    bool dir, peso_aresta, peso_vertice;
    bool invalido = false;
        
    for (int i = 3;i <= 5; i++)
    {
        if (argv[i] != NULL)
        {
            bool parametro;
            if (comparaStrings(argv[i], "0"))
                parametro = false;
            else if (comparaStrings(argv[i], "1"))
                parametro = true;
            else
                invalido = true;
            if (!invalido && i == 3)
                dir = parametro;
            else if (!invalido && i == 4)
                peso_aresta = parametro;

            else if (!invalido && i == 5)
                if (peso_aresta && parametro)
                {
                    cout << "Não é possível atribuir peso às arestas e aos vértices simultaneamente"<< endl;
                    exit(1);
                }
                else
                    peso_vertice = parametro;
        }
        if (argv[i] == NULL || invalido)
        {
    
            cout << "Argumento passado pela linha de comando inválido ou faltante" << endl;
            exit(1);
        }
    }

    cout << boolalpha << "dir: " << dir << endl;
    Grafo *g = new Grafo(dir);
    g->setPesoAresta(peso_aresta);

    ifstream arq_ent;
    arq_ent.open(argv[1], ios::in);
    if (arq_ent.is_open())
    {
        string str;

        getline(arq_ent, str);

        int num_vert = stoi(str);
        g->setOrdem(num_vert);

        while (!arq_ent.eof())
        {
            getline(arq_ent, str);

            int id1, id2, p_a = 0 /*, p_v = 0*/;

            separaDadoArqEnt(str, id1);
            separaDadoArqEnt(str, id2);
            if (peso_aresta)
            {
                separaDadoArqEnt(str, p_a);
            }

            g->addNo(id1);
            g->addNo(id2);
            g->addAresta(id1, id2, p_a);
            Aresta* novaAresta = new Aresta(id1, id2, p_a);
            cout<< "criando aresta entre: " << id1 << " e " << id2 << endl;
            g->adicionaArestasGrafo(novaAresta);
            No* noid1 = g->procurarNo(id1);
            noid1->adicionaAdjacencia(id2);

        }

        arq_ent.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de entrada" << endl;
        exit(1);
    }
cout << "tentando imprimir menu" << endl;
    imprimeMenu();
    int opcao;
    do {
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao != 10){
            switch (opcao)
            {
                int id;
                float cl, cm;
                //Fecho transitivo direto
                case 1:
                    id = leId(0);
                    g->fechoTransitivoDireto(id);
                    break;
                //Fecho transitivo indireto
                case 2:
                    id = leId(0);
                    g->fechoTransitivoIndireto(id);
                    break;
                //Coeficiente de agrupamento local
                case 3:
                    id = leId(0);
                    cl = g->coefAgrupLocal(id);
                    if (cl != -1)
                        cout << "Coefiente de agrupamento local do vertice de id " << id << ": " << cl << endl;
                    break;
                //Coeficiente de agrupamento medio
                case 4:
                    cm = g->coefAgrupMedio();
                    if (cm != -1)
                        cout << "Coefiente de agrupamento medio do grafo: " << cm << endl;
                    break;
                //Caminho minimo Djkstra
                case 5:{
                if(peso_aresta){
                int no1, no2;
                cout << endl << "Informe o id do Vertice inicial: ";
                cin >> no1;
                cout << "Informe o id do Vertice alvo: ";
                cin >> no2;
                if(g->procurarNo(no1) && g->procurarNo(no2)){
                    list<int> apenasImpressao = g->caminhoMinimoDijkstra(no1, no2);
                } else
                    cout << "Id do vertice não encontrado." << endl;
            } else
                cout << "O grafo nao esta ponderado. Nao eh possivel executar o algoritimo." << endl;
                    break;
                }
                //Caminho minimo Floyd
                case 6:{
            if(peso_aresta){
                int no1, no2;
                cout << "Informe o id do Vertice inicial: ";
                cin >> no1;
                cout << "Informe o id do Vertice alvo: ";
                cin >> no2;
                if(g->procurarNo(no1) && g->procurarNo(no2))
                    g->caminhoMinimoFloyd(no1, no2);
                else
                    cout << "Id do vertice não encontrado." << endl;
            } else
                cout << "O grafo nao esta ponderado. Nao eh possivel executar o algoritimo." << endl; 
            break;
        }
                    
                //Caminhamento em profundidade
                case 9: 
                    break;
                default:
                    if (opcao != 7 && opcao != 8)
                    {
                        cout << "Opcao invalida" << endl;
                        break;
                    }
                    else {
                    int num_vert;
                    cout << "Numero de Vertices: ";
                    cin >> num_vert;

                    int subConj_vertices[num_vert];

                    for (int i = 0; i < num_vert; i++)
                    {
                        subConj_vertices[i] = leId((i + 1));
                    }

                    //Arvore Geradora minima Prim
                    if (opcao == 7)
                        g->arvoreMinimaPrim(num_vert, subConj_vertices, argv[2]);
                    //Arvore Geradora minima Kruskal
                    else 
                        g->arvoreMinimaKruskal(num_vert, subConj_vertices, argv[2]);
                    break;
                    }
            }
            imprimeMenu();
        } 
        

    } while(opcao != 10);

    // Link para download do graphviz: https://graphviz.org/download/
    // Após o download:
    // No terminal: dot -Tyourformat(png, pdf...) your file -o output
    // Ex: dot -Tpng arquivo.dot -o arquivo.png

    // 1o parametro: grafo
    // 2o parametro: nome do arquivo .dot
    // 3o parametro: nome do grafo
    // g->escreveArquivoDot(g, "arquivo.dot", "G");

    return 0;
}