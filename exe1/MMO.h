#pragma once

#ifndef MMO_H
#define MMO_H

#include "ModeloCP1.h"



class MMO
{
	public:
		ModeloCP1 model;
		ofstream out;


		MMO(string s, int p,string saida);
		virtual void rodar()=0;
		void salva_resultado();
		~MMO();


};

#endif