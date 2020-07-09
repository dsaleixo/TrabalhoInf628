// exe1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <ilcplex/ilocplex.h>
#include <fstream>
#include <string>


typedef IloArray<IloNumArray> NumMatrix; //Tipo de dados Matriz bidimensional de numeros reais
typedef IloArray<IloNumVarArray> NumVarMatrix; //Tipo de dados Matriz bidimensional de variaveis

using namespace std;

void floyd(NumMatrix D, IloNum n) {

    int i, j, k;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++)  {
                if ((D[i][k] * D[k][j] != 0) && (i != j))
                {
                    if ((D[i][k] + D[k][j] < D[i][j]) || (D[i][j] == 0))
                    {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }
    }
}


int main()
{
   

    IloEnv env; ///Cria o ambiente: env
    IloModel model(env); ///Cria o modelo passando o ambiente
    IloRangeArray constraints(env); ///Vetor de restrições: constraints


    // LER DADOS

    ifstream in("dados\\pmed.txt");
    if (!in) {
        cout << "Erro ao abrir o arquivo\n";
        return 1;
    }

    IloInt n; //numero de locais
    IloInt m; //numero de entradas
    IloInt p;// numero de centos

    in >> n >> m >> p;

    NumMatrix D(env, n); // inicialaiza a matrix D
    for (int i = 0; i < n; i++) {
        D[i] = IloNumArray(env, n);
    }

    int a, b, c;
    for (int i = 0; i < m; i++) { // Le as distancia do arquivo 
        in >> a >> b >> c;
        D[a - 1][b - 1] = c;
        D[b - 1][a - 1] = c;
    }

    floyd(D, n);// algortitmo floyd para completar a tabela
    

    //Definição das VARIAVEIS de DECISAO

    //Matriz de variaveis x[i][j]: se o local i seja atendido pelo centro j
    NumVarMatrix x(env, n); //Cria n linhas para a matriz x
    for (int i = 0; i < n; i++) {
        //para cada linha, cria-se um array de m variaveis binárias:
        x[i] = IloNumVarArray(env, n, 0, 1, ILOINT);
    }

    //Vetor de facilidade y[j], se o centro será alocado em j
    IloNumVarArray y(env, n, 0, 1, ILOINT);

    //Raio R
    IloFloatVar r(env);

     
    // Função Objetivo
    IloExpr obj(env);
    obj += r;
    model.add(IloMinimize(env, obj));



    // Restrições


    IloExpr sum(env); // numero maximo de facilidade
    sum = IloSum(y);
    constraints.add(sum <= p);
    sum.end();



    for (IloInt i = 0; i < n; i++) { // todo local tem q ser atendido
        IloExpr sum(env);
        sum = IloSum(x[i]);
        constraints.add(sum == 1);
        sum.end();
    }

    for (IloInt i = 0; i < n; i++) {
        for (IloInt j = 0; j < n; j++) {
            constraints.add(x[i][j] - y[j] <= 0 );
        }
    }

    for (IloInt i = 0; i < n; i++) { // todo local tem q ser atendido
        IloExpr sum(env);
        sum = IloSum(x[i]);
        constraints.add(sum == 1);
        sum.end();
    }


    for (IloInt i = 0; i < n; i++) { // todo local tem q ser atendido
        IloExpr sum(env);
        sum = IloScalProd(D[i], x[i]);
        constraints.add(sum - r <= 0);
        sum.end();
    }
 

    model.add(constraints);

    IloCplex cplex1(env); //Declara-se objeto da classe IloCplex
    cplex1.extract(model);//Extrai o modelo a ser resolvido. Copia os dados do modelo em
                          //estruturas de dados eficientes a serem utilizados pelo CPLEX.
    cplex1.solve(); //resolve o modelo


    if (cplex1.solve()) { //executa o modelo
        cout << "REsultado: " << cplex1.getObjValue() << endl;
        //cplex1.out() <<"Optimal value: "<<cplex1.getObjValue() <<endl;
      
    }
    else cout << " No solution found " << endl;

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
