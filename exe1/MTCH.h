#pragma once

#ifndef MTCH_H
#define MTCH_H


#include "MMO.h"
class MTCH :
    public MMO
{

public:
    int lambda;
    MTCH(string s, int p, string saida, int lambda);
    virtual void rodar();
    void rodar(double A1, double A2, double B1, double B2);
};

#endif