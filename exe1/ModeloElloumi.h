#pragma once

#ifndef MODEL_ELLOUMI_H
#define MODEL_ELLOUMI_H

#include "Model.h"


class ModeloElloumi :
    public Model
{
    public:
        ModeloElloumi(string s,int p);
        IloNumArray D;
        IloInt Z_size;
        IloNumVarArray Z;
        IloNumVarArray y;
     
        

};

#endif