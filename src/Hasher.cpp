#include "Hasher.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <fstream>
using namespace std;
namespace fs = filesystem;

string Hasher::calcularMD5(const fs::path& caminhoArquivo) const{
    std::ifstream arquivoAberto(caminhoArquivo, ios::binary);
    
    if(!arquivoAberto.is_open()){
        throw runtime_error("Não foi possível abrir o arquivo especificado.");
    }
    
    //inicializando a biblioteca openssl para calcular o md5
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);

    //realiza o hash no arquivo
    char buffer[TAMANHO_BUFFER];
    
    while (arquivoAberto.read(buffer, TAMANHO_BUFFER) || arquivoAberto.gcount() > 0){
        EVP_DigestUpdate(ctx, buffer, arquivoAberto.gcount());
    }

    //transforma o hash bruto em hexadecimal
    unsigned char hashBruto[EVP_MAX_MD_SIZE];
    unsigned int tamanhoHash = 0;

    EVP_DigestFinal_ex(ctx, hashBruto, &tamanhoHash);
    EVP_MD_CTX_free(ctx);

    ostringstream oss;
    oss << hex << std::setfill('0');

    for (unsigned int i = 0; i < tamanhoHash; ++i) {
        oss << setw(2) << static_cast<int>(hashBruto[i]);
    }

    return oss.str();
}