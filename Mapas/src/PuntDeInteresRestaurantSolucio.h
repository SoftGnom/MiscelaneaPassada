#pragma once
#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() {
		this->m_cuisine = "";
		this->m_amenity = "";
		this->m_wheelchair = "";
	}

	PuntDeInteresRestaurantSolucio(Coordinate coord,std::string amenity, std::string name, std::string cuisine, std::string wheelchair)
	: PuntDeInteresBase(coord, name), m_cuisine(cuisine), m_wheelchair(wheelchair), m_amenity(amenity) {}

	std::string getName()
	{
		return PuntDeInteresBase::getName();
	}

	unsigned int getColor()
	{
		if ((m_cuisine == "pizza") && (m_wheelchair == "yes"))
			return 0x03FCBA;

		else if (m_cuisine == "chinese")
			return 0xA6D9F7;

		else if (m_wheelchair == "yes")
			return 0x251351;

		else
			return PuntDeInteresBase::getColor();
		
	}

private:
	std::string m_cuisine;
	std::string m_amenity;
	std::string m_wheelchair;
};
