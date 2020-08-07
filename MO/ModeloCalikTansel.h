#pragma once


#ifndef MODEL_CALIK_TANSEL_H
#define MODEL_CALIK_TANSEL_H

#include "Model.h"



class ModeloCalikTansel :
    public Model
{
    public:
        ModeloCalikTansel(string s, int p);
        vector<int> D;
        int Z_size;
        NumMatrix3D A;
        IloNumVarArray Z;
        IloNumVarArray y;
        
};

#endif