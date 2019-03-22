#include "Vozidlo.h"
#include "structures/heap_monitor.h"


Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{

	//Vozidlo bude v�dy obsluhova� t� ist� trasu (niekedy m��e vynecha� stredisko, ak tam ni� nevezie). T�to mu je potrebn� priradi�, �o m��ete spravi� dvomi sp�sobmi:
	//Pevn� trasa mu bude priraden�(napr., ke� ho vytvor�m a vlo��m do syst�mu, tak mu aj vyberiem / vysklad�m trasu, po ktorej bude v�dy chodi�)
	//Trasa mu bude zaka�d�m po��tan�(ve�mi pekn� a flexibiln� rie�enie, ale nemus�te to rie�i� takto)

	celkovaNosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	datumaCasEvidencie_ = Datum::getAktualnyDatum();
	SPZ_ = SPZ;
}

int Vozidlo::unikatnostSPZ_ = 000;

Vozidlo::~Vozidlo()
{
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}