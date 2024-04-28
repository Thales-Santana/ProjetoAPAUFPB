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

    for (const auto& linha : alocados) {
        totalElementos += linha.size();
    }

    // Penaliza por elementos não alocados
    somaCusto += (matriz[0].size() - totalElementos) * p;
    for (int i = 0; i < alocados.size(); ++i) {
        for (int j = 0; j < alocados[i].size(); ++j) {
            somaCusto += encontrarCusto(matriz, alocados[i][j].id, i);
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
        }
    }

    arquivo.close();
}

bool encontrarNoVetor(const std::vector<int>& vetor, int x) {
    // Verifica se o vetor está vazio
    if (vetor.empty()) {
        return false;
    }

    // Percorre cada elemento do vetor
    for (int elemento : vetor) {
        // Compara o elemento atual com o valor buscado
        if (elemento == x) {
            return true; // Valor encontrado!
        }
    }

    // Valor não encontrado
    return false;
}

void alocarJobs(std::vector<std::vector<Job>>& matriz, const std::vector<int>& capacidades, std::vector<std::vector<Job>>& jobsAlocados){
    int num_linhas = matriz.size();
    int num_colunas = matriz[0].size();
    std::vector<int> vetor_aux;
    jobsAlocados.resize(num_linhas);
    bool existe_no_vetor;

    for (int i = 0; i < num_linhas; ++i) {
        int capacidade_atual = capacidades[i];
        for (int j = 0; j < num_colunas; ++j) {
            existe_no_vetor = encontrarNoVetor(vetor_aux, matriz[i][j].id);
            if (matriz[i][j].tempo_processamento <= capacidade_atual && !existe_no_vetor) {
                capacidade_atual -= matriz[i][j].tempo_processamento;
                jobsAlocados[i].push_back(matriz[i][j]);
                vetor_aux.push_back(matriz[i][j].id);
            }
        }
    }
}
