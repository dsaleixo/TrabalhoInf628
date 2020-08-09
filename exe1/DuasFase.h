#pragma once


#ifndef DF_H
#define DF_H


#include "MMO.h"
#include <vector>

class DuasFase :
    public MMO
{
public:
    double nn,esc1,esc2;
    bool usar_escala;
    int teta;
    vector<int> passado;
    int indice;
    vector<Intervalo1> Heap;
    bool otimizado;
    DuasFase(string s, int p, string saida,double nn,int teta, bool usar_escala,bool otimizador);
    virtual void rodar();
    void rodarHeap();
    void rodarEpslon();
};

#endif