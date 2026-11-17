#include <stdexcept>
#include <Scanner.hpp>
using namespace std;
namespace fs = filesystem;


Scanner::Scanner(const filesystem::path& diretorioAlvo, bool recursivo) : diretorioAlvo(diretorioAlvo), recursivo(recursivo){
    //verificações do caminho do diretório
    if (!fs::exists(this->diretorioAlvo)){
        throw invalid_argument("Diretório não existe!");
    
    }else if ((!fs::is_directory(this->diretorioAlvo))){
        throw invalid_argument("O caminho passado não é um diretório!");
    }

};

vector<filesystem::path> Scanner::listarArquivos() const{
    vector<filesystem::path> arquivos;
    
    for (auto const& arquivo : filesystem::recursive_directory_iterator(this->diretorioAlvo)){
        //caso o arquivo encontrado for um arquivo adiciona no vetor de arquivos
        if (arquivo.is_regular_file()){
            arquivos.push_back(fs::path(arquivo));
        }
    }

    return arquivos;
}