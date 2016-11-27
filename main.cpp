///>>>>>>>>         Warshall e Dijkstra         <<<<<<<<<<///
///     Gustavo Cordeiro - UTFPR - novembro de 2016       ///
///-------------------------------------------------------///

#include <iostream>
#define INFINITO 8000000
using namespace std;

typedef struct {
    int peso;
    int ant;
    bool fixo;
}No;

//zera matriz quadrada de ordem n_elem
void zeraMatriz(int** matriz, int n_elem){
    for(int i=0;i<n_elem;i++)
        for(int j=0;j<n_elem;j++)
            matriz[i][j] = false;
}

//para dijkstra, todos os valores são infinitos, porem diagonal eh zero
void setMatriz(int** matriz, int n_elem){
    for(int i=0;i<n_elem;i++)
        for(int j=0;j<n_elem;j++){
            if(i==j)
                matriz[i][j] = 0;
            else
                matriz[i][j] = INFINITO;
        }
}
//retorna o no de menor peso(em relacao a posicao 1) ainda nao fixado
int menorPeso(No* nos, int n_elem){
    int menor=INFINITO;
    int pos=-1;
    for(int i=0;i<n_elem;i++){
        if((!nos[i].fixo)&&(nos[i].peso<menor)){
            menor = nos[i].peso;
            pos = i;
        }
    }
    return pos;
}
//print de matriz
void printMatriz(int** matriz, int n_elem){
    for(int j=0;j<n_elem;j++)
        cout << '\t' << j+1;
    cout << endl;
    for(int i=0;i<n_elem;i++){
        cout << i+1 << "|";
        for(int j=0;j<n_elem;j++){
            cout <<'\t' << matriz[i][j];
        }
        cout << endl;
    }
}
//print de nos
void printNos(No* nos, int n_elem){
    for(int j=0;j<n_elem;j++)
        cout << '\t' << j+1;
    cout << endl << "pesos:";
    for(int i=0;i<n_elem;i++)
        cout << '\t' << nos[i].peso;
    cout << endl << "ant:";
    for(int i=0;i<n_elem;i++)
        cout << '\t' << nos[i].ant+1;
}
//Algoritmo warshall
void warshall(int** matriz, int n_elem){
    for(int k=0;k<n_elem;k++){
        for(int i=0;i<n_elem;i++)
            for(int j=0;j<n_elem;j++)
                matriz[i][j] |=  matriz[i][k]&&matriz[k][j];
        ///cout << "M" << k+1 << ":\n";
        ///printMatriz(matriz,n_elem);
    }
}

//Algoritmo Dijkstra, retorna um vetor de No com caminhos e pesos
No* dijkstra(int** matriz, int n_elem, int start){
    //criando e zerando nos
    No* nos = new No[n_elem];
    for(int i=0;i<n_elem;i++){
        nos[i].ant = -1;
        nos[i].peso = INFINITO;
        nos[i].fixo = false;
    }
    nos[start].peso = 0;

    //rodando o algoritmos
    int pivo;
    for(int i=0;i<n_elem;i++){
        //acho o no de menor peso ainda não fixado
        pivo = menorPeso(nos,n_elem);
        //atualizo todas as suas conexoes
        int novo_peso;
        for(int j=0;j<n_elem;j++){
            novo_peso = nos[pivo].peso + matriz[pivo][j];
            //se um no nao fixo tiver um melhor peso
            if((!nos[j].fixo)&&(novo_peso<nos[j].peso)){
                nos[j].peso = novo_peso;
                nos[j].ant = pivo;
            }
        }
        //fixo pivo, pois ele era o menor
        nos[pivo].fixo = true;
        //se somente a ultima posicao importa
        ///if(nos[n_elem-1].fixo)
        ///    break;
    }
    return nos;
}

int main()
{
    int n_est, n_cid, ent;
    cout << "===============++ Warshall e Dijkstra ++===============" << endl << endl;
    cout << "Digite 1 para usar Warshall e 2 para Dijkstra: ";
    cin >> ent;
    cout << "Digite o numero de cidades e entradas: ";
    cin >> n_cid >> n_est;
    //criando matriz
    int *matriz[n_cid];
    for(int i=0;i<n_cid;i++)
        matriz[i] = new int[n_cid];
    //Warshall
    if(ent==1){
        bool eh_direcionado;
        cout << "O grafo eh direcionado?(1=sim/0=nao): ";
        cin >> eh_direcionado;
        zeraMatriz(matriz, n_cid);
        //coletando dados
        cout << "Digite o numero das duas cidades conectadas estrada vezes:" << endl;
        int cid1, cid2;
        for(int i=0;i<n_est;i++){
            cin >> cid1 >> cid2;
            matriz[cid1-1][cid2-1] = true;
            if(!eh_direcionado)
                matriz[cid2-1][cid1-1] = true;
        }
        //resolvendo e imprimindo
        cout << "Antes do Warshall:" << endl;
        printMatriz(matriz,n_cid);
        warshall(matriz,n_cid);
        cout << "Depois do Warshall:" << endl;
        printMatriz(matriz,n_cid);
    }
    //Dijkstra
    else if(ent==2){
        setMatriz(matriz, n_cid);
        //coletando dados
        cout << "Digite o numero das duas cidades conectadas e suas distancias estrada vezes:" << endl;
        int cid1, cid2, peso;
        for(int i=0;i<n_est;i++){
            cin >> cid1 >> cid2 >> peso;
            matriz[cid1-1][cid2-1] = peso;
            matriz[cid2-1][cid1-1] = peso;
        }
        cout << "Qual a cidade de inicio: ";
        int start;
        cin >> start;
         //resolvendo e imprimindo
        cout << "Antes do Dijkstra:" << endl;
        printMatriz(matriz,n_cid);
        No* nos = dijkstra(matriz,n_cid, start-1);
        cout << "Depois do Dijkstra:" << endl;
        printNos(nos,n_cid);
        //desalocando nos
        delete nos;
    }
    else
        cout << "=/" << endl;
    //desalocando vetor
    for(int i=0;i<n_cid;i++)
        delete matriz[i];
    return 0;
}
