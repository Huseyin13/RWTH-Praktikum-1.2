#include "Weg.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include "Kreuzung.h"



#include <iomanip>
#include <limits>


Weg::Weg(std::string name, double laenge, Tempolimit limit,bool bUeberholverbot):

	Simulationsobjekt(name),
	p_dLaenge(laenge),
	p_eTempolimit(limit),
	p_bUeberholverbot(bUeberholverbot){

}
Weg::~Weg(){

}

void Weg::vSimulieren()
{
    // Simülasyon öncesi listeyi güncelle
    p_pFahrzeuge.vAktualisieren();

    auto it = p_pFahrzeuge.begin();
    while (it != p_pFahrzeuge.end())
    {
        try {
            // 1. Aracı Simüle Et
            (*it)->vSimulieren();

            // 2. Aracı Çiz
            (*it)->vZeichnen(*this);
        }
        catch (Streckenende& e) {
            // --- DURUM A: YOLUN SONU ---
            auto pZiel = getZielKreuzung();

            if (pZiel) {
                // Yeni yolu seç
                auto pNeuerWeg = pZiel->pZufaelligerWeg(*this);

                // Bilgilendirme
                std::cout << "----------------------------------------" << std::endl;
                std::cout << "ZEIT      : " << dGlobaleZeit << std::endl;
                std::cout << "KREUZUNG  : " << pZiel->getName() << " " << pZiel->getTankstelle() << std::endl;
                std::cout << "WECHSEL   : " << this->getName() << " -> " << pNeuerWeg->getName() << std::endl;
                std::cout << "FAHRZEUG  : " << (*it)->getName() << std::endl;

                // İşlemler
                pZiel->vTanken(*(*it));
                pNeuerWeg->vAnnahme(std::move(*it));

                // SİLME (Atama YOK!)
                // Ertelenmiş liste olduğu için anında silinmez, iterator bozulmaz.
                p_pFahrzeuge.erase(it);
            }
            else {
                // Kavşak yoksa
                e.vBearbeiten();
                p_pFahrzeuge.erase(it); // Atama YOK!
            }
        }
        catch (Losfahren& e) {
            // --- DURUM B: HAREKETE GEÇİŞ ---
            e.vBearbeiten();
            vAnnahme(std::move(*it));
            p_pFahrzeuge.erase(it); // Atama YOK!
        }
        catch (const std::exception& e) {
            std::cerr << "Hata: " << e.what() << std::endl;
        }

        // --- KRİTİK DÜZELTME ---
        // ++it işlemini BURAYA aldık.
        // Try içinde hata olsa da olmasa da, silme olsa da olmasa da
        // bir sonraki araca geçmemiz lazım.
        // Ertelenmiş listede silinen eleman hemen yok olmadığı için ++it güvenlidir.
        ++it;
    }

    // Simülasyon sonrası listeyi güncelle (Gerçek silme burada yapılır)
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAusgeben(std::ostream& o) const{
	Simulationsobjekt::vAusgeben(o);


	o << std::right;
	o << std::setw(20) << p_dLaenge;

	o << "    ( ";

	for(const auto& fahrzeug : p_pFahrzeuge){
		o << fahrzeug->getName() << " : "<< fahrzeug->getGesamtStrecke() << " km , "<< " "<<fahrzeug->getTankInhalt()<<" L; ";
	}
	o << ")";

}

double Weg::getTempolimit() const{

	switch(p_eTempolimit){

		case Tempolimit::Innerorts:
			return 50.0;

		case Tempolimit::Landstrasse:
			return 100.0;

		case Tempolimit::Autobahn:
			return std::numeric_limits<double>::infinity();

		default:
			return 0.0;
	}

}


double Weg::getLaenge() const{
	return p_dLaenge;
}

void Weg::vKopf(){
	std::cout << std::left;

	std::cout << std::setw(5)<<"ID";
	std::cout << " | ";

	std::cout <<std::setw(20)<<"Name";
	std::cout << " | ";

	std::cout <<std::setw(10)<<"Laenge";
	std::cout << " | ";

	std::cout <<"Fahrzeuge";
	std::cout << std::endl;

	std::cout << "-------------------------------------------------------------------------------------------------------------"<< std::endl;
	std::cout << std::endl;


}


	//Das Fahrzeug in die Liste aufnehmen.
    // Besitzübergabe durch std::move, da unique_ptr nicht kopiert werden kann.
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug){

	pFahrzeug->vNeueStrecke(*this); //Setzt den Weg für das Fahrzeug

	p_pFahrzeuge.push_back(std::move(pFahrzeug));

}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit){

	pFahrzeug->vNeueStrecke(*this, dStartzeit); //Setzt den Weg und die Startzeit für das Fahrzeug

	p_pFahrzeuge.push_back(std::move(pFahrzeug));

}

void Weg::vZeichnen() const{

	for(const auto& fahrzeug : p_pFahrzeuge){
		fahrzeug->vZeichnen(*this);
	}
}


std::shared_ptr<Kreuzung> Weg::getZielKreuzung() const {
    return p_pZielKreuzung.lock(); // weak_ptr'ı kullanmak için kilitliyoruz
}

std::shared_ptr<Weg> Weg::getRueckweg() const {
    return p_pRueckweg.lock();
}
void Weg::SetzeZielKreuzung(std::shared_ptr<Kreuzung> pZielKreuzung) {
    // shared_ptr, weak_ptr'a otomatik atanabilir.
    p_pZielKreuzung = pZielKreuzung;
}

void Weg::SetzeRueckweg(std::shared_ptr<Weg> pRueckweg) {
    // shared_ptr, weak_ptr'a otomatik atanabilir.
    p_pRueckweg = pRueckweg;
}



