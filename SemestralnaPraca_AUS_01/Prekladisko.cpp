#include "Prekladisko.h"
#include "Dron.h"


Prekladisko::Prekladisko(std::string region)
{
	region_ = region;
	arrayDronov = new structures::ArrayList<Dron*>();

	// prekladisko m� v�dy aspo� dvoch dronov pri vytv�ran�
	arrayDronov->add(new Dron(eDrony::JEDEN));
	arrayDronov->add(new Dron(eDrony::DVA));
	arrayDronov->add(new Dron(eDrony::DVA));
}


Prekladisko::~Prekladisko()
{
	for (Dron * dron : *arrayDronov) {
		delete dron;
	}
	delete arrayDronov;
}

void Prekladisko::pridajDron(Dron * novyDron)
{
	// TODO sort by date
	arrayDronov->add(novyDron);
}

void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << region_ << std::endl;
	for (Dron * dron : *arrayDronov) {
		dron->toString();
	}
}

Dron * Prekladisko::vyberDrona(double hmotnostZasielky, double vzdialenost)
{
	// TODO pokra�ovanie -> v�ber spr�vneho drona na doru�enie z�sielky od adres�ta/odosielatela z/do skladiska
	for (Dron * dron : *arrayDronov) {
		if (dron->zvladneLet(vzdialenost) && dron->unesieZasielku(hmotnostZasielky)) {
			return dron;
		}
	}
	return 0;
}