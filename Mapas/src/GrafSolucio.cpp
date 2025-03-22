#include "pch.h"
#include "GrafSolucio.h"

bool operator==(Coordinate c1, Coordinate c2) //operador d'igualtat --> comparar coordenades
{
	return (c1.lat == c2.lat && c1.lon == c2.lon);
}

GrafSolucio::GrafSolucio(const std::vector<CamiBase*>& camins)
{
	m_numArestes = 0;
	m_numNodes = 0;

	for (int i = 0; i < camins.size(); i++) //extraure vectors de coordenades dels camins
	{
		std::vector<Coordinate> coordenades = camins[i]->getCamiCoords();
		afegirNode(coordenades[0]); //primera coordenada

		for (int j = 1; j < coordenades.size(); j++) //crear graf amb les coordenades dels camins
		{
			bool repetit = false;
			int k = 0;
			while (k < m_nodes.size() && !repetit) //comprovar coordenades repetides (no poden coincidir)
			{
				if (coordenades[j] == m_nodes[k]) //canvi coordenades per m_nodes
					repetit = true;
				else
					k++;
			}

			if (!repetit)
				afegirNode(coordenades[j]);

			afegirAresta(coordenades[j - 1], coordenades[j]);
		}
	}
}

void GrafSolucio::afegirNode(const Coordinate& node)
{
	bool repe = false;
	for (int i = 0; i < m_numNodes; i++)
	{
		if (node == m_nodes[i])
		{
			repe = true;
			break;
		}

	}

	if (!repe)
	{
		m_nodes.push_back(node);
		m_numNodes++;
		m_graf.resize(m_numNodes);
	}

}

void GrafSolucio::afegirAresta(Coordinate node1, Coordinate node2)
{
	//comprovar existencia dels nodes
	bool trobat1 = false;
	bool trobat2 = false;
	int i = 0;
	int j1 = 0; //index node1
	int j2 = 0; //index node2

	while ( (!trobat1 || !trobat2) && i < m_nodes.size())
	{
		if (node1 == m_nodes[i])
		{
			trobat1 = true;
			j1 = i;
		}

		if (node2 == m_nodes[i])
		{
			trobat2 = true;
			j2 = i;
		}
		i++;
	}

	if (trobat1 && trobat2) //els nodes existeixen
	{
		double distancia = Util::DistanciaHaversine(node1, node2);
		m_graf[j1].push_back({ j2, distancia }); //al node1 afegir aresta amb el node2
		m_graf[j2].push_back({j1, distancia}); //al node2 afegir aresta amb node1
		m_numArestes++;
	}
}

int GrafSolucio::indexCurt(vector<double>& distancies, vector<bool>& visitats)
{
	double min = 1.12123515e+25; //nombre còmicament gran
	int index = -1;
	for (int i = 0; i < m_numNodes; i++)
	{
		if (!visitats[i] && distancies[i] < min)
		{
			min = distancies[i];
			index = i;
		}
	}
	return index;
}

							//indexos		//distanciaHaversine		//vector de indexos recorreguts
void GrafSolucio::Dijkstra(int n1, int n2, vector<double>& distancies, vector<int>& recorreguts)
{
	double DISTMAX = 1.12123515e+25;
	distancies.resize(m_numNodes, DISTMAX);

	vector<bool> visitats;
	visitats.resize(m_numNodes, false);

	recorreguts.resize(m_numNodes, -1);
	distancies[n1] = 0; //la distancia del node amb si mateix es 0
	recorreguts[n1] = n1;

	for (int i = 0; i < m_numNodes - 1; i++) //mirar veins de tots els nodes
	{
		int posVeiAct = indexCurt(distancies, visitats); //distancies esta inicialitzat a DISTMAX
		visitats[posVeiAct] = true;
		if (posVeiAct == n2) return; //s'acaba la funcio

		for (int vei = 0; vei < m_numNodes; vei++) //actualitzar distancies i recorreguts
		{
			list<pair<int, double>>::iterator it = m_graf[posVeiAct].begin();
			bool trobat = false;

			while (!trobat && it != m_graf[posVeiAct].end()) //cereca del vei
			{
				if ((*it).first == vei)
					trobat = true;
				else
					it++;
			}

			if (trobat)
			{
				if (!visitats[vei]) //no hem passat per aquest vei
					if (distancies[posVeiAct] + (*it).second < distancies[vei]) //no es compleix la condicio
					{
						distancies[vei] = distancies[posVeiAct] + (*it).second;
						recorreguts[vei] = posVeiAct;
					} //la distancia d'aquest vei es menor que la de l'anterior
			}

		}
	}
}


void GrafSolucio::camiCurt(const Coordinate& node1, const Coordinate& node2, stack<Coordinate>& cami)
{
	//comprovar existencia dels nodes
	bool trobat1 = false;
	bool trobat2 = false;
	int i = 0;
	int j1 = 0; //index node1
	int j2 = 0; //index node2

	while ((!trobat1 || !trobat2) && i < m_nodes.size())
	{
		if (node1 == m_nodes[i])
		{
			trobat1 = true;
			j1 = i;
		}

		if (node2 == m_nodes[i])
		{
			trobat2 = true;
			j2 = i;
		}
		i++;
	}

	if (trobat1 && trobat2)
	{
		vector<int> recorregut;
		vector<double> distancies;

		Dijkstra(j1, j2, distancies, recorregut); //tots els valors de recorregut son -1
		int i = j2;
		cami.push(m_nodes[j2]);

		while (i != j1)
		{
			cami.push(m_nodes[recorregut[i]]);
			i = recorregut[i];
		}
	}
}