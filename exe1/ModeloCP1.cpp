#include "ModeloCP1.h"



ModeloCP1::ModeloCP1(string s,int p) : Model(s,p) {

    IloNumArray D = this->dados.calcula_D(this->env);
    IloInt Z_size = D.getSize();

   

    vector<vector<int>> S = this->dados.coleta_Si(this->env,D, Z_size);

    //Definição das VARIAVEIS de DECISAO=======================================

   //Matriz de variaveis k[j]
    IloNumVarArray Z(this->env, Z_size, 0, 1, ILOINT);


    //Vetor de facilidade y[j], se o centro será alocado em j
    IloNumVarArray y(this->env, this->dados.n, 0, 1, ILOINT);

    // Função Objetivo===============================================================


    IloExpr obj(this->env);
    obj += D[0];
    for (int i = 1; i < Z_size; i++) {
        obj += (D[i] - D[i - 1]) * Z[i];
    }

    this->model.add(IloMinimize(this->env, obj));

    // Restrições===================================================================


    IloExpr sum(this->env); // numero maximo de facilidade
    sum = IloSum(y);
    this->constraints.add(sum <= this->dados.p);
    sum.end();
   
   

    for (IloInt i = 0; i < this->dados.n; i++) {
        for (int k = 0; k < S[i].size(); k++) {
            IloExpr sum(this->env);
          
            sum += Z[S[i][k]];
            for (IloInt j = 0; j < this->dados.n; j++) {
                if (this->dados.D[i][j] < D[S[i][k]]) {
                    sum += y[j];
                }
            }
            this->constraints.add(sum >= 1);
            sum.end();
        }

    }

    for (int i = 0; i < Z_size - 1; i++) {// restrição mais importante
        this->constraints.add(Z[i] - Z[i+1] >= 0);
     
    }
    this->model.add(this->constraints);

  


   
}


