#pragma once
#include "Simulationsobjekt.h"
#include "Weg.h"

#include <memory>
#include <list>
#include <string>

class Fahrzeug;

class Kreuzung : public Simulationsobjekt {
public:
	Kreuzung(std::string name, double dTankstelle = 0.0);
	virtual ~Kreuzung() = default;

	static void vVerbinden(std::string sWegname1,
			std::string sWegname2,
			double dLaenge,
			std::shared_ptr<Kreuzung> startKreuzung, std::shared_ptr<Kreuzung> zielKreuzung,
			Tempolimit eTempolimit, bool bUeberholverbot = true);

	void vTanken(Fahrzeug& fahrzeug);

	virtual void vSimulieren() override;
	void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit);

	std::shared_ptr<Weg> pZufaelligerWeg(Weg& ankommenderWeg);

	std::shared_ptr<Weg> getWeg(std::string sName) const;

	double getTankstelle() const { return p_dTankstelle; }


protected:
	double p_dTankstelle;



private:
	std::list<std::shared_ptr<Weg>> p_pWege;

};
