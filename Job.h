#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <fstream>
#include <vector>

struct Job {
    int id;
    double razao;
    double razao_total;
    int tempo_processamento;
    int custo;

    Job() : id(0), tempo_processamento(0), custo(0), razao(0), razao_total(0) {}
};

void lerArquivo(const std::string& nomeArquivo, std::vector<int>& capacidades, std::vector<std::vector<Job>>& matrizJob, int& p);

#endif // JOB_H
