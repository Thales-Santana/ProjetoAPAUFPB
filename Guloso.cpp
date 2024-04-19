#include "Guloso.h"
#include "Job.h"
#include <algorithm>

void atualizarRazaoTotal(std::vector<std::vector<Job>>& matriz) {
    for (auto& linha : matriz) {
        double somaRazoesLinha = 0.0;
        for (auto& job : linha) {
            somaRazoesLinha += job.razao;
        }
        for (auto& job : linha) {
            job.razao_total = somaRazoesLinha;
        }
    }
}

void permutarColunas(std::vector<std::vector<Job>>& matriz) {
    std::vector<Job>& primeiraLinha = matriz.front();
    int num_linhas = matriz.size();
    int num_colunas = matriz[0].size();
    for (int i = 0; i < primeiraLinha.size(); ++i) {
        for (int j = 0; j < num_linhas; ++j) {
            for (int k = 0; k < num_colunas; ++k) {
                if (primeiraLinha[i].id == matriz[j][k].id && i != k) {
                    std::swap(matriz[j][i], matriz[j][k]);
                }
            }
        }
    }
}

void preencherMatriz(std::vector<std::vector<Job>>& matriz, const std::vector<int>& capacidades, std::vector<std::vector<int>>& jobsAlocados) {
    int num_linhas = matriz.size();
    int num_colunas = matriz[0].size();
    int jobContador = 0;
    jobsAlocados.resize(num_linhas, std::vector<int>(num_colunas, 0));

    for (int i = 0; i < num_linhas; ++i) {
        int capacidade_atual = capacidades[i];
        for (int j = 0; j < num_colunas; ++j) {
            if (i == 0) {
                if (matriz[i][j].tempo_processamento <= capacidade_atual) {
                    capacidade_atual -= matriz[i][j].tempo_processamento;
                    jobsAlocados[i][j] = matriz[i][j].id;
                    jobContador++;
                }
            } else {
                if (matriz[i][j].tempo_processamento <= capacidade_atual && jobsAlocados[i - 1][j] == 0) {
                    capacidade_atual -= matriz[i][j].tempo_processamento;
                    jobsAlocados[i][j] = matriz[i][j].id;
                }
            }
        }
    }
}

void igualarLinhas(std::vector<std::vector<Job>>& matriz) {
    int num_linhas = matriz.size();
    int num_colunas = matriz[0].size();

    for (int j = 0; j < num_colunas; ++j) {
        int id = matriz[0][j].id;
        for (int i = 1; i < num_linhas; ++i) {
            auto it = std::find_if(matriz[i].begin(), matriz[i].end(), [id](const Job& job) { return job.id == id; });
            if (it != matriz[i].end()) {
                std::iter_swap(it, matriz[i].begin() + j);
            }
        }
    }
}
