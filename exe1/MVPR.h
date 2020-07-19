#pragma once


#ifndef MVPR_H
#define MVPR_H


#include "MMO.h"
class MVPR :
    public MMO
{
    public:
        int lambda;
        MVPR(string s, int p, string saida, int lambda);
        virtual void rodar();
        void rodar(double A1, double A2, double B1, double B2);

};

#endif
