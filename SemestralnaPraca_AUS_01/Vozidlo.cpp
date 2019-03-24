#include "Vozidlo.h"
#include "structures/heap_monitor.h"

using namespace std;

Vozidlo::Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ)
{
	//Vozidlo bude v�dy obsluhova� t� ist� trasu (niekedy m��e vynecha� stredisko, ak tam ni� nevezie). T�to mu je potrebn� priradi�, �o m��ete spravi� dvomi sp�sobmi:
	//Pevn� trasa mu bude priraden�(napr., ke� ho vytvor�m a vlo��m do syst�mu, tak mu aj vyberiem / vysklad�m trasu, po ktorej bude v�dy chodi�)
	//Trasa mu bude zaka�d�m po��tan�(ve�mi pekn� a flexibiln� rie�enie, ale nemus�te to rie�i� takto)

	nosnost_ = nostnostVozidla;
	prevadzkoveNaklady_ = prevadzkoveNaklady;
	SPZ_ = SPZ;
	datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();
	// Zmenil som Linked na Array - POZOR 
	linkedListTrasaVozidla = new structures::ArrayList<Prekladisko*>();
}

Vozidlo::~Vozidlo()
{
	delete linkedListTrasaVozidla;
}

void Vozidlo::toString()
{
	std::cout << "Prevazdkove naklady - " << prevadzkoveNaklady_ << "\t SPZ - " << SPZ_ << "\t CELKOVE NAKLADY: " << naklady_ << " " << std::endl;
}

void Vozidlo::pridajPrekladiskoDoTrasyVozidla(Prekladisko* prekladisko) {
	linkedListTrasaVozidla->add(prekladisko);
}