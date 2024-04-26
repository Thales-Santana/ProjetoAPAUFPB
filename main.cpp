#include "main.h"
#include <algorithm>
#include <iomanip>
#include <limits>

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

// Define uma função para calcular o custo total de uma solução dada
double calcularCustoTotal(const std::vector<std::vector<Job>>& matriz, const std::vector<std::vector<int>>& jobsAlocados, int p) {
    double custo_total = 0.0;

    // Itera através de cada servidor
    for (int i = 0; i < matriz.size(); ++i) {
        // Itera através de cada job no servidor
        for (int j = 0; j < matriz[i].size(); ++j) {
            // Verifica se o job está alocado para o servidor
            if (jobsAlocados[i][j] != 0) {
                // Adiciona o custo do job alocado ao custo total
                custo_total += matriz[i][j].custo;
            }
        }
    }

    // Itera através de cada job que não está alocado para nenhum servidor
    for (int i = 0; i < jobsAlocados.size(); ++i) {
        for (int j = 0; j < jobsAlocados[i].size(); ++j) {
            if (jobsAlocados[i][j] == 0) {
                // Adiciona o custo fixo para cada job que não está alocado para nenhum servidor
                custo_total += p;
            }
        }
    }

    return custo_total;
}

// Define uma função para realizar a busca exaustiva para a troca de jobs
void swap(std::vector<std::vector<Job>>& matriz, std::vector<std::vector<int>>& jobsAlocados, int p) {
    int num_servidores = matriz.size();
    int num_jobs = matriz[0].size();

    double melhor_custo = std::numeric_limits<double>::max(); // Inicializa com um valor grande
    std::vector<std::vector<Job>> melhor_matriz = matriz;
    std::vector<std::vector<int>> melhores_jobsAlocados = jobsAlocados;

    // Itera através de todas as combinações possíveis de troca de dois jobs entre diferentes servidores
    for (int servidor1 = 0; servidor1 < num_servidores; ++servidor1) {
        for (int job1 = 0; job1 < num_jobs; ++job1) {
            for (int servidor2 = 0; servidor2 < num_servidores; ++servidor2) {
                for (int job2 = 0; job2 < num_jobs; ++job2) {
                    // Verifica se a troca desses jobs é viável
                    if (servidor1 != servidor2) {
                        std::swap(matriz[servidor1][job1], matriz[servidor2][job2]);
                        std::swap(jobsAlocados[servidor1][job1], jobsAlocados[servidor2][job2]);

                        // Calcula o custo total da nova solução
                        double custo_atual = calcularCustoTotal(matriz, jobsAlocados, p);

                        // Verifica se a nova solução é melhor do que a melhor encontrada até agora
                        if (custo_atual < melhor_custo) {
                            melhor_custo = custo_atual;
                            melhor_matriz = matriz;
                            melhores_jobsAlocados = jobsAlocados;
                        }

                        // Reverte a troca
                        std::swap(matriz[servidor1][job1], matriz[servidor2][job2]);
                        std::swap(jobsAlocados[servidor1][job1], jobsAlocados[servidor2][job2]);
                    }
                }
            }
        }
    }

    // Atualiza as matrizes originais com a melhor solução encontrada
    matriz = melhor_matriz;
    jobsAlocados = melhores_jobsAlocados;
}

int main() {
    std::string nomeArquivo = "/home/mathe/ProjetoAPAUFPB/file.txt";

    std::vector<int> arrayB;
    std::vector<std::vector<Job>> matrizJob;
    std::vector<std::vector<int>> jobsAlocados;
    int custo_fixo; // p

    lerArquivo(nomeArquivo, arrayB, matrizJob, custo_fixo);

    std::cout << "Capacidades:" << std::endl;
    for (int val : arrayB) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Realiza o algoritmo guloso
    atualizarRazaoTotal(matrizJob);
    std::sort(matrizJob.begin(), matrizJob.end(), [](const std::vector<Job>& a, const std::vector<Job>& b) {
        return a[0].razao_total < b[0].razao_total;
    });
    std::sort(matrizJob[0].begin(), matrizJob[0].end(), [](const Job& a, const Job& b) {
        return a.razao < b.razao;
    });
    permutarColunas(matrizJob);
    preencherMatriz(matrizJob, arrayB, jobsAlocados);

    // Realiza a operação de troca para explorar a vizinhança
    swap(matrizJob, jobsAlocados, custo_fixo);
    
    // Imprime o resultado
    imprimirMatriz(matrizJob);
    std::cout << std::endl;
    imprimirMatrizInt(jobsAlocados);

    return 0;
}
