#include <iostream>
#include <vector>
#include "Job.h"
#include "Guloso.h"
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>

void imprimirMatriz(const std::vector<std::vector<Job>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& job : linha) {
            std::cout << "Job(" << job.id << "): "  << job.tempo_processamento << " | " << job.custo << "\n";
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

void swap(std::vector<std::vector<Job>> &matriz, const std::vector<int> &capacidades, int p)
{
    int num_servidores = matriz.size();

    double melhor_custo = std::numeric_limits<double>::max(); // Inicializa com um valor grande
    std::vector<std::vector<Job>> melhores_matriz = matriz;

    // Itera através de todas as combinações possíveis de troca de dois jobs entre diferentes servidores
    for (int servidor1 = 0; servidor1 < num_servidores; ++servidor1)
    {
        for (int job1 = 0; job1 < matriz[servidor1].size(); ++job1)
        {
            for (int servidor2 = 0; servidor2 < num_servidores; ++servidor2)
            {
                for (int job2 = 0; job2 < matriz[servidor2].size(); ++job2)
                {
                    // Verifica se a troca desses jobs é viável e respeita a capacidade
                    if (servidor1 != servidor2 &&
                        matriz[servidor2].size() < matriz[servidor1].size() &&
                        std::accumulate(matriz[servidor2].begin(), matriz[servidor2].end(), 0,
                                        [](int sum, const Job &job)
                                        { return sum + job.tempo_processamento; }) +
                                matriz[servidor1][job1].tempo_processamento <=
                            capacidades[servidor2])
                    {
                        std::swap(matriz[servidor1][job1], matriz[servidor2][job2]);

                        // Calcula o custo total da nova solução
                        double custo_atual = calcularCustoTotal(matriz, matriz, p);

                        // Verifica se a nova solução é melhor do que a melhor encontrada até agora
                        if (custo_atual < melhor_custo) {
                            melhor_custo = custo_atual;
                            melhores_matriz = matriz;
                        }

                        // Reverte a troca
                        std::swap(matriz[servidor1][job1], matriz[servidor2][job2]);
                    }
                }
            }
        }
    }

    // Atualiza as matrizes originais com a melhor solução encontrada
    matriz = melhores_matriz;
}

void swapIntra(std::vector<std::vector<Job>> &matriz, const std::vector<int> &capacidades, int p)
{
    int num_servidores = matriz.size();
    std::vector<std::vector<Job>> jobsAlocados;
    alocarJobs(matriz, capacidades, jobsAlocados);
    int melhor_custo = calcularCustoTotal(matriz, jobsAlocados, p);
    std::vector<std::vector<Job>> melhores_matriz = matriz;

    // Itera através de todas as combinações possíveis de troca de dois jobs entre diferentes servidores
    for (int i = 0; i < matriz[0].size(); ++i) {
        for (int j = i; j < matriz[0].size() - 1; ++j) {
            for (int k = 0; k < num_servidores; ++k) {
                std::swap(matriz[k][i], matriz[k][j+1]);
            }
            alocarJobs(matriz, capacidades, jobsAlocados);
            int custo_atual = calcularCustoTotal(matriz, jobsAlocados, p);

            // Verifica se a nova solução é melhor do que a melhor encontrada até agora
            if (custo_atual < melhor_custo) {
                melhor_custo = custo_atual;
                melhores_matriz = matriz;
            } else {
                for (int k = 0; k < num_servidores; ++k) {
                    std::swap(matriz[k][i], matriz[k][j+1]);
                }
            }
        }
    }

    // Atualiza as matrizes originais com a melhor solução encontrada
    matriz = melhores_matriz;
}

int main()
{
    std::string nomeArquivo = "file.txt";

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

    ordenacaoGuloso(matrizJob);
    imprimirMatriz(matrizJob);
    // Realiza a operação de troca para explorar a vizinhança

    swapIntra(matrizJob, arrayB, custo_fixo);
    alocarJobs(matrizJob, arrayB, jobsAlocados);
    // swap(jobsAlocados, custo_fixo);

    // Imprime o resultado
    imprimirMatriz(matrizJob);
    std::cout << std::endl;
    imprimirMatrizInt(matrizJob);

    std::cout << std::endl;
    imprimirMatrizInt(jobsAlocados);
    std::cout << std::endl;
    std::cout << "Custo:" << std::endl;
    std::cout << calcularCustoTotal(matrizJob, jobsAlocados, custo_fixo);
    return 0;
}