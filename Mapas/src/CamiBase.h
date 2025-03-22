#pragma once

#include "Common.h"
#include <vector>

class CamiBase {
	public:
		virtual std::vector<Coordinate> getCamiCoords() = 0;
		virtual void afegirCoord(Coordinate cord) = 0;
		virtual void afegirCoord(double lat, double lon) = 0;
		virtual void afegirId(std::string id) = 0;
		virtual void cercaCoords(std::vector<XmlElement>& xmlElements) = 0;
};

