#include <iostream> // Für Ein- und Ausgabe, z.B. std::cout und std::cin
#include <memory>  // Für Smart Pointer wie std::unique_ptr und std::shared_ptr
#include <vector>  // Für die Verwendung von std::vector (dynamische Arrays)
#include <iomanip> // Für Formatierung von Ausgaben, z.B. std::setprecision, std::setw
#include <cmath> //Für mathematische Funktionen, z.B. std::fabs, std::pow
#include <algorithm> // Für Algorithmen wie std::max
#include <random> // Für Zufallszahlengenerierung

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"

using namespace vertagt;

//Simulation von Fahrzeugen erfordert, dass alle Fahrzeuge denselben Zeitverlauf kennen.
double dGlobaleZeit = 0.0;

//Kleine Konstante für Gleitkomma-Vergleiche
const double epsilon = 1e-6;

//Funktionsdeklarationen
void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();
void vAufgabe_7();
//void vAufgabe_AB1();
double eingabeKontrolle();

int main() {

	//Aufgabenblock 1 Tests
	//vAufgabe_1();
	//vAufgabe_1a();
    //vAufgabe_2();
	//vAufgabe_3();
	//vAufgabe_AB1(); //Etest funktion

	//Aufgabenblock 2 Tests
	//vAufgabe_4();
	//vAufgabe_5();
	//vAufgabe_6();
	//vAufgabe_6a();
	vAufgabe_7();



	return 0;
}


//Überprüfung der Benutzereingabe für positive double Werte
double eingabeKontrolle(){
						double wert;
						while(true){

							std::cin >> wert;

							if(std::cin.fail()){
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
								std::cout << "Ungültige Eingabe, bitte geben Sie eine positive Zahl ein"<< std::endl;
								}else{
									return wert;
							}
						}
					}



