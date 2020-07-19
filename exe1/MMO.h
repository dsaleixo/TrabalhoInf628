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
 


class MMO
{
	public:
		ModeloCP1 model;
		set<Solucao,less<Solucao>> paleto;

		MMO(string s, int p,string saida);
		void imprime(ofstream &out);
		virtual void rodar()=0;
		void salva_resultado();
		void setP(int p);
		void reset();
		~MMO();


};

#endif