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
using namespace std;

MMO* MetodoFabrica(int i, string s, int p) {
	if (i == 0) return new OMOSP(s, p, "", 10);//Métodos Clássicos de OMO, Método da Soma Ponderada :
	else if (i == 1) return new OMOERestrito(s, p, "", 10);//Métodos Clássicos de OMO, Método ε-Restrito: ;
	else if (i == 2)return new MSP(s, p, "");//Método da Soma Ponderada Biobjetivo 
	else if (i == 3) return new EpslonRestrito(s, p, "");//Método ε - Restrito
	else if (i == 4) return new EpslonRestritoAproximado(s, p, "", 10); //Método ε - Restrito Aproximado
	else if (i == 5) return new BBM(s, p, "");  //Método da Caixa Balanceada 
	else if (i == 6) return new DuasFase(s,p,"",0.1,10,false); // Duas false sem escala
	else if (i == 7) return new DuasFase(s, p, "", 0.1, 10, true); // Duas fases com escala
	return NULL;

}




int main() {
	int numero_p[5] = { 5,10,15,20,30 };
	for (int m = 6; m < 7; m++) {// varia os modelos
		ofstream out("resultado/out25_" + to_string(m) + ".txt");
		for (int i = 1; i < 7; i++) {// varia os mapas
			MMO* mmo = MetodoFabrica(m, "dados/pmed"+to_string(i), 5);
			for (int p = 0; p < 2; p++) { // varias os p
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


// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar:
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
