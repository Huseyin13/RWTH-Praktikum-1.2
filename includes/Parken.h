#pragma once
#include "Verhalten.h"
#include <cmath> //std::abs

class Parken : public Verhalten {



public:

	double p_dStartzeit; // Zeitpunkt, zu dem das Fahrzeug losfährt

	Parken(Weg& weg, double startzeit);

	virtual ~Parken() = default;

	double dStrecke(Fahrzeug& fzg, double dZeitIntervall) const override;



protected:





private:


};
