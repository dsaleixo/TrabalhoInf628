#pragma once


#ifndef MODEL_CALIK_TANSEL_H
#define MODEL_CALIK_TANSEL_H

#include "Model.h"

typedef IloArray<NumMatrix> NumMatrix3D;

class ModeloCalikTansel :
    public Model
{
    public:
        ModeloCalikTansel(string s);
        NumMatrix3D cria_matrizA(IloNumArray D, int k);
};

#endif