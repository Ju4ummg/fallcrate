#pragma once

#include <filesystem>
#include <string>

class Logger {
private:
    std::filesystem::path caminhoLog;

public:
    explicit Logger(const std::filesystem::path& caminhoLog);

    void registrar(const std::string& mensagem) const;
};
