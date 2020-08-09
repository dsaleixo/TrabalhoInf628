#include "MTCH.h"







MTCH::MTCH(string s, int p, string saida, int lambda,bool otimizado) : MMO(s, p, saida) {
	this->otimizado = otimizado;
	this->lambda = lambda;
}


void MTCH::rodar() {

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
void MTCH::rodar(double A1, double A2, double B1, double B2) {




	double gama1 = (B1 - A1) / this->lambda;
	double gama2 = (A2 - B2) / this->lambda;

	
	double Beta1 = 1 / (B1 - A1);
	double Beta2 = 1 / (A2 - B2);

	double w = 1;
	double p1 = A1;
	double p2 = A2;

	for (int i = 0; i < this->lambda; i++) {
		w -= 1.0 / this->lambda;
		
	
		if (this->otimizado) {
			this->model.setInicio(this->model.buscaBinaria(B2));

			this->model.setFim(this->model.buscaBinaria(p2) + 1);
		}

		IloFloatVar u(model.env);


		model.CriaVariavel();
		IloExpr obj(model.env);
		obj += u;
		model.setFuncaoObj(u);

		model.addRestricao(w*Beta1*model.getFuncaoObjCusto() - u <= 0);
		model.addRestricao((1-w)*Beta2*model.getFuncaoObjRaio() - u <= 0);

		model.addRestricao(model.getFuncaoObjCusto() >= p1 + gama1);
		model.addRestricao(model.getFuncaoObjRaio() <= p2-gama2);

		model.geraRestricoesbase();
		model.finalizarestricoes();

		model.resolve();


		if (!model.tem_solucao()) {
			model.reset();
			return;
		}

		this->salva_resultado();
		 p1 = model.getValorCusto();
		p2  = model.getValorRaio();
		//cout << A1_linha <<" "<<C1<<" " << B1_linha << endl;
		//cout << B2_linha << " " << C2 << " "<< A2_linha << endl;

		model.reset();


	}


	
	



}