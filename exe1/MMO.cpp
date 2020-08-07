#include "MMO.h"


MMO::MMO(string s, int p,string saida): model(s,p,false,false) {
	
	
}


void MMO::deleta_ambiente() {
	this->model.delete_amb();
}

MMO::~MMO() {
	
}

bool myfunction(Solucao* a, Solucao* b) {
	if (a->f1 < b->f1) return true;
	else if (a->f1 == b->f1 && a->f2 < b->f2)true;
	return false;
}

bool operator<(const Solucao& a, const Solucao& b)
{
	if (a.f1 < b.f1) return true;
	else if (a.f1 == b.f1 && a.f2 < b.f2)true;
	return false;
}

bool operator<(const Intervalo1& a, const Intervalo1& b)
{
	if (a.a < b.a) return true;
	return false;

}



void MMO::setP(int p) {
	model.dados.p = p;
}

void MMO::reset() {
	paleto.clear();
	model.reset();
}

void MMO::imprime(ofstream &out) {
	
	set <Solucao, less <Solucao> > ::iterator itr;
	out << paleto.size() << " pontos dominantes" << endl;
	for (itr = paleto.begin(); itr != paleto.end(); ++itr)
	{
		out << itr->f1 << " " << itr->f2 << endl;;
	}
}




void MMO::salva_resultado() {
	Solucao s;
	
	s.f2 = model.getValorRaio();

	s.f1 = model.getValorCusto();
	
	paleto.insert(s);


}
