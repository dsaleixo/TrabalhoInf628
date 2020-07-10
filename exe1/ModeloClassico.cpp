#include "ModeloClassico.h"



ModeloClassico::ModeloClassico(string s,int p) : Model(s,p) {
	
    //Definição das VARIAVEIS de DECISAO=======================================

    //Matriz de variaveis x[i][j]: se o local i seja atendido pelo centro j
    NumVarMatrix x(this->env, this->dados.n); //Cria n linhas para a matriz x
    for (int i = 0; i < this->dados.n; i++) {
        //para cada linha, cria-se um array de m variaveis binárias:
        x[i] = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);
    }

    //Vetor de facilidade y[j], se o centro será alocado em j
    IloNumVarArray y(this->env, this->dados.n, 0, 1, ILOINT);

    //Raio R
    IloFloatVar r(this->env);


    // Função Objetivo===============================================================


    IloExpr obj(this->env);
    obj += r;
    this->model.add(IloMinimize(this->env, obj));



    // Restrições===================================================================


    IloExpr sum(this->env); // numero maximo de facilidade
    sum = IloSum(y);
    this->constraints.add(sum <= this->dados.p);
    sum.end();



    for (IloInt i = 0; i < this->dados.n; i++) { 
        for (IloInt j = 0; j < this->dados.n; j++) {
            this->constraints.add(x[i][j] - y[j] <= 0);
        }
    }

    for (IloInt i = 0; i < this->dados.n; i++) { // todo local tem q ser atendido
        IloExpr sum(this->env);
        sum = IloSum(x[i]);
        this->constraints.add(sum == 1);
        sum.end();
    }


    for (IloInt i = 0; i < this->dados.n; i++) { // lance do raio
        IloExpr sum(env);
        sum = IloScalProd(this->dados.D[i], x[i]);
        this->constraints.add(sum - r <= 0);
        sum.end();
    }


    this->model.add(this->constraints);



}


