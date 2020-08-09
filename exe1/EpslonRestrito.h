#pragma once

#ifndef ER_H
#define ER_H

#include "MMO.h"
class EpslonRestrito :
    public MMO
{
    public:
        bool otimizado;
        EpslonRestrito(string s, int p, string saida,bool otimizado);
        virtual void rodar();
        void rodar(double A1, double A2, double B1, double B2);

};

#endif