#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct ResultadoVerificacao {
    std::vector<std::string> modificados;
    std::vector<std::string> novos;
    std::vector<std::string> removidos;
    int totalAnalisados;
};

class Comparator {
public:
    Comparator() = default;

    ResultadoVerificacao comparar(
        const std::unordered_map<std::string, std::string>& estadoAnterior,
        const std::unordered_map<std::string, std::string>& estadoAtual) const;
};
