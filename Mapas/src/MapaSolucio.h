#pragma once
#include "MapaBase.h"
#include "PuntDeInteresBase.h"
#include "CamiSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "ClasseCami.h"
#include "Util.h"
#include "GrafSolucio.h"
#include "BallTree.h"

class MapaSolucio : public MapaBase {
public:
	void getPdis(std::vector<PuntDeInteresBase*>& pdis)
	{
		for (int i = 0; i < m_pdis.size(); i++)
		{
			pdis.push_back(m_pdis[i]);
		}
	}

	void getCamins(std::vector<CamiBase*>& camins)
	{
		for (int i = 0; i < m_camins.size(); i++)
		{
			camins.push_back(m_camins[i]);

		}
	}

	void parsejaXmlElements(std::vector<XmlElement>& xmlElements)
	{
		m_pdis.clear();
		m_camins.clear();
		for (int i = 0; i < xmlElements.size(); i++)
		{
			if(xmlElements[i].id_element=="node") //node
			tipusPuntInteres(xmlElements[i]);

			else if ( (xmlElements[i].id_element == "way") && (ClasseCami::highway(xmlElements[i]))) //cami
			{

				CamiSolucio* cami = new CamiSolucio;

				for (int j = 0; j < xmlElements[i].fills.size(); j++)
				{
					if (xmlElements[i].fills[j].first == "nd")			 
					{						
						if (xmlElements[i].fills[j].second[0].first == "ref")
						{
							std::string id = xmlElements[i].fills[j].second[0].second;
							cami->afegirId(id);
						}
					}
				}
				cami->cercaCoords(xmlElements); //buscar coordenades
				if (cami->getCamiCoords().size() != 0) //comprovar nodes dels camins
					m_camins.push_back(cami);
			}
		}
	}

	bool cami(XmlElement element) //comprovar si l'element un cami
	{
		bool tag = false;
		bool name = false;

		for (int i = 0; i < element.fills.size(); i++)
		{
			if (element.fills[i].first == "tag")
			{
				tag = true;

				std::pair<std::string, std::string> valorTag = Util::kvDeTag(element.fills[i].second);
				if (valorTag.first == "highway" || valorTag.first == "public_transport" || valorTag.first == "access" || valorTag.first == "entrance")
					return true;

				if (valorTag.first == "name")
					name = true;
			}
		}

		if (tag == false)
			return true;
		if (name == false)
			return true;

		return false;
	}

	bool rest(XmlElement element)
	{
		for (int i = 0; i < element.fills.size(); i++)
		{
			if (element.fills[i].first == "tag")
			{
				std::pair<std::string, std::string> valorTag = Util::kvDeTag(element.fills[i].second);

				if ((valorTag.first == "amenity") && (valorTag.second == "restaurant"))
					return true;

			}
		}

		return false;
	}

	bool botiga(XmlElement element)
	{
		for (int i = 0; i < element.fills.size(); i++)
		{
			if (element.fills[i].first == "tag")
			{
				std::pair<std::string, std::string> valorTag = Util::kvDeTag(element.fills[i].second);

				if (valorTag.first == "shop")
					return true;
			}
		}

		return false;
	}

