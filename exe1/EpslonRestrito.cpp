#include "EpslonRestrito.h"




EpslonRestrito::EpslonRestrito(string s, int p, string saida,bool otimizado) : MMO(s, p, saida) {
	this->otimizado = otimizado;
}


void EpslonRestrito::rodar() {

	this->model.setInicio(0);

	this->model.setFim(this->model.Z_size);



	double A1, A2, B1, B2;
	int i, f;


	model.CriaVariavel();
	model.setFuncaoObj(model.getFuncaoObjCusto());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	A1 = model.getValorCusto();
	f = this->model.buscaBinaria(this->model.getValorRaio() + 1);
	model.reset();

	if (this->otimizado) {
		i = this->model.buscaBinaria(this->model.Menores[this->model.dados.p]);
		this->model.setInicio(i);
		int aux = this->model.buscaBinaria(this->model.maiorD()) + 1;
		if (f < aux)this->model.setFim(f);
		else this->model.setFim(aux);

	}
	model.CriaVariavel();
	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	B2 = model.getValorRaio();
	i = this->model.buscaBinaria(B2);
	model.reset();



	if (this->otimizado) {
		this->model.setInicio(i);
		this->model.setFim(f);
	}
	model.CriaVariavel();
	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();
	model.addRestricao(model.getFuncaoObjCusto() <= A1);
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	this->salva_resultado();
	A2 = model.getValorRaio();
	model.reset();


	if (this->otimizado) {
		this->model.setInicio(i);
		this->model.setFim(f);
	}
	model.CriaVariavel();
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

		if (this->otimizado) {
			this->model.setInicio(this->model.buscaBinaria(B2));

			this->model.setFim(this->model.buscaBinaria(A2) + 1);
		}

		int C1;
		model.CriaVariavel();
		model.setFuncaoObj(model.getFuncaoObjCusto());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjRaio() <= A2-0.5);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao())return;
	
		C1 = model.getValorCusto();
		model.reset();


		int C2;
		model.CriaVariavel();
		model.setFuncaoObj(model.getFuncaoObjRaio());
		model.geraRestricoesbase();
		model.addRestricao(model.getFuncaoObjCusto() <= C1);
		model.finalizarestricoes();
		model.resolve();
		if (!model.tem_solucao())return;
		this->salva_resultado();
		C2 = model.getValorRaio();
		model.reset();
		//cout<<"C " << C1 << " " << C2 << endl;
		A1 = C1;
		A2 = C2;
	}




}