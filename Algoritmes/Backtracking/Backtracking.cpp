#include "pch.h"
#include "Graph.h"
#include <set>


// =============================================================================
// SalesmanTrackBacktracking ===================================================
// =============================================================================


struct DefProblemaSTB {
	CGraph* m_graph;//graf
	list<CEdge*> m_Arestes;//ruta actual i puntar d'on estem
	CTrack* m_solucio;//guardar la millo ruta
	double m_longMillo;//guardar la longitud de la millo ruta
	double m_long;//guardar la longitud actual
	CVisits* m_visits;//guardar tots els visitats
};

DefProblemaSTB prob;

void SalesmanTrackBacktrackingRec()
{

	CVertex* actual = prob.m_Arestes.back()->m_pDestination;
	bool visitatActual = actual->m_valor;
	actual->m_valor = true;


	if (prob.m_long >= prob.m_longMillo) {
		actual->m_valor = visitatActual;
		return;
	}

	if (prob.m_Arestes.back()->m_pDestination == prob.m_visits->m_Vertices.back()) {


		bool fi = true;
		for (std::list<CVertex*>::iterator it = prob.m_visits->m_Vertices.begin(); it != prev(prob.m_visits->m_Vertices.end()); ++it) {
			if ((*it)->m_valor == false) {
				fi = false;
				break;
			}
		}
		if (fi) {
			prob.m_solucio->m_Edges.assign(prob.m_Arestes.begin(), prob.m_Arestes.end());
			prob.m_longMillo = prob.m_long;
			actual->m_valor = visitatActual;
			return;
		}
	}

	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		if ((*itSeguent)->m_valor == false) {
			(*itSeguent)->m_valor = true;
			prob.m_Arestes.push_back((*itSeguent));
			prob.m_long += (*itSeguent)->m_Length;
			SalesmanTrackBacktrackingRec();
			prob.m_long -= (*itSeguent)->m_Length;
			prob.m_Arestes.pop_back();
			(*itSeguent)->m_valor = false;
		}
	}

	actual->m_valor = visitatActual;
	return;
}


CTrack SalesmanTrackBacktracking(CGraph& graph, CVisits& visits)
{
	//tot a false edge
	for (std::list<CEdge>::iterator it = graph.m_Edges.begin(); it != graph.m_Edges.end(); ++it) {
		it->m_valor = false;
	}

	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_valor = false;
	}

	prob.m_graph = &graph;
	prob.m_visits = &visits;
	prob.m_solucio = prob.m_solucio = new CTrack(prob.m_graph);;
	prob.m_long = 0;
	prob.m_longMillo = std::numeric_limits<int>::max();

	CVertex* actual = prob.m_visits->m_Vertices.front();
	actual->m_valor = true;
	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		(*itSeguent)->m_valor = true;
		prob.m_Arestes.push_back((*itSeguent));
		prob.m_long += (*itSeguent)->m_Length;
		SalesmanTrackBacktrackingRec();
		prob.m_long -= (*itSeguent)->m_Length;
		prob.m_Arestes.pop_back();
		(*itSeguent)->m_valor = false;

	}
	return (*prob.m_solucio);
}