void vAufgabe_1(){

	std::cout<<"-----vAufgabe_1() gestartet-----"<<std::endl;

	Fahrzeug fzg1("Stack-Fahrzeug");//Erstellen eines Stack-Objekts
	//Es wird automatisch gelöscht, wenn der Block endet

	Fahrzeug* pFzg = new Fahrzeug("Heap-Fahrzeug");//Erstellen eines Heap-Objekts
	delete pFzg;


	// Erstellen eines unique_ptr mit make_unique
	auto uPtr1 = std::make_unique<Fahrzeug>("Unique-1");//auto bedeutet --> std::unique_ptr<Fahrzeug>, es wird automatisch erkannt

	auto uPtr2_move = std::make_unique<Fahrzeug>("Unique-2-Move");

	// Erstellen eines shared_ptr mit make_shared
	auto sPtr1 = std::make_shared<Fahrzeug>("Shared-1");
	//  noch einmal für den Test
	auto sPtr_move = std::make_shared<Fahrzeug>("Shared-2-Move");

	// Shared Pointer Kopiertest startet
	std::cout << "Shared Pointer Kopiertest" << std::endl;
	std::cout << "sPtr1 Referenzanzahl (vor dem Kopieren): " << sPtr1.use_count() << std::endl;

	auto sPtr2_kopieren = sPtr1; // Kopieren, use_count = 2

	auto sptr3_kopieren = sPtr1; //use_count = 3

	std::cout << "sPtr1 Referanzanzahl (nach dem Kopieren): " << sPtr1.use_count() << std::endl;
	std::cout << "sPtr2_kopieren Referanzanzahl: " << sPtr2_kopieren.use_count() << std::endl;

	// Unique Pointer Kopiervorgang (ERROR!)
	// Wenn wir den Kommentar in der folgenden Zeile entfernen, wird der Code nicht kompiliert.
    //auto uPtr_copy = uPtr1;
    // Weil unique_ptr kann nicht kopiert werden,wurde diese Zeile ein Error verursachen



	// Unique Pointer Transporttest
	std::cout << "Unique Pointer Transporttest" << std::endl;
	std::vector<std::unique_ptr<Fahrzeug>> vecUniquePtr; //Erstellen einen Vector, der unique_ptr zu Fahrzeugen speichert.

	// uPtr1 kann man nicht kopieren, weil unique_ptr ist.
	// Besitz muss verchoben werden -mit move()-
	//push_back fügt das Objekt am ende des Vektors ein
	vecUniquePtr.push_back(std::move(uPtr1));

	vecUniquePtr.push_back(std::move(uPtr2_move));

	//Kontroltest, ob uPtr1 null ist.
	if(!uPtr1){
		std::cout << "uPtr1 ist jetzt null (Besitz ist verschoben)." << std::endl;
	}

	//Vektör wird geleert werden mit clear().
	std::cout << "vecUniquePtr.clear() wird aufgerufen." << std::endl;

	vecUniquePtr.clear();//Der Vektor ist nun leer und size ist 0.

	std::cout << "vecUniquePtr.clear() wurde aufgerufen." << std::endl;


	// Hier werden wir sehen, dass die Fahrzeuge(Unique-1 und Unique-2-Move) gelöscht werden.


	// Shared Pointer Transporttest
	std::cout << "Shared Pointer Transporttest" << std::endl;

	// Erstellen einen Vector, der shared_ptr zu Fahrzeugen speichert.
	std::vector<std::shared_ptr<Fahrzeug>> vecSharedPtr;



	  std::cout << "sPtr1 Referenzanzahl (vor dem Kopieren): "
	              << sPtr1.use_count() << std::endl; // Ausgabe: 3




	  //sPtr1 wird in den Vektor kopiert und der Referenzzähler wird erhöht.
	  vecSharedPtr.push_back(sPtr1);



	  std::cout << "sPtr1 Referenzanzahl (nach dem Kopieren): "
	            << sPtr1.use_count() << std::endl; // Ausgabe: 4
    // Nun hat sPtr1 eine Referenzanzahl von 4 -----> sPtr1, sPtr2kopieren, sptr3_kopieren und der vecSharedPtr[0].



	// Jetzt TRANSPORTIEREN wir sPtr_move in den Vektor (mit move()).
	  std::cout << "sPtr_move Referenzanzahl (vor dem Transportieren): "
	            << sPtr_move.use_count() << std::endl; // Ausgabe: 1



	  //Transportieren mit move(), Referenzzähler wird NICHT erhöht.
	  vecSharedPtr.push_back(std::move(sPtr_move));



	  std::cout << "sPtr_move Referenzanzahl (nach dem Transportieren): "
	            << sPtr_move.use_count() << std::endl; // Ausgabe: 0
	      if (sPtr_move == nullptr) {
	          std::cout << "sPtr_move = nullptr (Besitz ist verschoben in den Vektor)" << std::endl;
	      }
	  //sPtr_move ist jetzt null, da der Besitz des Objekts durch den Vektor übernommen wurde.



	  std::cout << "Referenzanzahlen vor dem Ende von vAufgabe_1():" << std::endl;
	  std::cout << "sPtr1 Referenzanzahl : " << sPtr1.use_count() << std::endl;
	  std::cout << "sPtr_move Referenzanzahl : " << sPtr_move.use_count() << std::endl;

	  //Wenn wir schauen, welche sptr zuerst gelöscht werden, werden wir sehen, dass die Fahrzeuge "Shared-2-Move" zuerst gelöscht werden,
	  //weil sPtr_move der einzige Besitzer war und jetzt null ist.
	  std::cout << "vAufgabe_1() wird beendet..." << std::endl;
	  // Hier endet die Funktion vAufgabe_1.

	  /* Alle lokalen shared_ptr (sPtr1, sPtr_move, sPtr2_kopieren, sptr3_kopieren) werden zerstört.
	  Die Referenzanzahlen der Objekte im Heap werden entsprechend verringert.
	  Wenn die Referenzanzahl eines Objekts 0 erreicht, wird es automatisch gelöscht.*/





}
// vAufgabe_1a: Grundlegende Simulationsstruktur.
void vAufgabe_1a(){
	std::cout<<"-----vAufgabe_1a() gestartet-----"<<std::endl;

	std::vector<std::unique_ptr<Fahrzeug>> vektor_Fzg;

	double dSimulationsEnde = 5.0;
	double dZeitakt = 1.0;


	//Erstellen von 3 Fahrzeugen mit Benutzereingabe
	for(int i=0; i<3;i++){

		std::string sName;
		double dGeschwindigkeit;

		std::cout<<"Bitte geben Sie den Namen des Fahrzeugs "<<i+1<<": ";
		std::cin>>sName;

		std::cout<<"Bitte geben Sie die maximale Geschwindigkeit des Fahrzeugs "<<i+1<<": ";
		dGeschwindigkeit = eingabeKontrolle();



		auto pNeuesFzg = std::make_unique<Fahrzeug>(sName, dGeschwindigkeit);

		vektor_Fzg.push_back(std::move(pNeuesFzg));

	}

	//Hauptsimulationsschleife
	while(dGlobaleZeit<dSimulationsEnde){
		//Die Schleife läuft, bis die gesamte Simulationszeit erreicht ist.


		//Erhöht die globale Zeit in jedem Simulationsschritt.
		dGlobaleZeit += dZeitakt;


		std::cout<<"\nAktuelle Globale Zeit: "<<
				std::fixed<<std::setprecision(2)<<
				dGlobaleZeit<<std::endl;


		//Ausgabe der Kopfzeile für die Fahrzeugdaten.(ID, Name, Geschwindigkeit, Gesamtstrecke, etc.)
		Fahrzeug::vKopf();

		std::cout<<std::endl;

		for(auto& pFzg : vektor_Fzg){
			//Durchläuft alle Fahrzeuge im Vektor.

			//Simuliert die Bewegung des Fahrzeugs für das aktuelle Zeitintervall.
			pFzg->vSimulieren();//(*pfzg).vSimulieren(); = pFzg->vSimulieren(); Fahrzeugzustand aktualisieren

			std::cout << *pFzg; //Fahrzeuginformationen ausgeben dank der Überladung des Ausgabeoperators

			std::cout<<std::endl;
		}


	}

}

