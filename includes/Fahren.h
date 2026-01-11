#pragma once
#include "Verhalten.h"



class Fahren : public Verhalten {


public:

		Fahren(Weg& weg);
	double dStrecke(Fahrzeug& fzg, double dZeitIntervall) const override;

};
