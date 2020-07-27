#include "ModeloCP1.h"



ModeloCP1::ModeloCP1(string s,int p) : Model(s,p) {

    this->D = this->dados.calcula_D();
     this->Z_size = D.size();

   

     this->S = this->dados.coleta_Si(this->env,this->D, this->Z_size);

    //Definição das VARIAVEIS de DECISAO=======================================

   //Matriz de variaveis k[j]
    Z = IloNumVarArray(this->env, Z_size, 0, 1, ILOINT);


    //Vetor de facilidade y[j], se o centro será alocado em j
    y = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);

    

   
   


   
}


IloExpr ModeloCP1::getFuncaoObjRaio(int inicio, int fim) {
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
void ModeloCP1::geraRestricoesbase(int inicio, int fim) {

    IloExpr sum(this->env); // numero maximo de facilidade
    sum = IloSum(y);
    this->constraints.add(sum <= this->dados.p);
    sum.end();

  
    sum = IloExpr(this->env); // numero maximo de facilidade
    sum = IloSum(y);
    this->constraints.add(sum >= 1);
    sum.end();

    for (IloInt i = 0; i < this->dados.n; i++) {
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

    //Matriz de variaveis k[j]
    Z = IloNumVarArray(this->env, Z_size, 0, 1, ILOINT);


    //Vetor de facilidade y[j], se o centro será alocado em j
    y = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);
   

}


int ModeloCP1::getValorRaio(int inicio,int fim) {
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