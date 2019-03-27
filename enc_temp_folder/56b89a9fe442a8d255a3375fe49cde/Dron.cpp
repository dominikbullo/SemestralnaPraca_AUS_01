#include "Dron.h"
using namespace std;

Dron::Dron(const eDrony typDronu, string serioveCislo)
{
	typ_ = typDronu;
	serioveCislo_ = serioveCislo;
	datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();

	// evidujem bud�ce objedn�vky, ktor� m� dron vybavi�
	frontObjednavok_ = new structures::ExplicitQueue<Objednavka*>();

	switch (typDronu) {
	case eDrony::JEDEN:
		nosnost_ = (int)dronTypuJeden::NOSNOST;
		primernaRychlost_ = (int)dronTypuJeden::PRIEMERNA_RYCHLOST;
		maxDobaLetu_ = (int)dronTypuJeden::MAX_DOBA_LETU;
		casNaNabitie10Percent_ = (int)dronTypuJeden::CAS_NABITIE_10_PERCENT;
		break;

	case eDrony::DVA:
		nosnost_ = (int)dronTypuDva::NOSNOST;
		primernaRychlost_ = (int)dronTypuDva::PRIEMERNA_RYCHLOST;
		maxDobaLetu_ = (int)dronTypuDva::MAX_DOBA_LETU;
		casNaNabitie10Percent_ = (int)dronTypuDva::CAS_NABITIE_10_PERCENT;
		break;

	default:
		cout << "Neviem vytvorit takyto dron" << endl;
	}
}

Dron::~Dron()
{
	// Preto�e v de�truktore firmy som vymazal v�etky objedn�vky -> tu u� nemus�m
	frontObjednavok_->clear();
	delete frontObjednavok_;
}

void Dron::pridajObjednavku(Objednavka * novaObjednavka)
{
	double vzdialenostObjednavky = novaObjednavka->getOdosielatel()->getVzdialenostOdPrekladiska();
	double trvanieLetuObjednavky = trvanieLetu(vzdialenostObjednavky);
	time_t pom = Datum::string_to_time_t(vytazenyDo_);

	this->vytazenyDo_ = Datum::time_t_to_string(pom + trvanieLetuObjednavky);
	znizKapacituBaterie(trvanieLetuObjednavky);
	this->celkovyPocetNalietanychHodin_ += trvanieLetuObjednavky / 60 / 60;
	this->celkovyPocetPrepravenychZasielok_++;
	novaObjednavka->setDatumaCasUkoncenia_(Datum::time_t_to_string(pom + trvanieLetuObjednavky));

	frontObjednavok_->push(novaObjednavka);
}

void Dron::spracujObjednavky()
{
	//throw std::exception("Dron::spracujObjednavky: Not implemented yet.");
	if (frontObjednavok_->isEmpty()) { return; }
	//TODO think about this
	while (frontObjednavok_->peek()->getDatumaCasUkoncenia_() < Datum::getAktualnyDatumaCas())
	{
		Objednavka* vybranaObjednavka = frontObjednavok_->peek();
		vytazeny_ = false;
		vybranaObjednavka->setStav(eStavObjednavky::ZREALIZOVANA);
		std::cout << "Objednavka bola zrealizovana" << std::endl;
		vybranaObjednavka->toString();
		frontObjednavok_->pop();

	}

}


bool Dron::stihnePriletietPreZasielku(double vzdialenost) {
	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

	tm *ltm = localtime(&aktualnyCas);
	struct tm casNajneskor = *ltm;
	casNajneskor.tm_hour = 20;
	casNajneskor.tm_min = 00;

	time_t ocakavanyCasPriletu = this->casPriletuPreZasielku(vzdialenost);
	return ocakavanyCasPriletu <= mktime(&casNajneskor);
}


void Dron::toString()
{
	cout << "******************** Informacie o dronovi **********************" << endl;
	cout <<
		"Seriove cislo - " << this->serioveCislo_ << endl <<
		"Datum zaradenia do prevadzky - " << this->datumaCasEvidencie_ << endl <<
		"Typ - " << ((typ_ == eDrony::JEDEN) ? "jeden" : "dva") << endl <<
		"Obsadeny do - " << this->vytazenyDo_ << endl <<
		"Kapacita baterie - " << this->kapacitaBaterie_ << endl <<
		"celkovyPocetNalietanychHodin - " << this->celkovyPocetNalietanychHodin_ << endl <<
		"celkovyPocetPrepravenychZasielok - " << this->celkovyPocetPrepravenychZasielok_ << endl;
	cout << "*******************************************************************" << endl;

}

