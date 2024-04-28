#include <unordered_map>
#include "Job.h"

int encontrarCusto(const std::vector<std::vector<Job>>& matriz, int valor, int index) {
    // Iterar sobre cada linha da matriz
    for (size_t j = 0; j < matriz[index].size(); ++j) {
        // Se o valor for encontrado, retornar as coordenadas (i, j)
        if (matriz[index][j].id == valor) {
            return matriz[index][j].custo;
        }
    }
    return -1;
}

int calcularCustoTotal(const std::vector<std::vector<Job>>& matriz,
                     const std::vector<std::vector<Job>>& alocados, int p) {
  int somaCusto = 0;
  int totalElementos = 0;

  // Count allocated elements and print
  for (const auto& linha : alocados) {
    totalElementos += linha.size();
  }
  std::cout << "** Total allocated elements: " << totalElementos << " **" << std::endl;

  // Calculate penalty for unallocated elements and print
  somaCusto += (matriz[0].size() - totalElementos) * p;
  std::cout << "** Penalty for unallocated elements: " << (matriz[0].size() - totalElementos) * p << " **" << std::endl;

  // Iterate through allocated jobs and calculate processing time
  for (int i = 0; i < alocados.size(); ++i) {
    for (int j = 0; j < alocados[i].size(); ++j) {
      int custoJob = encontrarCusto(matriz, alocados[i][j].id, i);
      somaCusto += custoJob;
      std::cout << "  - Server " << i << ", Job " << j << ": Processing Time = " << custoJob << std::endl;
      // Check for potential errors from encontrarCusto (replace -1 with appropriate error value)
      if (custoJob == -1) {
          std::cerr << "Error: Job " << alocados[i][j].id << " not found in server " << i << std::endl;
      }
    }
  }

  return somaCusto;
}

void lerArquivo(const std::string& nomeArquivo, std::vector<int>& capacidades, std::vector<std::vector<Job>>& matrizJob, int& p) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        exit(1);
    }

    int n, m;
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
            matrizJob[i][j].somaCustoTempo = matrizJob[0][j].custo + matrizJob[0][j].tempo_processamento;
        }
    }

    arquivo.close();
}