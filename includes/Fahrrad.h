#pragma once
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {

private:



protected:




public:

	Fahrrad(std::string name, double maxGeschwindigkeit);

	virtual void vAusgeben(std::ostream& o) const override;
	virtual void vSimulieren() override;

	virtual double dGeschwindigkeit() const override;

	virtual void vZeichnen(const Weg& rWeg) const; // Zeichnen-Methode für Fahrzeug
};