// vAufgabe_2: Testet Vererbung & Polymorphie.
void vAufgabe_2(){

	std::cout<<"-----vAufgabe_2() gestartet-----"<<std::endl;

	//Vektor zum Speichern von Fahrzeugen (PKW und Fahrrad)
	std::vector<std::unique_ptr<Fahrzeug>> vektor_Fzg;

	//Benutzereingabe für Anzahl der PKWs und Fahrräder
	int iAnzahlPKW, iAnzahlFahrrad; //Anzahl der PKWs und Fahrräder
	double dSimulationsEnde = 5.0; //Gesamtsimulationszeit in Stunden
	double dZeitakt = 1.0; //Zeitintervall für jeden Simulationsschritt in Stunden

	//Eingabe der Anzahl der PKWs und Fahrräder
	//Mit Eingabekontrolle werden nur positive Werte akzeptiert
	std::cout<<"Bitte geben Sie die Anzahl der PKWs ein: ";
	iAnzahlPKW = eingabeKontrolle(); //Eingabekontrolle für iAnzahlPKW
	std::cout<<"Bitte geben Sie die Anzahl der Fahrräder ein: ";
	iAnzahlFahrrad = eingabeKontrolle(); //Eingabekontrolle für iAnzahlFahrrad

	//PKW erzeugen und zum Vektor hinzufügen
	for(int i=0; i<iAnzahlPKW;i++){
		std::string sName;
		double dGeschwindigkeit;
		double dVerbrauch;
		double dTankvolumen;




		std::cout<<"Bitte geben Sie den Namen des PKWs "<<i+1<<": ";
		std::cin>>sName; //Eingabe des Namens des PKWs
		std::cout<<"Bitte geben Sie die maximale Geschwindigkeit des PKWs "<<i+1<<": ";
		dGeschwindigkeit = eingabeKontrolle(); //Eingabekontrolle für maximale Geschwindigkeit
		std::cout<<"Bitte geben Sie den Verbrauch des PKWs "<<i+1<<" (L/100km): ";
		dVerbrauch = eingabeKontrolle(); //Eingabekontrolle für Verbrauch
		std::cout<<"Bitte geben Sie das Tankvolumen des PKWs "<<i+1<<" (L): ";
		dTankvolumen = eingabeKontrolle(); //Eingabekontrolle für Tankvolumen

		//Erstellen eines neuen PKW-Objekts mit den eingegebenen Daten
		auto pNeuesFzg = std::make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, dTankvolumen);

		//Hinzufügen des neuen PKW zum Vektor
		vektor_Fzg.push_back(std::move(pNeuesFzg));

	}

	//Fahrrad erzeugen und zum Vektor hinzufügen
	for(int i=0; i<iAnzahlFahrrad;i++){
		std::string sName;
		double dGeschwindigkeit;
		std::cout<<"Bitte geben Sie den Namen des Fahrrads "<<i+1<<": ";
		std::cin>>sName;
		std::cout<<"Bitte geben Sie die maximale Geschwindigkeit des Fahrrads "<<i+1<<": ";
		dGeschwindigkeit = eingabeKontrolle(); //Eingabekontrolle für maximale Geschwindigkeit

		//Erstellen eines neuen Fahrrad-Objekts mit den eingegebenen Daten
		auto pNeuesFzg = std::make_unique<Fahrrad>(sName, dGeschwindigkeit);
		//Hinzufügen des neuen Fahrrads zum Vektor
		vektor_Fzg.push_back(std::move(pNeuesFzg));

	}

	//Flag, um Tankvorgang nur einmal auszuführen
	bool bGetankt = false;

	//Hauptsimulationsschleife
	while(dGlobaleZeit<dSimulationsEnde){

		//Erhöht die globale Zeit in jedem Simulationsschritt.
		dGlobaleZeit += dZeitakt;

		//PKW tanken nach 3 Stunden (nur einmal)
		if(fabs(dGlobaleZeit - 3.0)<epsilon && !bGetankt){
			//globaleZeit >= 3.0 und bGetankt ist false
			bGetankt = true;//Setzt das Flag, um weiteren Tankvorgang zu verhindern
			std::cout<<"--- Tankvorgang bei 3 Stunden ---"<<std::endl;
			for(auto& pFzg : vektor_Fzg){
				pFzg->dTanken(); //Nur PKWs werden tanken, Fahrräder ignorieren diese Methode
			}
		}


		std::cout<<"\nAktuelle Globale Zeit: "<<
				std::fixed<<std::setprecision(2)<<
				dGlobaleZeit<<std::endl;

		//Ausgabe der Kopfzeile für die Fahrzeugdaten.(ID, Name, Geschwindigkeit, Gesamtstrecke, etc.)
		Fahrzeug::vKopf();

		std::cout<<std::endl;

		//Simulieren und Ausgabe jedes Fahrzeugs im Vektor mit Rangen-basiertem for-loop
		for(auto& pFzg : vektor_Fzg){

			pFzg->vSimulieren();//(*pfzg).vSimulieren(); = pFzg->vSimulieren(); Fahrzeugzustand aktualisieren

			std::cout << *pFzg; //Fahrzeuginformationen ausgeben

			std::cout<<std::endl;
		}

	}
}

