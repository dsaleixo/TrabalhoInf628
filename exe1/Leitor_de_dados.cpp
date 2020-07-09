#include "Leitor_de_dados.h"


Leitor_de_Dados::Leitor_de_Dados() {

}



void Leitor_de_Dados::Ler(IloEnv env, string s){

    // LER DADOS

    ifstream in(s);
    if (!in) {
        throw "Erro ao abrir o arquivo";
        
    }

    
    IloInt m; //numero de entradas
  

    in >> this->n >> m >> this->p;

    this->D = NumMatrix(env, this->n); // inicialaiza a matrix D
    for (int i = 0; i < this->n; i++) {
        this->D[i] = IloNumArray(env, this->n);
    }

    int a, b, c;
    for (int i = 0; i < m; i++) { // Le as distancia do arquivo 
        in >> a >> b >> c;
        this->D[a - 1][b - 1] = c;
        this->D[b - 1][a - 1] = c;
    }

    floyd();// algortitmo floyd para completar a tabela
   
}



void Leitor_de_Dados::floyd() {
    int i, j, k;
    for (k = 0; k < this->n; k++) {
        for (i = 0; i < this->n; i++) {
            for (j = 0; j < this->n; j++) {
                if ((this->D[i][k] * this->D[k][j] != 0) && (i != j))
                {
                    if ((this->D[i][k] + this->D[k][j] < this->D[i][j]) || (this->D[i][j] == 0))
                    {
                        this->D[i][j] = this->D[i][k] + this->D[k][j];
                    }
                }
            }
        }
    }
}

