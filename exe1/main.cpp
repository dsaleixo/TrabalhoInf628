// exe1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "ModeloClassico.h"
#include "ModeloElloumi.h"
#include "ModeloCalikTansel.h"
#include "ModeloCP2.h"




using namespace std;

Model* MetodoFabrica(int i,string s, int p) {
	if (i == 0)return new ModeloClassico(s, p);
	else if (i == 1)return new ModeloElloumi(s, p);
	else if (i == 2)return new ModeloCalikTansel(s, p);
	else if (i == 3) return new ModeloCP2(s, p);
	return NULL;

}



int main()
{

	int numero_p[5] = { 5,10,15,20,30 };
	ofstream out("saida.txt");
	
	
	for (int i = 1; i < 2; i++) {
		for (int p = 0; p < 1; p++) {
			for (int m = 0; m < 4; m++) {
				cout << i << " " << p << " " << m << endl;
				Model* model = MetodoFabrica(m, "dados\\pmed"+to_string(i)+".txt", numero_p[p]);
			
				long double Tfinal;
				long double TInicial;
				TInicial = (clock() / (double)CLOCKS_PER_SEC);
				model->resolve();
				Tfinal = (clock() / (double)CLOCKS_PER_SEC) - TInicial;
				double resultado = model->imprime_solucao();
				out << i << " " << p << " " << m << " " << resultado << " " << Tfinal<< endl;
				delete model;
			}
		}
	}
	out.close();
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
