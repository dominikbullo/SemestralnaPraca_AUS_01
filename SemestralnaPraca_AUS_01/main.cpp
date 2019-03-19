#include <iostream>
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "Vozidlo.h"
#include "Datum.h"
#include "Dron.h"
#include "Firma.h"

int main()
{
	initHeapMonitor();
	// TODO 2: Vyp�sanie zoznamu vozidiel pod�a d�tumu zaradenia do evidencie. Vyp�e sa �PZ,
	// nosnos� vozidla a celkov� prev�dzkov� n�klady od d�tumu zaradenia do evidencie.

	// TODO 3: Pridanie nov�ho dronu do lok�lneho prekladiska. Dron je charakterizovan� s�riov�m
	//��slom a typom, ktor� ur�uje jeho �al�ie atrib�ty, ktor�mi s� nosnos�, r�chlos�, doba letu a doba nab�jania.

	// TODO 4: Vyp�sanie v�etk�ch dronov evidovan�ch v zadanom lok�lnom prekladisku. Pri
	//ka�dom drone sa vyp�e jeho d�tum zaradenia do evidencie, typ, celkov� po�et nalietan�ch hod�n a celkov� po�et prepraven�ch z�sielok.

	Firma * firma = new Firma();
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));
	firma->pridajVozidlo(new Vozidlo(10, 100));

	Dron * dron1 = new Dron(eDrony::JEDEN);
	Dron * dron2 = new Dron(eDrony::DVA);



	system("pause");
	return 0;
}