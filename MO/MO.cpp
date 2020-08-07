

#include <iostream>

#include "ModeloClassico.h"
#include "ModeloElloumi.h"
#include "ModeloCalikTansel.h"
#include "ModeloCP1.h"
#include "ModeloCP2.h"

#include <time.h>
#include <string>
#include "ModeloCP1Original.h"

using namespace std;



Model* FabricaModelo(int i, string s, int p) {
	
	if (i == 0)return new ModeloClassico(s, p);
	//else if (i == 2)return new ModeloElloumi(s, p);
	else if (i == 1)return new ModeloCalikTansel(s, p);
	else if (i == 2) return new ModeloCP2(s, p);
	else if (i == 3) return new ModeloCP1Original(s, p);
	else if (i == 4) return new ModeloCP1(s, p, true, 1);
	else if (i == 5) return new ModeloCP1(s, p, true, 2);
	else if (i == 6) return new ModeloCP1(s, p, true, 3);
	
	
	return NULL;

}



void testeMO()
{

	cout << "Incio modelos" << endl;
	int numero_p[5] = { 5,10,15,20,30 };

	ofstream out("saida.txt");
	ofstream outt("tempos.txt");
	Model* model;

	out << "n" << "  p" << " Classico    CalikTansel  CP2  CP1	CP1O	CP1OH1	CP1OH2" << endl;
	outt << "n" << "  p" << " Classico    CalikTansel  CP2  CP1	CP1O	CP1OH1	CP1OH2" << endl;

	for (int i = 1; i < 21; i++) {// varia os mapas
		for (int p = 0; p < 5; p++) { // varias os p
			outt << i << "  " << numero_p[p];
			for (int m = 0; m < 7; m++) {// varia os modelos
				cout << i << " " << p << " " << m << endl;

				long double Tfinal;
				long double TInicial;
				TInicial = (clock() / (double)CLOCKS_PER_SEC);
				model = FabricaModelo(m, "dados/pmed" + to_string(i), numero_p[p]);
				//Model* model = MetodoFabrica(m, "pmed"+to_string(i)+".txt", numero_p[p]);


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








int main() {
	
	testeMO();
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
