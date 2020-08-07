#include "ModeloCP1.h"



ModeloCP1::ModeloCP1(string s,int p,bool montar,int heuristica) : Model(s,p) {

    this->D = this->dados.calcula_D();
     this->Z_size = D.size();
     this->Menores = this->dados.calcula_Menores();

    
     this->S = this->dados.coleta_Si(this->env,this->D, this->Z_size);

     this->constroiN();

    

    //Definição das VARIAVEIS de DECISAO=======================================


     if (heuristica==0) {
         this->inicio = 0;
         this->fim = this->Z_size;
        
     }
     else if(heuristica==1){
         this->inicio = this->buscaBinaria(this->Menores[p]);
         this->fim = this->buscaBinaria(this->maiorD());
         
         
     }
     else {
         this->inicio = this->buscaBinaria(this->Menores[p]);
         this->fim = this->buscaBinaria(this->GRASP_PR(heuristica));
        
     }
     


     if (montar) {

         this->CriaVariavel();
         this->setFuncaoObj(this->getFuncaoObjRaio());
         this->geraRestricoesbase();
         this->finalizarestricoes();
    }

   
}




IloExpr ModeloCP1::getFuncaoObjRaio() {
    IloExpr obj(this->env);
    obj += D[inicio];
   
    for (int i = 1+inicio; i < fim; i++) {
        int k = i - inicio;
        int j = i - 1;
     
        obj += (this->D[i] - this->D[j]) * this->Z[k];
      
    }
    return obj;
}



IloExpr ModeloCP1::getFuncaoObjCusto() {
    IloExpr obj(this->env);
    for (int i = 0; i < this->dados.n; i++) {
        obj += this->dados.Custo[i] * this->y[i];
    }
    return obj;
}

void ModeloCP1::setFuncaoObj(IloExpr obj) {
    this->model.add(IloMinimize(this->env, obj));
}
void ModeloCP1::geraRestricoesbase() {

    IloExpr sum(this->env); // numero maximo de facilidade
    sum = IloSum(y);
    this->constraints.add(sum <= this->dados.p);
    sum.end();

  
    sum = IloExpr(this->env); // numero maximo de facilidade
    sum = IloSum(y);
    this->constraints.add(sum >= 1);
    sum.end();
   
    for (int i = 0; i < this->dados.n; i++) {

        

            IloExpr sum(this->env);
            sum += Z[0];
            for (IloInt j = 0; j < this->dados.n; j++) {
                if (this->dados.Dist[i][j] < D[inicio]) {
                    sum += y[j];
                }
            }
            this->constraints.add(sum >= 1);
            sum.end();


            IloExpr sum2(this->env);
            int aux = (fim - inicio) - 1;
            sum2 += Z[aux];
            for (IloInt j = 0; j < this->dados.n; j++) {
                if (this->dados.Dist[i][j] < D[inicio+aux ]) {
                    sum2 += y[j];
                }
            }
            this->constraints.add(sum2 >= 1);
            sum2.end();
            


        for (int k = 0; k < S[i].size(); k++) {
            

            if (S[i][k] >= inicio  && S[i][k] < fim) {
                IloExpr sum(this->env);
                sum += Z[S[i][k]-inicio];
                for (IloInt j = 0; j < this->dados.n; j++) {
                    if (this->dados.Dist[i][j] < D[S[i][k]]) {
                        sum += y[j];
                    }
                }
                this->constraints.add(sum >= 1);
                sum.end();
            }
        }

    }

    for (int i = 0; i < (fim-inicio) - 1; i++) {// restrição mais importante
        this->constraints.add(Z[i] - Z[i + 1] >= 0);

    }
}
void ModeloCP1::addRestricao(IloRange rest) {
    this->constraints.add(rest);
}


int ModeloCP1::buscaBinaria(int x) {
    int e = -1, d = Z_size; // atenção!
    while (e < d - 1) {
        int m = (e + d) / 2;
        if (D[m] < x) e = m;
        else d = m;
    }
    return d;
}


void ModeloCP1::finalizarestricoes() {
    this->model.add(this->constraints);
}

void ModeloCP1::reset() {
    this->model.end();
    this->constraints.end();
    this->cplex1.end();
    
    env.end();
  
    env = IloEnv();
    this->model = IloModel(this->env);
    this->constraints = IloRangeArray(this->env);
    
  
   

}

void ModeloCP1::CriaVariavel() {

    //Matriz de variaveis k[j]
    Z = IloNumVarArray(this->env, fim - inicio, 0, 1, ILOINT);


    //Vetor de facilidade y[j], se o centro será alocado em j
    y = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);

}



int ModeloCP1::getValorRaio() {
    int result;
    
    result = D[inicio];
    int i = 1 + inicio;
    for (; i < fim; i++) {
        int k = i - inicio;
       
        if (this->cplex1.getValue(this->Z[k]) < 0.5 )break;
    }
    return this->D[i-1];

}
int ModeloCP1::getValorCusto() {
    IloInt result=0;
    for (int i = 0; i < this->dados.n; i++) {
        if (this->cplex1.getValue(y[i]) >= 0.5)
            result += this->dados.Custo[i];
        
    }
    
    return result;
}


void  ModeloCP1::setInicio(int i) {
    this->inicio = i;
}

