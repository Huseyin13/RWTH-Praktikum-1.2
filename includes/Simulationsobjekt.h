#pragma once
#include <string>
#include <iostream>

extern double dGlobaleZeit; //Globale Simulationszeit

class Simulationsobjekt {

public:

	Simulationsobjekt(std::string name);

	virtual void vAusgeben(std::ostream& o) const;

	//Reine virtuelle Funktion zur Simulation des Objekts
	virtual void vSimulieren() = 0;

	//Vergleichsoperator basierend auf der eindeutigen ID
	bool operator==(const Simulationsobjekt& other) const;

	virtual ~Simulationsobjekt();


	//Verboten: Kopierkonstruktor
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	std::string getName() const {
		return p_sName;
	}

protected:

	std::string p_sName; //Simulationsobjekt name

	double p_dZeit; //Letzte Simulationszeit





private:

	const int p_iId; // Simulationsobjekt ID

	static int p_iMaxId; //Maximale Simulationsobjekt ID (Anzahl der erstellten Simulationsobjekte)


};
