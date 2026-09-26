#include "pch.h"
#include "Graph.h"
#include <queue>
#include <iostream>
#include <iomanip> 
#include <random>
#include <chrono>

// Coloracio de graf backtracking ==================================================

bool ColoringBacktrackingRec(CGraph* graph, std::list<CVertex>::iterator itActual, std::vector<std::vector<bool>>* v)
{

	std::vector<bool>* colorsAcesibles = &((*v)[(*itActual).m_valor]);


	for (std::list<CEdge*>::iterator it = itActual->m_Edges.begin(); it != itActual->m_Edges.end(); ++it) {
		if ((*it)->m_pDestination->m_Color != -1) {
			(*colorsAcesibles)[(*it)->m_pDestination->m_Color] = false;
		}
	}

	std::list<CVertex>::iterator itNext = next(itActual);
	if (itNext == graph->m_Vertices.end()) {
		for (int i = 0; i < colorsAcesibles->size(); i++) {
			if ((*colorsAcesibles)[i]) {
				itActual->m_Color = i;
				return true;

			}
		}
	}
	else {
		for (int i = 0; i < colorsAcesibles->size(); i++) {
			if ((*colorsAcesibles)[i]) {
				itActual->m_Color = i;
				if (ColoringBacktrackingRec(graph, itNext, v))
					return true;

			}/*
			else {
				(*colorsAcesibles)[i] = true;
			}*/
		}
	}

	itActual->m_Color = -1;
	for (int i = 0; i < colorsAcesibles->size(); i++) {
		(*colorsAcesibles)[i] = true;
	}

	return false;
}

bool ColoringBacktracking(CGraph& graph)
{

	if (graph.m_Vertices.size() > 0) {

		int n = 0;
		for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
			it->m_Color = -1;
			it->m_valor = n;
			n++;
		}

		std::vector<std::vector<bool>> colorsAcesibles(
			graph.m_Vertices.size(),
			std::vector<bool>((graph.m_MaxColors), true)
		);

		return ColoringBacktrackingRec(&graph, graph.m_Vertices.begin(), &colorsAcesibles);

	}
	return true;
}
/*
* V4
* 

bool ColoringBacktrackingRec(CGraph* graph, std::list<CVertex>::iterator itActual, std::vector<std::vector<bool>>* v)
{

	std::vector<bool>* colorsAcesibles = &((*v)[(*itActual).m_valor]);


	for (std::list<CEdge*>::iterator it = itActual->m_Edges.begin(); it != itActual->m_Edges.end(); ++it) {
		if ((*it)->m_pDestination->m_Color != -1) {
			(*colorsAcesibles)[(*it)->m_pDestination->m_Color] = false;
		}
	}

	std::list<CVertex>::iterator itNext = next(itActual);
	if (itNext == graph->m_Vertices.end()) {
		for (int i = 0; i < colorsAcesibles->size(); i++) {
			if ((*colorsAcesibles)[i]) {
				itActual->m_Color = i;
				return true;

			}
		}
	}
	else {
		for (int i = 0; i < colorsAcesibles->size(); i++) {
			if ((*colorsAcesibles)[i]) {
				itActual->m_Color = i;
				if (ColoringBacktrackingRec(graph, itNext, v))
					return true;

			}
		}
	}

	itActual->m_Color = -1;
		for (int i = 0; i < colorsAcesibles->size(); i++) {
			(*colorsAcesibles)[i] = true;
		}

	return false;
}

bool ColoringBacktracking(CGraph& graph)
{

	if (graph.m_Vertices.size() > 0) {

		int n = 0;
		for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
			it->m_Color = -1;
			it->m_valor = n;
			n++;
		}

		std::vector<std::vector<bool>> colorsAcesibles(
			graph.m_Vertices.size(),
			std::vector<bool>((graph.m_MaxColors), true)
		);

		return ColoringBacktrackingRec(&graph, graph.m_Vertices.begin(), &colorsAcesibles);

	}
	return true;
}
*/
/*
* V3
* 
bool ColoringBacktrackingRec(CGraph* graph, std::list<CVertex>::iterator itActual)
{

		std::vector<bool> colorsAcesibles((graph->m_MaxColors), true);

		for (std::list<CEdge*>::iterator it = itActual->m_Edges.begin(); it != itActual->m_Edges.end(); ++it) {
			if ((*it)->m_pDestination->m_Color != -1) {
				colorsAcesibles[(*it)->m_pDestination->m_Color] = false;
			}
		}

		std::list<CVertex>::iterator itNext = next(itActual);
		if (itNext == graph->m_Vertices.end()) {
			for (int i = 0; i < colorsAcesibles.size(); i++) {
				if (colorsAcesibles[i]) {
					itActual->m_Color = i;
					return true;

				}
			}
		}
		else {
			for (int i = 0; i < colorsAcesibles.size(); i++) {
				if (colorsAcesibles[i]) {
					itActual->m_Color = i;
					if (ColoringBacktrackingRec(graph, itNext))
						return true;

				}
			}
		}

		itActual->m_Color = -1;

	//}

	return false;
}

bool ColoringBacktracking(CGraph& graph)
{
	int n = 0;
	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_Color = -1;
		it->m_valor = n;
		n++;
	}

	if(graph.m_Vertices.size()>0)
		return ColoringBacktrackingRec(&graph, graph.m_Vertices.begin());
	return true;
}
//*/

