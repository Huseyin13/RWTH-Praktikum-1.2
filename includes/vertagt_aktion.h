#pragma once

#include <list>

// DİKKAT: Namespace BURADA başlıyor
namespace vertagt
{
	// 1. VAktion Sınıfı
	template <class T>
	class VAktion
	{
	protected:
		std::list<T>& p_pListe;

	public:
		VAktion() = delete; // Default yasak
		VAktion(std::list<T>& ptListe) : p_pListe(ptListe){}
		virtual ~VAktion() = default;
		virtual void vAusfuehren() = 0;
	};

	// 2. VPushBack Sınıfı (NAMESPACE İÇİNDE OLMALI)
	template <class T>
	class VPushBack : public VAktion<T>
	{
	private:
		T p_objekt;
	public:
		VPushBack() = delete;
		VPushBack(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj))	{}
		virtual ~VPushBack() = default;
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.push_back(std::move(p_objekt));
		}
	};

	// 3. VPushFront Sınıfı (NAMESPACE İÇİNDE OLMALI)
    template <class T>
    class VPushFront : public VAktion<T>
    {
    private:
        T p_objekt;
    public:
        VPushFront() = delete;
        VPushFront(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj)) {}
        virtual ~VPushFront() = default;
        void vAusfuehren() override
        {
            VAktion<T>::p_pListe.push_front(std::move(p_objekt));
        }
    };

	// 4. VErase Sınıfı (NAMESPACE İÇİNDE OLMALI)
	template <class T>
	class VErase : public VAktion<T>
	{



	public:
		using iterator = typename std::list<T>::iterator;
		VErase() = delete;
		VErase(std::list<T>& liste, iterator it) : VAktion<T>(liste), p_it(it) {}
		virtual ~VErase() = default;
		void vAusfuehren() override
		{
			this->p_pListe.erase(p_it);
		}
	private:
			iterator p_it;
	};

} // <--- DİKKAT: Namespace BURADA bitiyor. Tüm sınıflar bu parantezin üstünde olmalı!
