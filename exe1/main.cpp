// exe1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

#include "ModeloCP1.h"

#include "OMOSP.h"
#include "OMOERestrito.h"
#include "MSP.h"
#include "EpslonRestrito.h"
#include "EpslonRestritoAproximado.h"
#include "MVPR.h"
#include "MTCH.h"
#include "BBM.h"
#include "DuasFase.h"
#include "MetodoDavid.h"

using namespace std;

MMO* MetodoFabrica(int i, string s, int p) {
	if (i == 0)return new MSP(s, p, "",true);//Método da Soma Ponderada Biobjetivo //true = otimizado
	else if (i == 1)return new MSP(s, p, "", false);//Método da Soma Ponderada Biobjetivo //true = otimizado
	else if (i == 2) return new EpslonRestrito(s, p, "", true);//Método ε - Restrito
	else if (i == 3) return new EpslonRestrito(s, p, "", false);//Método ε - Restrito
	else if (i == 4) return new MVPR(s, p, "", 10,true); //Método ε - Restrito Aproximado
	else if (i == 5) return new MVPR(s, p, "", 10, false); //Método ε - Restrito Aproximado
	else if (i == 6) return new MTCH(s, p, "", 10, true); //Método ε - Restrito Aproximado
	else if (i == 7) return new MTCH(s, p, "", 10, false); //Método ε - Restrito Aproximado
	else if (i == 8) return new BBM(s, p, "",true);  //Método da Caixa Balanceada 
	else if (i == 9) return new BBM(s, p, "",false);  //Método da Caixa Balanceada 
	else if (i == 10) return new DuasFase(s,p,"",0.1,10,false,true); // Duas false sem escala
	else if (i == 11) return new DuasFase(s, p, "", 0.1, 10, false,false); // Duas false sem escala
	else if (i == 12) return new MetodoDavid(s, p, "", 3, true);
	else if (i == 13) return new MetodoDavid(s, p, "", 3, false); 
	
	return NULL;

}










void testeBO() {
	int numero_p[5] = { 5,10,15,20,30 };
	for (int m = 13; m < 14; m++) {// varia os modelos
		ofstream out("resultado/out" + to_string(m) + ".txt");
		for (int i = 1; i < 2; i++) {// varia os mapas
			MMO* mmo = MetodoFabrica(m, "dados/pmed"+to_string(i), 5);
			for (int p = 0; p < 1; p++) { // varias os p
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
