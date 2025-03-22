#include "pch.h"
#include "CamiSolucio.h"

void CamiSolucio::cercaCoords(std::vector<XmlElement>& xmlElements)
{
	{
		int indexElements;
		int indexAtributs;
		bool trobat;
		bool trobat2;
		double lat, lon;

		for (int indexIds = 0; indexIds < m_ids.size(); indexIds++)
		{
			indexElements = 0;
			trobat = false;

			while (indexElements < xmlElements.size() && trobat != true) //trobar ID
			{
				indexAtributs = 0;
				trobat2 = false;

				if (xmlElements[indexElements].id_element == "node") //ID trobat (node)
				{
					while (indexAtributs < xmlElements[indexElements].atributs.size() && trobat2 != true) //trobar ID del node
					{
						if (xmlElements[indexElements].atributs[indexAtributs].first == "id") //ID del node trobat
						{
							trobat2 = true;
							if (xmlElements[indexElements].atributs[indexAtributs].second == m_ids[indexIds])
							{
								int cont = 0;
								indexAtributs = 0;

								while (indexAtributs < xmlElements[indexElements].atributs.size() && cont < 2)//trobar latitud i longitud
								{
									if (xmlElements[indexElements].atributs[indexAtributs].first == "lat")
									{
										cont++;
										lat = stod(xmlElements[indexElements].atributs[indexAtributs].second);
									}

									else if (xmlElements[indexElements].atributs[indexAtributs].first == "lon")
									{
										cont++;
										lon = stod(xmlElements[indexElements].atributs[indexAtributs].second);
									}

									indexAtributs++;
								}
								if (cont == 2)
								{
									afegirCoord(lat, lon);
									trobat = true;
								}
							}
						}
						indexAtributs++;
					}
				}
				indexElements++;
			}
		}
	}
}