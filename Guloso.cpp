#include "Guloso.h"
#include "Job.h"
#include <algorithm>

void preencherMatriz(std::vector<std::vector<Job>>& matriz, const std::vector<int>& capacidades, std::vector<std::vector<Job>>& jobsAlocados) {
    for (int i = 0; i < matriz.size(); ++i) {
        std::sort(matriz[i].begin(), matriz[i].end(), [](const Job& a, const Job& b) {
            return a.somaCustoTempo < b.somaCustoTempo;
        });
    }

    int num_linhas = matriz.size();
    int num_colunas = matriz[0].size();
    jobsAlocados.resize(num_linhas);
    int count = 0;
    for (int i = 0; i < num_linhas; ++i) {
        int capacidade_atual = capacidades[i];
        for (int j = 0 + count; j < num_colunas; ++j) {
            if (matriz[i][j].tempo_processamento <= capacidade_atual) {
                capacidade_atual -= matriz[i][j].tempo_processamento;
                jobsAlocados[i].push_back(matriz[i][j]);
                count++;
            }
        }
    }
}
