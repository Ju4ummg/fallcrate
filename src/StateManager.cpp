#include "StateManager.hpp"
#include <fstream>
#include <stdexcept>
#include <sstream>
using namespace std;
namespace fs = filesystem;

StateManager::StateManager(const filesystem::path& caminhoReferencia) : caminhoReferencia(caminhoReferencia) {}

bool StateManager::referenciaExiste() const {
    return fs::exists(this->caminhoReferencia);
}

bool StateManager::salvarEstado(const unordered_map<string, string>& estado) const {
    ofstream arquivo(this->caminhoReferencia, ios::trunc);

    if (!arquivo.is_open()) {
        return false;
    }

    for (const auto& [caminho, hash] : estado) {
        arquivo << caminho << "|" << hash << "\n";
    }

    arquivo.close();
    return true;
}

unordered_map<string, string> StateManager::carregarEstado() const {
    unordered_map<string, string> estado;
    ifstream arquivo(this->caminhoReferencia);

    if (!arquivo.is_open()) {
        throw runtime_error("Não foi possível abrir o arquivo de referência.");
    }

    string linha;
    while (getline(arquivo, linha)) {
        size_t separador = linha.find('|');
        if (separador == string::npos) {
            continue;
        }

        string caminho = linha.substr(0, separador);
        string hash = linha.substr(separador + 1);
        estado[caminho] = hash;
    }

    return estado;
}
