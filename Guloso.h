#ifndef GULOSO_H
#define GULOSO_H

#include <vector>

struct Job;

void atualizarRazaoTotal(std::vector<std::vector<Job>>& matriz);
void permutarColunas(std::vector<std::vector<Job>>& matriz);
void preencherMatriz(std::vector<std::vector<Job>>& matriz, const std::vector<int>& capacidades, std::vector<std::vector<int>>& jobsAlocados);
void igualarLinhas(std::vector<std::vector<Job>>& matriz);

#endif // GULOSO_H