void vAufgabe_3(){
	std::cout<<"-----vAufgabe_3() gestartet-----"<<std::endl;

	//Vektor zum Speichern von Fahrzeugen (PKW und Fahrrad)
	std::vector<std::unique_ptr<Fahrzeug>> vektor_Fzg;

	//Fügen wir ein Fahrrad und ein PKW zum Vektor mit festen Werten hinzu
	vektor_Fzg.push_back(std::make_unique<Fahrrad>("Fahrrad-1", 25.0));

	vektor_Fzg.push_back(std::make_unique<PKW>("PKW-1", 150.0, 6.5, 60.0));

	//Simulationsprozess für 3 Stunden mit Zeitintervall von 1.5 Stunden
	    double dSimulationsEnde = 3.0;
	    double dZeitakt = 1.5;

	    while(dGlobaleZeit < dSimulationsEnde) {
	        dGlobaleZeit += dZeitakt;

	        std::cout<<"-------------------------------------------------"<<std::endl;
	        std::cout<<"\nAktuelle Globale Zeit: "<<
	        		std::fixed<<std::setprecision(2)<<
					dGlobaleZeit<<std::endl;

	        Fahrzeug::vKopf();

	        std::cout << std::endl;

	        for(auto& pFzg : vektor_Fzg) {
	            pFzg->vSimulieren();
	            std::cout << *pFzg << std::endl;
	        }
	    }

	    // Nach 3 Stunden Simulation, führen wir die Tests durch
	    std::cout << "\n--- 3 Stunden ist vorbei ---\n" << std::endl;
	    std::cout << " Die Tests werden gestartet...\n" << std::endl;


	    std::cout << "Test 1: Ausgabeoperator Test" << std::endl;
	    std::cout<<std::endl;

	    Fahrzeug::vKopf();
	    std::cout << std::endl;
	    for(auto& pFzg : vektor_Fzg) {

	    	std::cout << *pFzg << std::endl;
	    }

	    std::cout << "\n Test 2: Vergleichsoperator '<' Test" << std::endl;

	    // Referenzen auf das Fahrrad und den PKW im Vektor
	    Fahrzeug& Fahrrad_1 = *vektor_Fzg[0];
	    Fahrzeug& PKW_1 = *vektor_Fzg[1];

	    std::cout<< "Gesamtstrecke von dem Fahrrad: " << Fahrrad_1.getGesamtStrecke() << " km" << std::endl;
	    std::cout<< "Gesamtstrecke von dem PKW: " << PKW_1.getGesamtStrecke() << " km" << std::endl;


	    if(Fahrrad_1 < PKW_1) {
	        std::cout << "Der Vergleichsoperator '<' funktioniert korrekt: Fahrrad hat weniger Gesamtstrecke als PKW." << std::endl;
	    } else {
	        std::cout << "FEHLER: Der Vergleichsoperator '<' funktioniert NICHT korrekt!" << std::endl;
	    }


	    	// Test 3: Kopierkonstruktor Test
	    	// Wir versuchen, ein Fahrzeugobjekt zu kopieren.
	    	// Dies sollte fehlschlagen, da der Kopierkonstruktor gelöscht wurde.
	        // Der folgende Code ist absichtlich auskommentiert, da er einen Kompilierungsfehler verursachen sollte.
	        // "use of deleted function 'Fahrzeug::Fahrzeug(const Fahrzeug&)'"
	        //Fahrzeug f2 = Fahrrad_1;

	        std::cout << "\n SCHLUSS DER TESTS\n" << std::endl;

	        std::cout << "\n--- AUFGABENBLOCK 1 TAMAMLANDI ---" << std::endl;
}

