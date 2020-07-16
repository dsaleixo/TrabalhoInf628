#include "OMOERestrito.h"

OMOERestrito::OMOERestrito(string s, int p, string saida,int decremento) : MMO(s, p, saida) {
	this->descremento = decremento;
}

void OMOERestrito::rodar() {
	double tem_solucao;

	model.setFuncaoObj(model.getFuncaoObjCusto());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	double f1 = model.getValorCusto();
	this->salva_resultado();
	model.reset();
	

	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();
	model.addRestricao(model.getFuncaoObjCusto() <= f1);
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	this->salva_resultado();
	double epslon = model.getValorRaio();
	model.reset();

	while (true) {
		model.setFuncaoObj(model.getFuncaoObjCusto());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjRaio() <= epslon);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao())return;
		this->salva_resultado();
		model.reset();
		epslon -= this->descremento;
	}






}