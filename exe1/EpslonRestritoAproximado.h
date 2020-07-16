#pragma once
#include "MMO.h"

#ifndef ERA_H
#define ERA_H

class EpslonRestritoAproximado :
    public MMO
{
public:
    int n;
    EpslonRestritoAproximado(string s, int p, string saida,int delta);
    virtual void rodar();
    void rodar(double A1, double A2, double B1, double B2);
};

#endif