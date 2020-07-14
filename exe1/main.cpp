// exe1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "ModeloPmedianas.h"
#include "ModeloClassico.h"
#include "ModeloElloumi.h"
#include "ModeloCalikTansel.h"
#include "ModeloCP1.h"
#include "ModeloCP2.h"

using namespace std;

Model* MetodoFabrica(int i, string s, int p) {
	if (i == 0) return new ModeloPmedianas(s, p);
	else if (i == 1)return new ModeloClassico(s, p);
	//else if (i == 2)return new ModeloElloumi(s, p);
	else if (i == 2)return new ModeloCalikTansel(s, p);
	else if (i == 3) return new ModeloCP1(s, p);
	else if (i == 4) return new ModeloCP2(s, p);
	return NULL;

}

int main()
{

	cout << "Incio modelos" << endl;
	int numero_p[5] = { 5,10,15,20,30 };

	ofstream out("saida.txt");
	ofstream outt("tempos.txt");
	Model* model;

	out << "n" << "  p" << " medianas  Classico    CalikTansel  CP1  CP2" << endl;
	outt << "n" << "  p" << " medianas  Classico    CalikTansel  CP1  CP2" << endl;

	for (int i = 16; i < 21; i++) {// varia os mapas
		for (int p = 0; p < 5; p++) { // varias os p
			outt << i << "  " << numero_p[p];
			for (int m = 0; m < 5; m++) {// varia os modelos
				cout << i << " " << p << " " << m << endl;

				model = MetodoFabrica(m, "dados/pmed" + to_string(i) + ".txt", numero_p[p]);
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