/*
* V - nno
* 
struct DefProblemaSTB {
	CGraph* m_graph;//graf
	list<CEdge*> m_Arestes;//ruta actual i puntar d'on estem
	CTrack* m_solucio;//guardar la millo ruta
	double m_longMillo;//guardar la longitud de la millo ruta
	double m_long;//guardar la longitud actual
	CVisits* m_visits;//guardar tots els visitats
};

DefProblemaSTB prob;

void SalesmanTrackBacktrackingRec()
{

	CVertex* actual = prob.m_Arestes.back()->m_pDestination;
	bool visitatActual = actual->m_valor;
	actual->m_valor = true;


	if (prob.m_long >= prob.m_longMillo) {
		actual->m_valor = visitatActual;
		return;
	}

	if (prob.m_Arestes.back()->m_pDestination == prob.m_visits->m_Vertices.back()) {


		bool fi = true;
		for (std::list<CVertex*>::iterator it = prob.m_visits->m_Vertices.begin(); it != prev(prob.m_visits->m_Vertices.end()); ++it) {
			if ((*it)->m_valor == false) {
				fi = false;
				break;
			}
		}
		if (fi) {
			prob.m_solucio->m_Edges.assign(prob.m_Arestes.begin(), prob.m_Arestes.end());
			prob.m_longMillo = prob.m_long;
			actual->m_valor = visitatActual;
			return;
		}
	}

	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		if ((*itSeguent)->m_valor == false) {
			(*itSeguent)->m_valor = true;
			prob.m_Arestes.push_back((*itSeguent));
			prob.m_long += (*itSeguent)->m_Length;
			SalesmanTrackBacktrackingRec();
			prob.m_long -= (*itSeguent)->m_Length;
			prob.m_Arestes.pop_back();
			(*itSeguent)->m_valor = false;
		}
	}

	actual->m_valor = visitatActual;
	return;
}


CTrack SalesmanTrackBacktracking(CGraph& graph, CVisits& visits)
{
	//tot a false edge
	for (std::list<CEdge>::iterator it = graph.m_Edges.begin(); it != graph.m_Edges.end(); ++it) {
		it->m_valor = false;
	}

	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_valor = false;
	}

	prob.m_graph = &graph;
	prob.m_visits = &visits;
	prob.m_solucio = prob.m_solucio = new CTrack(prob.m_graph);;
	prob.m_long = 0;
	prob.m_longMillo = std::numeric_limits<int>::max();

	CVertex* actual = prob.m_visits->m_Vertices.front();
	actual->m_valor = true;
	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		(*itSeguent)->m_valor = true;
		prob.m_Arestes.push_back((*itSeguent));
		prob.m_long += (*itSeguent)->m_Length;
		SalesmanTrackBacktrackingRec();
		prob.m_long -= (*itSeguent)->m_Length;
		prob.m_Arestes.pop_back();
		(*itSeguent)->m_valor = false;

	}
	return (*prob.m_solucio);
}*/

/*
*  V0.1 - NO se que pasa
struct DefProblemaSTB {
	CGraph* m_graph;//graf
	list<CEdge*> m_Arestes;//ruta actual i puntar d'on estem
	CTrack* m_solucio;//guardar la millo ruta
	double m_longMillo;//guardar la longitud de la millo ruta
	double m_long;//guardar la longitud actual
	CVisits* m_visits;//guardar tots els visitats
};

DefProblemaSTB prob;

void SalesmanTrackBacktrackingRec()
{

	CVertex* actual = prob.m_Arestes.back()->m_pDestination;
	bool visitatActual = actual->m_valor;
	actual->m_valor = true;


	if (prob.m_long >= prob.m_longMillo) {
		actual->m_valor = visitatActual;
		return;
	}

	if (prob.m_Arestes.back()->m_pDestination == prob.m_visits->m_Vertices.back()) {


		bool fi = true;
		for (std::list<CVertex*>::iterator it = prob.m_visits->m_Vertices.begin(); it != prev(prob.m_visits->m_Vertices.end()); ++it) {
			if ((*it)->m_valor == false) {
				fi = false;
				break;
			}
		}
		if (fi) {
			prob.m_solucio->m_Edges.assign(prob.m_Arestes.begin(), prob.m_Arestes.end());
			prob.m_longMillo = prob.m_long;
			actual->m_valor = visitatActual;
			return;
		}
	}

	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		if ((*itSeguent)->m_valor == false) {
			(*itSeguent)->m_valor = true;
			prob.m_Arestes.push_back((*itSeguent));
			prob.m_long += (*itSeguent)->m_Length;
			SalesmanTrackBacktrackingRec();
			prob.m_long -= (*itSeguent)->m_Length;
			prob.m_Arestes.pop_back();
			(*itSeguent)->m_valor = false;
		}
	}

	actual->m_valor = visitatActual;
	return;
}


CTrack SalesmanTrackBacktracking(CGraph& graph, CVisits& visits)
{
	//tot a false edge
	for (std::list<CEdge>::iterator it = graph.m_Edges.begin(); it != graph.m_Edges.end(); ++it) {
		it->m_valor = false;
	}

	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_valor = false;
	}

	prob.m_graph = &graph;
	prob.m_visits = &visits;
	prob.m_solucio = prob.m_solucio = new CTrack(prob.m_graph);;
	prob.m_long = 0;
	prob.m_longMillo = std::numeric_limits<int>::max();

	CVertex* actual = prob.m_visits->m_Vertices.front();
	actual->m_valor = true;
	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		(*itSeguent)->m_valor = true;
		prob.m_Arestes.push_back((*itSeguent));
		prob.m_long += (*itSeguent)->m_Length;
		SalesmanTrackBacktrackingRec();
		prob.m_long -= (*itSeguent)->m_Length;
		prob.m_Arestes.pop_back();
		(*itSeguent)->m_valor = false;

	}
	return (*prob.m_solucio);
}
*/


