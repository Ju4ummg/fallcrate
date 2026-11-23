#include "Comparator.hpp"
using namespace std;

ResultadoVerificacao Comparator::comparar(
    const unordered_map<string, string>& estadoAnterior,
    const unordered_map<string, string>& estadoAtual) const {

    ResultadoVerificacao resultado;
    resultado.totalAnalisados = estadoAtual.size();

    for (const auto& [caminho, hashAtual] : estadoAtual) {
        auto it = estadoAnterior.find(caminho);

        if (it == estadoAnterior.end()) {
            resultado.novos.push_back(caminho);

        } else if (it->second != hashAtual) {
            resultado.modificados.push_back(caminho);
        }
    }

    for (const auto& [caminho, hashAnterior] : estadoAnterior) {
        if (estadoAtual.find(caminho) == estadoAtual.end()) {
            resultado.removidos.push_back(caminho);
        }
    }

    return resultado;
}
