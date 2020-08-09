#pragma once
#include "MMO.h"

#ifndef MD_H
#define MD_H

class MetodoDavid :
    public MMO
{
public:
    int n;
    bool otimizado;
    MetodoDavid(string s, int p, string saida, int delta,bool otimizado);
    virtual void rodar();
    void rodar(double A1, double A2, double B1, double B2);
    void terminar();
};

#endif