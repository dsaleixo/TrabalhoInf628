#include "MSP.h"


MSP::MSP(string s, int p, string saida) : MMO(s,p,saida){

}


void MSP::rodar() {

	//rodar(1232, 127, 13, 210, 1.0 / (1232 - 13), (1.0 / 210 - 127));


	double A1, A2, B1, B2;
	model.CriaVariavel(this->model.Z_size);
	model.setFuncaoObj(model.getFuncaoObjCusto());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	A1 = model.getValorCusto();
	
	model.reset();

	model.CriaVariavel(this->model.Z_size);
	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();

	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	
	B2 = model.getValorRaio();

	model.reset();


	model.CriaVariavel(this->model.Z_size);
	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();
	
	model.addRestricao(model.getFuncaoObjCusto() <= A1);
	model.finalizarestricoes();
	model.resolve();

	if (!model.tem_solucao())return;
	this->salva_resultado();
	A2= model.getValorRaio();
	
	model.reset();



	model.CriaVariavel(this->model.Z_size);
	model.setFuncaoObj(model.getFuncaoObjCusto());
	model.geraRestricoesbase();

	model.addRestricao(model.getFuncaoObjRaio() <= B2);
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	this->salva_resultado();
	B1 = model.getValorCusto();
	

	model.reset();
	

	rodar(A1, A2, B1, B2, 100.0 / (B1 - A1), 100.0 / (A2 - B2));

}
void MSP::rodar(double A1, double A2, double B1, double B2,double Beta1,double Beta2) {
	if (abs(A1 - B1) < 0.2 && abs(B2 == A2) < 0.2)return;
	

	double gama = (A2 - B2) / (B1 - A1);

	double alpha1 = gama / (gama + 1);
	double alpha2 = 1 - alpha1;


	int inicio = this->model.buscaBinaria(B2);

	int fim = this->model.buscaBinaria(A2)+1;


	double C1, C2;
	
	model.CriaVariavel(fim -  inicio);
	
	model.setFuncaoObj(Beta1*alpha1*model.getFuncaoObjCusto()+
					Beta2 * alpha2 * model.getFuncaoObjRaio(inicio,fim));

	model.geraRestricoesbase(inicio,fim);

	model.addRestricao(model.getFuncaoObjCusto() <= B1 - 1);

	model.addRestricao(model.getFuncaoObjRaio(inicio, fim) <= A2 -1  );
	
	
	

	model.finalizarestricoes();
	model.resolve();

	if (!model.tem_solucao()) {
		model.reset();
		return;
	}
	this->salva_resultado(inicio, fim);
	C1 = model.getValorCusto();
	C2 = model.getValorRaio(inicio,fim);

	model.reset();
	
	rodar(C1, C2, B1, B2, Beta1, Beta2);
	rodar(A1, A2, C1, C2, Beta1, Beta2);




}