/*
* V0-No va suficient rapit

struct DefProblemaSTB {
	CGraph* m_graph;//graf
	list<CEdge*> m_Arestes;//ruta actual i puntar d'on estem
	CTrack* m_solucio;//guardar la millo ruta
	double m_longMillo;//guardar la longitud de la millo ruta
	double m_long;//guardar la longitud actual
	CVisits* m_visits;//guardar tots els visitats
};


void SalesmanTrackBacktrackingRec(DefProblemaSTB* prob)
{

	CVertex* actual = prob->m_Arestes.back()->m_pDestination;
	bool visitatActual = actual->m_valor;
	actual->m_valor = true;


	if (prob->m_long >= prob->m_longMillo) {
		actual->m_valor = visitatActual;
		return;
	}

	if (prob->m_Arestes.back()->m_pDestination == prob->m_visits->m_Vertices.back()) {


		bool fi = true;
		for (std::list<CVertex*>::iterator it = prob->m_visits->m_Vertices.begin(); it != prev(prob->m_visits->m_Vertices.end()); ++it) {
			if ((*it)->m_valor == false) {
				fi = false;
				break;
			}
		}
		if (fi) {
			prob->m_solucio->m_Edges.assign(prob->m_Arestes.begin(), prob->m_Arestes.end());
			prob->m_longMillo = prob->m_long;
			actual->m_valor = visitatActual;
			return;
		}
	}

	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		if ((*itSeguent)->m_valor == false) {
			(*itSeguent)->m_valor = true;
			prob->m_Arestes.push_back((*itSeguent));
			prob->m_long += (*itSeguent)->m_Length;
			SalesmanTrackBacktrackingRec(prob);
			prob->m_long -= (*itSeguent)->m_Length;
			prob->m_Arestes.pop_back();
			(*itSeguent)->m_valor = false;
		}
	}

	actual->m_valor = visitatActual;
	return;
}


CTrack SalesmanTrackBacktracking(CGraph& graph, CVisits& visits)
{
	//tot a false edge
	for (std::list<CEdge>::iterator it = graph.m_Edges.begin(); it != graph.m_Edges.end(); ++it) {
		it->m_valor = false;
	}

	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); ++it) {
		it->m_valor = false;
	}

	DefProblemaSTB prob;
	prob.m_graph = &graph;
	prob.m_visits = &visits;
	prob.m_solucio = prob.m_solucio = new CTrack(prob.m_graph);;
	prob.m_long = 0;
	prob.m_longMillo = std::numeric_limits<int>::max();

	CVertex* actual = prob.m_visits->m_Vertices.front();
	actual->m_valor = true;
	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		(*itSeguent)->m_valor = true;
		prob.m_Arestes.push_back((*itSeguent));
		prob.m_long += (*itSeguent)->m_Length;
		SalesmanTrackBacktrackingRec(&prob);
		prob.m_long -= (*itSeguent)->m_Length;
		prob.m_Arestes.pop_back();
		(*itSeguent)->m_valor = false;

	}
	return (*prob.m_solucio);
}

*/
/*

struct DefProblemaSTB {
	CGraph* m_graph;//graf
	list<CEdge*> m_Arestes;//ruta actual i puntar d'on estem
	CTrack* m_solucio;//guardar la millo ruta
	int m_longMillo;//guardar la longitud de la millo ruta
	int m_long;//guardar la longitud actual
	CVisits* m_visits;//guardar tots els visitats
	vector<bool> m_visitsVisitats;//si em pasat per tots (el ultim no comta)
};


bool SalesmanTrackBacktrackingRec(DefProblemaSTB* prob)
{

	int visitat = -1;
	CVertex* actual = prob->m_Arestes.back()->m_pDestination;
	//comprovar si estas en una visitada
	int i = 0;
	for (std::list<CVertex*>::iterator it = prob->m_visits->m_Vertices.begin(); it != prev(prob->m_visits->m_Vertices.end()); ++it) {
		if ((*it) == actual) {
			if (prob->m_visitsVisitats[i] == false) {
				visitat = i;
				prob->m_visitsVisitats[i] = true;
			}
			break;
		}
		i++;
	}

	bool fi = true;
	for (std::vector<bool>::iterator it = prob->m_visitsVisitats.begin(); it != prob->m_visitsVisitats.end(); ++it) {
		if ((*it) == false) {
			fi = false;
			break;
		}
	}

	if (fi && &prob->m_Arestes.back()->m_pDestination == &prob->m_visits->m_Vertices.back()) {
		prob->m_solucio->m_Edges.assign(prob->m_Arestes.begin(), prob->m_Arestes.end());
		prob->m_longMillo = prob->m_long;
		return true;//copiar de ruta actial a millo
	}
	else {
		if (prob->m_long >= prob->m_longMillo) {
			if (visitat != -1) {
				prob->m_visitsVisitats[visitat] = false;
			}
			return false;
		}
		else {
			//marcar edges
			for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
				if ((*itSeguent)->m_valor == false) {
					(*itSeguent)->m_valor = true;
					prob->m_Arestes.push_back((*itSeguent));
					prob->m_long += (*itSeguent)->m_Length;
					if (SalesmanTrackBacktrackingRec(prob)) {
						return true;
					}
					prob->m_long -= (*itSeguent)->m_Length;
					prob->m_Arestes.pop_back();
					(*itSeguent)->m_valor = false;
				}
			}
		}
	}

	if (visitat != -1) {
		prob->m_visitsVisitats[visitat] = false;
	}
	return false;
}


CTrack SalesmanTrackBacktracking(CGraph& graph, CVisits& visits)
{
	//tot a false edge
	for (std::list<CEdge>::iterator it = graph.m_Edges.begin(); it != graph.m_Edges.end(); ++it) {
		it->m_valor = false;
	}

	DefProblemaSTB prob;
	prob.m_graph = &graph;
	prob.m_visits = &visits;
	CTrack solucio(prob.m_graph);
	prob.m_solucio = &solucio;
	prob.m_long = 0;
	prob.m_longMillo = INFINITY;
	vector<bool> visitsVisitats(prob.m_visits->m_Vertices.size()-1, false);
	prob.m_visitsVisitats = visitsVisitats;

	CVertex* actual = prob.m_visits->m_Vertices.front();

	for (std::list<CEdge*>::iterator itSeguent = actual->m_Edges.begin(); itSeguent != actual->m_Edges.end(); ++itSeguent) {
		(*itSeguent)->m_valor = true;
		prob.m_Arestes.push_back((*itSeguent));
		prob.m_long += (*itSeguent)->m_Length;
		if (SalesmanTrackBacktrackingRec(&prob)) {
			return (*prob.m_solucio);
		}
		prob.m_long -= (*itSeguent)->m_Length;
		prob.m_Arestes.pop_back();
		(*itSeguent)->m_valor = false;

	}
	return (*prob.m_solucio);
}

*/




