#ifndef GULOSO_H
#define GULOSO_H

#include <vector>

struct Job;

void preencherMatriz(std::vector<std::vector<Job>>& matriz, const std::vector<int>& capacidades, std::vector<std::vector<Job>>& jobsAlocados);

#endif // GULOSO_H
