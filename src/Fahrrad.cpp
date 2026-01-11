#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h" //bZeichneFahrrad Funktion
#include <cmath> //pow fonksiyonu
#include <algorithm>//std::max fonksiyonu

// Konstruktor der Fahrrad-Klasse
// Initialisierungsliste wird verwendet, um die Basisklassenmember direkt zu initialisieren
// (p_sName, p_iId usw.) und effizient zu arbeiten (keine unnötigen Zuweisungen)
Fahrrad::Fahrrad(std::string name, double maxGeschwindigkeit):
		Fahrzeug(name, maxGeschwindigkeit){

}

// Überschreiben der virtuellen Ausgeben-Funktion
// Ruft die Basisklassenmethode auf, um die gemeinsamen Fahrzeuginformationen auszugeben
//Es gibt keine zusätzlichen Fahrrad-spezifischen Informationen aus.
void Fahrrad::vAusgeben(std::ostream& o) const{
	Fahrzeug::vAusgeben(o);
}

// Überschreiben der virtuellen Simulieren-Funktion
//Es gibt keine speziellen Simulationsregeln für Fahrräder,
// daher wird einfach die Basisklassenmethode aufgerufen.
void Fahrrad::vSimulieren(){
	Fahrzeug::vSimulieren();
}

// Überschreiben der aktuellen Geschwindigkeitsberechnung
// Die Geschwindigkeit des Fahrrads wird basierend auf der zurückgelegten Gesamtstrecke angepasst.
// Für je 20 km Strecke wird die Geschwindigkeit um 10% reduziert, jedoch nicht unter 12 km/h.
double Fahrrad::dGeschwindigkeit() const{

	// Berechnung der Reduktion basierend auf der Gesamtstrecke
	//Typecast zu int, um die Anzahl der 20 km Abschnitte zu erhalten
	// z.B. 45 km -> 2 (2*20=40 km, Rest 5 km)
	double dReduktion = (int)(p_dGesamtStrecke/20.0);

	// Berechnung des Reduktionsfaktors
	// Für jede 20 km Strecke wird die Geschwindigkeit um 10% reduziert
	// dFactor = 0.9^dReduktion
	//Funktion pow aus cmath Bibliothek hilft hier
	double dFactor = pow(0.9, dReduktion);//0.9*0.9=0*81

	// Berechnung der aktuellen Geschwindigkeit
	// Maximale Geschwindigkeit wird mit dem Reduktionsfaktor multipliziert
	double dAktuelGeschw = p_dMaxGeschwindigkeit * dFactor;

	// Sicherstellen, dass die Geschwindigkeit nicht unter 12 km/h fällt
	// std::max stellt den größeren Wert von 12.0 und dAktuelGeschw zurück
	// Somit wird garantiert, dass die Geschwindigkeit mindestens 12 km/h beträgt
	return std::max(12.0, dAktuelGeschw);
}

// Zeichnen-Methode für Fahrrad
void Fahrrad::vZeichnen(const Weg& rWeg) const{
	double dWegLaenge = rWeg.getLaenge();
	    double dRelPosition = p_dAbschnittStrecke / dWegLaenge;

	    bZeichneFahrrad(p_sName, rWeg.getName(), dRelPosition, dGeschwindigkeit());
}




