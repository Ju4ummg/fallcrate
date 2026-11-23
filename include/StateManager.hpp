#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

class StateManager {
private:
    std::filesystem::path caminhoReferencia;

public:
    //recebe o caminho onde o arquivo de referência (ex: referencia.json) será salvo/lido
    explicit StateManager(const std::filesystem::path& caminhoReferencia);

    //verifica se já existe uma referência salva anteriormente
    bool referenciaExiste() const;

    //grava o mapa (caminho -> hash) no disco; retorna true se der certo
    bool salvarEstado(const std::unordered_map<std::string, std::string>& estado) const;

    //lê o arquivo do disco e reconstrói o mapa (caminho -> hash) na memória
    std::unordered_map<std::string, std::string> carregarEstado() const;
};