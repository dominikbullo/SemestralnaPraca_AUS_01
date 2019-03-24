#include "Prekladisko.h"
#include "Dron.h"

int Prekladisko::unikatneSerioveCislo_ = 000000;

Prekladisko::Prekladisko(std::string region)
{
	unikatneSerioveCislo_ = 000000;
	region_ = region;
	arrayListDronov = new structures::ArrayList<Dron*>();

	// evidujem �akaj�ce objedn�vky v skladisku
	frontObjednavok = new structures::ExplicitQueue<Objednavka*>();

	//arrayListObjednavokNaVybavenie->push(new Objednavka(10, new Odosielatel("BA", 10), new Adresat("MA", 15.5)));

	// prekladisko m� v�dy aspo� p�r dronov pri vytv�ran�
	this->pridajDron(new Dron(eDrony::JEDEN, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
}

Prekladisko::~Prekladisko()
{
	for (Dron * dron : *arrayListDronov) {
		delete dron;
	}
	delete arrayListDronov;

	frontObjednavok->clear();
	delete frontObjednavok;
}

void Prekladisko::pridajDron(Dron * novyDron)
{
	// TODO sort by date
	//int index = 0;
	//for (Vozidlo *vozidlo : *arrayListVozidiel) {
	//	// FIXED zara�ovanie pod�a d�tumu aj �asu
	//	if (noveVozidlo->getDatumaCasEvidencie() < vozidlo->getDatumaCasEvidencie()) {
	//		arrayListVozidiel->insert(noveVozidlo, index);
	//		return;
	//	}
	//	index++;
	//}
	//arrayListVozidiel->add(noveVozidlo);
	arrayListDronov->add(novyDron);
}

void Prekladisko::pridajObjednavku(Objednavka * objednavka)
{
	frontObjednavok->push(objednavka);
}
void Prekladisko::spracujObjednavky()
{
	cout << "Spracovavam objednavky v regione: " << this->dajRegion() << endl;
	while (!frontObjednavok->isEmpty())
	{
		cout << "Spracovavam objednavku: " << endl;
		frontObjednavok->pop()->toString();
	}
}

void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << region_ << std::endl;
	for (Dron * dron : *arrayListDronov) {
		dron->toString();
	}
}

Dron * Prekladisko::vyberDrona(double hmotnostZasielky, double vzdialenost, string casVytvoreniaObjednavky)
{
	// NOTE v�ber spr�vneho drona na doru�enie z�sielky od adres�ta/odosielatela z/do skladiska
	Dron* kandidatNaDrona;

	for (Dron * dron : *arrayListDronov) {
		// premenna tak dam toho prveho
		// h�adaj tu najlep�ieho drona
		if (!dron->jeVolny()) {
			//a je lep�� ako kandid�t, tak zme� kandid�ta -> ako zist�m, �i je lep�� ako kandid�t 
			kandidatNaDrona = dron;
			continue; // break ?
		}

		if (dron->zvladneLet(vzdialenost) &&
			dron->unesieZasielku(hmotnostZasielky) &&
			dron->stihnePriletietPreZasielku(vzdialenost))
		{
			return dron;
		}

	}

	std::cout << "Takuto objednavku nezvladne dorucit ziaden dron" << std::endl;
	return NULL;
}

std::string Prekladisko::set_get_SerioveCislo()
{
	int pom = ++unikatneSerioveCislo_;
	std::string formated = std::string(6 - std::to_string(pom).length(), '0') + std::to_string(pom);
	serioveCislo_ = region_ + formated;
	return serioveCislo_;
}

