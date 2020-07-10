#include "ModeloCalikTansel.h"


ModeloCalikTansel::ModeloCalikTansel(string s,int p) : Model(s,p){

	IloNumArray D = this->dados.calcula_D(this->env);
	IloInt Z_size = D.getSize();

	NumMatrix3D A = this->cria_matrizA(D,Z_size);

	

	//Matriz de variaveis k[j]
	IloNumVarArray Z(this->env, Z_size, 0, 1, ILOINT);


	//Vetor de facilidade y[j], se o centro será alocado em j
	IloNumVarArray y(this->env, this->dados.n, 0, 1, ILOINT);

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




NumMatrix3D ModeloCalikTansel::cria_matrizA(IloNumArray D,int k) {
	NumMatrix3D A(this->env, this->dados.n);
	for (int i = 0; i < this->dados.n; i++) {
		A[i] = NumMatrix(env, this->dados.n);
		for (int j = 0; j < this->dados.n; j++) {
			A[i][j] = IloNumArray(env, k);
		}
	}

	for (int i = 0; i < this->dados.n; i++) {
		for (int j = 0; j < this->dados.n; j++) {
			for (int t = 0; t < k; t++) {
				if (this->dados.D[i][j]<=D[t]) {
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