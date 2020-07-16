#include "ModeloPmedianasCapacitado.h"


ModeloPmedianasCapacitado::ModeloPmedianasCapacitado(string s, int p) : Model(s, p) {
    //Definição das VARIAVEIS de DECISAO=======================================

    //Matriz de variaveis x[i][j]: se o local i seja atendido pelo centro j
    NumVarMatrix x(this->env, this->dados.n); //Cria n linhas para a matriz x
    for (int i = 0; i < this->dados.n; i++) {
        //para cada linha, cria-se um array de m variaveis binárias:
        x[i] = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);
    }

    //Vetor de facilidade y[j], se o centro será alocado em j
    IloNumVarArray y(this->env, this->dados.n, 0, 1, ILOINT);

    // Função Objetivo===============================================================


    IloExpr obj(this->env);
    for (int i = 0; i < this->dados.n; i++) {
        for (int j = 0; j < this->dados.n; j++) {
            obj += x[i][j] * this->dados.Dist[i][j];
        }
    }

    this->model.add(IloMinimize(this->env, obj));



    // Restrições===================================================================



    IloExpr sum(this->env); // numero maximo de facilidade
    sum = IloSum(y);
    this->constraints.add(sum <= this->dados.p);
    sum.end();


    for (IloInt i = 0; i < this->dados.n; i++) { // todo local tem q ser atendido
        IloExpr sum(this->env);
        sum = IloSum(x[i]);
        this->constraints.add(sum == 1);
        sum.end();
    }


    for (IloInt i = 0; i < this->dados.n; i++) { //Xij <=Yj
        for (IloInt j = 0; j < this->dados.n; j++) {
            this->constraints.add(x[i][j] - y[j] <= 0);
        }
    }


    for (IloInt j = 0; j < this->dados.n; j++) { 
        IloExpr sum(this->env);
        for (int i=0;i<this->dados.n;i++){
            sum += x[i][j] * this->dados.Demanda[i];
        }
        
        this->constraints.add(sum - this->dados.Q <= 0);
        sum.end();
    }

    this->model.add(this->constraints);
}