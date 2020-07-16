#include "OMOSP.h"

OMOSP::OMOSP(string s, int p,string saida,int num_w): MMO(s,p,saida) {
	this->num_w = num_w;
}

void OMOSP::rodar() {

	double enc = 1.0 / this->num_w;
	for (double i = 0; i < this->num_w; i++) {
		double w = i * enc;
		model.setFuncaoObj(w * model.getFuncaoObjRaio() + (1 - w) * model.getFuncaoObjCusto());
		model.geraRestricoesbase();
		model.finalizarestricoes();
		model.resolve();
		this->salva_resultado();
		model.reset();
	}

	double w = 1;
	model.setFuncaoObj(w * model.getFuncaoObjRaio() + (1 - w) * model.getFuncaoObjCusto());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	this->salva_resultado();
	model.reset();

}