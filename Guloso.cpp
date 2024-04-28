#include "Guloso.h"
#include "Job.h"
#include <algorithm>

void ordenacaoGuloso(std::vector<std::vector<Job>>& matriz) {
    for (int i = 0; i < matriz.size(); ++i) {
        std::sort(matriz[i].begin(), matriz[i].end(), [](const Job& a, const Job& b) {
            return a.tempo_processamento < b.tempo_processamento;
        });
    }
}
