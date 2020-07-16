#pragma once


#ifndef MODEL_H
#define MODEL_H

#include "Leitor_de_dados.h"
#include <ilcplex/ilocplex.h>
typedef IloArray<IloNumVarArray> NumVarMatrix;

class Model
{
	public:
		Model(string s,int p);
		~Model();
		void resolve();
		double imprime_solucao();
		bool tem_solucao();

		Leitor_de_Dados dados;
		IloEnv env; ///Cria o ambiente: env
		IloModel model; ///Cria o modelo passando o ambiente
		IloCplex cplex1;
		IloRangeArray constraints; ///Vetor de restrições: constraints

};

#endif