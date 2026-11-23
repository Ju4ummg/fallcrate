#pragma once
#include <cstddef>
#include <filesystem>
#include <string>

class Hasher {
private:
    //tamanho do bloco de leitura (4 KB) para não sobrecarregar a RAM em arquivos grandes
    static constexpr std::size_t TAMANHO_BUFFER = 4096;

public:
    Hasher() = default;

    //calcula e retorna o hash MD5 em texto hexadecimal de um arquivo
    std::string calcularMD5 (const std::filesystem::path& caminhoArquivo) const;
};