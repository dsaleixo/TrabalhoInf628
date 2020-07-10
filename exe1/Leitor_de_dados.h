#pragma once


#ifndef LEITOR_DE_DADOS_H
#define LEITOR_DE_DADOS_H

#include <iostream>
#include <ilcplex/ilocplex.h>
#include <fstream>


using namespace std;

typedef IloArray<IloNumArray> NumMatrix; //Tipo de dados Matriz bidimensional de numeros reais

class Leitor_de_Dados{

	public:
		void Ler(IloEnv env,string s,int p);
		Leitor_de_Dados();
		void floyd();
		IloNumArray calcula_D(IloEnv env);

		//variavaeis 
		IloInt n; //numero de locais
		IloInt p; //numero de centro
		NumMatrix D;

};
#endif




