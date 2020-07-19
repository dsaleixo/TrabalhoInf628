#include "MTCH.h"







MTCH::MTCH(string s, int p, string saida, int lambda) : MMO(s, p, saida) {
	this->lambda = lambda;
}


void MTCH::rodar() {

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
		
	
		IloFloatVar u(model.env);



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