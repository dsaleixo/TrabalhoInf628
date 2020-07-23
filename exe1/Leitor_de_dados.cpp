#include "Leitor_de_dados.h"
#include <set>
#include <vector>
#include <iterator>

Leitor_de_Dados::Leitor_de_Dados() {

}

Leitor_de_Dados::~Leitor_de_Dados() {
    for (int i = 0; i < n; i++)
        delete[] Dist[i];

    delete[] Dist;
}

void Leitor_de_Dados::Ler(IloEnv env, string s,int p){

    // LER DADOS

    ifstream in(s+".txt");
    if (!in) {
        throw "Erro ao abrir o arquivo";
        
    }
 
    int m;

    in >> this->n >>m>> this->p ;
    this->p = p;

   

    this->Dist = new int*[this->n]; // inicialaiza a matrix D
    for (int i = 0; i < this->n; i++) {
        this->Dist[i] = new int[this->n];
        for (int j = 0; j < this->n; j++)this->Dist[i][j] = 0;
    }

  

    int a, b, c;
    for (int i = 0; i < m; i++) { // Le as distancia do arquivo 
        in >> a >> b >> c;
        this->Dist[a - 1][b - 1] = c;
        this->Dist[b - 1][a - 1] = c;
    }

    floyd();// algortitmo floyd para completar a tabela

    
   
    in.close();

    ifstream in2(s + "Custo.txt");
    if (!in2) {
        throw "Erro ao abrir o arquivo";

    }

    int aux;
    for (int i = 0; i < this->n; i++) {
        in2 >> aux;
        Custo.push_back(aux);
    }
    

    in2.close();
}


void Leitor_de_Dados::Ler2(IloEnv env, string s, int p) {

    // LER DADOS

    ifstream in(s);
    if (!in) {
        throw "Erro ao abrir o arquivo";

    }



    in >> this->n >> this->p >> this->Q;
    this->p = p;

    Demanda = IloNumArray(env, this->n);
    /*
    this->Dist = NumMatrix(env, this->n); // inicialaiza a matrix D
    for (int i = 0; i < this->n; i++) {
        this->Dist[i] = IloNumArray(env, this->n);
    }
    */
    double a, d;

    for (int i = 0; i < this->n; i++) { // Le as distancia do arquivo 
        Ponto ponto;
        in >> a >> ponto.x >> ponto.y >> d;
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
            this->Dist[i][j] = aux;
            this->Dist[j][i] = aux;
            
        }
    }


}


void Leitor_de_Dados::floyd() {
    int i, j, k;
    for (k = 0; k < this->n; k++) {
        for (i = 0; i < this->n; i++) {
            for (j = 0; j < this->n; j++) {
                if ((this->Dist[i][k] * this->Dist[k][j] != 0) && (i != j))
                {
                    if ((this->Dist[i][k] + this->Dist[k][j] < this->Dist[i][j]) || 
                                                                (this->Dist[i][j] == 0))
                    {
                        this->Dist[i][j] = this->Dist[i][k] + this->Dist[k][j];
                    }
                }
            }
        }
    }
}

vector<int> Leitor_de_Dados::calcula_D() {
    set <int, less <int> > s1;

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            s1.insert(this->Dist[i][j]);
        }
    }

    vector<int> v;

    set <int, less <int> > ::iterator itr;
  
    for (itr = s1.begin(); itr != s1.end(); ++itr)
    {
        v.push_back(*itr);
       
    }


    return v;
}



NumMatrix3D Leitor_de_Dados::cria_matrizA(IloEnv env,IloIntArray Dt, int k) {
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
                if (this->Dist[i][j] <= Dt[t]) {
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



vector<vector<int>> Leitor_de_Dados::coleta_Si(IloEnv env, vector<int> Dt, int k) {

    vector<vector<int>> S;

    for (int i = 0; i < this->n; i++) {
        vector<int> Si;
        for (int t = 0; t < k - 1; t++) {
            int contK = 0;
            int contK1 = 0;
            for (int j = 0; j < this->n; j++) {
                if (this->Dist[i][j] == Dt[t]) contK++;

            }
            if (!contK == 0)Si.push_back(t);
        }
        Si.push_back(k - 1);

        S.push_back(Si);


    }



    return S;

}


