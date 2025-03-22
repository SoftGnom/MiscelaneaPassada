#pragma once
#include <vector>
#include <list>
#include <string>
#include <stack>
#include "Common.h"
#include "Util.h"
#include "CamiSolucio.h"

using namespace std;

class GrafSolucio
{
public:
	GrafSolucio() {}; //constructor per defecte --> no fa res
	GrafSolucio(const std::vector<CamiBase*>& camins); //constructor a partir d'un vector de camins
	void afegirNode(const Coordinate& node);
	void afegirAresta(Coordinate node1, Coordinate node2);
	void Dijkstra(int n1, int n2, vector<double>& distancies, vector<int>& recorreguts);
	void camiCurt(const Coordinate& node1, const Coordinate& node2, stack<Coordinate>& cami);
	int indexCurt(vector<double>& distancies, vector<bool>& visitats);


private:
	vector<list<pair<int, double>>> m_graf; //int --> index del vei | double --> distancia amb el vei
	vector<Coordinate> m_nodes; //tots els nodes de tots els camins que formen el graf
	int m_numNodes;
	int m_numArestes;
};

bool operator==(Coordinate c1, Coordinate c2); //operador d'igualtat --> comparar coordenades