#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrausnahme.h"





Fahren::Fahren(Weg& weg):
		Verhalten(weg){

}

double Fahren::dStrecke(Fahrzeug& fzg, double dZeitIntervall) const {


	if(fzg.getAbschnittStrecke() >= p_pWeg.getLaenge()){

		throw Streckenende(fzg, p_pWeg);
	}


	//Berechnung der möglichen Strecke basierend auf der aktuellen Geschwindigkeit des Fahrzeugs
	double dMoeglicheStrecke = fzg.dGeschwindigkeit() * dZeitIntervall;

	//Berechnung der verbleibenden Strecke auf dem Weg
	double dVerbleibendeStrecke = p_pWeg.getLaenge() - fzg.getAbschnittStrecke();


	//if(std::abs(dVerbleibendeStrecke) < 1e-6) return 0.0; //Wenn die verbleibende Strecke sehr klein ist, gib 0 zurück

	//Wenn die mögliche Strecke größer ist als die verbleibende Strecke, gib die verbleibende Strecke zurück
	if(dMoeglicheStrecke > dVerbleibendeStrecke){

		return dVerbleibendeStrecke;
	}



	//Die tatsächlich zurückgelegte Strecke ist das Minimum aus möglicher Strecke und verbleibender Strecke
	return  dMoeglicheStrecke;
}