	void tipusPuntInteres(XmlElement element) //Punts d'interes
	{
		if(!cami(element)) //Assegurar que no son camins
		{
			//Variables comunes
			std::string name;
			std::string wheelchair;

			if (rest(element)) //Restaurant
			{
				std::string cuisine;
				std::string amenity;
				double lat, lon;
				int i = 0;
				bool trobat = false;

				while ((i < element.atributs.size()) && (!trobat))
				{
					if (element.atributs[i].first == "lat")
					{
						i++;
						if (element.atributs[i].first == "lon")
							trobat = true;
					}
					else
						i++;
				}

				if (trobat)
				{
					lat = stod(element.atributs[i - 1].second);
					lon = stod(element.atributs[i].second);
				}

				for (int i = 0; i < element.fills.size(); i++)
				{
					if (element.fills[i].first == "tag")
					{
						std::pair<std::string, std::string> tag = Util::kvDeTag(element.fills[i].second);
						if (tag.first == "amenity")
							amenity = tag.second;
						else if (tag.first == "cuisine")
							cuisine = tag.second;
						else if (tag.first == "wheelchair")
							wheelchair = tag.second;
						else
							name = tag.second;
					}
				}

				Coordinate cord{lat, lon};

				m_pdis.push_back(new PuntDeInteresRestaurantSolucio(cord,amenity,name,cuisine,wheelchair));
			}

			else if (botiga(element)) //Botiga
			{
				std::string shop;
				std::string hours;
				double lat, lon;				
				int i = 0;
				bool trobat = false;

				while ((i < element.atributs.size()) && (!trobat))
				{
					if (element.atributs[i].first == "lat")
					{
						i++;
						if (element.atributs[i].first == "lon")
							trobat = true;
					}
					else
						i++;
				}

				if (trobat)
				{
					lat = stod(element.atributs[i - 1].second);
					lon = stod(element.atributs[i].second);
				}

				for (int i = 0; i < element.fills.size(); i++)
				{
					if (element.fills[i].first == "tag")
					{
						std::pair<std::string, std::string> valorTag = Util::kvDeTag(element.fills[i].second);
						if (valorTag.first == "name")
							name = valorTag.second;
						if (valorTag.first == "shop")
							shop = valorTag.second;
						if (valorTag.first == "opening_hours")
							hours = valorTag.second;
						if (valorTag.first == "wheelchair")
							wheelchair = valorTag.second;
					}
				}
				Coordinate cord{lat, lon};
				m_pdis.push_back(new PuntDeInteresBotigaSolucio(cord,name,shop,hours,wheelchair));
			}

			else //cap tipus --> punt base
			{
				std::string nom;
				double lat, lon;
				bool trobat = false;
				int i = 0;

				while(i<element.fills.size()&&trobat!=true) //bucle buscar nom
				{
					if (element.fills[i].first == "tag")
					{
						std::pair<std::string, std::string> valorTag = Util::kvDeTag(element.fills[i].second);
						if (valorTag.first == "name")
						{
							nom = valorTag.second;
							trobat = true;
						}
					}
					i++;
				}

				//buscar coordenades --> reutilitzar variables
				trobat = false;
				i = 0;
				while ((i < element.atributs.size()) && (!trobat))
				{
					if (element.atributs[i].first == "lat")
					{
						i++;
						if (element.atributs[i].first == "lon")
							trobat = true;
					}
					else
						i++;
				}

				if (trobat)
				{
					lat = stod(element.atributs[i - 1].second);
					lon = stod(element.atributs[i].second);
				}

				Coordinate cord{lat, lon};
				m_pdis.push_back(new PuntDeInteresBase(cord,nom));
			}
			
		}	
	}

	CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) //comprovar coordenades?
	{
		//Coordenades dels punts:
		Coordinate CoordDesd = desde->getCoord();
		Coordinate CoordA = a->getCoord();
		BallTree arbre;

		std::vector<Coordinate> coordTotals;

		for (int i = 0; i < m_camins.size(); i++)
		{
			std::vector<Coordinate> coordCami = m_camins[i]->getCamiCoords();
			for (int j = 0; j < coordCami.size(); j++)
			{
				coordTotals.push_back(coordCami[j]); //afegir coordenades de tots els camins al arbre
			}
		}

		//es construeix l'arbre amb totes les coordenades de tots els camins del mapa
		arbre.construirArbre(coordTotals);
		Coordinate Q = { 0,0 };

		//trobar nodes-cami mes propers als punts d'interes d'origen i desti
		Coordinate properD = arbre.nodeMesProper(CoordDesd, Q, (&arbre));
		properD = Q;
		Coordinate properA = arbre.nodeMesProper(CoordA, Q, (&arbre));
		properA = Q;


		GrafSolucio graf(m_camins); //construir graf --> NO HI HA ARESTES

		//*Buscar camí més curt al graf implementant Dijstra
		stack<Coordinate> cami;
		graf.camiCurt(properD, properA, cami);

		CamiBase* caminet = new CamiSolucio; //cami mes curt a retornar

		while (!cami.empty())
		{
			caminet->afegirCoord(cami.top());
			cami.pop();
		}

		return caminet;
	}

private:
	std::vector<PuntDeInteresBase*> m_pdis;
	std::vector<CamiBase*> m_camins;
};