#include "Zasielka.h"

using namespace std;

Zasielka::Zasielka(double hmotnost, Objednavka * objednavka)
{
	this->hmotnost_ = hmotnost;
	this->region_ = objednavka->getOdosielatel()->getRegion();
	this->vzdialenostOdPrekladiska_ = objednavka->getOdosielatel()->getVzdialenostOdPrekladiska();
	this->objednavka_ = objednavka;
	// NOTE: nemus�m vedie� smer, v sklade iba zmenim region a vzdialenost
	//this->smerZasielky = eSmerZasielky::DO_CENTRALNEHO_SKLADU;
}

Zasielka::~Zasielka()
{
	this->hmotnost_ = 0;
	this->vzdialenostOdPrekladiska_ = 0;
	this->region_ = "";
}


void Zasielka::toString()
{
	cout << "********************* Informacie o zasielke ***********************" << endl;
	cout <<
		"Hmotnost zasielky: " << hmotnost_ << endl <<
		"datumaCasSpracovania_: " << datumaCasSpracovania_ << endl <<
		"datumaCasPrevzatia_: " << datumaCasPrevzatia_ << endl <<
		"datumaCasUkoncenia_: " << datumaCasUkoncenia_ << endl;
	cout << "********************** Pre tuto objednavku ************************" << endl;
	this->objednavka_->toString();
	cout << "*******************************************************************" << endl;
	cout << "*******************************************************************" << endl;
	cout << "*******************************************************************" << endl;
}
