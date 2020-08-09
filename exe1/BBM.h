#pragma once

#ifndef BBM_H
#define BBM_H

#include "MMO.h"





class BBM :
    public MMO
{
public:
    bool otimizado=true;
    vector<Intervalo1> Heap;
    BBM(string s, int p, string saida,bool otimizado);
    virtual void rodar();
    void rodarHeap();

};

#endif