#include "pch.h"
#include "Graph.h"
#include <queue>


// =============================================================================
// Dijkstra ====================================================================
// =============================================================================

void Dijkstra(CGraph& graph, CVertex *pStart)
{
}

// =============================================================================
// DijkstraQueue ===============================================================
// =============================================================================

struct nodeConjelat
{
    double m_distacia;
    CVertex* m_Node;
    CVertex* m_NodeAnterior;
    //CEdge* m_AresteEntreNodes;

    bool operator<(const nodeConjelat& b) const {
        return m_distacia > b.m_distacia; // Invertit per a Min-Heap
    }
};

void DijkstraQueue(CGraph& graph, CVertex *pStart)
{
	//Inicialitzar les distàncies dels vèrtexs a infinit (double m_DijkstraDistance).
//Marcar tots el vèrtex com no visitats(bool m_DijkstraVisit).
	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_DijkstraDistance = std::numeric_limits<double>::infinity();
		it->m_DijkstraVisit = false;
		it->m_pDijkstraPrevious = nullptr;
		it->m_Node = nullptr;
	}
	// el vèrtex pStart que serà a 0 (double m_DijkstraDistance).
	pStart->m_DijkstraDistance = 0;

	//definir pActual que serà el vèrtex actual que l’inicialitzarem amb el vèrtex pStart
	CVertex* pActual = pStart;

	std::priority_queue<nodeConjelat> vertexPetit;

	// Repetir mentre pActual != NULL
	while (pActual != NULL) {
		// Recorre tots els veïns v de pActual
		for (std::list<CEdge*>::iterator it = (*pActual).m_Edges.begin(); it != (*pActual).m_Edges.end(); ++it) {
			double distancia = (pActual->m_DijkstraDistance + (*it)->m_Length);
			if (!((*it)->m_pDestination->m_DijkstraVisit) && ((*it)->m_pDestination->m_DijkstraDistance > distancia)) {//No fa falta? el if
				(*it)->m_pDestination->m_DijkstraDistance = distancia;
				(*it)->m_pDestination->m_Node = pActual;
				(*it)->m_pDestination->m_pDijkstraPrevious = (*it);
				nodeConjelat node;
				node.m_Node = (*it)->m_pDestination;
				node.m_distacia = distancia;
				node.m_NodeAnterior = pActual;
				//TODO: el que s'hinsereix es una copia no es el orijinal
				vertexPetit.push(node);
			}
		}
		//Marcar pActual com visitat
		pActual->m_DijkstraVisit = true;
		//pActual = vèrtex no visitat amb distancia més petita o NULL si no hi ha vèrtexs no visitats
		if (vertexPetit.size() > 0) {
			do {
				nodeConjelat temp = vertexPetit.top();
				vertexPetit.pop();
				if (std::abs(temp.m_distacia - temp.m_Node->m_DijkstraDistance) < 0.00001) {
					//if (temp.m_Node->m_Node == temp.m_NodeAnterior) {
						pActual = temp.m_Node;
					//}
				}
				else {
					pActual = NULL;
				}
			} while (pActual == NULL && vertexPetit.size() > 0);
		}
		else
			pActual = NULL;

	}


	int a = 0;
	a = 1;

}