void  ModeloCP1::setFim(int f) {
    this->fim = f;
}


void ModeloCP1::GreedyRandomized(set<int>& s, float alpha,int limite) {
     srand((unsigned)time(0)); //para gerar números aleatórios reais.
    int aleatorio =  rand() % (this->dados.n ) ;

    s.insert(this->menormaiorD()  );

    while (s.size() < this->dados.p&& s.size()<limite) {
        
        srand((unsigned)time(0));
        int k = 5; // ver dps
        if ((rand()% 100)/100.0 < alpha) {
            int w = acharW(s, true);
            int v = this->NN[w][rand() % k].indice;
            s.insert(v);
        }
        else {
            int v = rand() % this->dados.n;
            s.insert(v);
        }

    }

 
}

int ModeloCP1::acharW(set<int>& s, bool ind) {
    int w = -1;
    int maior = 0;

    for (int i = 0; i < this->dados.n; i++) {
        int menor =1000000;
       
        if (s.find(i) != s.end())continue;
            for (int j : s) {
              
                if (this->dados.Dist[i][j] < menor) {
                    menor = this->dados.Dist[i][j];
                }
                if (maior > menor)break;
            }
        
        if (menor > maior) {
            w = i;
            maior = menor;
        }
    }
    if (ind) return w;
    else return maior;

}

void ModeloCP1::constroiN() {
    for (int i = 0; i < this->dados.n; i++) {
        vector<N> Nv;
        for (int j = 0; j < this->dados.n; j++) {
            N n;
            n.indice = j;
            n.Dist = this->dados.Dist[i][j];
            Nv.push_back(n);
        }
        sort(Nv.begin(), Nv.end());
        NN.push_back(Nv);
    }
}

bool operator<(const N& a, const N& b)
{
    return a.Dist < b.Dist;

}

void ModeloCP1::Tabu(set<int>& s, int Lmax) {
    
    for (int i = 0; i < Lmax; i++) {
        set<int> s1 = s;
        int w = this->NN[this->acharW(s1, true)][rand() % 5].indice;
        srand((unsigned)time(0));
        int remove = rand() % s1.size();
        s1.erase(remove);
        s1.insert(w);
        int D1= this->acharW(s, false);
        int D2 = this->acharW(s1, false);
        if (D1 > D2) {
            s = s1;
        }
    }

}


set<int> ModeloCP1::PathRelinking(set<int>& sc, set<int>& se, double beta) {
    set<int> sr = sc;
    vector<Q> q;

    set<int> seIsc;
    set_intersection(sc.begin(), sc.end(),se.begin(), se.end(),inserter(seIsc, seIsc.begin()));

    set<int> sc1;
    set_difference(sc.begin(), sc.end(),
        seIsc.begin(), seIsc.end(),
        inserter(sc1, sc1.begin()));

    set<int> se1;
    set_difference(se.begin(), se.end(),
        seIsc.begin(), seIsc.end(),
        inserter(se1, se1.begin()));

    for (int i = 0; i < beta * seIsc.size();i++) {
        for (int vc : sc1) {
            for (int ve : se1) {
                set<int> St = sr;
                St.erase(vc);
                St.erase(ve);
                Q qi;
                qi.s = St;
                qi.vc = vc;
                qi.ve = ve;
                q.push_back(qi);
            }
        }
        int ind = -1;
        int menor = 1000000;
        int ii = 0;
        for (Q qq : q) {
            int w = this->acharW(qq.s,false);
            if (menor > w) {
                ind = ii;
                menor = w;
            }
            ii++;
        }

        sc1.erase(q[ind].vc);
        se1.erase(q[ind].ve);
        q.clear();

    }
    this->Tabu(sr, 5);
    return sr;
}

int ModeloCP1::GRASP_PR(int heuristica){
    
    int menor = 10000;

    for (int i = 0; i < 1; i++) {
        set<int> S;

        this->GreedyRandomized(S, 0.5, 1000);
        if(heuristica==3)this->Tabu(S, 3);
        int w = this->acharW(S,false);
        if (menor > w) {
            menor = w;
        }
    }
    
   
    return menor;
}


int ModeloCP1::maiorD() {
    int menor = 1000000;

    for (int i = 0; i < this->dados.n; i++) {
        if (NN[i][(this->dados.n - 1) - this->dados.p].Dist<menor) {
            menor = NN[i][(this->dados.n - 1) - this->dados.p].Dist;
       }
    }
    return menor;
}
int ModeloCP1::menormaiorD() {
    int menor = 1000000;
    int ind = 0;
    for (int i = 0; i < this->dados.n; i++) {
        if (NN[i][(this->dados.n - 1) ].Dist < menor) {
            menor = NN[i][(this->dados.n - 1) ].Dist;
            ind = i;
        }
    }
    return ind;
}

int  ModeloCP1::seraMinimo() {
    set<int, greater<int> > s;
    for (int i = 0; i < this->dados.n; i ++) {
        for (int j = 0; j < this->dados.p; j++) {
            s.insert(this->NN[i][j].Dist);
        }
    }
    set <int, less <int> > ::iterator itr= s.begin();
    
        for (int i = 0; i < this->dados.p; i++)++itr;
    
        return *itr;

}