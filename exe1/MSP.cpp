#include "MSP.h"


MSP::MSP(string s, int p, string saida,bool otimizado) : MMO(s,p,saida){
	this->otimizado = otimizado;
}


void MSP::rodar() {
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
	f = this->model.buscaBinaria(this->model.getValorRaio()+1);
	model.reset();

	if (this->otimizado) {
		i = this->model.buscaBinaria(this->model.Menores[this->model.dados.p]);
			this->model.setInicio(i);
			int aux = this->model.buscaBinaria(this->model.maiorD())+1;
			if(f<aux)this->model.setFim(f);
			else this->model.setFim(aux);
	
	}
	model.CriaVariavel();
	model.setFuncaoObj(model.getFuncaoObjRaio());
	model.geraRestricoesbase();
	model.finalizarestricoes();
	model.resolve();
	if (!model.tem_solucao())return;
	B2 = model.getValorRaio();
	i = this->model.buscaBinaria(B2 );
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
	A2= model.getValorRaio();	
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
	

	rodar(A1, A2, B1, B2, 100.0 / (B1 - A1), 100.0 / (A2 - B2));

}
void MSP::rodar(double A1, double A2, double B1, double B2,double Beta1,double Beta2) {
	if (abs(A1 - B1) < 0.2 && abs(B2 - A2) < 0.2)return;
	

	double gama = (A2 - B2) / (B1 - A1);

	double alpha1 = gama / (gama + 1);
	double alpha2 = 1 - alpha1;



	if (this->otimizado) {
			this->model.setInicio( this->model.buscaBinaria(B2));

			this->model.setFim(this->model.buscaBinaria(A2) + 1);
	}
	

	double C1, C2;
	
	model.CriaVariavel();
	
	model.setFuncaoObj(Beta1*alpha1*model.getFuncaoObjCusto()+
					Beta2 * alpha2 * model.getFuncaoObjRaio());

	model.geraRestricoesbase();

	model.addRestricao(model.getFuncaoObjCusto() <= B1 - 1);

	model.addRestricao(model.getFuncaoObjRaio() <= A2 -1  );
	
	
	

	model.finalizarestricoes();
	model.resolve();

	if (!model.tem_solucao()) {
		model.reset();
		return;
	}
	this->salva_resultado();
	C1 = model.getValorCusto();
	C2 = model.getValorRaio();

	model.reset();
	
	rodar(C1, C2, B1, B2, Beta1, Beta2);
	rodar(A1, A2, C1, C2, Beta1, Beta2);




}