void vAufgabe_4(){
	std::cout<<"-----vAufgabe_4() gestartet-----"<<std::endl;

	//Erstellen 2 Fahrzeug-Objekte
	auto p1 = std::make_unique<PKW>("Mercedes", 300.0, 7.5, 70.0);
	auto p2 = std::make_unique<Fahrrad>("BMX", 25.0);

	//Erstellen eines Weg-Objekts
	Weg weg1("Autobahn A1", 100.0, Tempolimit::Landstrasse);

	//Anfang der Simulation
	Weg::vKopf();
	std::cout<<std::endl;
	weg1.vAusgeben(std::cout);
	std::cout<<std::endl;
	//Fahrzeuge zum Weg hinzufügen
	std::cout<< "Fahrzeuge wurden zum Weg hinzugefügt." <<std::endl;
	std::cout<<std::endl;
	weg1.vAnnahme(std::move(p1));
	weg1.vAnnahme(std::move(p2));


	//Nach dem Hinzufügen der Fahrzeuge den Zustand des Wegs ausgeben
	Weg::vKopf();
	weg1.vAusgeben(std::cout);
	std::cout<<std::endl;

	//Simulation des Wegs
	std::cout<< "\n--- Simulation des Wegs startet ---\n"<<std::endl;
	weg1.vSimulieren();
	std::cout<<std::endl;

	//Zustand des Wegs nach der Simulation ausgeben
	Weg::vKopf();
	weg1.vAusgeben(std::cout);
	std::cout<<std::endl;


	//Simulationschritt
	std::cout<< "\n----------- NAECHSTER SIMULATIONSSCHRITT --------------\n"<<std::endl;

	for(int i=0; i<3; i++){
		dGlobaleZeit += 0.5; //Erhöhen der globalen Zeit um 1 Stunde
		std::cout<<"Aktuelle Globale Zeit: "<<
				std::fixed<<std::setprecision(2)<<
				dGlobaleZeit<<std::endl;

		weg1.vSimulieren(); //Simulation des Wegs

		Weg::vKopf();
		weg1.vAusgeben(std::cout);
		std::cout<<std::endl;

	}


}

