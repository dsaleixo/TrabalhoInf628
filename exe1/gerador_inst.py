

import numpy as np

from random import randint



def floyd(Dist,n) :
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if Dist[i][k] * Dist[k][j] != 0 and i != j :
                    if Dist[i][k] + Dist[k][j] < Dist[i][j] or Dist[i][j] == 0:
                        Dist[i][j] = Dist[i][k] + Dist[k][j];
   
    return D

def f(n,nExtra,Tmin,Tmax,custoMin,CustoMax,saida1,saida2):
  Locais = []
  Custo = []
  for i in range(1,n):
    T = randint(Tmin,Tmax)
    Locais.append([i,i+1,T])
  T = randint(Tmin,Tmax)
  Locais.append([n,1,T])
  for i in range(nExtra): 
    x = randint(1,n)
    y = x
    while x==y:
      y = randint(1,n)
    T = randint(Tmin,Tmax)
    Locais.append([x,y,T])
      
  for i in range(n):
    Custo.append(randint(custoMin,CustoMax))
  
  arquivo = open(saida1, 'w')
  arquivo.write(str(n)+' '+str(n+nExtra)+' '+str(5)+"\n")
  for l in Locais:
    arquivo.write(str(l[0])+' '+str(l[1])+' '+str(l[2])+"\n")
  arquivo.close()
  arquivo = open(saida2, 'w')
  for c in Custo:
    arquivo.write(str(c)+"\n")
  arquivo.close()

nome ="./dados/Pcentros"
f(50,50,1,200,10,1000,nome+".txt",nome+"Custo.txt")
for i in range(1,21):
  f(50,50,1,200,10,1000,nome+str(i)+".txt",nome+str(i)+"Custo.txt")
for i in range(21,41):
  f(100,100,1,100,10,1000,nome+str(i)+".txt",nome+str(i)+"Custo.txt")





