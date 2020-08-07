#pragma once


#ifndef MODEL_CLASSICO_H
#define MODEL_CLASSICO_H

#include "Model.h"

class ModeloClassico :
    public Model
{
    public:
        ModeloClassico(string s,int p);
        NumVarMatrix x;
        IloNumVarArray y;
        IloFloatVar r;

};

#endif