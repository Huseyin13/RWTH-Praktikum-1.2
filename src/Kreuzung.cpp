#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Weg.h"

#include <iostream>
#include <cstdlib>



Kreuzung::Kreuzung(std::string name, double dTankstelle)
	: Simulationsobjekt(name), p_dTankstelle(dTankstelle) {
}

void Kreuzung::vVerbinden(std::string sWegname1,
		std::string sWegname2,
		double dLaenge,
		std::shared_ptr<Kreuzung> pstartKreuzung, std::shared_ptr<Kreuzung> pzielKreuzung,
		Tempolimit eTempolimit, bool bUeberholverbot) {

auto hinWeg = std::make_shared<Weg>(sWegname1, dLaenge, eTempolimit, bUeberholverbot);
auto rueckWeg = std::make_shared<Weg>(sWegname2, dLaenge, eTempolimit, bUeberholverbot);

hinWeg->SetzeRueckweg(rueckWeg);
rueckWeg->SetzeRueckweg(hinWeg);

hinWeg->SetzeZielKreuzung(pzielKreuzung);
rueckWeg->SetzeZielKreuzung(pstartKreuzung);




pstartKreuzung->p_pWege.push_back(hinWeg);
pzielKreuzung->p_pWege.push_back(rueckWeg);

}

void Kreuzung::vTanken(Fahrzeug& fahrzeug)
{
    if (p_dTankstelle > 0)
    {
        // Depodaki tüm yakıtı teklif et, araç ihtiyacı kadarını alır.
        // dTanken fonksiyonu, ne kadar aldığını geri döner.
        double dGetankteMenge = fahrzeug.dTanken(std::numeric_limits<double>::infinity());

        // İstasyonun rezervini güncelle
        p_dTankstelle -= dGetankteMenge;

        if (p_dTankstelle < 0) p_dTankstelle = 0; // Negatife düşmesin
    }
}

// --- vAnnahme: Aracı Kabul Etme ---
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit)
{
    // 1. Gelen araca önce benzin teklif et
    vTanken(*pFahrzeug);

    // 2. Aracı listedeki İLK yola koy (Şimdilik PDF böyle istiyor)
    // p_pWege.front() listenin başındaki yolu verir.
    p_pWege.front()->vAnnahme(std::move(pFahrzeug), dStartzeit);
}

// --- vSimulieren: Yolları Simüle Etme ---
void Kreuzung::vSimulieren()
{
    // Kavşağa bağlı tüm yolları tek tek simüle et
    for (auto& weg : p_pWege)
    {
        weg->vSimulieren();
    }
}

// --- getWeg: İsimle Yol Bulma (Getter) ---
std::shared_ptr<Weg> Kreuzung::getWeg(std::string sName) const
{
    for (auto& weg : p_pWege)
    {
        if (weg->getName() == sName)
        {
            return weg;
        }
    }
    return nullptr; // Bulunamazsa
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& ankommenderWeg){
	if(p_pWege.size() == 1){
		//Sadece bir yol varsa, o yolu döndür
		return p_pWege.front();
	}

	auto pVerbotenerWeg = ankommenderWeg.getRueckweg();

	while(true){
		//Rastgele bir indeks seç
		int zufallsIndex = rand() % p_pWege.size();

		auto it = p_pWege.begin();
		std::advance(it, zufallsIndex);

		//Eğer seçilen yol yasaklı yol değilse, o yolu döndür
		if(*it != pVerbotenerWeg){
			return *it;
		}
	}

}
