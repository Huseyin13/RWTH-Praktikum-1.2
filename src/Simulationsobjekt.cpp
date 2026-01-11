#include "Simulationsobjekt.h"
#include <iomanip>




int Simulationsobjekt::p_iMaxId = 0;

Simulationsobjekt::Simulationsobjekt(std::string name):
		p_sName(name),
		p_dZeit(0.0),
		p_iId(++p_iMaxId)

{
	std::cout<<"Simulationsobjekt erstellt -> ID : " << p_iId <<", Name : "<<p_sName<<std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream& o) const {
	o << std::left;
	o << std::setw(8) << p_iId;
	o << std::setw(10) << p_sName;
	o << ":";
}

//Vergleichsoperator basierend auf der eindeutigen ID
bool Simulationsobjekt::operator==(const Simulationsobjekt& other) const {
    return this->p_iId == other.p_iId;
}

Simulationsobjekt::~Simulationsobjekt(){
	std::cout<<"Simulationsobjekt gelöscht -> ID : " << p_iId <<", Name : "<<p_sName<<std::endl;
}
