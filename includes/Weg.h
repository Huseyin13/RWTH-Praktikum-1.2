#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

#include <list>
#include <memory>

class Kreuzung; //Vorwärtsdeklaration der Kreuzung-Klasse

class Fahrzeug; //Vorwärtsdeklaration der Fahrzeug-Klasse

class Weg : public Simulationsobjekt {

public:

	Weg(std::string name, double p_dLaenge, Tempolimit limit = Tempolimit::Autobahn, bool bUeberholverbot = true);
	virtual ~Weg();

	virtual void vSimulieren() override;
	virtual void vAusgeben(std::ostream& o) const override;

	double getTempolimit() const;

	double getLaenge() const;

	static void vKopf();

	void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug);

	void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit);

	void vZeichnen() const;

	void SetzeZielKreuzung(std::shared_ptr<Kreuzung> zielKreuzung);
	void SetzeRueckweg(std::shared_ptr<Weg> rueckweg);

	std::shared_ptr<Kreuzung> getZielKreuzung() const;
	std::shared_ptr<Weg> getRueckweg() const;





protected:

private:
	double p_dLaenge; //Länge des Wegs in km
	Tempolimit p_eTempolimit; //Tempolimit des Wegs

	bool p_bUeberholverbot; //Gibt an, ob Überholverbot auf dem Weg herrscht

	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; //Liste der Fahrzeuge auf dem Weg

	std::weak_ptr<Kreuzung> p_pZielKreuzung; //Zielkreuzung des Wegs

	std::weak_ptr<Weg> p_pRueckweg;
};
