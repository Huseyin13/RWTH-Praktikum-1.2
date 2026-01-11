#include <iostream>
#include "PKW.h"
#include "Weg.h"
#include "Simuclient.h"
#include <iomanip>

/* Konstruktor der PKW-Klasse
Initialisierungsliste wird verwendet, um:
Basisklassenmember direkt zu initialisieren (p_sName, p_iId usw.)
und effizient zu arbeiten (keine unnötigen Zuweisungen)
PKW-spezifische Variablen werden ebenfalls direkt initialisiert: Verbrauch, Tankvolumen, Tankinhalt*/
PKW::PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankVolumen):
		Fahrzeug(name,maxGeschwindigkeit)
		{
	p_dVerbrauch = verbrauch;
	p_dTankVolumen = tankVolumen;
	p_dTankInhalt = tankVolumen / 2.0; // Startet mit halbem Tankinhalt



}

//Getankte Menge zurückgeben
double PKW::dTanken(double dMenge) {
	double d_freierPlatz = p_dTankVolumen - p_dTankInhalt; // Verfügbarer Platz im Tank

	// Überprüfen, ob die zu tankende Menge gültig ist
	if(dMenge <= 0.0){
		return 0.0;
	}

	// Überprüfen, ob die zu tankende Menge den verfügbaren Platz überschreitet
	if(dMenge>= d_freierPlatz){

		p_dTankInhalt = p_dTankVolumen;

		// Nur der verfügbare Platz wurde getankt
		//Deswegen geben wir den freien Platz zurück
		return d_freierPlatz;

	}else // Normales Tanken
	{
		p_dTankInhalt += dMenge;

		// Die gesamte Menge wurde getankt
		return dMenge;
	}
}

void PKW::vAusgeben(std::ostream& o) const{

	// Rufen wir die Basisklassenmethode auf, um die gemeinsamen Fahrzeuginformationen auszugeben
	Fahrzeug::vAusgeben(o);

	// Fügen wir die PKW-spezifischen Informationen hinzu: Verbrauch und Tankinhalt
			o << std::fixed << std::setprecision(2)
			  << std::right
			  << std::setw(11) << p_dVerbrauch
			  << std::setw(16) << p_dTankInhalt;

}



void PKW::vSimulieren(){


	    if (p_dTankInhalt <= 0.0 || (dGlobaleZeit - p_dZeit) <= 0.0) {
	        p_dZeit = dGlobaleZeit;
	        return;
	    }

	    double dStreckeVorher = p_dGesamtStrecke;
        Fahrzeug::vSimulieren();

        double dGefahreneStrecke = p_dGesamtStrecke - dStreckeVorher;

        if(dGefahreneStrecke >0.0){

        	double dVerbrauchterKraftstoff = (dGefahreneStrecke * p_dVerbrauch) / 100.0;

        	p_dTankInhalt -= dVerbrauchterKraftstoff;

			if(p_dTankInhalt < 0.0){
				p_dTankInhalt = 0.0; // Verhindert negativen Tankinhalt
			}
        }
	    }


double PKW::getTankInhalt() const{
	return p_dTankInhalt;
}


double PKW::dGeschwindigkeit() const{

	// 1. Arabanın teorik maksimum hızını al
	double aktuelleGeschwindigkeit = p_dMaxGeschwindigkeit;

	// 2. Araba bir yolda mı? (Verhalten pointer'ı dolu mu?)
	// p_pVerhalten, Fahrzeug sınıfından miras gelir.
	if(p_pVerhalten != nullptr){

		Weg& aktuellerWeg = p_pVerhalten->getWeg();

		double wegTempolimit = aktuellerWeg.getTempolimit();


		if(aktuelleGeschwindigkeit > wegTempolimit){
			aktuelleGeschwindigkeit = wegTempolimit;
		}

	}

	return aktuelleGeschwindigkeit;

}

void PKW::vZeichnen(const Weg& rWeg) const{
		// 1. Yolun toplam uzunluğunu al
	    double dWegLaenge = rWeg.getLaenge();

	    // 2. Rölatif (Oransal) konumu hesapla (Gidilen Yol / Toplam Yol)
	    // Örn: 100km yolun 50. kilometresindeysek sonuç 0.5 olur.
	    double dRelPosition = p_dAbschnittStrecke / dWegLaenge;
	bZeichnePKW(p_sName, rWeg.getName(), dRelPosition, dGeschwindigkeit(), p_dTankInhalt);
}







