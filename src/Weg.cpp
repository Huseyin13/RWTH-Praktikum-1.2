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

void Weg::vSimulieren(){

	p_pFahrzeuge.vAktualisieren(); //Aktualisiere die Liste der Fahrzeuge vor der Simulation

	for(auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it){
		try {
			// *it bize unique_ptr verir.
			// (*it)->vSimulieren() diyerek aracın fonksiyonunu çağırıyoruz.
			(*it)->vSimulieren();

			//Zeichnen des Fahrzeugs auf dem Weg
			(*it)->vZeichnen(*this);

		}

		// 2. Hata Yakalama: Eğer araba "throw" yaparsa buraya düşer
		catch (Streckenende& e) {
			auto pZiel = getZielKreuzung();

		if(pZiel){
			// --- DURUM A: KAVŞAK VAR (YOLCULUK DEVAM EDİYOR) ---

			// Yeni yolu seç
			auto pNeuerWeg = pZiel->pZufaelligerWeg(*this);

			// PDF'teki tabloyu yazdır (e.vBearbeiten YOK!)
			std::cout << "ZEIT      : " << dGlobaleZeit << std::endl;
		    std::cout << "KREUZUNG  : " << pZiel->getName() << " " << pZiel->getTankstelle() << std::endl;
	        std::cout << "WECHSEL   : " << this->getName() << " -> " << pNeuerWeg->getName() << std::endl;
	        std::cout << "FAHRZEUG  : " << (*it)->getName() << std::endl;

	        //Benzin al
	        pZiel->vTanken(*(*it));
			// Aracı yeni yola al
	        pNeuerWeg->vAnnahme(std::move(*it));

		    // Bizim listeden sil (artık kavşağın sorumluluğunda)
			p_pFahrzeuge.erase(it);
		}
		else{
			e.vBearbeiten();
			// 3. Hata İşleme: Hatanın "vBearbeiten" metodunu çağır
			p_pFahrzeuge.erase(it); //Fahrzeug vom Weg entfernen
		}
		}
		catch (Losfahren& e){
		            // SENARYO 1: Araç park halindeydi, harekete geçti.
		            // PDF der ki: Harekete geçen araç listede yeniden konumlandırılmalı.

					e.vBearbeiten();
		            // 1. Aracı listeden "Çalıyoruz" (Move ile sahipliği alıp tekrar yola ekle)
		            // vAnnahme fonksiyonu "push_back" yapar, yani aracı en sona (hareketliler arasına) atar.
		            vAnnahme(std::move(*it));

		            // 2. Eski boş kalan kabuğu listeden silme emri veriyoruz.
		            p_pFahrzeuge.erase(it);

		            // Bilgi mesajı (İstersen)
		            // std::cout << "Parktan Cikti: " << (*it)->getName() << std::endl;
		 }
		catch(const std::exception& e){
			//Diğer tüm standart istisnalar için genel hata işleme
			std::cout << "Fehler bei der Simulation von Fahrzeug: " << e.what() << std::endl;
		}
	}
	p_pFahrzeuge.vAktualisieren(); //Aktualisiere die Liste der Fahrzeuge nach der Simulation


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



