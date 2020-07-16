#pragma once
#ifndef MODEL_CP2_H
#define MODEL_CP2_H

#include "Model.h"
#include <vector>


class ModeloCP2 :
    public Model
{
public:
    ModeloCP2(string s, int p);
    IloNumArray D;
    IloInt Z_size;
    vector<vector<int>> S;
    IloFloatVar r;
    IloNumVarArray y;
    
};

#endif
