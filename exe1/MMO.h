#pragma once

#ifndef MMO_H
#define MMO_H

#include "ModeloCP1.h"
#include <set>
#include <iterator>
#include <algorithm>

struct Solucao
{
	int f1, f2;
};
 

struct Intervalo1
{
	double A1, A2, B1, B2, a;

};

bool operator<(const Intervalo1& a, const Intervalo1& b);

class MMO
{
	public:
		ModeloCP1 model;
		set<Solucao,less<Solucao>> paleto;

		MMO(string s, int p,string saida);
		void imprime(ofstream &out);
		virtual void rodar()=0;
		void salva_resultado(int inicio, int fim);
		void salva_resultado();
		void setP(int p);
		void reset();
		void deleta_ambiente();
		~MMO();


};

#endif