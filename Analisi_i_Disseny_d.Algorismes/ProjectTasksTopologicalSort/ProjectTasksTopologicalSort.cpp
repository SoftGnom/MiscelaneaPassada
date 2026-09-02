#include "pch.h"
#include "Graph.h"
#include "ProjectTasks.h"
#include <stdarg.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <random>
using namespace std;

// =============================================================================
// ProjectTaskTopologicalSortGreedy ============================================
// =============================================================================
//*  - V3:
CTopologicalOrder ProjectTaskTopologicalSortGreedy(CProjectTasks& project)
{
	CTopologicalOrder ret = CTopologicalOrder(&project);

	for (std::list<CProTask>::iterator it = project.m_Tasks.begin(); it != project.m_Tasks.end(); ++it) {
		it->m_Valor = (it->m_Previous.size());
		//ret.m_Cyclic.push_back(&(*it));
	}

	bool fiwhile = true;

	while (fiwhile) {
		std::list<CProTask>::iterator it = project.m_Tasks.begin();
		fiwhile = false;
		while (it != project.m_Tasks.end()) {
			if (it->m_Valor == 0) {
				fiwhile = true;
				CProTask* escullit = &(*it);

				ret.m_Order.push_back(escullit);
				for (std::list<CProTask*>::iterator it2 = escullit->m_Next.begin(); it2 != escullit->m_Next.end(); ++it2) {
					(*it2)->m_Valor--;
					//assert((*it2)->m_Valor >= 0);
				}
				escullit->m_Valor = -1;
			}
			it++;
		}


	}

	std::list<CProTask>::iterator it = project.m_Tasks.begin();
	while (it != project.m_Tasks.end()) {
		if (it->m_Valor > 0) {
			ret.m_Cyclic.push_back(&(*it));
		}
		it++;
	}

	return ret;
}
