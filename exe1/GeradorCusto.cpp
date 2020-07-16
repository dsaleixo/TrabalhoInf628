// exe1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;


int main()
{


    srand((unsigned)time(0)); //para gerar números aleatórios reais.
    // LER DADOS
    for (int i = 1; i < 21; i++) {
        ifstream in("dados\\pmed" + to_string(i) + ".txt");
        if (!in) {
            cout << "Erro ao abrir o arquivo\n";
            return 1;
        }


        ofstream out("dados\\pmedCusto" + to_string(i) + ".txt");
        int n;
        in >> n;
        cout << n << endl;
        for (int j = 0; j < n; j++) {

            int maior = 1000;
            int menor = 10;
            int aleatorio = rand() % (maior - menor + 1) + menor;
            out << aleatorio << endl;

        }
        out.close();
        in.close();
    }
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