void vAufgabe_5() {
	// Aufgabe 5: Parkverhalten implementieren und testen
	std::cout << "-----vAufgabe_5() gestartet-----" << std::endl;

	// Erstellen eines Weg-Objekts mit innerörtlichem Tempolimit
	Weg weg1("Stadtstraße", 100.0, Tempolimit::Innerorts);

	// Erstellen eines PKW-Objekts
	auto pPKW = std::make_unique<PKW>("Audi", 120.0, 6.0, 50.0);

	auto pPKW2 = std::make_unique<PKW>("BMW", 130.0, 7.0, 60.0);

	// Fahrzeuge zum Weg hinzufügen
	weg1.vAnnahme(std::move(pPKW));
	weg1.vAnnahme(std::move(pPKW2),2.0); // Parken für 2 Stunden

	for(int i = 0; i < 6; i++) {
		dGlobaleZeit += 0.5; // Erhöhen der globalen Zeit um 0.5 Stunden

		// Ausgabe der aktuellen globalen Zeit
		std::cout << "Aktuelle Globale Zeit: " <<
			std::fixed << std::setprecision(2) <<
			dGlobaleZeit << std::endl;


		weg1.vSimulieren(); // Simulation des Wegs

		// Ausgabe des Zustands des Wegs nach der Simulation
		Weg::vKopf();
		weg1.vAusgeben(std::cout);
		std::cout << std::endl;
	}
}

void vAufgabe_6(){
	std::cout << "-----vAufgabe_6() gestartet-----" << std::endl;

	if(bInitialisiereGrafik(800,500)){
		std::cout << "Grafik erfolgreich initialisiert." << std::endl;
	}else{
		std::cout << "Fehler bei der Initialisierung der Grafik." << std::endl;
		return;
	}

	int Koordinaten1[] = {100, 100, 700, 100};

	int Koordinaten2[] = {100, 300, 700, 300};

	Weg weg1("Strasse1", 500.0, Tempolimit::Innerorts);
	bZeichneStrasse("Strasse1", "b1", 500, 2, Koordinaten1);

	Weg weg2("Strasse2", 500.0, Tempolimit::Landstrasse);
	bZeichneStrasse("Strasse2", "b2", 500, 2, Koordinaten2);

	auto p1 = std::make_unique<PKW>("BMW", 60.0, 3.0,130.0);
	auto p2 = std::make_unique<PKW>("Mercedes", 100.0, 3.0,100.0);


	// Arabaları yollara yerleştirelim
	weg1.vAnnahme(std::move(p1));
	weg2.vAnnahme(std::move(p2),3.0); // 3 saat park et

	for (int i = 0; i < 50; i++) {
		weg1.vSimulieren();
		weg2.vSimulieren();

		// Sunucuya saati gönderelim
		vSetzeZeit(dGlobaleZeit);


		//Takip edebilmek için
		vSleep(100);

		dGlobaleZeit += 0.5;
	}

	vSleep(2000); // Sonuçları görebilmek için biraz bekleyelim
	vBeendeGrafik();

}

