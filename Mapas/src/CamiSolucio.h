#pragma once
#include "CamiBase.h"
#include "ClasseCami.h"


class CamiSolucio : public CamiBase
{
public:
	CamiSolucio() {};
	~CamiSolucio() {};
	std::vector<Coordinate> getCamiCoords() { return m_punts; }

	void afegirCoord(Coordinate cord) { m_punts.push_back(cord); }
	void afegirCoord(double lat, double lon) { m_punts.push_back({lat, lon}); }
	void afegirId(std::string id) { m_ids.push_back(id); }
	void cercaCoords(std::vector<XmlElement>& xmlElements);
private:
	std::vector<Coordinate> m_punts;
	std::vector<std::string> m_ids;
};