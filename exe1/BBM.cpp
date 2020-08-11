#include "BBM.h"



BBM::BBM(string s, int p, string saida, bool otimizador) : MMO(s, p, saida) {
	this->otimizado = otimizador;
}


void BBM::rodar() {

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


	Intervalo1 intervalo;
	intervalo.A1 = A1;
	intervalo.B1 = B1;
	intervalo.A2 = A2;
	intervalo.B2 = B2;
	intervalo.a = abs(A1 - B1) * abs(B2 - A2);

	Heap.push_back(intervalo);
	push_heap(Heap.begin(), Heap.end());
	rodarHeap();

}





void BBM::rodarHeap() {
	
	while (!Heap.empty()){
	

		Intervalo1 intervalo = Heap.front();

		pop_heap(Heap.begin(), Heap.end());
		Heap.pop_back();

		double A1 = intervalo.A1;
		double A2 = intervalo.A2;
		double B1 = intervalo.B1;
		double B2 = intervalo.B2;
		if (abs(A1 - B1) < 0.2 && abs(B2 - A2) < 0.2)continue;
	
	

		double C1, C2;
		C1 = C2 = -1;
		if (this->otimizado) {
			this->model.setInicio(this->model.buscaBinaria(B2));

			this->model.setFim(this->model.buscaBinaria((A2 + B2) / 2) + 2);
		}
	
	
		model.CriaVariavel();
		model.setFuncaoObj(model.getFuncaoObjCusto());
		model.geraRestricoesbase();

		model.addRestricao(model.getFuncaoObjCusto() <= B1);
		model.addRestricao(model.getFuncaoObjCusto() >= A1);

		model.addRestricao(model.getFuncaoObjRaio() >= B2);
		model.addRestricao(model.getFuncaoObjRaio() <= (A2 + B2) / 2 );

		model.finalizarestricoes();
		model.resolve();

		if (!model.tem_solucao()) {
			model.reset();

		}
		else {

			C1 = model.getValorCusto();
			model.reset();


			if (this->otimizado) {
				this->model.setInicio(this->model.buscaBinaria(B2));

				this->model.setFim(this->model.buscaBinaria((A2 + B2) / 2) + 2);
			}
			model.CriaVariavel();
			model.setFuncaoObj(model.getFuncaoObjRaio());
			model.geraRestricoesbase();

			model.addRestricao(model.getFuncaoObjCusto() <= C1);
			model.addRestricao(model.getFuncaoObjCusto() >= A1);

			model.addRestricao(model.getFuncaoObjRaio() >= B2);
			model.addRestricao(model.getFuncaoObjRaio() <= (A2 + B2) / 2 - 0.05);

			model.finalizarestricoes();
			model.resolve();
			if (!model.tem_solucao()) {
				model.reset();
			}
			else {

				this->salva_resultado();
				C2 = model.getValorRaio();
				model.reset();
				
			}


		}



		double D1, D2;
		D1 = D2 = -1;
		if (this->otimizado) {
			this->model.setInicio(this->model.buscaBinaria((A2 + B2) / 2));

			this->model.setFim(this->model.buscaBinaria(A2 ) + 1);
		}
		model.CriaVariavel();
		model.setFuncaoObj(model.getFuncaoObjRaio());
		model.geraRestricoesbase();

		model.addRestricao(model.getFuncaoObjCusto() <= C1- 0.5);
		model.addRestricao(model.getFuncaoObjCusto() >= A1);

		model.addRestricao(model.getFuncaoObjRaio() <= A2);
		model.addRestricao(model.getFuncaoObjRaio() >= (A2 + B2) / 2);

		model.finalizarestricoes();
		model.resolve();

		if (!model.tem_solucao()) {
			model.reset();

		}
		else {

			D2 = model.getValorRaio();
			model.reset();
			if (this->otimizado) {
				this->model.setInicio(this->model.buscaBinaria((A2 + B2) / 2));

				this->model.setFim(this->model.buscaBinaria(D2)+2);
			}
			model.CriaVariavel();
			model.setFuncaoObj(model.getFuncaoObjCusto());
			model.geraRestricoesbase();

			model.addRestricao(model.getFuncaoObjCusto() <= C1);
			model.addRestricao(model.getFuncaoObjCusto() >= A1);

			model.addRestricao(model.getFuncaoObjRaio() <= D2);
			model.addRestricao(model.getFuncaoObjRaio() >= (A2 + B2) / 2);

			model.finalizarestricoes();
			model.resolve();
			if (!model.tem_solucao()) {
				model.reset();
			}
			else {
				this->salva_resultado();
				D1 = model.getValorCusto();
				model.reset();
			}


		}
		
		if (C1 != -1 && C2 != -1 && !(abs(C1 - B1) < 0.1 && (C2 - B2) < 0.1)) {
			Intervalo1 intervalo2;
			intervalo2.A1 = C1;
			intervalo2.A2 = C2;
			intervalo2.B1 = B1;
			intervalo2.B2 = B2;
			intervalo2.a = abs(B1 - C1) * abs(C2 - B2);
			Heap.push_back(intervalo2);
			push_heap(Heap.begin(), Heap.end());
		}
		if (D1 != -1 && D2 != -1 && !(abs(A1 - D1) < 0.1 && (A2 - D2) < 0.1)) {
			Intervalo1 intervalo2;
			intervalo2.A1 = A1;
			intervalo2.A2 = A2;
			intervalo2.B1 = D1;
			intervalo2.B2 = D2;
			intervalo2.a = abs(A1 - D1) * abs(D2 - A2);
			Heap.push_back(intervalo2);
			push_heap(Heap.begin(), Heap.end());

		}


	}

}