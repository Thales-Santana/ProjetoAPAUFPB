#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include "Job.h"
#include "Guloso.h"

void imprimirMatriz(const std::vector<std::vector<Job>>& matriz);
void imprimirMatrizInt(const std::vector<std::vector<int>>& matriz);
void lerArquivo(const std::string& nomeArquivo, std::vector<int>& capacidades, std::vector<std::vector<Job>>& matrizJob);

#endif // MAIN_H
