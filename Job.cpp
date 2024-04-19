#include "Job.h"

void lerArquivo(const std::string& nomeArquivo, std::vector<int>& capacidades, std::vector<std::vector<Job>>& matrizJob) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        exit(1);
    }

    int n, m, p;
    arquivo >> n >> m >> p;

    capacidades.resize(m);
    for (int i = 0; i < m; ++i) {
        if (!(arquivo >> capacidades[i])) {
            std::cerr << "Erro ao ler a capacidade " << i + 1 << " do vetor." << std::endl;
            exit(1);
        }
    }

    matrizJob.resize(m, std::vector<Job>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizJob[i][j].id = j + 1;
            if (!(arquivo >> matrizJob[i][j].tempo_processamento)) {
                std::cerr << "Erro ao ler a matriz na posição (" << i + 1 << ", " << j + 1 << ")." << std::endl;
                exit(1);
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(arquivo >> matrizJob[i][j].custo)) {
                std::cerr << "Erro ao ler a matriz na posição (" << i + 1 << ", " << j + 1 << ")." << std::endl;
                exit(1);
            }
            matrizJob[i][j].razao = static_cast<double>(matrizJob[i][j].custo) / static_cast<double>(matrizJob[i][j].tempo_processamento);
        }
    }

    arquivo.close();
}
