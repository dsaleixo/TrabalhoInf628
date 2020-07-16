#pragma once

#ifndef OMOER_H
#define OMOER_H
#include "MMO.h"
class OMOERestrito :
    public MMO
{
    public:
        double descremento;
        OMOERestrito(string s, int p, string saida, int decremento);
        virtual void rodar();
};

#endif