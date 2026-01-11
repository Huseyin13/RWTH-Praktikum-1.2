#pragma once
#include <exception>
#include <string>
#include <iostream>
#include "Fahrzeug.h"
#include "Weg.h"





class Fahrausnahme : public std::exception {

protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;

public:
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg)
		: p_pFahrzeug(fahrzeug), p_pWeg(weg) {}

	virtual void vBearbeiten() = 0;



};


class Losfahren : public Fahrausnahme {

public:

	Losfahren(Fahrzeug& fahrzeug, Weg& weg)
		: Fahrausnahme(fahrzeug, weg) {}

	virtual void vBearbeiten() override {
		std::cout << "Fahrzeug " << p_pFahrzeug.getName()
			<< " faehrt auf den Weg " << p_pWeg.getName()
			<< " los"<< std::endl;
	}
};


class Streckenende : public Fahrausnahme {
	public:
	Streckenende(Fahrzeug& fahrzeug, Weg& weg)
		: Fahrausnahme(fahrzeug, weg) {}

	void vBearbeiten() override {
		std::cout << "Fahrzeug " << p_pFahrzeug.getName()
			<< " hat das Ende des Weges " << p_pWeg.getName()
			<< " erreicht" << std::endl;
	}
};
