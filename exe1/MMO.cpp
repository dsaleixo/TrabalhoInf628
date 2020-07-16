#include "MMO.h"


MMO::MMO(string s, int p,string saida): model(s,p) {
	out.open(saida);
	out << "Raio" << " " << "Custo" << endl;
}

MMO::~MMO() {
	out.close();
}

void MMO::salva_resultado() {
	out << model.getValorRaio() << " " << model.getValorCusto() << endl;
}
