#pragma once

#ifndef MSP_H
#define MSP_H

#include "MMO.h"
class MSP :
    public MMO
{
    public:
        bool otimizado;
        MSP(string s, int p, string saida,bool otimizado);
        virtual void rodar();
        void rodar(double A1, double A2, double B1, double B2,double Beta1, double Beta2);
};

#endif