/*
* V2
* /

bool ColoringBacktrackingRec(CGraph* graph, std::list<CVertex>::iterator itActual)
{
	if (itActual == graph->m_Vertices.end()) { //cas fianl
		return true;
	}
	else { //cas intermitg

		std::vector<bool> colorsAcesibles((graph->m_MaxColors),true);

		for (std::list<CEdge*>::iterator it = itActual->m_Edges.begin(); it != itActual->m_Edges.end(); ++it) {
			if ((*it)->m_pDestination->m_Color != -1) {
				colorsAcesibles[(*it)->m_pDestination->m_Color] = false;
			}
		}

		std::list<CVertex>::iterator itNext = next(itActual);
		for (int i = 0; i < colorsAcesibles.size(); i++) {
			if (colorsAcesibles[i]) {
				itActual->m_Color = i;
				if (ColoringBacktrackingRec(graph, itNext))
					return true;

			}
		}
		itActual->m_Color = -1;

	}

	return false;
}

bool ColoringBacktracking(CGraph& graph)
{
		
int n = 0;
for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
	it->m_Color = -1;
	it->m_valor = n;
	n++;
}


return ColoringBacktrackingRec(&graph, graph.m_Vertices.begin());
}
//*/
/*
* V1
* /
bool ColoringBacktrackingRec(CGraph* graph, std::list<CVertex>::iterator itActual)
{
	if (itActual == graph->m_Vertices.end()) { //cas fianl
		return true;
	}
	else { //cas intermitg

		std::vector<bool> colorsAcesibles((graph->m_MaxColors), true);

		for (std::list<CEdge*>::iterator it = itActual->m_Edges.begin(); it != itActual->m_Edges.end(); ++it) {
			if ((*it)->m_pDestination->m_Color != -1) {
				colorsAcesibles[(*it)->m_pDestination->m_Color] = false;
			}
		}

		std::list<CVertex>::iterator itNext = next(itActual);
		for (int i = 0; i < colorsAcesibles.size(); i++) {
			if (colorsAcesibles[i]) {
				itActual->m_Color = i;
				if (ColoringBacktrackingRec(graph, itNext))
					return true;

			}
		}
		itActual->m_Color = -1;

	}

	return false;
}

bool ColoringBacktracking(CGraph& graph)
{

	graph.m_Vertices.sort([](const CVertex n1, const CVertex n2) {
		return (n1.m_Edges.size() > n2.m_Edges.size());
		});
		
	int n = 0;
	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_Color = -1;
		it->m_valor = n;
		n++;
	}


	return ColoringBacktrackingRec(&graph, graph.m_Vertices.begin());
}
//*/
/*
* V0.1-No fucniona 
* 
bool ColoringBacktrackingRec(CGraph* graph, std::vector<std::vector<bool>>* colorsAtjacents, std::list<CVertex>::iterator itActual)
{
	if (itActual == graph->m_Vertices.end()) { //cas fianl
		return true;
	}
	else { //cas intermitg

		std::vector<bool>* colorsAcesibles = &((*colorsAtjacents)[(*itActual).m_valor]);

		if ((*colorsAcesibles)[(*colorsAcesibles).size() - 1]) { //crar que visitar i que no (al sempre fer el mateix recorregut amb els mateixos vertex no cal regenerar la llista)
			for (std::list<CEdge*>::iterator it = itActual->m_Edges.begin(); it != itActual->m_Edges.end(); ++it) {
				if ((*it)->m_Color != -1) {
					(*colorsAcesibles)[(*it)->m_Color] = false;
				}
			}
			(*colorsAcesibles)[(*colorsAcesibles).size() - 1] = false;
		}

		std::list<CVertex>::iterator itNext = next(itActual);
		for (int i = 0; i < colorsAcesibles->size(); i++) {
			if ((*colorsAcesibles)[i]) {
				itActual->m_Color = i;
				if (ColoringBacktrackingRec(graph, colorsAtjacents, itNext))
					return true;

			}
		}
		itActual->m_Color = -1;

	}

	return false;
}

bool ColoringBacktracking(CGraph& graph)
{

	graph.m_Vertices.sort([](const CVertex n1, const CVertex n2) {
		return (n1.m_Edges.size() > n2.m_Edges.size());
		});

	std::vector<std::vector<bool>> colorsAcesibles(
		graph.m_Vertices.size(),
		std::vector<bool>((graph.m_MaxColors)+1, true)
	);

	int n = 0;
	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_Color = -1;
		it->m_valor = n;
		n++;
	}


	return ColoringBacktrackingRec(&graph, &colorsAcesibles, graph.m_Vertices.begin());
}
//*/

