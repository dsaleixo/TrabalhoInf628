#include "EpslonRestrito.h"




EpslonRestrito::EpslonRestrito(string s, int p, string saida) : MMO(s, p, saida) {

}


void EpslonRestrito::rodar() {

	double A1, A2, B1, B2;
	model.setFuncaoObj(model.getFuncaoObjCusto());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	A1 = model.getValorCusto();

	model.reset();


	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	B2 = model.getValorRaio();

	model.reset();



	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();
	model.addRestricao(model.getFuncaoObjCusto() <= A1);
	model.finalizarestricoes();
	model.resolve();

	if (!model.tem_solucao())return;
	this->salva_resultado();
	A2 = model.getValorRaio();
	model.reset();




	model.setFuncaoObj(model.getFuncaoObjCusto());
	model.geraRestricoesbase();
	model.addRestricao(model.getFuncaoObjRaio() <= B2);
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	this->salva_resultado();
	B1 = model.getValorCusto();

	model.reset();


	rodar(A1, A2, B1, B2);

}
void EpslonRestrito::rodar(double A1, double A2, double B1, double B2) {


	while (!(abs(A1 - B1) < 0.5 && abs(B2 - A2) < 0.5)) {

		double C1;
		model.setFuncaoObj(model.getFuncaoObjCusto());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjRaio() <= A2-1);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao())return;
	
		C1 = model.getValorCusto();
		model.reset();


		double C2;
		model.setFuncaoObj(model.getFuncaoObjRaio());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjCusto() <= C1);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao())return;
		this->salva_resultado();
		C2 = model.getValorRaio();
		model.reset();

		A1 = C1;
		A2 = C2;
	}




}