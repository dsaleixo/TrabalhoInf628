#pragma once


#ifndef MODEL_H
#define MODEL_H

#include "Leitor_de_dados.h"
#include <ilcplex/ilocplex.h>

class Model
{
	public:
		Model(string s);
		void resolve();
		void imprime_solucao();

		Leitor_de_Dados dados;
		IloEnv env; ///Cria o ambiente: env
		IloModel model; ///Cria o modelo passando o ambiente
		IloCplex cplex1;
		IloRangeArray constraints; ///Vetor de restri��es: constraints

};

#endif