void vAufgabe_6a(){
	std::cout << "-----vAufgabe_6a() gestartet-----" << std::endl;

	VListe<int> testList;

	static std::mt19937 device(0); // Sabit tohumlu rastgele sayı üreteci
	std::uniform_int_distribution<int> dist(1, 10); // 1 ile 100 arasında uniform dağılım

	for(int i = 0; i < 10; i++) {
		int randomValue = dist(device);
		testList.push_back(randomValue);
		std::cout << "Hinzufügen: " << randomValue << std::endl;
	}

	std::cout<< "Pushback ist fertig aber noch nicht aktualisiert." << std::endl;
	std::cout << "Ist die Liste leer? " << (testList.empty() ? "Ja" : "Nein") << std::endl;

	std::cout << "Aktualisiere die Liste..." << std::endl;
	testList.vAktualisieren();
	std::cout << "Liste nach der Aktualisierung:" << std::endl;
	for(auto& value : testList) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	//Entfernung Elemente größer als 5 test
	std::cout << "Entfernung Elemente größer als 5..." << std::endl;
	for(auto it = testList.begin(); it != testList.end(); it++ ) {
		if(*it > 5) {
			testList.erase(it);
		}
	}

	//Kontrollausgabe nach Entfernung
	//Wir haben noch nicht aktualisiert
	//Die Elemente sollten noch da sein
	std::cout << "Liste nach der Entfernung (vor Aktualisierung):" << std::endl;
	for(auto& value : testList) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	std::cout << "Aktualisiere die Liste nach der Entfernung..." << std::endl;
	testList.vAktualisieren();
	std::cout << "Liste nach der Aktualisierung:" << std::endl;
	for(auto& value : testList) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	//Test zum hinzufügen am Anfang und am Ende der Liste
	std::cout << "Füge 999 am Anfang und 111 am Ende der Liste hinzu." << std::endl;
	testList.push_front(999);
	testList.push_back(111);

	testList.vAktualisieren();
	std::cout << "Letzte Aktualisierung..." << std::endl;

	for(auto& value : testList) {
		std::cout << value << " ";
	}
	std::cout << std::endl;
	std::cout << "Ende von vAufgabe_6a()" << std::endl;
}

