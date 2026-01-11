#pragma once

#include "vertagt_aktion.h"
#include <list>
#include <memory>

//Bilgisayar Dünyasında (C++): Bir listenin üzerinde for döngüsü ile gezerken (iterator kullanarak),
//o listenin içinden bir elemanı silersen (erase) veya yeni eleman eklersen (push_back),
//o an kullandığın iterator bozulur (Iterator Invalidation). Program "Ben şu an neredeyim?" diye şaşırır ve Crash (Çökme) yaşanır.
//Simülasyonda arabaları tek tek ilerletiyoruz (vSimulieren). Bir araba yolun sonuna geldiğinde onu silmemiz gerekiyor.
//Döngü içindeyken silersek program patlar.
//Bunu önlemek için "ertelenmiş işlemler" (deferred actions) kullanıyoruz.
//Yani, silme veya ekleme işlemlerini hemen yapmıyoruz. Onları bir listeye kaydediyoruz.
//Döngü bittikten sonra bu listeyi işleyip tüm silme ve ekleme işlemlerini yapıyoruz.

namespace vertagt
{
	template <class T> class VAktion;
	template <class T> class VPushBack;
	template <class T> class VPushFront;
	template <class T> class VErase;
	// Vertagt Liste Sınıfı

	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default;
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			vAktualisieren();
			p_objekte.clear();  // Leere die Liste der Objekte
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end();
		}
		bool empty() const
		{
			return p_objekte.empty(); // Gibt zurück, ob die Liste leer ist
		}

		// Schreibfunktionen
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj)));
		}

		void push_front(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj)));
		}

		void erase(iterator it)
		{
			auto aktion = std::make_unique<VErase<T>>(p_objekte, it);
			// Aktive Eindelete-Aktion in der Aktionsliste speichern
			p_aktionen.push_back(std::move(aktion));
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			// Änderungen auf Objektliste übertragen
			for (auto& aktion : p_aktionen)
			{
					aktion->vAusfuehren();  // Aktion ausführen
			}
			// Aktionsliste löschen
			p_aktionen.clear();  // Leere die Aktionsliste nach der Ausführung
		}
	};
} // namespace vertagt
