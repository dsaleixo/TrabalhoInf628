#include "Leitor_de_dados.h"
#include <set>
#include <vector>
#include <iterator>

Leitor_de_Dados::Leitor_de_Dados() {

}



void Leitor_de_Dados::Ler(IloEnv env, string s,int p){

    // LER DADOS

    ifstream in(s);
    if (!in) {
        throw "Erro ao abrir o arquivo";
        
    }

    
 
  

    in >> this->n >> this->p >>this->Q;
    this->p = p;

    Demanda = IloNumArray(env, this->n);

    this->D = NumMatrix(env, this->n); // inicialaiza a matrix D
    for (int i = 0; i < this->n; i++) {
        this->D[i] = IloNumArray(env, this->n);
    }

    double a,d;

    for (int i = 0; i < this->n ; i++) { // Le as distancia do arquivo 
        Ponto ponto;
        in >> a >> ponto.x >> ponto.y>> d;
        this->pontos.push_back(ponto);
        this->Demanda[i] = d;
        
    }

    this->calcula_distancia_entre_locais();
   


}


int Leitor_de_Dados::distancia_entre_pontos(Ponto p1, Ponto p2) {
    int a = (p1.x - p2.x);
    a *= a;
    int b = (p1.y - p2.y);
    b *= b;
    return round(sqrt(a + b));
}


void Leitor_de_Dados::calcula_distancia_entre_locais() {
    
    for (int i = 0; i < this->n;i++) {
        for (int j = i; j < this->n; j++) {
            int aux = distancia_entre_pontos(this->pontos[i], this->pontos[j]);
            this->D[i][j] = aux;
            this->D[j][i] = aux;
            
        }
    }


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

IloNumArray Leitor_de_Dados::calcula_D(IloEnv env) {
    set <float, less <float> > s1;

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            s1.insert(this->D[i][j]);
        }
    }

    IloNumArray v(env,s1.size());

    set <float, less <float> > ::iterator itr;
    int i = 0;
    for (itr = s1.begin(); itr != s1.end(); ++itr)
    {
        v[i] =*itr;
        i++;
    }


    return v;
}



NumMatrix3D Leitor_de_Dados::cria_matrizA(IloEnv env,IloNumArray Dt, int k) {
    NumMatrix3D A(env, this->n);
    for (int i = 0; i < this->n; i++) {
        A[i] = NumMatrix(env, this->n);
        for (int j = 0; j < this->n; j++) {
            A[i][j] = IloNumArray(env, k);
        }
    }

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            for (int t = 0; t < k; t++) {
                if (this->D[i][j] <= Dt[t]) {
                    A[i][j][t] = 1;

                }
                else {
                    A[i][j][t] = 0;
                }
            }
        }

    }
    return A;

}



vector<vector<int>> Leitor_de_Dados::coleta_Si(IloEnv env, IloNumArray Dt, int k) {

    vector<vector<int>> S;

    for (int i = 0; i < this->n; i++) {
        vector<int> Si;
        for (int t = 0; t < k - 1; t++) {
            int contK = 0;
            int contK1 = 0;
            for (int j = 0; j < this->n; j++) {
                if (this->D[i][j] == Dt[t]) contK++;

            }
            if (!contK == 0)Si.push_back(t);
        }
        Si.push_back(k - 1);

        S.push_back(Si);


    }



    return S;

}