// =============================================================================
// SalesmanTrackBacktrackingGreedy =============================================
// =============================================================================
/*
CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{
	CTrack ret(&graph);
	CVertex* nDespres;

	//• Sigui v la primera visita de la llista de visites
	CVertex* nActual = (*visits.m_Vertices.begin());
	//• Candidats = tots els vèrtexs de la llista de visites menys el primer i l'últim.
	list<CVertex*> perVisitar;
	if (visits.m_Vertices.size() > 2) {
		for (std::list<CVertex*>::iterator it = std::next(visits.m_Vertices.begin()); it != std::prev(visits.m_Vertices.end()); ++it) {
			perVisitar.push_back(*it);
		}
	}

	//• Repetir mentre candidats no estigui buit
	while (!perVisitar.empty()) {
		//NO? nActual = nAnterior;
	//	– Aplicant l’algorisme de Dijkstra calcular les distàncies de tots els vèrtexs del graf a v.
		DijkstraQueue(graph, nActual);
		//	– Seleccionar v1 com el vèrtex pertanyent a Candidats amb distància mínima.
		list<CVertex*>::iterator itEliminar = (perVisitar.begin());
		for (std::list<CVertex*>::iterator it = next(itEliminar); it != (perVisitar.end()); ++it) {
			if ((*itEliminar)->m_DijkstraDistance > (*it)->m_DijkstraDistance)
				itEliminar = it;
		}
		nDespres = (*itEliminar);
		//	– Afegir el camí de v a v1 al resultat.
		vector<CEdge*> intercambi;
		for (CVertex* it = (*itEliminar); it != nActual; it = it->m_Node) {
			intercambi.push_back(it->m_Aresta);
		}
		for (std::vector<CEdge*>::iterator it = (intercambi.end()); it != (intercambi.begin()); ) {
			--it;
			ret.m_Edges.push_back((*it));
		}
		//	– Treure v1 de Candidats
		perVisitar.erase(itEliminar);
		//	– v = v1
		nActual = nDespres;
	}
	//• Anar de l’últim candidat seleccionat al vèrtex final de la llista de visites.
	DijkstraQueue(graph, nActual);
	vector<CEdge*> intercambi;
	for (CVertex* it = (*std::prev(visits.m_Vertices.end())); it != nActual; it = it->m_Node) {
		intercambi.push_back(it->m_Aresta);
	}
	for (std::vector<CEdge*>::iterator it = (intercambi.end()); it != (intercambi.begin()); ) {
		--it;
		ret.m_Edges.push_back((*it));
	}


	return ret;
	//return CTrack(&graph);
}


*/


