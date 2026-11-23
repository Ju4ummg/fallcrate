#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include "Scanner.hpp"
#include "Hasher.hpp"
#include "StateManager.hpp"
#include "Comparator.hpp"
#include "Logger.hpp"
using namespace std;
namespace fs = filesystem;

static const int CODIGO_OK = 0;
static const int CODIGO_ALTERACOES = 1;
static const int CODIGO_ERRO = 2;

static const string NOME_REFERENCIA = ".fallcrate_ref";
static const string NOME_LOG = ".fallcrate_log";

void exibirUso() {
    cout << "Uso: fallcrate <comando> <diretorio>" << endl;
    cout << "Comandos:" << endl;
    cout << "  cadastrar  - Cria a referência inicial dos arquivos" << endl;
    cout << "  verificar  - Verifica a integridade dos arquivos" << endl;
}

unordered_map<string, string> gerarEstadoAtual(const fs::path& diretorio) {
    Scanner scanner(diretorio);
    Hasher hasher;
    unordered_map<string, string> estado;

    auto arquivos = scanner.listarArquivos();

    for (const auto& arquivo : arquivos) {
        fs::path relativo = fs::relative(arquivo, diretorio);
        string chave = relativo.string();

        if (chave == NOME_REFERENCIA || chave == NOME_LOG) {
            continue;
        }

        estado[chave] = hasher.calcularMD5(arquivo);
    }

    return estado;
}

int executarCadastro(const fs::path& diretorio) {
    Logger logger(diretorio / NOME_LOG);
    StateManager gerenciador(diretorio / NOME_REFERENCIA);

    try {
        auto estado = gerarEstadoAtual(diretorio);

        if (!gerenciador.salvarEstado(estado)) {
            cerr << "Erro: não foi possível salvar a referência." << endl;
            logger.registrar("ERRO - Falha ao salvar referência para: " + diretorio.string());
            return CODIGO_ERRO;
        }

        cout << "Referência criada com sucesso." << endl;
        cout << "Arquivos cadastrados: " << estado.size() << endl;
        logger.registrar("CADASTRO - " + to_string(estado.size()) + " arquivos registrados em: " + diretorio.string());
        return CODIGO_OK;

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        logger.registrar("ERRO - " + string(e.what()));
        return CODIGO_ERRO;
    }
}

int executarVerificacao(const fs::path& diretorio) {
    Logger logger(diretorio / NOME_LOG);
    StateManager gerenciador(diretorio / NOME_REFERENCIA);

    try {
        if (!gerenciador.referenciaExiste()) {
            cerr << "Erro: nenhuma referência encontrada. Execute 'cadastrar' primeiro." << endl;
            logger.registrar("ERRO - Referência não encontrada para: " + diretorio.string());
            return CODIGO_ERRO;
        }

        auto estadoAnterior = gerenciador.carregarEstado();
        auto estadoAtual = gerarEstadoAtual(diretorio);

        Comparator comparador;
        auto resultado = comparador.comparar(estadoAnterior, estadoAtual);

        cout << "Verificação concluída." << endl;
        cout << "Arquivos analisados: " << resultado.totalAnalisados << endl;
        cout << "Arquivos modificados: " << resultado.modificados.size() << endl;
        cout << "Arquivos novos: " << resultado.novos.size() << endl;
        cout << "Arquivos removidos: " << resultado.removidos.size() << endl;

        if (!resultado.modificados.empty()) {
            cout << "\n--- Arquivos modificados ---" << endl;
            for (const auto& arq : resultado.modificados) {
                cout << "  " << arq << endl;
            }
        }

        if (!resultado.novos.empty()) {
            cout << "\n--- Arquivos novos ---" << endl;
            for (const auto& arq : resultado.novos) {
                cout << "  " << arq << endl;
            }
        }

        if (!resultado.removidos.empty()) {
            cout << "\n--- Arquivos removidos ---" << endl;
            for (const auto& arq : resultado.removidos) {
                cout << "  " << arq << endl;
            }
        }

        bool houveAlteracao = !resultado.modificados.empty() ||
                              !resultado.novos.empty() ||
                              !resultado.removidos.empty();

        if (houveAlteracao) {
            cout << "\nAlterações detectadas!" << endl;
            logger.registrar("VERIFICAÇÃO - Alterações detectadas em: " + diretorio.string() +
                " | Modificados: " + to_string(resultado.modificados.size()) +
                " | Novos: " + to_string(resultado.novos.size()) +
                " | Removidos: " + to_string(resultado.removidos.size()));
            return CODIGO_ALTERACOES;
        }

        cout << "\nNenhuma alteração detectada." << endl;
        logger.registrar("VERIFICAÇÃO - Nenhuma alteração em: " + diretorio.string() +
            " | Arquivos analisados: " + to_string(resultado.totalAnalisados));
        return CODIGO_OK;

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        logger.registrar("ERRO - " + string(e.what()));
        return CODIGO_ERRO;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        exibirUso();
        return CODIGO_ERRO;
    }

    string comando = argv[1];
    fs::path diretorio = fs::absolute(argv[2]);

    if (!fs::exists(diretorio)) {
        cerr << "Erro: o diretório '" << argv[2] << "' não existe." << endl;
        return CODIGO_ERRO;
    }

    if (!fs::is_directory(diretorio)) {
        cerr << "Erro: '" << argv[2] << "' não é um diretório." << endl;
        return CODIGO_ERRO;
    }

    if (comando == "cadastrar") {
        return executarCadastro(diretorio);

    } else if (comando == "verificar") {
        return executarVerificacao(diretorio);

    } else {
        cerr << "Erro: comando desconhecido '" << comando << "'." << endl;
        exibirUso();
        return CODIGO_ERRO;
    }
}
