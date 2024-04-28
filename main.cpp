#include <iostream>
#include <vector>
#include "Job.h"
#include "Guloso.h"
#include <algorithm>
#include <iomanip>
#include <limits>

void imprimirMatriz(const std::vector<std::vector<Job>> &matriz)
{
    for (const auto &linha : matriz)
    {
        for (const auto &job : linha)
        {
            std::cout << "Job(" << job.id << "): " << std::fixed << std::setprecision(2) << job.somaCustoTempo << " | " << job.tempo_processamento << " | " << job.custo << "\n";
        }
    }
}

void imprimirMatrizInt(const std::vector<std::vector<Job>> &matriz)
{
    for (int i = 0; i < matriz.size(); ++i)
    {
        for (int j = 0; j < matriz[i].size(); ++j)
        {
            std::cout << " " << matriz[i][j].id << " ";
        }
        std::cout << std::endl;
    }
}

void insertTask(std::vector<std::vector<Job>> &jobsAlocados, int server, int origin, int p)
{
    // Save the original task for later restoration
    Job originalTask = jobsAlocados[server][origin];

    // Initialize best cost and best jobs allocated (assuming positive cost)
    int bestCost = std::numeric_limits<int>::max();
    std::vector<std::vector<Job>> bestJobsAlocados = jobsAlocados;

    // Perform task insertion at all possible positions within the same server
    for (int destination = 0; destination < jobsAlocados[server].size(); ++destination)
    {
        if (destination != origin)
        {
            // Move the task to the specified destination
            std::swap(jobsAlocados[server][origin], jobsAlocados[server][destination]);

            int totalCost = calcularCustoTotal(jobsAlocados, jobsAlocados, p);

            // Update the best solution if the new cost is better
            if (totalCost < bestCost)
            {
                bestCost = totalCost;
                bestJobsAlocados = jobsAlocados;
            }

            // Revert the task insertion to explore the next position
            std::swap(jobsAlocados[server][origin], jobsAlocados[server][destination]);
        }
    }

    // Restore the original task arrangement
    jobsAlocados[server][origin] = originalTask;

    // Update the actual jobs allocated with the best solution found
    jobsAlocados = bestJobsAlocados;
}

void swap(std::vector<std::vector<Job>> &matriz, std::vector<std::vector<Job>> &jobsAlocados, int p)
{
    int num_servidores = matriz.size();
    int num_jobs = matriz[0].size();

    double melhor_custo = std::numeric_limits<double>::max(); // Inicializa com um valor grande
    std::vector<std::vector<Job>> melhores_jobsAlocados = jobsAlocados;

    // Itera através de todas as combinações possíveis de troca de dois jobs entre diferentes servidores
    for (int servidor1 = 0; servidor1 < num_servidores; ++servidor1)
    {
        for (int job1 = 0; job1 < jobsAlocados[servidor1].size(); ++job1)
        {
            for (int servidor2 = 0; servidor2 < num_servidores; ++servidor2)
            {
                for (int job2 = 0; job2 < jobsAlocados[servidor2].size(); ++job2)
                {
                    // Verifica se a troca desses jobs é viável
                    if (servidor1 != servidor2)
                    {
                        // Realiza a troca dos jobs
                        std::swap(jobsAlocados[servidor1][job1], jobsAlocados[servidor2][job2]);

                        // Calcula o custo total da nova solução
                        double custo_atual = calcularCustoTotal(matriz, jobsAlocados, p);

                        // Verifica se a nova solução é melhor do que a melhor encontrada até agora
                        if (custo_atual < melhor_custo)
                        {
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

int main()
{
    std::string nomeArquivo = "file.txt";

    std::vector<int> arrayB;
    std::vector<std::vector<Job>> matrizJob;
    std::vector<std::vector<Job>> jobsAlocados;
    int custo_fixo; // p

    lerArquivo(nomeArquivo, arrayB, matrizJob, custo_fixo);

    std::cout << "Capacidades:" << std::endl;
    for (int val : arrayB)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    preencherMatriz(matrizJob, arrayB, jobsAlocados);

    // Realiza a operação de troca para explorar a vizinhança
    swap(matrizJob, jobsAlocados, custo_fixo);

    // Print results after swap
    imprimirMatriz(matrizJob);
    std::cout << std::endl;
    imprimirMatrizInt(jobsAlocados);
    std::cout << std::endl;
    int costAfterSwap = calcularCustoTotal(matrizJob, jobsAlocados, custo_fixo);

    for (int server = 0; server < jobsAlocados.size(); ++server)
    {
        for (int origin = 0; origin < jobsAlocados[server].size(); ++origin)
        {
            insertTask(jobsAlocados, server, origin, custo_fixo);
        }
    }

    // Print results after insertion exploration
    imprimirMatriz(matrizJob);
    std::cout << std::endl;
    imprimirMatrizInt(jobsAlocados);
    std::cout << std::endl;
    int costAfterInsertion = calcularCustoTotal(matrizJob, jobsAlocados, custo_fixo);
    std::cout << "Custo after insertion exploration:" << costAfterInsertion << std::endl;

    // Compare and print best result
    std::cout << "** Best Cost: **" << (costAfterSwap < costAfterInsertion ? costAfterSwap : costAfterInsertion) << std::endl;

    return 0;
}
