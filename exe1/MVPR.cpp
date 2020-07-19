#include "MVPR.h"



MVPR::MVPR(string s, int p, string saida, int lambda) : MMO(s, p, saida) {
	this->lambda=lambda;
}


void MVPR::rodar() {

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
void MVPR::rodar(double A1, double A2, double B1, double B2) {

	double R1 = A1;
	double R2 = B2;

	double gama1 = (B1 - A1) / this->lambda;
	double gama2 = (A2 - B2) / this->lambda;


	double A1_linha = A1 + gama1;
	double A2_linha = A2 - gama2;

	double B1_linha = B1 - gama1;
	double B2_linha = B2 + gama2;

	double R1_linha = R1 + gama1;
	double R2_linha = R2 + gama2;

	

	IloFloatVar u(model.env);


	
	IloExpr obj(model.env);
	obj += u;
	model.setFuncaoObj(u);

	model.addRestricao(model.getFuncaoObjCusto()-u<=R1_linha);
	model.addRestricao(model.getFuncaoObjRaio() - u <= R2_linha);

	model.addRestricao(model.getFuncaoObjCusto() <= B1_linha);
	model.addRestricao(model.getFuncaoObjRaio() <= A2_linha);

	model.addRestricao(model.getFuncaoObjCusto() >= A1_linha);
	model.addRestricao(model.getFuncaoObjRaio() >= B2_linha);

	model.geraRestricoesbase();
	model.finalizarestricoes();

	model.resolve();

	
	if (!model.tem_solucao()) {
		model.reset();
		return;
	}

	this->salva_resultado();
	double C1 = model.getValorCusto();
	double C2 = model.getValorRaio();
	//cout << A1_linha <<" "<<C1<<" " << B1_linha << endl;
	//cout << B2_linha << " " << C2 << " "<< A2_linha << endl;

	model.reset();
	rodar(C1, C2, B1, B2);
	rodar(A1, A2, C1, C2);



}