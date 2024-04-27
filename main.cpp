#include <iostream>
#include <vector>
#include "Job.h"
#include "Guloso.h"
#include <algorithm>
#include <iomanip>

void imprimirMatriz(const std::vector<std::vector<Job>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& job : linha) {
            std::cout << "Job(" << job.id << "): " << std::fixed << std::setprecision(2) << job.somaCustoTempo << " | " << job.tempo_processamento << " | " << job.custo << "\n";
        }
    }
}

void imprimirMatrizInt(const std::vector<std::vector<Job>>& matriz) {
    for (int i = 0; i < matriz.size(); ++i) {
        for (int j = 0; j < matriz[i].size(); ++j) {
            std::cout << " " << matriz[i][j].id << " ";
        }
        std::cout << std::endl;
    }
}

void swap(std::vector<std::vector<Job>>& matriz, std::vector<std::vector<Job>>& jobsAlocados, int p) {
    int num_servidores = matriz.size();
    int num_jobs = matriz[0].size();

    double melhor_custo = std::numeric_limits<double>::max(); // Inicializa com um valor grande
    std::vector<std::vector<Job>> melhores_jobsAlocados = jobsAlocados;

    // Itera através de todas as combinações possíveis de troca de dois jobs entre diferentes servidores
    for (int servidor1 = 0; servidor1 < num_servidores; ++servidor1) {
        for (int job1 = 0; job1 < jobsAlocados[servidor1].size(); ++job1) {
            for (int servidor2 = 0; servidor2 < num_servidores; ++servidor2) {
                for (int job2 = 0; job2 < jobsAlocados[servidor2].size(); ++job2) {
                    // Verifica se a troca desses jobs é viável
                    if (servidor1 != servidor2) {
                        std::swap(jobsAlocados[servidor1][job1], jobsAlocados[servidor2][job2]);

                        // Calcula o custo total da nova solução
                        double custo_atual = calcularCustoTotal(matriz, jobsAlocados, p);

                        // Verifica se a nova solução é melhor do que a melhor encontrada até agora
                        if (custo_atual < melhor_custo) {
                            melhor_custo = custo_atual;
                            melhores_jobsAlocados = jobsAlocados;
                        }

                        // Reverte a troca
                        std::swap(jobsAlocados[servidor1][job1], jobsAlocados[servidor2][job2]);
                    }
                }
            }
        }
    }

    // Atualiza as matrizes originais com a melhor solução encontrada
    jobsAlocados = melhores_jobsAlocados;
}

int main() {
    std::string nomeArquivo = "C://Users//thale//CLionProjects//ProjetoAPAGuloso//file.txt";

    std::vector<int> arrayB;
    std::vector<std::vector<Job>> matrizJob;
    std::vector<std::vector<Job>> jobsAlocados;
    int custo_fixo; // p

    lerArquivo(nomeArquivo, arrayB, matrizJob, custo_fixo);

    std::cout << "Capacidades:" << std::endl;
    for (int val : arrayB) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    preencherMatriz(matrizJob, arrayB, jobsAlocados);

    // Realiza a operação de troca para explorar a vizinhança
    swap(matrizJob, jobsAlocados, custo_fixo);

    // Imprime o resultado
    imprimirMatriz(matrizJob);
    std::cout << std::endl;
    imprimirMatrizInt(jobsAlocados);
    std::cout << std::endl;
    std::cout << "Custo:"<< std::endl;
    std::cout << calcularCustoTotal(matrizJob,jobsAlocados,custo_fixo);
    return 0;
}