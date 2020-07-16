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
        IloNumArray D;
        IloInt Z_size;
        vector<vector<int>> S;
        IloNumVarArray Z;
        IloNumVarArray y;

        IloExpr getFuncaoObjRaio();
        IloExpr getFuncaoObjCusto();

        void setFuncaoObj(IloExpr obj);
        void geraRestricoesbase();
        void addRestricao(IloRange rest);
        void finalizarestricoes();
        double getValorRaio();
        double getValorCusto();

        void reset();



};

#endif