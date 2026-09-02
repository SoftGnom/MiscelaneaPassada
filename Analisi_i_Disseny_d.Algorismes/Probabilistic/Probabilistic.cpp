#include "pch.h"
#include "Graph.h"
#include <queue>
#include <iostream>
#include <iomanip> 
#include <random>
#include <chrono>

// SalesmanTrackProbabilistic ==================================================



using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;



std::pair<double, std::vector<int>> GenerarCamiAleatori(int n, MatriuResultatP& estructura) {

    std::pair<double, std::vector<int>> ret(0.0, std::vector<int>(n, 0));
    std::vector<bool> visitat(n, false);

    ret.first = 0;

    // set node inicial
    ret.second[0] = 0;
    visitat[0] = true;

    // set node final
    ret.second[n - 1] = (n - 1);
    visitat[n - 1] = true;

    // Construïm el camí
    for (int pas = 1; pas < (n - 1); ++pas) {

        int actual = ret.second[pas - 1];
        std::vector<std::pair<int, double>> opcions;
        double sumaInverses = 0;

        // Busquem opcions no visitats
        for (int i = 1; i < n - 1; ++i) {
            if (!visitat[i]) {
                double d = estructura[actual][i].second;

                // Corretjir errors i definir pes
                double pes;
                if (d <= 0) pes = 100.0;
                else if (d >= std::numeric_limits<double>::max()) pes = 0;
                else pes = 1.0 / (d * d * d * d);

                opcions.push_back({ i, pes });
                sumaInverses += pes;

            }
        }

        // escollir el correcte i buscar-lo
        double llindar = ((double)rand() / RAND_MAX) * sumaInverses;

        double acumulat = 0;
        int triat = -1;

        for (auto& opcio : opcions) {
            acumulat += opcio.second;
            if (acumulat >= llindar) {
                triat = opcio.first;
                break;
            }
        }


        // Actualitzem el camí i l'estat
        ret.first += estructura[actual][triat].second;
        ret.second[pas] = triat;
        visitat[triat] = true;
    }

    ret.first += estructura[ret.second[n - 2]][ret.second[n - 1]].second;

    return ret;
}


CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització 
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            
            i++;
        }
    }
    
    // Escalat cúbic consolidat: (600 * std::pow(NUM_NODES, 3))
    long long tempsTotal = static_cast<long long>(100 * std::pow(NUM_NODES, 3));

    // Amplada consolidada: (base * 1.5 * 1.5) = base * 2.25
    double pAmplada = 0.225;

    // CÀLCULS DERIVATS
    // L'amplada defineix quants intents nous fem
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));

    std::pair<double, std::vector<int>> millo(std::numeric_limits<double>::max(), std::vector<int>(NUM_NODES, true));
    std::pair<double, std::vector<int>> actual(0.0, std::vector<int>(NUM_NODES, 0));

    if (NUM_NODES > 3) {

        // Dins de SalesmanTrackProbabilistic, per a cada intent (nCercas):
        for (int i_intent = 0; i_intent < nCercas; i_intent++) {
            // 1. Generar solució inicial (Greedy o Aleatòria) [cite: 24, 25, 26]
            actual = GenerarCamiAleatori(NUM_NODES, estructura);

            // 2. Descens del Gradient Sistemàtic [cite: 61]
            bool milloraAconseguida = true;
            while (milloraAconseguida) {
                milloraAconseguida = false;

                // Bucle sistemàtic extret de l'enunciat 
                for (int i = 1; i < (int)NUM_NODES - 2; ++i) {
                    for (int j = i + 1; j < (int)NUM_NODES - 1; ++j) {

                        // Càlcul ràpid de l'estalvi amb la matriu precalculada [cite: 43, 44]
                        double costActual = estructura[actual.second[i - 1]][actual.second[i]].second +
                            estructura[actual.second[j]][actual.second[j + 1]].second;

                        double costNou = estructura[actual.second[i - 1]][actual.second[j]].second +
                            estructura[actual.second[i]][actual.second[j + 1]].second;

                        if (costNou < costActual) {
                            // Si millora, fem l'intercanvi (2-Opt: invertir el segment) [cite: 29, 65]
                            std::reverse(actual.second.begin() + i, actual.second.begin() + j + 1);
                            actual.first = actual.first - costActual + costNou;

                            milloraAconseguida = true; // Hem de repetir el descens [cite: 66]
                        }
                    }
                }
            }

            // Guardar si és la millor global de tots els intents [cite: 55]
            if (actual.first < millo.first) {
                millo.first = actual.first;
                for (int k = 0; k < NUM_NODES; k++) millo.second[k] = actual.second[k];
            }
        }


        
    }
    else {//fer algo amb el 4?

        millo.second[0] = 0;
        millo.first = 0;

        for (int i = 1; i < NUM_NODES; ++i) {
            millo.second[i] = i;
            millo.first += estructura[millo.second[i - 1]][i].second;
        }
    }


    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.second[i - 1];
        int desti = millo.second[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}
