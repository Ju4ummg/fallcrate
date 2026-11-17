#pragma once

#include <filesystem>
#include <vector>

class Scanner {
private:
    std::filesystem::path diretorioAlvo;
    bool recursivo;

public:
    //define o diretório a ser monitorado e se a varredura entra em subpastas
    explicit Scanner(const std::filesystem::path& diretorioAlvo, bool recursivo = true);

    //percorre o diretório e retorna apenas arquivos regulares (ignora pastas)
    std::vector<std::filesystem::path> listarArquivos() const;
};