size_t NUM_NODES;
using InfoConnexio = std::pair<std::list<CEdge*>, double>;
using MatriuResultat = std::vector<std::vector<InfoConnexio>>;

// Variables globals per recollir el millor resultat del Backtracking
double g_millorDistancia = std::numeric_limits<double>::max();
std::vector<int> g_millorCami;

void Backtracking(int u, double distAcumulada, std::vector<int>& cami, std::vector<bool>& visitat, const MatriuResultat& estructura, int n) {
	// Poda
	if (distAcumulada >= g_millorDistancia) return;

	// Cas base: hem visitat tots els nodes intermedis (n-1 perquè l'últim és fix)
	if (cami.size() == n - 1) {
		double distFinal = distAcumulada + estructura[u][n - 1].second;
		if (distFinal < g_millorDistancia) {
			g_millorDistancia = distFinal;
			g_millorCami = cami;
			g_millorCami.push_back(n - 1);
		}
		return;
	}

	// Recórrer candidats (de l'1 al n-2)
	for (int v = 1; v < n - 1; ++v) {
		if (!visitat[v]) {
			visitat[v] = true;
			cami.push_back(v);

			Backtracking(v, distAcumulada + estructura[u][v].second, cami, visitat, estructura, n);

			cami.pop_back();
			visitat[v] = false;
		}
	}
}


CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{

	NUM_NODES = visits.m_Vertices.size();
	g_millorDistancia = std::numeric_limits<double>::max();

	const size_t n = visits.m_Vertices.size();
	std::vector<CVertex*> vVisits(visits.m_Vertices.begin(), visits.m_Vertices.end());
	MatriuResultat estructura(n, std::vector<InfoConnexio>(n));

	// Fase 1: Omplir la matriu (el teu mètode de Dijkstra + reconstrucció)
	for (int i = 0; i < n; i++) {
		DijkstraQueue(graph, vVisits[i]);
		for (int j = 0; j < n; j++) {
			if (i == j) {
				estructura[i][j].second = std::numeric_limits<double>::infinity();
			}
			else {
				CVertex* nodeDesti = vVisits[j];
				estructura[i][j].second = nodeDesti->m_DijkstraDistance;

				// Reconstrucció tal com la feies: de destí a origen amb push_front
				CVertex* nodeActual = nodeDesti;
				while (nodeActual != vVisits[i] && nodeActual->m_Node != nullptr) {
					estructura[i][j].first.push_front(nodeActual->m_pDijkstraPrevious);
					nodeActual = nodeActual->m_Node;
				}
			}
		}
	}

	// Fase 2: Preparar i llançar el Backtracking
	g_millorDistancia = std::numeric_limits<double>::max();
	std::vector<bool> visitat(n, false);
	std::vector<int> camiActual;

	visitat[0] = true;
	camiActual.push_back(0);

	Backtracking(0, 0.0, camiActual, visitat, estructura, n);

	// Fase 3: Construir el CTrack final amb les teves llistes d'arestes
	CTrack ret(&graph);
	for (size_t i = 1; i < g_millorCami.size(); i++) {
		int u = g_millorCami[i - 1];
		int v = g_millorCami[i];
		for (CEdge* aresta : estructura[u][v].first) {
			ret.m_Edges.push_back(aresta);
		}
	}

	return ret;


}






/*
* V0
CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{
	return CTrack(&graph);
}
*/