void vAufgabe_7(){
	std::cout << "-----vAufgabe_7() gestartet-----" << std::endl;
	// 1. KAVŞAKLARI OLUŞTUR
	    // Kr2 benzin istasyonuna sahip (1000 litre), diğerleri 0.
	    auto pKr1 = std::make_shared<Kreuzung>("Kr1", 0);
	    auto pKr2 = std::make_shared<Kreuzung>("Kr2", 1000);
	    auto pKr3 = std::make_shared<Kreuzung>("Kr3", 0);
	    auto pKr4 = std::make_shared<Kreuzung>("Kr4", 0);

	    // 2. KAVŞAKLARI BAĞLA (Yolları Oluştur)
	    // Parametreler: (GidişAdı, DönüşAdı, Uzunluk, Başlangıç, Bitiş, HızLimiti, SollamaYasağı)

	    // Strasse 1: Kr1 <-> Kr2
	    Kreuzung::vVerbinden("W12", "W21", 40.0, pKr1, pKr2, Tempolimit::Innerorts, true);

	    // Strasse 2: Kr2 <-> Kr3 (Sağdan giden uzun yol)
	    Kreuzung::vVerbinden("W23a", "W32a", 115.0, pKr2, pKr3, Tempolimit::Autobahn, false);

	    // Strasse 3: Kr2 <-> Kr3 (Düz inen kısa yol)
	    Kreuzung::vVerbinden("W23b", "W32b", 40.0, pKr2, pKr3, Tempolimit::Innerorts, true);

	    // Strasse 4: Kr2 <-> Kr4 (Yatay yol)
	    Kreuzung::vVerbinden("W24", "W42", 55.0, pKr2, pKr4, Tempolimit::Innerorts, true);

	    // Strasse 5: Kr3 <-> Kr4 (Aşağıdaki yatay yol)
	    Kreuzung::vVerbinden("W34", "W43", 85.0, pKr3, pKr4, Tempolimit::Autobahn, false);

	    // Strasse 6: Kr4 <-> Kr4 (Kendi etrafında dönen döngü - Loop)
	    // Başlangıç ve Bitiş aynı kavşak!
	    Kreuzung::vVerbinden("W44a", "W44b", 130.0, pKr4, pKr4, Tempolimit::Landstrasse, false);


	    // 3. ARAÇLARI OLUŞTUR VE YERLEŞTİR
	    // İlk araçları Kr1'e koyalım
	    auto pBMW = std::make_unique<PKW>("BMW", 100, 7.5, 50); // Hız, tüketim, depo
	    auto pAudi = std::make_unique<PKW>("Audi", 120, 8.0, 55);
	    auto pGol = std::make_unique<PKW>("Gol", 90, 6.0, 40);

	    // Araçları Kr1'e teslim et (vAnnahme).
	    // Dikkat: vAnnahme bunları rastgele bir yola sokacak.
	    pKr1->vAnnahme(std::move(pBMW), 0.5); // 0.5 saat sonra başlasın
	    pKr1->vAnnahme(std::move(pAudi), 1.0);
	    pKr1->vAnnahme(std::move(pGol), 1.5);


	    // 4. SİMÜLASYON DÖNGÜSÜ
	    dGlobaleZeit = 0.0;

	    // Grafiği Başlat (Eğer SimuClient kullanıyorsan)
	    bInitialisiereGrafik(1000, 700);
	    		int pStrasse1[] = { 680, 40, 680, 300 };

	        // Strasse 2 Koordinatları (Kr2 -> Kr3, Sağdan kavisli)
	        // Şekildeki ara noktalar: (850, 300), (970, 390), (970, 500), (850, 570)
	        int pStrasse2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };

	        // Strasse 3 Koordinatları (Kr2 -> Kr3, Düz aşağı)
	        int pStrasse3[] = { 680, 300, 680, 570 };

	        // Strasse 4 Koordinatları (Kr2 -> Kr4, Yatay sola)
	        int pStrasse4[] = { 680, 300, 320, 300 };

	        // Strasse 5 Koordinatları (Kr3 -> Kr4, Alttan kavisli)
	        // Şekildeki ara noktalar: (500, 570), (350, 510), (320, 420)
	        int pStrasse5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };

	        // Strasse 6 Koordinatları (Kr4 -> Kr4, Loop/Döngü)
	        // Şekildeki ara noktalar: (170, 300), (70, 250), (80, 90), (200, 60), (320, 150)
	        int pStrasse6[] = { 320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300 };

	        // Yolları çiz
	        bZeichneStrasse("W12", "W21", 40, 2, pStrasse1);
	        bZeichneStrasse("W23a", "W32a", 115, 6, pStrasse2); // 6 nokta var
	        bZeichneStrasse("W23b", "W32b", 40, 2, pStrasse3);
	        bZeichneStrasse("W24", "W42", 55, 2, pStrasse4);
	        bZeichneStrasse("W34", "W43", 85, 5, pStrasse5);    // 5 nokta var
	        bZeichneStrasse("W44a", "W44b", 130, 7, pStrasse6); // 7 nokta var
	    for (int i = 0; i < 200; i++) // 200 adım simüle edelim
	    {
	        vSetzeZeit(dGlobaleZeit);

	        // A) Kavşakları Çiz (Koordinatlar PDF'ten alındı)
	        bZeichneKreuzung(680, 40);  // Kr1
	        bZeichneKreuzung(680, 300); // Kr2
	        bZeichneKreuzung(680, 570); // Kr3
	        bZeichneKreuzung(320, 300); // Kr4



	        // B) Kavşakları Simüle Et (İçlerindeki yolları ve araçları ilerletir)
	        pKr1->vSimulieren();
	        pKr2->vSimulieren();
	        pKr3->vSimulieren();
	        pKr4->vSimulieren();

	        vSleep(100);
	        dGlobaleZeit += 0.1; // Zamanı ilerlet
	    }

	    // Grafik penceresini beklet (kapanmaması için)
	    vBeendeGrafik();


}



/*void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    std::vector<int> ausgabe{15};
    double dTakt = 0.3;

    std::vector<std::unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(std::make_unique <PKW>("Audi", 231, 11.4));
    vecFahrzeuge.push_back(std::make_unique <Fahrrad>("BMX", 19.8));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << std::endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}*/




