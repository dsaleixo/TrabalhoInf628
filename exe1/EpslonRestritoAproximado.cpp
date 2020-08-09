#include "EpslonRestritoAproximado.h"




EpslonRestritoAproximado::EpslonRestritoAproximado(string s, int p, string saida,int n,bool otimizado) : MMO(s, p, saida) {
	this->n = n;
	this->otimizado = otimizado;
}


void EpslonRestritoAproximado::rodar() {

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
void EpslonRestritoAproximado::rodar(double A1, double A2, double B1, double B2) {


	double delta = (A2 - B2) / this->n;;

	for (double e = A2 - delta; e - B2 > 0.005; e -= delta) {
		
		double C1;
		model.setFuncaoObj(model.getFuncaoObjCusto());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjRaio() <= e);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao()) {
			model.reset();
			continue;
		}
		C1 = model.getValorCusto();
		model.reset();

		
		model.setFuncaoObj(model.getFuncaoObjRaio());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjCusto() <= C1);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao()) {
			model.reset();
			continue;
		}
		this->salva_resultado();
		
		model.reset();




	}



	delta = (B1 - A1) / this->n;;
	
	for (double e = B1 - delta; e - A1 > 0.005; e -= delta) {

		double C1;
		model.setFuncaoObj(model.getFuncaoObjRaio());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjCusto() <= e);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao()) {
			model.reset();
			continue;
		}
		C1 = model.getValorRaio();
		model.reset();

	
		model.setFuncaoObj(model.getFuncaoObjCusto());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjRaio() <= C1);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao()) {
			model.reset();
			continue;
		}
		this->salva_resultado();
		
		model.reset();




	}





}