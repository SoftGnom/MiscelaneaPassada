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
