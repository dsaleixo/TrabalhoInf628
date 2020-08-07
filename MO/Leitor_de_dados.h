#pragma once


#ifndef LEITOR_DE_DADOS_H
#define LEITOR_DE_DADOS_H

#include <iostream>
#include <ilcplex/ilocplex.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

typedef IloArray<IloNumArray> NumMatrix; //Tipo de dados Matriz bidimensional de numeros reais
typedef IloArray<NumMatrix> NumMatrix3D;

struct Ponto
{
	int x, y;


};



class Leitor_de_Dados{

	public:
		void Ler(IloEnv env,string s,int p);
		void Ler2(IloEnv env, string s, int p);
		Leitor_de_Dados();
		void floyd();
		void calcula_distancia_entre_locais();
		vector<int> calcula_D();// nome confuso, este metodo não calculas as distancias
		vector<int> calcula_Menores();
		NumMatrix3D cria_matrizA(IloEnv env, vector<int> Dt, int k);
		vector<vector<int>> coleta_Si(IloEnv env, vector<int> Dt, int k);
		int distancia_entre_pontos(Ponto p1, Ponto p2);
		~Leitor_de_Dados();




		//variavaeis 
		int n; //numero de locais
		int p; //numero de centro
		int **Dist;
		IloInt Q;
		vector<int> Custo;
		vector<Ponto> pontos;
		IloNumArray Demanda;
		

};
#endif




