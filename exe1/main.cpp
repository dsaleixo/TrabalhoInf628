// exe1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "ModeloPmedianas.h"
#include "ModeloClassico.h"
#include "ModeloElloumi.h"
#include "ModeloCalikTansel.h"
#include "ModeloCP1.h"
#include "ModeloCP2.h"
#include "OMOSP.h"
#include "OMOERestrito.h"
#include "MSP.h"
#include "EpslonRestrito.h"
#include "EpslonRestritoAproximado.h"
#include "MVPR.h"
#include "MTCH.h"
#include "BBM.h"
#include "DuasFase.h"
#include "ModeloCP1Original.h"
using namespace std;

MMO* MetodoFabrica(int i, string s, int p) {
	if (i == 0) return new OMOSP(s, p, "", 10);//Métodos Clássicos de OMO, Método da Soma Ponderada :
	else if (i == 1) return new OMOERestrito(s, p, "", 10);//Métodos Clássicos de OMO, Método ε-Restrito: ;
	else if (i == 2)return new MSP(s, p, "",true);//Método da Soma Ponderada Biobjetivo //true = otimizado
	else if (i == 3) return new EpslonRestrito(s, p, "");//Método ε - Restrito
	else if (i == 4) return new EpslonRestritoAproximado(s, p, "", 10); //Método ε - Restrito Aproximado
	else if (i == 5) return new BBM(s, p, "");  //Método da Caixa Balanceada 
	else if (i == 6) return new DuasFase(s,p,"",0.1,10,false); // Duas false sem escala
	else if (i == 7) return new DuasFase(s, p, "", 0.1, 10, true); // Duas fases com escala
	return NULL;

}


Model* FabricaModelo(int i, string s, int p) {
	if (i == 0)return new ModeloClassico(s, p);
	//else if (i == 2)return new ModeloElloumi(s, p);
	else if (i == 1)return new ModeloCalikTansel(s, p);
	else if (i == 2) return new ModeloCP1Original(s, p);
	else if (i == 3) return new ModeloCP2(s, p);
	return NULL;

}



void testeMO()
{

	cout << "Incio modelos" << endl;
	int numero_p[5] = { 5,10,15,20,30 };

	ofstream out("saida.txt");
	ofstream outt("tempos.txt");
	Model* model;

	out << "n" << "  p" << " medianas  Classico    CalikTansel  CP1  CP2" << endl;
	outt << "n" << "  p" << " medianas  Classico    CalikTansel  CP1  CP2" << endl;

	for (int i = 1; i < 41; i++) {// varia os mapas
		for (int p = 0; p < 1; p++) { // varias os p
			outt << i << "  " << numero_p[p];
			for (int m = 0; m < 4; m++) {// varia os modelos
				cout << i << " " << p << " " << m << endl;

				model = FabricaModelo(m, "dados/Pcentros" + to_string(i), numero_p[p]);
				//Model* model = MetodoFabrica(m, "pmed"+to_string(i)+".txt", numero_p[p]);

				long double Tfinal;
				long double TInicial;
				TInicial = (clock() / (double)CLOCKS_PER_SEC);
				model->resolve();
				Tfinal = (clock() / (double)CLOCKS_PER_SEC) - TInicial;
				double resultado = model->imprime_solucao();

				cout << "  " << resultado << endl;  cout << "  " << Tfinal << endl;
				outt << "  " << Tfinal;
				out << "  " << resultado;
				delete model;
			}
			out << endl;
			outt << endl;
		}
	}
	out.close();

	cout << "FIM Modelos" << endl;
	
}





void testeBO() {
	int numero_p[5] = { 5,10,15,20,30 };
	for (int m = 2; m < 3; m++) {// varia os modelos
		ofstream out("resultado/out04_" + to_string(m) + ".txt");
		for (int i = 1; i < 27; i++) {// varia os mapas
			MMO* mmo = MetodoFabrica(m, "dados/Pcentros"+to_string(i), 5);
			for (int p = 0; p < 5; p++) { // varias os p
				mmo->setP(numero_p[p]);


				out << "i=" << i << "		" << "n=" << mmo->model.dados.n << "		" << "p="<< numero_p[p] << endl;

				long double Tfinal;
				long double TInicial;
				TInicial = (clock() / (double)CLOCKS_PER_SEC);
				mmo->rodar();
			
				Tfinal = (clock() / (double)CLOCKS_PER_SEC) - TInicial;
				mmo->imprime(out);
				out << "Tempo(s): " << Tfinal << endl << endl;
				mmo->reset();
			}
			
			delete mmo;
		}
	}
}



int main() {
	testeBO();
	//testeBO();
	return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar:
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
