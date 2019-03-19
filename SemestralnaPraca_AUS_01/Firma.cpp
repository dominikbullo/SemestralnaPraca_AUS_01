#include "Firma.h"



Firma::Firma()
{
	arrayVozidiel = new structures::ArrayList<Vozidlo*>();
}


Firma::~Firma()
{
}

void Firma::pridajVozidlo(Vozidlo * noveVozidlo)
{
	int index = 0;
	for (Vozidlo* var : *arrayVozidiel) {
		// TODO: vklada� vozidl� poporade -> pod�a nejak�ho �asu ? 
		if (noveVozidlo->getSPZ() <= var->getSPZ()) {
			arrayVozidiel->insert(noveVozidlo, index);
			return;
		}
		index++;
	}
	arrayVozidiel->add(noveVozidlo);

}