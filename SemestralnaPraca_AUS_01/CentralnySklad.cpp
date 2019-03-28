#include "CentralnySklad.h"

using namespace std;

CentralnySklad::CentralnySklad()
{
	arrayListZasielok = new structures::ArrayList<Zasielka*>();
}

CentralnySklad::~CentralnySklad()
{
	delete arrayListZasielok;
}

void CentralnySklad::prijmiZasielky(Vozidlo * vozidlo)
{

	for (Zasielka* zasielka : vozidlo->getArrayListZasielok())
	{
		arrayListZasielok->add(zasielka);
	}
	// TODO po pridan�, odstra� zasielku z vozidla -> vyber a prelo� do in�ho 
	// TODO otestova� 
	vozidlo->getArrayListZasielok().clear();
}

void CentralnySklad::vypisZoznamZasielok() {
	cout << endl << "*******************************************************************" << endl;
	cout << "*************** Zoznam zasielok v centralnom sklade ***************" << endl;
	cout << "*******************************************************************" << endl << endl;
	for (Zasielka* zasielka : *arrayListZasielok)
	{
		zasielka->toString();
	}
}
void CentralnySklad::naplVozidla() {
}