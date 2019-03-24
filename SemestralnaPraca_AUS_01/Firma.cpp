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
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		delete vozidlo;
	}
	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		delete prekladisko;
	}
	for (Objednavka * objednavka : *linkedListObjednavok) {
		delete linkedListObjednavok;
	}
	delete arrayListVozidiel;
	delete arrayListPrekladisk;
	delete linkedListObjednavok;
}
Firma * Firma::get()
{
	return this;
}

void Firma::pridajPrekladisko(Prekladisko* novePrekladisko)
{
	arrayListPrekladisk->add(novePrekladisko);
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

Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string okres) {
	// zlo�itos� O(n)

	// NOTE osetrenie zl�ho vstupu
	//for (auto & c : okres) c = toupper(c);

	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		if (prekladisko->dajOkres() == okres) {
			return prekladisko;
		}
	}
	// TODO: throw exeption
	throw std::logic_error("Prekladisko v tomto okrese sa nenaslo");
}

// TODO 5:Pri vytv�ran� objedn�vky je nutn� kontrolova�, �i ned�jde k jej zamietnutiu zo strany
// AoE.Dokon�en� objedn�vka je zaraden� do frontu objedn�vok �akaj�cich na spracovanie.
// TODO 5:Po�as vystavovania objedn�vky, m��e by� z�sielka z viacer�ch d�vodov zamietnut�:
		//	a) z�sielka by musela by� vyzdvihnut� a� po 20:00;
		//	b) z�sielka je mimo ak�n� r�dius dronov(dron nestihne d�js� k odosielate�ovi / adres�tovi
		//	a vr�ti� sa sp� predt�m, ako sa mu vybije bat�ria);
		//	c) z�sielku nie je mo�n� doru�i�, preto�e je jej hmotnos� vy��ia ako nosnos� dostupn�ch
		//	dronov v lok�lnom prekladisku odosielate�a, resp.adres�ta;
		//	d) nalo�enie z�sielky do vozidla prekro�� jeho nosnos�;
		//	e) prijatie z�sielky v lok�lnom prekladisku odosielate�a by sp�sobilo, �e toto lok�lne
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

	std::cout << "Takuto objednavku nezvladne dorucit ziadne vozidlo" << std::endl;
	return NULL;
}

Objednavka * Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// TODO pokra�ovanie 5ky

	Objednavka * objednavka = new Objednavka(hmotnostZasielky, odosielatel, adresat);

	// zist�m prekladisko, kde sa odosielal dron
	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());

	// zist�m, �i m�m nejak�ho drona, ktor� stihne, unesie a je nabit� 
	Dron* dronPreOdosielatela = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska());
	// TODO
	//objednavka->pripaDronaPreOdosielatela();

	// zist�m �i mi do prekladiska pr�de auto ktor� bude ma� nosno� tak�, �e zvl�dne odniest objednavku
	Vozidlo* vozidloPreOdosielatela = this->vyberVozidlo(hmotnostZasielky, prekladiskoOdoslania);
	// TODO
	//objednavka->priradVozidlo();

	Prekladisko* prekladiskoAdresata = this->dajPrekladiskoPodlaRegionu(adresat->getRegion());
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(hmotnostZasielky, prekladiskoAdresata);
	// TODO
	//objednavka->priradVozidlo();

	// FIXME toto sa ale p�taj a� nesk�r, resp na nejak� �as, kedy tam dan� objedn�vka bude 
	Dron* dronPreAdresata = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, adresat->getVzdialenostOdPrekladiska());

	// treba vymaza� !
	//return new Objednavka(hmotnostZasielky, odosielatel, adresat);
	return NULL;
}

