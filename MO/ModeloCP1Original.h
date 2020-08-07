#pragma once
#include "Model.h"
#ifndef MODEL_CP1_ORIGINAL_H
#define MODEL_CP1_ORIGINAL_H

class ModeloCP1Original :
    public Model
{
    public:
        vector<int> D;
        int Z_size;
        vector<vector<int>> S;
        ModeloCP1Original(string s, int p);
};
#endif
