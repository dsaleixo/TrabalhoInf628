#include "ModeloCP2.h"



ModeloCP2::ModeloCP2(string s, int p) : Model(s, p) {

    IloNumArray D = this->dados.calcula_D(this->env);
    IloInt Z_size = D.getSize();

    

    vector<vector<int>> S = this->dados.coleta_Si(this->env,D, Z_size);

    //Definição das VARIAVEIS de DECISAO=======================================

    IloFloatVar r(this->env);


    //Vetor de facilidade y[j], se o centro será alocado em j
    IloNumVarArray y(this->env, this->dados.n, 0, 1, ILOINT);

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
        for (int k = 0; k < S[i].size(); k++) {
            IloExpr sum(this->env);

            
            for (IloInt j = 0; j < this->dados.n; j++) {
                if (this->dados.D[i][j] < D[S[i][k]]) {
                    sum += y[j];
                }
            }
            sum = r + D[S[i][k]] *sum;
            this->constraints.add(sum - D[S[i][k]] >= 0);
            sum.end();
        }

    }


    this->model.add(this->constraints);





}

