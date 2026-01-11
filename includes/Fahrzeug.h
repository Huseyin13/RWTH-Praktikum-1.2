#pragma once
#include <string>
#include <limits>
#include <memory>
#include "Simulationsobjekt.h"
#include "Verhalten.h"

class Weg; //Vorwärtsdeklaration der Weg-Klasse

class Fahrzeug : public Simulationsobjekt {



	protected:


		//Zeiger auf das aktuelle Wegobjekt, auf dem sich das Fahrzeug befindet
		std::unique_ptr<Verhalten> p_pVerhalten;

		Weg* p_pWeg = nullptr; //Zeiger auf den aktuellen Weg

		double p_dVerbrauch; // Liter pro 100 km, Kraftstoffverbrauch des PKWs
		double p_dTankVolumen; // Maximales Tankvolumen in Litern
		double p_dTankInhalt; // Aktueller Tankinhalt in Litern
		double p_dMaxGeschwindigkeit; //Maximale Geschwindigkeit

		double p_dGesamtStrecke; //Gesamt zurückgelegte Strecke

		double p_dGesamtZeit; //Gesamt gefahrene Zeit

		double p_dAbschnittStrecke; //Zurückgelegte Strecke auf dem aktuellen Abschnitt

		double p_dGesamtVerbrauch = 0.0; // Gesamtverbrauch in Litern



	public:


		Fahrzeug(std::string name, double maxGeschwindigkeit = 0.0);//constructor mit name und maxGeschwindigkeit parameter

		//Warum virtual? Damit der Destruktor der abgeleiteten Klassen
		virtual ~Fahrzeug(); //destructor


		// Statische Methode zur Ausgabe der Kopfzeile für Fahrzeugdaten
		//Warum static? Weil die Tabellenüberschrift nicht zu einem konkreten Objekt gehört, sondern zur Klasse selbst.
		static void vKopf(); //Kopfzeile ausgeben


		// Ausgabe der Fahrzeugdaten auf einen Stream
		// Virtuelle Methode, damit abgeleitete Klassen sie überschreiben können
		// und ihre spezifischen Daten hinzufügen können
		//ostream als Referenz übergeben, damit wir auf verschiedene Ausgabeströme schreiben können
		virtual void vAusgeben(std::ostream& o) const;

		// Simulation des Fahrzeugs für das aktuelle Zeitintervall
		virtual void vSimulieren();


		/* Virtuelle Tankfunktion für alle Fahrzeuge.
		 Defaultparameter: unendlich -> bedeutet "so viel wie möglich tanken".
		 Basisklasse: macht nichts und gibt 0 zurück.
		 Abgeleitete Klassen wie PKW überschreiben diese Funktion.*/
		virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());


		// Berechnung der aktuellen Geschwindigkeit des Fahrzeugs
		virtual double dGeschwindigkeit() const;

		// Überladen des Vergleichsoperators '<' für Fahrzeuge basierend auf der Gesamtstrecke
		bool operator<(const Fahrzeug& anderesFahrzeug) const;



		  /* Wir verbieten den Kopierkonstruktor.
		     WARUM? Jedes Fahrzeug MUSS eine einzigartige 'p_iId' haben,
		     die es nur vom 'p_iMaxId'-Zähler bekommt.
		     Ein Kopiervorgang (z.B. Fahrzeug f2 = f1) würde die ID
		     duplizieren und unser System brechen.(compile time errror)*/
		Fahrzeug(const Fahrzeug&) = delete;

		// Getter für die Gesamtstrecke
		double getGesamtStrecke() const;

		virtual double getTankInhalt() const; //Standardmäßig 0.0 für Fahrzeuge ohne Tank

		void vNeueStrecke(Weg& weg); //Neue Strecke setzen basierend auf dem Weg

		void vNeueStrecke(Weg& weg, double p_Startzeit); //Neue Strecke setzen basierend auf dem Weg

		double getAbschnittStrecke() const ;

		virtual void vZeichnen(const Weg& rWeg) const; // Zeichnen-Methode für Fahrzeug













};
// Überladen des Ausgabeoperators für Fahrzeug
// Warum außerhalb der Klasse? Weil es eine freie Funktion ist,
// die nicht zu einem bestimmten Fahrzeugobjekt gehört.
// ostrem ist nicht meine Klasse gehört, deshalb außerhalb der Klasse definiert
std::ostream& operator<<(std::ostream& o, const Fahrzeug& x);
