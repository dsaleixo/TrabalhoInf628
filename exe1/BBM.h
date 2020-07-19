#pragma once

#ifndef BBM_H
#define BBM_H

#include "MMO.h"

struct Intervalo1
{
    double A1, A2, B1, B2,a;

};



class BBM :
    public MMO
{
public:
    vector<Intervalo1> Heap;
    BBM(string s, int p, string saida);
    virtual void rodar();
    void rodarHeap();
};

#endif