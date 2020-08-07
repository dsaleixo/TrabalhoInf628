#pragma once

#ifndef MODEL_CP1_H
#define MODEL_CP1_H

#include "Model.h"
#include <vector>
#include <set>


struct N
{
    int indice, Dist;

};

struct Q {
    set<int> s;
    int vc, ve;
};



class ModeloCP1 :
    public Model
   
{
    public:
        ModeloCP1(string s, int p, bool montar,int heuristica);
        vector<int> D;
        vector<int> Menores;
        int Z_size;
        int inicio;
        void setInicio(int i);
        int fim;
        void setFim(int f);
        vector<vector<int>> S;
        IloNumVarArray Z;
        IloNumVarArray y;
        vector<vector<N>> NN;
        void constroiN();
        IloExpr getFuncaoObjRaio();
        void CriaVariavel();
      
        void GreedyRandomized(set<int> &s,float alpha,int limite);
        int acharW(set<int>& s,bool ind);
        void Tabu(set<int>& s, int Lmax);
        int GRASP_PR(int heuristica);
        set<int> PathRelinking(set<int>& sc, set<int>& se,double beta);
        int maiorD();
        int menormaiorD();
        int seraMinimo();
        IloExpr getFuncaoObjCusto();

        void setFuncaoObj(IloExpr obj);
   
        void geraRestricoesbase();
        int buscaBinaria(int x);
        void addRestricao(IloRange rest);
        void finalizarestricoes();
        
        int getValorRaio();
        int getValorCusto();

        void reset();



};

#endif