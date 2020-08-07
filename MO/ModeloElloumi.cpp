#include "ModeloElloumi.h"




ModeloElloumi::ModeloElloumi(string s,int p) : Model(s,p) {

    this->D = this->dados.calcula_D();
    this->Z_size = D.size();


    //Definição das VARIAVEIS de DECISAO=======================================

   //Matriz de variaveis k[j]
    this->Z =IloNumVarArray(this->env, Z_size, 0, 1, ILOINT);
    

    //Vetor de facilidade y[j], se o centro será alocado em j
    this->y = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);

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


    for (IloInt i = 0; i < this->dados.n; i++) { // vai ter pelo menos um centro
        IloExpr sum(this->env);
        sum = IloSum(y);
        this->constraints.add(sum >= 1);
        sum.end();
    }



    for (IloInt i = 0; i < this->dados.n; i++) {
        for (IloInt k = 1; k < Z_size; k++) {
            IloExpr sum(this->env);
            sum += Z[k];
            for (IloInt j = 0; j < this->dados.n; j++) {
                if (this->dados.Dist[i][j] < D[k]) {
                    sum += y[j];
                }
            }
            this->constraints.add(sum >= 1);
            sum.end();
        }

    }
  


    this->model.add(this->constraints);



}


