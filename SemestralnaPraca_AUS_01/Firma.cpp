#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

using namespace std;
Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayListVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayListPrekladisk = new structures::ArrayList<Prekladisko*>();

	// kv�li �tatistik�m -> ko�ko zamietnut�ch, ko�ko v kraji a pod.
	linkedListObjednavok = new structures::LinkedList<Objednavka*>();
}

Firma::~Firma()
{
	// treba premazat vsetky objekty ktore som kam naplnil
	for (Objednavka * objednavka : *linkedListObjednavok) {
		delete objednavka;
	}
	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		delete prekladisko;
	}
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		delete vozidlo;
	}
	delete arrayListVozidiel;
	delete arrayListPrekladisk;
	delete linkedListObjednavok;
}


void Firma::vypisanieVsetkychObjednavok()
{
	for (Objednavka * var : *linkedListObjednavok) {
		var->toString();
	}
}

void  Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	pridajRegionyDoTrasyVozidla(noveVozidlo);
	// vozidlo prid�vam v�dy na koniec, t�m p�dom viem, �e vozidl� s� zoraden� pod�a poradia zaevidovania
	int index = 0;
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		// FIXED zara�ovanie pod�a d�tumu aj �asu
		if (noveVozidlo->getDatumaCasEvidencie() < vozidlo->getDatumaCasEvidencie()) {
			arrayListVozidiel->insert(noveVozidlo, index);
			return;
		}
		index++;
	}
	arrayListVozidiel->add(noveVozidlo);

}
void Firma::pridajRegionyDoTrasyVozidla(Vozidlo* vozidlo) {
	string userInput;
	while (userInput != "0") {
		cout << "Ktory region chces pridat do trasy vozidla - " << vozidlo->getSPZ() << " " << endl;
		cin >> userInput;
		if (userInput != "0") {
			vozidlo->pridajPrekladiskoDoTrasyVozidla(this->dajPrekladiskoPodlaRegionu(userInput));
		}
	}
	return;
}

Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string region) {
	// zlo�itos� O(n)

	// NOTE osetrenie zl�ho vstupu
	//for (auto & c : region) c = toupper(c);

	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		if (prekladisko->dajRegion() == region) {
			return prekladisko;
		}
	}
	cout << "Prekladisko v tomto okrese sa nenaslo" << endl;
	return NULL;
}

// TODO 5:Pri vytv�ran� objedn�vky je nutn� kontrolova�, �i ned�jde k jej zamietnutiu zo strany
// AoE.Dokon�en� objedn�vka je zaraden� do frontu objedn�vok �akaj�cich na spracovanie.
// TODO //	e) prijatie z�sielky v lok�lnom prekladisku odosielate�a by sp�sobilo, �e toto lok�lne
		//	prekladisko nedok�e doru�i� niektor� z�sielky, ktor�ch adres�ti sa nach�dzaj� v jeho
		//	regi�ne, do 18:00 dan�ho d�a.

Vozidlo* Firma::vyberVozidlo(double hmotnostZasielky, Prekladisko* prekladiskoNaPrevzatieZasielky) {
	// TODO pozeraj e�te dopredu an napl�novan� z�sielky toho vozidla 
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		if (vozidlo->prechadzaPrekladiskom(prekladiskoNaPrevzatieZasielky) &&
			vozidlo->dokazeNalozitZasielku(hmotnostZasielky))
		{
			return vozidlo;
		}
	}
	cout << "Vyhovujuce vozidlo sa nenaslo" << endl;
	return NULL;
}

// TODO: V�etko
void Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// vytvor�m
	Objednavka * objednavka = new Objednavka(hmotnostZasielky, odosielatel, adresat);
	//zaevidujem do firmy
	this->linkedListObjednavok->add(objednavka);

	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());


	// zist�m drona z tohto prekladiska, �i m�m nejak�ho drona, ktor� stihne, unesie a je nabit� 
	// TODO vyber drona ak nie je vo�n� -> zisti �as, kedy m��e
	Dron* dronPreOdosielatela = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska(), objednavka->getDatumaCasVytvorenia());


	// zist�m �i mi do prekladiska pr�de auto ktor� bude ma� nosno� tak�, �e zvl�dne odniest objednavku
	Vozidlo* vozidloPreOdosielatela = this->vyberVozidlo(hmotnostZasielky, prekladiskoOdoslania);

	// TODO: ADRESAT
	Prekladisko* prekladiskoAdresata = this->dajPrekladiskoPodlaRegionu(adresat->getRegion());
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(hmotnostZasielky, prekladiskoAdresata);
	// FIXME toto sa ale p�taj a� nesk�r, resp na nejak� �as, kedy tam dan� objedn�vka bude 
	// Dron* dronPreAdresata = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, adresat->getVzdialenostOdPrekladiska());

	//if (dronPreOdosielatela == NULL ||
	// TODO
	if (dronPreOdosielatela == NULL ||
		vozidloPreOdosielatela == NULL ||
		vozidloPreAdresata == NULL)
	{
		objednavka->setStav(eStavObjednavky::ZAMIETNUTA);
	}
	else
	{
		if (dronPreOdosielatela->vytazenyDo() > Datum::time_t_to_string(Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + 60 * 60)) {
			// TODO if setDatumaCasSpracovania_ > 1 hodina -> mo�nos� zru�enia ;
			if (chceUserZrusitObjednavku(dronPreOdosielatela, objednavka)) { return; }
		}
		std::cout << "Predpokladany cas priletu dronu je " << std::endl;
		objednavka->setStav(eStavObjednavky::PRIJATA);
		objednavka->setDatumaCasSpracovania_(dronPreOdosielatela->vytazenyDo());
		dronPreOdosielatela->pridajObjednavku(objednavka);




		vozidloPreOdosielatela->pridajZasielku(objednavka->getHmotnostZasielky());
		// prida� ?
		//prekladiskoAdresata->pridajObjednavku(objednavka);
	}
}

bool Firma::chceUserZrusitObjednavku(Dron * dronPreOdosielatela, Objednavka * objednavka)
{
	int userInput;
	cout << "Vasu zasielku m�zeme spracovat o viac ako hodinu a to konkretne " <<
		dronPreOdosielatela->vytazenyDo() << endl <<
		"Prajete si zasielku zrusit?" << endl;
	cout <<
		"1. ANO" << endl <<
		"2. NIE" << endl;
	cin >> userInput;
	if (userInput == 1) {
		objednavka->setStav(eStavObjednavky::ZRUSENA);
		cout << "Vasa objednavka bola zrusena" << endl;
		return true;
	}
	return false;
}

