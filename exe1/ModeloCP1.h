#pragma once

#ifndef MODEL_CP1_H
#define MODEL_CP1_H

#include "Model.h"
#include <vector>

class ModeloCP1 :
    public Model
   
{
    public:
        ModeloCP1(string s, int p);
        vector<int> D;
        int Z_size;
        vector<vector<int>> S;
        IloNumVarArray Z;
        IloNumVarArray y;

        IloExpr getFuncaoObjRaio(int inicio, int fim);
        IloExpr getFuncaoObjRaio() {
            return getFuncaoObjRaio(0, Z_size);
        }

        IloExpr getFuncaoObjCusto();

        void setFuncaoObj(IloExpr obj);
        void geraRestricoesbase(int inicio, int fim);
        void geraRestricoesbase() {
            geraRestricoesbase(0, Z_size);
        }
        int buscaBinaria(int x);
        void addRestricao(IloRange rest);
        void finalizarestricoes();
        int getValorRaio(int inicio, int fim);
        int getValorRaio() {
            return getValorRaio(0, Z_size);
        }
        int getValorCusto();

        void reset();



};

#endif