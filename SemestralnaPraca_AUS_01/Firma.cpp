#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayPrekladisk = new structures::ArrayList<Prekladisko*>();
	linkObjednavok = new structures::LinkedList<Objednavka*>();
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
	for (Objednavka * objednavka : *linkObjednavok) {
		delete linkObjednavok;
	}
	delete arrayVozidiel;
	delete arrayPrekladisk;
	delete linkObjednavok;
}

void Firma::pridajPrekladisko(Prekladisko* novePrekladisko)
{
	arrayPrekladisk->add(novePrekladisko);
}

void Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	// vozidlo prid�vam v�dy na koniec, t�m p�dom viem, �e vozidl� s� zoraden� pod�a poradia zaevidovania
	int index = 0;
	for (Vozidlo *vozidlo : *arrayVozidiel) {
		// FIXME pozor na toto porovn�vanie 
		if (vozidlo->getDatumaCasEvidencie() <= noveVozidlo->getDatumaCasEvidencie()) {
			arrayVozidiel->insert(noveVozidlo, index);
			return;
		}
		index++;
	}
	arrayVozidiel->add(noveVozidlo);
}

void Firma::vypisZoznamVozidiel()
{
	for (Vozidlo* var : *arrayVozidiel) {
		var->toString();
	}

}

Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string okres) {
	// zlo�itos� O(n)

	// NOTE osetrenie zl�ho vstupu
	//for (auto & c : okres) c = toupper(c);

	for (Prekladisko * prekladisko : *arrayPrekladisk) {
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

Objednavka * Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// TODO pokra�ovanie 5ky

	// zist�m prekladisko, kde sa odosielal dron
	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());
	// zist�m, �i m�m nejak�ho drona, ktor� stihne, unesie a je nabit� 
	Dron* dron = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska());

	// treba vymaza� !
	return new Objednavka(hmotnostZasielky, odosielatel, adresat);
}

