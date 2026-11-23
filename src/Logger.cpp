#include "Logger.hpp"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;

Logger::Logger(const filesystem::path& caminhoLog) : caminhoLog(caminhoLog) {}

void Logger::registrar(const string& mensagem) const {
    ofstream arquivo(this->caminhoLog, ios::app);

    if (!arquivo.is_open()) {
        return;
    }

    auto agora = chrono::system_clock::now();
    auto tempo = chrono::system_clock::to_time_t(agora);
    tm tempoLocal;
    localtime_r(&tempo, &tempoLocal);

    ostringstream oss;
    oss << put_time(&tempoLocal, "%d/%m/%Y %H:%M:%S");

    arquivo << "[" << oss.str() << "] " << mensagem << "\n";
}
