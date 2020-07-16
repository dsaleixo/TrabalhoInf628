#include "ModeloCalikTansel.h"


ModeloCalikTansel::ModeloCalikTansel(string s,int p) : Model(s,p){

	this->D = this->dados.calcula_D(this->env);
	this->Z_size = this->D.getSize();

	A = this->dados.cria_matrizA(this->env,this->D,this->Z_size);

	

	//Matriz de variaveis k[j]
	Z = IloNumVarArray(this->env, this->Z_size, 0, 1, ILOINT);


	//Vetor de facilidade y[j], se o centro será alocado em j
	y = IloNumVarArray(this->env, this->dados.n, 0, 1, ILOINT);

	// Função Objetivo===============================================================


	IloExpr obj(this->env);

	for (int i = 0; i < Z_size; i++) {
		obj += D[i] * Z[i];
	}

	this->model.add(IloMinimize(this->env, obj));


	// Restrições===================================================================


	IloExpr sum(this->env); // numero maximo de facilidade
	sum = IloSum(y);
	this->constraints.add(sum <= this->dados.p);
	sum.end();


	
		IloExpr sum2(this->env);
		sum2 = IloSum(Z);
		this->constraints.add(sum2 == 1);
		sum2.end();
	


	
	for (IloInt i = 0; i < this->dados.n; i++) {
		for (IloInt k = 0; k < Z_size; k++) {
			IloExpr sum(this->env);
			for (IloInt j = 0; j < this->dados.n; j++) {
			
					sum += A[i][j][k]*y[j];
				
			}
			this->constraints.add(sum - Z[k] >= 0);
			sum.end();
		}

	}
	

	
    this->model.add(this->constraints);

}




