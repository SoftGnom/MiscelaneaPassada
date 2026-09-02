#include "pch.h"
#include "Graph.h"
#include <queue>
#include <iostream>
#include <iomanip> 

// SalesmanTrackBranchAndBoundGeneric ===================================================

struct nodeConjelatBB
{
    std::vector<int> m_camiActual;    // Camí d'índexs de la matriu
    int m_seguentPosCami;
    double m_distacia;               // L(camí): El que porto realment
    double m_estimacio;              // H(camí): El que em queda (nivells 2 o 3)
    double m_fitaInferior;           // F(camí) = m_distacia + m_estimacio
    std::vector<bool> m_utilitzat;   // Nodes de la matriu visitats

    bool operator<(const nodeConjelatBB& b) const {
        return m_fitaInferior > b.m_fitaInferior; // Min-Heap: el més petit a dalt
    }
};


CTrack SalesmanTrackBranchAndBoundGeneric(CGraph& graph, CVisits& visits, int nivell)
{
    const size_t NUM_NODES = visits.m_Vertices.size();
    using InfoConnexio = std::pair<std::list<CEdge*>, double>;
    using MatriuResultat = std::vector<std::vector<InfoConnexio>>;

    // Inicialització 
    MatriuResultat estructura(NUM_NODES, std::vector<InfoConnexio>(NUM_NODES, { {}, 0.0 }));
    std::vector<double> minims(NUM_NODES);
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            double min = std::numeric_limits<double>::max();
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    if (min > node->m_DijkstraDistance) min = node->m_DijkstraDistance;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            minims[i] = min;
            i++;
        }
    }


    nodeConjelatBB inicial = {
        std::vector<int>(NUM_NODES),       // Camí d'índexs de la matriu
        0,
        0.0,                               // L(camí): El que porto realment
        0.0,                               // H(camí): El que em queda (nivells 2 o 3)
        0.0,                               // F(camí) = m_distacia + m_estimacio
        std::vector<bool>(NUM_NODES, true)// Nodes de la matriu visitats
    };

    
    std::priority_queue<nodeConjelatBB> llistaAComprovar; //monticle binari ¿node mes proxim?

    std::vector<double> disMin(NUM_NODES); //distacias minimas a sumar

    double temp = 0;
    for (int i = visits.m_Vertices.size() - 1; i >= 0; i--) {
        temp += minims[i];
        disMin[i] = temp;
    }

    //init pos inicial
    inicial.m_camiActual[0] = 0;
    inicial.m_utilitzat[0] = false;
    inicial.m_seguentPosCami++;

    //INfiltrat - calculem la fita inferior inicial
    if (nivell == 1) {
        inicial.m_estimacio = 0.0; // En B&B 1 la fita és només la distància real (0 al principi)
    }
    else {
        // En B&B 2 o 3, la fita inicial és la suma de tots els mínims
        // perquè és el mínim "teòric" que haurem de recórrer
        inicial.m_estimacio = disMin[0];
    }

    inicial.m_fitaInferior = inicial.m_distacia + inicial.m_estimacio;

    llistaAComprovar.push(inicial);

    nodeConjelatBB solucioFi;
    double cotaSuperior = std::numeric_limits<double>::max(); // Per podar branques dolentes

    //bucle per a coneixa el cami
    while (!llistaAComprovar.empty()) {
        nodeConjelatBB nodeMenor = llistaAComprovar.top();
        llistaAComprovar.pop();

        // Poda: Si el nodeMenor es pitjor que la millor solució
        if (nodeMenor.m_fitaInferior >= cotaSuperior) continue;

        // Cas Final: hem visitat tots els nodes
        if (nodeMenor.m_seguentPosCami == NUM_NODES) {
            if (nodeMenor.m_distacia < cotaSuperior) {
                cotaSuperior = nodeMenor.m_distacia;
                solucioFi = nodeMenor;
            }
            break;//continue;
        }

        int ultimNodeIdx = nodeMenor.m_camiActual[nodeMenor.m_seguentPosCami - 1];

        bool fi = true;
        for (int i = 1; i < NUM_NODES; i++) {
            if (nodeMenor.m_utilitzat[i]) {
                //Deixa el ultim per el final
                if ( (i == (NUM_NODES - 1)) && (nodeMenor.m_seguentPosCami < i) ) continue;
                
                
                //Calcul de l'estimació (H)
                double estimacio;
                if (nivell == 1) {
                    estimacio = 0.0;
                }
                else if (nivell == 2) {// L'estimació és la suma dels mínims dels nodes que encara falten
                    estimacio = nodeMenor.m_estimacio - minims[i];
                    if (estimacio < 0) {
                        double sumaH = 0;
                        for (int k = 1; k < NUM_NODES; k++) {
                            if (nodeMenor.m_utilitzat[k]) sumaH += minims[k];
                        }
                        estimacio = sumaH;
                    }
                    
                }
                else if (nivell == 3) {// Aquí pots posar una heurística més forta
                    
                    // Fem serveir el nivell 2
                    estimacio = nodeMenor.m_estimacio - minims[i];

                    if (estimacio < 0) {
                        double sumaH = 0;
                        for (int k = 1; k < NUM_NODES; k++) {
                            if (nodeMenor.m_utilitzat[k]) sumaH += minims[k];
                        }
                        estimacio = sumaH;
                    }

                }

                double distacia = estructura[ultimNodeIdx][i].second;

                if ((distacia + estimacio) < cotaSuperior) {

                    //Actualitzem
                    nodeConjelatBB temp = nodeMenor;
                    temp.m_utilitzat[i] = false;
                    temp.m_camiActual[nodeMenor.m_seguentPosCami] = i;
                    temp.m_seguentPosCami++;

                    temp.m_distacia += distacia;
                    temp.m_estimacio = estimacio;
                    temp.m_fitaInferior = temp.m_distacia + temp.m_estimacio;


                    llistaAComprovar.push(temp);
                }
            }
        }
    }

    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = solucioFi.m_camiActual[i - 1];
        int desti = solucioFi.m_camiActual[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}



// SalesmanTrackBranchAndBound1 ===================================================

CTrack SalesmanTrackBranchAndBound1(CGraph& graph, CVisits& visits)
{
    return SalesmanTrackBranchAndBoundGeneric(graph, visits, 1);
}

// SalesmanTrackBranchAndBound2 ===================================================

CTrack SalesmanTrackBranchAndBound2(CGraph& graph, CVisits &visits)
{
    return SalesmanTrackBranchAndBoundGeneric(graph, visits, 2);
}

// SalesmanTrackBranchAndBound3 ===================================================

CTrack SalesmanTrackBranchAndBound3(CGraph& graph, CVisits &visits)
{
    return SalesmanTrackBranchAndBoundGeneric(graph, visits, 3);
}
