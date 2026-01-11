#include <iostream>
#include "Fahrzeug.h"
#include "Parken.h"
#include "Fahren.h"
#include <iomanip>
#include "Weg.h"






//Konstruktor mit Name und maxGeschwindigkeit Parameter
Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit):
		Simulationsobjekt(name),
		p_dVerbrauch(0.0),
		p_dTankVolumen(0.0),
		p_dTankInhalt(0.0),
		p_dMaxGeschwindigkeit(maxGeschwindigkeit<0.0 ? 0.0 : maxGeschwindigkeit),
		p_dGesamtStrecke(0.0),
		p_dGesamtZeit(0.0),
		p_dAbschnittStrecke(0.0)
		{
}

//Destruktor
//Der Destruktor wird aufgerufen, wenn ein Fahrzeugobjekt gelöscht wird
Fahrzeug::~Fahrzeug() {
}






void Fahrzeug::vKopf() {

	//Kopfzeile für die Fahrzeugdaten ausgeben
	// Textausgabe wird linkbündig ausgerichtet.
	std::cout << std::left;
	std::cout << std::setw(5) << "ID"; //Breit 5 für ID
	std::cout << std::setw(15) << "Name"; //Breit 15 für Name
	std::cout << std::setw(20) << "MaxGeschwindigkeit"; //Breit 20 für MaxGeschwindigkeit
	std::cout << std::setw(15) << "AktuelleGeschw"; //Breit 15 für AktuelleGeschw
	std::cout << std::setw(15) << "GesamtStrecke"; //Breit 15 für GesamtStrecke
	std::cout << std::setw(15) << "Verbrauch"; //Breit 15 für Verbrauch
	std::cout << std::setw(15) << "Tankinhalt"; //Breit 15 für Tankinhalt



}

// Ausgabe der Fahrzeugdaten auf einen Stream
void Fahrzeug::vAusgeben(std::ostream& o) const {

	// Textausgabe wird linkbündig ausgerichtet.
	o << std::left;

	o << std::fixed << std::setprecision(2); // Stellen wir feste Kommazahl mit 2 Nachkommastellen ein.

	Simulationsobjekt::vAusgeben(o); //Ruft die vAusgeben Methode der Basisklasse Simulationsobjekt auf.

	o << std::right; // Ab hier rechtsbündig

	o << std::setw(18) << p_dMaxGeschwindigkeit;
	o << std::setw(16) << dGeschwindigkeit();
	o << std::setw(14) << p_dGesamtStrecke;

    // Formatierungzustände am Ende der Ausgabe zurücksetzen.
    // defaultfloat entfernt feste Kommazahl-Einstellung.
    // std::defaultfloat stellt die Standardausgabe wieder her.
	o << std::defaultfloat << std::right;

}



// Virtuelle Tankfunktion für alle Fahrzeuge.
// In Fahrzeug datei tanken ist notwendig, damit wir 'dTanken' auch auf allgemeinen Fahrzeug-Zeigern (z.B. im Vektor)
// aufrufen können, ohne zu wissen, ob es ein PKW oder Fahrrad ist.
double Fahrzeug::dTanken(double dMenge){
		return 0.0;
	}



void Fahrzeug::vSimulieren(){
	// Simuliert die Bewegung des Fahrzeugs für das vergangene Zeitintervall.
	// Aktualisiert die zurückgelegte Strecke, die Fahrzeit und synchronisiert die Fahrzeugzeit.

    	//Überprüfen wir, ob die Fahrzeugzeit hinter der globalen Zeit liegt
    	if(p_dZeit < dGlobaleZeit){//verhindert versehentlich doppelte Simulation

    		// 1. Zeitintervall berechnen
    		double dZeitIntervall = dGlobaleZeit - p_dZeit;

    		// 2. Berechne die zurückgelegte Strecke basierend auf dem aktuellen Verhalten
    		double dStrecke = 0.0;

    		// Überprüfen, ob ein Verhalten (Weg) zugewiesen ist
    		if(p_pVerhalten){
				dStrecke = p_pVerhalten->dStrecke(*this, dZeitIntervall);
			}

    		// 3. Aktualisiere die Gesamtstrecke und Gesamtzeit
    		p_dGesamtStrecke += dStrecke;
    		p_dGesamtZeit += dZeitIntervall;
    		p_dAbschnittStrecke += dStrecke;


    		if(p_dTankInhalt >0.0){
    			p_dTankInhalt -= dStrecke * p_dVerbrauch/100; //Verbrauch aktualisieren
    		}

    		if(p_dTankInhalt <0.0){
				p_dTankInhalt = 0.0; //Verhindert negativen Tankinhalt
			}
    		// 4. Aktualisiere die Fahrzeugzeit auf die globale Zeit
    		p_dZeit = dGlobaleZeit;
    	}



    }



	//Berechnung der aktuellen Geschwindigkeit des Fahrzeugs
    double Fahrzeug::dGeschwindigkeit() const{

    	double dTempolimit = p_pVerhalten ? p_pVerhalten->getWeg().getTempolimit() : std::numeric_limits<double>::infinity();

    	return std::min(p_dMaxGeschwindigkeit, dTempolimit);
    }




    //cout<< fahrzeug*;
    // Überladen des Ausgabeoperators für Fahrzeug
    std::ostream& operator<<(std::ostream& o, const Fahrzeug& fzg){
		fzg.vAusgeben(o);
		return o;
	}





    // Überladen des Vergleichsoperators '<' für Fahrzeuge basierend auf der Gesamtstrecke
    // Im Hintergrund funktionieren wie fahrad1.operator<(anderesFahrzeug);
    bool Fahrzeug::operator<(const Fahrzeug& anderesFahrzeug) const{ //const, weil wir die Objekte nicht verändern wollen
    	return this->p_dGesamtStrecke < anderesFahrzeug.p_dGesamtStrecke;
    }





    // Getter für Gesamtstrecke
    // Um die Gesamtstrecke in den Tests abzufragen
    double Fahrzeug::getGesamtStrecke() const{
		return p_dGesamtStrecke;
	}




    double Fahrzeug::getTankInhalt() const{
		// Basisklasse Fahrzeug hat keinen Tankinhalt
		// Daher geben wir 0.0 zurück
		return 0.0;
	}




    void Fahrzeug::vNeueStrecke(Weg& weg){

    	p_pVerhalten = std::make_unique<Fahren>(weg);

    	p_pWeg = &weg;

    	p_dAbschnittStrecke = 0.0;
    }




    void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeit){

		p_pVerhalten = std::make_unique<Parken>(weg,dStartzeit);

		p_pWeg = &weg;

		p_dAbschnittStrecke = 0.0;
	}




    double Fahrzeug::getAbschnittStrecke() const{
    			return p_dAbschnittStrecke;
    }

    void Fahrzeug::vZeichnen(const Weg& rWeg) const{
		//Leere Implementierung in der Basisklasse
		//Abgeleitete Klassen können diese Methode überschreiben, um spezifische Zeichnungslogik bereitzustellen
	}




