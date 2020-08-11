#include "DuasFase.h"




DuasFase::DuasFase(string s, int p, string saida, double nn, int teta, bool usar_escala,bool otimizador) : MMO(s, p, saida) {
	this->nn = nn;
	this->teta = teta;
	this->otimizado = otimizador;
	for (int i = 0; i < teta; i++) {
		passado.push_back(0);
	}
	indice = 0;
	esc1 = esc2 = 1;
	this->usar_escala = usar_escala;


}


void DuasFase::rodar() {

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

	if (usar_escala) {
		esc1 = 1.0/abs(B1 - A1);
		esc2 = 1.0 / abs(A2 - B2);
	}

	intervalo.a = (abs(A1 - B1)/this->esc1 )* (abs(B2 - A2)/this->esc2);

	Heap.push_back(intervalo);
	push_heap(Heap.begin(), Heap.end());
	rodarHeap();
	//rodarEpslon();

}





void DuasFase::rodarHeap() {

	while (!Heap.empty()) {


		int beta = 0;
		for (int i = 0; i < teta; i++) {
			beta += passado[i];
		}

		if (beta >= teta * nn && false) {
			return;
		}


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
		model.addRestricao(model.getFuncaoObjRaio() <= (A2 + B2) / 2);

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

			this->model.setFim(this->model.buscaBinaria(A2) + 1);
		}
		model.CriaVariavel();
		model.setFuncaoObj(model.getFuncaoObjRaio());
		model.geraRestricoesbase();

		model.addRestricao(model.getFuncaoObjCusto() <= C1 - 0.5);
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

				this->model.setFim(this->model.buscaBinaria(D2) + 2);
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

		
		bool achou = false;
		if (C1 != -1 && C2 != -1 && !(abs(C1 - B1) < 0.1 && (C2 - B2) < 0.1)) {
			Intervalo1 intervalo2;
			intervalo2.A1 = C1;
			intervalo2.A2 = C2;
			intervalo2.B1 = B1;
			intervalo2.B2 = B2;
			intervalo2.a = (abs(B1 - C1) / this->esc1) * (abs(C2 - B2) / this->esc2);
		
			Heap.push_back(intervalo2);
			push_heap(Heap.begin(), Heap.end());
			achou =true;
		}
		if (D1 != -1 && D2 != -1 && !(abs(A1 - D1) < 0.1 && (A2 - D2) < 0.1)) {
			Intervalo1 intervalo2;
			intervalo2.A1 = A1;
			intervalo2.A2 = A2;
			intervalo2.B1 = D1;
			intervalo2.B2 = D2;
			intervalo2.a = (abs(A1 - B1) / this->esc1) * (abs(D2 - A2) / this->esc2);
		
			Heap.push_back(intervalo2);
			push_heap(Heap.begin(), Heap.end());
			achou = true;

		}

		if (achou) {
			passado[indice] = 0;
		}
		else {
			passado[indice] = 1;
		}
		indice = (indice + 1) % teta;
	}

}



void DuasFase::rodarEpslon() {

	while (!Heap.empty()) {

		
		Intervalo1 intervalo = Heap.front();

		pop_heap(Heap.begin(), Heap.end());
		Heap.pop_back();

		double A1 = intervalo.A1;
		double A2 = intervalo.A2;
		double B1 = intervalo.B1;
		double B2 = intervalo.B2;

		while (!(abs(A1 - B1) < 0.5 && abs(B2 - A2) < 0.5)) {

			if (this->otimizado) {
				this->model.setInicio(this->model.buscaBinaria(B2));

				this->model.setFim(this->model.buscaBinaria(A2) + 1);
			}

			int C1;
			model.CriaVariavel();
			model.setFuncaoObj(model.getFuncaoObjCusto());
			model.geraRestricoesbase();
			model.addRestricao(model.getFuncaoObjRaio() <= A2 - 0.5);
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

}