/*
* V0-No complet
* \

bool ColoringBacktrackingRec(CGraph* graph, CVertex* actual, int n)
{



	if (n == graph->m_Vertices.size()) { //cas fianl
		return true;
	}
	else { //cas intermitg

		actual->m_Edges.sort([](const CEdge* n1, const CEdge* n2) {
			return (n1->m_pDestination->m_Edges.size() > n2->m_pDestination->m_Edges.size());
			});

		std::vector<bool> colorsAcesibles(graph->m_MaxColors, true);

		for (std::list<CEdge*>::iterator it = actual->m_Edges.begin(); it != actual->m_Edges.end(); ++it) {
			if ((*it)->m_Color != -1) {
				colorsAcesibles[(*it)->m_Color] = false;
			}
		}

		for (int i = 0; i < colorsAcesibles.size(); i++) {
			if (colorsAcesibles[i]) {
				actual->m_Color = i;
				for (std::list<CEdge*>::iterator it = actual->m_Edges.begin(); it != actual->m_Edges.end(); ++it) {
					if ((*it)->m_Color == -1)
						if (ColoringBacktrackingRec(graph, (*it)->m_pDestination, n + 1))
							return true;
				}
			}
		}
		actual->m_Color = -1;
	}

	return false;
}

bool ColoringBacktracking(CGraph& graph)
{
	int nMaxConexions = 0;
	CVertex* nodeMaxConexions;
	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_Color = -1;
		if (it->m_Edges.size() > nMaxConexions) {
			nodeMaxConexions = &(*it);
		}
	}


	return ColoringBacktrackingRec(&graph, nodeMaxConexions, 0);
}
//*/

//ChromaticNumberBacktracking =======================================================

int ChromaticNumberBacktracking(CGraph& graph)
{
	return -1;
}

// Coloracio de graf probabilistic ==================================================

bool ColoringProbabilistic(CGraph& graph)
{
	return false;
}

//ChromaticNumberProbabilistic =======================================================

int ChromaticNumberProbabilistic(CGraph& graph)
{
	return -1;
}
