#include "Dron.h"


Dron::Dron(const eDrony typDronu, std::string serioveCislo)
{
	typ_ = typDronu;
	serioveCislo_ = serioveCislo;
	datumEvidencie_ = Datum::getAktualnyDatumaCas();

	// evidujem bud�ce objedn�vky, ktor� m� dron vybavi�
	arrayListObjednavokNaVybavenie = new structures::ArrayList<Objednavka*>();

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
		std::cout << "Neviem vytvorit takyto dron" << std::endl;
	}
}

Dron::~Dron()
{
	// Preto�e v de�truktore firmy som vymazal v�etky objedn�vky -> tu u� nemus�m
	delete arrayListObjednavokNaVybavenie;
}
void Dron::pridajObjednavku(Objednavka * novaObjednavka) {
	// �o tu treba e�te ???
	vytazeny_ = true;
	std::string vytazenyDo = novaObjednavka->getCasDokonceniaObjednavky(novaObjednavka->getOdosielatel()->getVzdialenostOdPrekladiska());
	// TODO mo�no �ekn�t �i je moment�lne vy�a�en� a do kedy. ak by to bolo men�ie tak to viem porovn�va�
	int index = 0;
	for (Objednavka *objednavka : *arrayListObjednavokNaVybavenie) {
		if (novaObjednavka->getDatumaCasVytvorenia() < objednavka->getDatumaCasVytvorenia())
		{
			arrayListObjednavokNaVybavenie->insert(objednavka, index);
			return;
		}
		index++;
	}
	arrayListObjednavokNaVybavenie->add(novaObjednavka);
}
bool Dron::stihnePriletietPreZasielku(double vzdialenost) {
	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

	tm *ltm = localtime(&aktualnyCas);
	struct tm casNajneskor = *ltm;
	casNajneskor.tm_hour = 20;
	casNajneskor.tm_min = 00;

	time_t ocakavanyCasPriletu = this->casPriletuPreZasielku(vzdialenost);
	std::cout <<
		(ocakavanyCasPriletu <= mktime(&casNajneskor) ?
			"Predpokladany cas priletu dronu ( " + this->serioveCislo_ + " ) : " + Datum::time_t_to_string(ocakavanyCasPriletu) : "Dron to nestihne") <<
		std::endl;
	return ocakavanyCasPriletu <= mktime(&casNajneskor);
}


void Dron::toString()
{
	std::cout << "Datum zaradenia do prevadzky - " << this->datumEvidencie_ <<
		"\t Seriove cislo - " << this->serioveCislo_ <<
		"\t TYP - " << ((typ_ == eDrony::JEDEN) ? "jeden" : "dva") << "\t celkovyPocetNalietanychHodin - " <<
		this->celkovyPocetNalietanychHodin_ << "\t celkovyPocetPrepravenychZasielok - " <<
		this->celkovyPocetPrepravenychZasielok_ << std::endl;
}

