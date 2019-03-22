#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

#include "structures/heap_monitor.h"

#include "Konstatnty.h"
#include "Datum.h"
#include "Vozidlo.h"


class Vozidlo
{
public:
	Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ);
	~Vozidlo();
	void toString();
	inline int getCelkovaNosnost() {
		return celkovaNosnost_;
	}
	inline int getPrevazdkoveNaklady() {
		return prevadzkoveNaklady_;
	}
	inline std::string getSPZ() {
		return SPZ_;
	}
	inline int getNaklady() {
		return naklady_;
	}
	std::string getDatumaCasEvidencie() {
		return datumaCasEvidencie_;
	}
	void pridajZasielku(double hmotnostZasielky) {
		nosnost_ -= hmotnostZasielky;
	}
	bool dokazeNalozitZasielku(double hmotnostZasielky) {
		return celkovaNosnost_ >= nosnost_ + hmotnostZasielky;
	}
	// TODO: e) prijatie z�sielky v lok�lnom prekladisku odosielate�a by sp�sobilo, �e toto lok�lne
	//			prekladisko nedok�e doru�i� niektor� z�sielky, ktor�ch adres�ti sa nach�dzaj� v jeho regi�ne, do 18:00 dan�ho d�a.

private:
	void setSPZ();
	int prevadzkoveNaklady_;
	int celkovaNosnost_;
	std::string datumaCasEvidencie_;
	std::string SPZ_ = "ZA_";
	int naklady_ = 0;
	double nosnost_ = celkovaNosnost_;

protected:
	static int unikatnostSPZ_;
};

