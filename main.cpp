#include "main.h"
#include <algorithm>
#include <iomanip>

void imprimirMatriz(const std::vector<std::vector<Job>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& job : linha) {
            std::cout << "Job(" << job.id << "): " << std::fixed << std::setprecision(2) << job.razao << " | " << job.tempo_processamento << " | " << job.custo << "\n";
        }
        std::cout << "Razão total: " << linha[0].razao_total << std::endl;
    }
}

void imprimirMatrizInt(const std::vector<std::vector<int>>& matriz) {
    for (const auto& linha : matriz) {
        for (int elemento : linha) {
            std::cout << elemento << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string nomeArquivo = "C://Users//thale//CLionProjects//ProjetoAPAGuloso//file.txt";

    std::vector<int> arrayB;
    std::vector<std::vector<Job>> matrizJob;
    std::vector<std::vector<int>> jobsAlocados;

    lerArquivo(nomeArquivo, arrayB, matrizJob);

    std::cout << "Capacidades:" << std::endl;
    for (int val : arrayB) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    atualizarRazaoTotal(matrizJob);
    std::sort(matrizJob.begin(), matrizJob.end(), [](const std::vector<Job>& a, const std::vector<Job>& b) {
        return a[0].razao_total < b[0].razao_total;
    });

    std::sort(matrizJob[0].begin(), matrizJob[0].end(), [](const Job& a, const Job& b) {
        return a.razao < b.razao;
    });

    permutarColunas(matrizJob);
    preencherMatriz(matrizJob, arrayB, jobsAlocados);
    imprimirMatriz(matrizJob);
    std::cout << std::endl;
    imprimirMatrizInt(jobsAlocados);

    return 0;
}
