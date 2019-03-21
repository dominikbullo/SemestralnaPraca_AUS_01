#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayPrekladisk = new structures::ArrayList<Prekladisko*>();
}

Firma::~Firma()
{
	// treba premazat vsetky objekty ktore som kam naplnil
	for (Vozidlo *vozidlo : *arrayVozidiel) {
		delete vozidlo;
	}
	for (Prekladisko * prekladisko : *arrayPrekladisk) {
		delete prekladisko;
	}
	delete arrayVozidiel;
	delete arrayPrekladisk;
}

void Firma::pridajPrekladisko(Prekladisko* novePrekladisko)
{
	arrayPrekladisk->add(novePrekladisko);
}

void Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	// vozidlo prid�vam v�dy na koniec, t�m p�dom viem, �e vozidl� s� zoraden� pod�a poradia zaevidovania
	arrayVozidiel->add(noveVozidlo);
}

void Firma::vypisZoznamVozidiel()
{
	for (Vozidlo* var : *arrayVozidiel) {
		var->toString();
	}

}

Prekladisko* Firma::dajPrekladiskoPodlaOkresu(std::string okres) {
	// zlo�itos� O(n)
	for (Prekladisko * prekladisko : *arrayPrekladisk) {
		if (prekladisko->dajOkres() == okres) {
			return prekladisko;
		}
	}
	// TODO: throw exeption
	throw std::logic_error("Prekladisko v tomto okrese sa nenaslo");
}