#include "ModeloCP1.h"



ModeloCP1::ModeloCP1(string s,int p) : Model(s,p) {

    this->D = this->dados.calcula_D(this->env);
     this->Z_size = D.getSize();

   

     this->S = this->dados.coleta_Si(this->env,this->D, this->Z_size);

    //Definição das VARIAVEIS de DECISAO=======================================

   //Matriz de variaveis k[j]
    Z = IloNumVarArray(this->env, Z_size, 0, 1, ILOINT);


    //Vetor de facilidade y[j], se o centro será alocado em j
    y = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);

    

   
   


   
}


IloExpr ModeloCP1::getFuncaoObjRaio() {
    IloExpr obj(this->env);
    obj += D[0];
    for (int i = 1; i < this->Z_size; i++) {
        obj += (this->D[i] - this->D[i - 1]) * this->Z[i];
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

    for (IloInt i = 0; i < this->dados.n; i++) {
        for (int k = 0; k < S[i].size(); k++) {
            IloExpr sum(this->env);

            sum += Z[S[i][k]];
            for (IloInt j = 0; j < this->dados.n; j++) {
                if (this->dados.Dist[i][j] < D[S[i][k]]) {
                    sum += y[j];
                }
            }
            this->constraints.add(sum >= 1);
            sum.end();
        }

    }

    for (int i = 0; i < Z_size - 1; i++) {// restrição mais importante
        this->constraints.add(Z[i] - Z[i + 1] >= 0);

    }
}
void ModeloCP1::addRestricao(IloRange rest) {
    this->constraints.add(rest);
}

void ModeloCP1::finalizarestricoes() {
    this->model.add(this->constraints);
}

void ModeloCP1::reset() {
    this->model.end();
    this->constraints.end();
    this->cplex1.end();
    
    env.removeAllProperties();
    env = IloEnv();
    this->model = IloModel(this->env);
    this->constraints = IloRangeArray(this->env);

    Z = IloNumVarArray(this->env, Z_size, 0, 1, ILOINT);


    //Vetor de facilidade y[j], se o centro será alocado em j
    y = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);


}


double ModeloCP1::getValorRaio() {
    double result;
    result = D[0];
    for (int i = 1; i < this->Z_size; i++) {
        result += (this->D[i] - this->D[i - 1]) * this->cplex1.getValue(this->Z[i]);
        if (this->cplex1.getValue(this->Z[i]) == 0)break;
    }
    return result;

}
double ModeloCP1::getValorCusto() {
    double result=0;
    for (int i = 0; i < this->dados.n; i++) {
        result += this->dados.Custo[i] * this->cplex1.getValue(y[i]);
    }
    return result;
}