#include "BBM.h"



BBM::BBM(string s, int p, string saida) : MMO(s, p, saida) {

}


void BBM::rodar() {

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



bool operator<(const Intervalo1& a, const Intervalo1& b)
{
	if (a.a < b.a) return true;
	return false;

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

	

		double C1, C2;
		C1 = C2 = -1;
		model.setFuncaoObj(model.getFuncaoObjCusto());
		model.geraRestricoesbase();

		model.addRestricao(model.getFuncaoObjCusto() <= B1);
		model.addRestricao(model.getFuncaoObjCusto() >= A1);

		model.addRestricao(model.getFuncaoObjRaio() >= B2);
		model.addRestricao(model.getFuncaoObjRaio() <= (A2 + B2) / 2);

		model.finalizarestricoes();
		model.resolve();

		if (!model.tem_solucao()) {
			model.reset();

		}
		else {

			C1 = model.getValorCusto();
			model.reset();
			model.setFuncaoObj(model.getFuncaoObjRaio());
			model.geraRestricoesbase();

			model.addRestricao(model.getFuncaoObjCusto() <= C1);
			model.addRestricao(model.getFuncaoObjCusto() >= A1);

			model.addRestricao(model.getFuncaoObjRaio() >= B2);
			model.addRestricao(model.getFuncaoObjRaio() <= (A2 + B2) / 2);

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
		model.setFuncaoObj(model.getFuncaoObjRaio());
		model.geraRestricoesbase();

		model.addRestricao(model.getFuncaoObjCusto() <= C1);
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