#pragma once
#ifndef OMOSP_H
#define OMOSP_H

#include "MMO.h"
#include <iostream>
using namespace std;

class OMOSP :
    public MMO
{
public:
    int num_w;
    OMOSP(string s, int p,string saida, int num_w);
    virtual void rodar() ;
};

#endif
