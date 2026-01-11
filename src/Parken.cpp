#include "Parken.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrausnahme.h"

extern double dGlobaleZeit; //Globale Simulationszeit


Parken::Parken(Weg& weg, double startzeit):
		Verhalten(weg),
		p_dStartzeit(startzeit){



}


double Parken::dStrecke(Fahrzeug& fzg, double dZeitIntervall) const {


	if(dGlobaleZeit < p_dStartzeit)


		return 0.0; // Fahrzeug bleibt stehen, wenn die globale Zeit die Startzeit erreicht oder überschreitet


	else{
		throw Losfahren(fzg, p_pWeg);
	}

}







