#include "pch.h"
#include "GraphApplication.h"
#include "GraphApplicationDlg.h"
#include <set>



// =============================================================================
// CONVEX HULL =================================================================
// =============================================================================

// left ========================================================================
// Recta de p1 a p2. i posició del punt p respecte la recta
// resultat>0: p a la esquerra.
// resultat==0: p sobre la recta.
// resultat<0: p a la dreta

double PosicioRespeteRecta(CGPoint& rectaPuntA, CGPoint& rectaPuntB, CGPoint &puntEvaluar)
{
	return (rectaPuntA.m_Y - rectaPuntB.m_Y) * (puntEvaluar.m_X - rectaPuntB.m_X) - (rectaPuntA.m_X - rectaPuntB.m_X) * (puntEvaluar.m_Y - rectaPuntB.m_Y);
}

// AreaTriangle ================================================================

double AreaTriangle(CGPoint& a, CGPoint& b, CGPoint c)
{
	return abs((a.m_Y - b.m_Y) * (c.m_X - b.m_X) - (a.m_X - b.m_X) * (c.m_Y - b.m_Y)) / 2.0;
}


// QuickHull ===================================================================



void QuickHullRec(vector<CVertex*>* perimetre, vector<CVertex*>*  nodes, CVertex* puntA, CVertex* puntB)
{
	//Calcular el 3er punt
	std::vector<CVertex*>::iterator it = nodes->begin();
	CVertex* mesLluny = (*it);
	double areaMesLluny = std::abs(AreaTriangle(puntA->m_Point, puntB->m_Point, mesLluny->m_Point));
	++it;
	while (it != nodes->end()) {
		double areaTemp = std::abs(AreaTriangle(puntA->m_Point, puntB->m_Point, (*it)->m_Point));
		if (areaMesLluny < areaTemp) {
			mesLluny = (*it);
			areaMesLluny = areaTemp;
		}
		++it;
	}
	
	//Mirar quins punts no estan en el triangle del 3er punt
	vector<CVertex*> partPositiva;
	vector<CVertex*> partNegativa;
	for (std::vector<CVertex*>::iterator it = nodes->begin(); it != nodes->end(); ++it) {
		double posPositiva = PosicioRespeteRecta(puntA->m_Point, mesLluny->m_Point, (*it)->m_Point);
		double posNegativa = PosicioRespeteRecta(mesLluny->m_Point, puntB->m_Point, (*it)->m_Point);
		if (posPositiva > 0) {
			partPositiva.push_back((*it));
		}
		else {
			if (posNegativa > 0) {
				partNegativa.push_back((*it));
			}
		}
	}

	//Cridar per a incluir els punts no inclosos i definir la solucio
	if (partPositiva.size() > 1) {
		QuickHullRec(perimetre, &partPositiva, puntA, mesLluny);
	}
	else {
		if (partPositiva.size() == 1) {
			perimetre->push_back((*partPositiva.begin()));
		}
	}

	perimetre->push_back(mesLluny);

	if (partNegativa.size() > 1) {
		QuickHullRec(perimetre, &partNegativa, mesLluny, puntB);
	}
	else {
		if (partNegativa.size() == 1) {
			perimetre->push_back((*partNegativa.begin()));
		}
	}
}


CConvexHull QuickHull(CGraph& graph)
{
	CConvexHull ret(&graph);
	int size = (graph.m_Vertices.size());
	if (size > 2) {//si hi ha suficenta informacio

		//buscar 2 punts molt allunyats (max i min de X)
		std::list<CVertex>::iterator it = graph.m_Vertices.begin();
		CVertex* maxX = &(*it);//Cambiar per un algorisme mes aficient?
		it++;
		CVertex* minX = &(*it);
		if (maxX->m_Point.m_X < minX->m_Point.m_X) {
			CVertex* temp = maxX;
			maxX = minX;
			minX = temp;
		}
		it++;
		while (it != graph.m_Vertices.end() ) {
			auto point = (*it).m_Point;
			if (point.m_X > maxX->m_Point.m_X) {
				maxX = &(*it);
			}
			else {
				if (point.m_X < minX->m_Point.m_X) {
					minX = &(*it);
				}
			}
			++it;
		}

		//Mirar quins punts estan per sobre i per sota de la linia
		vector<CVertex*> partPositiva;
		vector<CVertex*> partNegativa;
		for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
			double pos = PosicioRespeteRecta(minX->m_Point, maxX->m_Point, it->m_Point);
			if (pos > 0) {
				partPositiva.push_back(&(*it));
			}
			else {
				if (pos < 0) {
					partNegativa.push_back(&(*it));
				}
			}
		}

		//Cridar per a incluir els punts no inclosos i definir la solucio
		vector<CVertex*> retPartPositiva;
		vector<CVertex*> retPartNegativa;

		if (partPositiva.size() > 1) {
			retPartPositiva.push_back(minX);
			QuickHullRec(&retPartPositiva, &partPositiva, minX, maxX);
		} else {
			if (partPositiva.size() == 1) {
				retPartPositiva.push_back((*partPositiva.begin()));
			}
		}

		if (partNegativa.size() > 1) {
			retPartNegativa.push_back(maxX);
			QuickHullRec(&retPartNegativa, &partNegativa, maxX, minX);
		}
		else {
			if (partNegativa.size() == 1) {
				retPartNegativa.push_back((*partNegativa.begin()));
			}
		}

		for (std::vector<CVertex*>::iterator it = retPartPositiva.begin(); it != retPartPositiva.end(); ++it) {
			ret.m_Vertices.push_back((*it));
		}
		for (std::vector<CVertex*>::iterator it = retPartNegativa.begin(); it != retPartNegativa.end(); ++it) {
			ret.m_Vertices.push_back((*it));
		}
	}
	else {
		//solucionar els casos exepcinalsi
		if (size == 1) {
			ret.m_Vertices.push_back(&(*graph.m_Vertices.begin()));
		}
		else {
			if (size == 2) {
				std::list<CVertex>::iterator it = graph.m_Vertices.begin();
				CVertex* a = &(*it);
				it++;
				CVertex* b = &(*it);
				if ((a->m_Point.m_X == b->m_Point.m_X) && (a->m_Point.m_Y == b->m_Point.m_Y)) {
					ret.m_Vertices.push_back(a);
				}
				else {
					ret.m_Vertices.push_back(a);
					ret.m_Vertices.push_back(b);
				}
			}
		}
	}

	return 	ret;
}
