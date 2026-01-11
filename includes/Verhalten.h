#pragma once



class Weg; //Vorwärtsdeklaration der Weg-Klasse
class Fahrzeug; //Vorwärtsdeklaration der Fahrzeug-Klasse

class Verhalten {

public:

	Verhalten(Weg& weg);

	virtual ~Verhalten() = default;


	virtual double dStrecke(Fahrzeug& fzg, double dZeitIntervall) const = 0;

	Weg& getWeg() const {
		return p_pWeg;
	}




protected:

	Weg& p_pWeg;




private:




};
