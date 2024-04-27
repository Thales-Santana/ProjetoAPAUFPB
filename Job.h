#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <fstream>
#include <vector>

struct Job {
    int id;
    double somaCustoTempo; // Razão do custo pelo tempo
    int tempo_processamento;
    int custo;

    Job() : id(0), tempo_processamento(0), custo(0), somaCustoTempo(0) {}
};

void lerArquivo(const std::string& nomeArquivo, std::vector<int>& capacidades, std::vector<std::vector<Job>>& matrizJob, int &p);
int calcularCustoTotal(const std::vector<std::vector<Job>> &matriz, const std::vector<std::vector<Job>> &alocados, int p);

#endif // JOB_H
