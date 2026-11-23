# FallCrate

A aplicação FallCrate foi desenvolvida para a disciplina de Sistemas Operacionais da Universidade Tecnológica Federal do Paraná, ministrada pelo Prof. Dr. Rodrigo Hübner.

## Resumo da aplicação

A aplicação funciona como um "guardião de arquivos": monitora a integridade de um diretório especificado pelo usuário, detectando arquivos modificados, novos e removidos por meio de hashes criptográficos MD5.

## Funcionalidades

- **Cadastro da referência inicial:** percorre os arquivos de um diretório (incluindo subpastas) e armazena seus caminhos relativos e hashes MD5.
- **Verificação de integridade:** compara os arquivos atuais com a referência previamente armazenada.
- **Identificação de alterações:** detecta arquivos modificados, novos e removidos.
- **Geração de relatórios:** apresenta os resultados da verificação de maneira organizada, listando os arquivos afetados.
- **Registro de eventos:** mantém um log das verificações realizadas, incluindo data, horário e resultado.
- **Tratamento de erros:** identifica diretórios inexistentes, caminhos inválidos e falhas na execução.
- **Interoperabilidade com Shell Script:** script `guardiao.sh` automatiza a execução e interpreta os códigos de saída.

## Compilação

Requisitos: `g++` com suporte a C++17 e `libssl-dev` (OpenSSL).

```bash
# Instalar dependência (Debian/Ubuntu)
sudo apt install libssl-dev

# Compilar
make
```

## Execução

### Uso direto

```bash
# Cadastrar referência inicial
./fallcrate cadastrar ./meu_diretorio

# Verificar integridade
./fallcrate verificar ./meu_diretorio
```

### Uso via Shell Script

```bash
# Cadastrar
./guardiao.sh cadastrar ./meu_diretorio

# Verificar
./guardiao.sh verificar ./meu_diretorio
```

## Códigos de saída

| Código | Significado                       |
|--------|-----------------------------------|
| 0      | Execução concluída sem alterações |
| 1      | Alterações detectadas             |
| 2      | Erro durante a execução           |

## Arquivos gerados

- `.fallcrate_ref` — Arquivo de referência com os hashes, salvo dentro do diretório monitorado.
- `.fallcrate_log` — Log de eventos com data/hora de cada operação.

## Testes

```bash
# Criar diretório de teste
mkdir -p /tmp/teste
echo "conteudo" > /tmp/teste/arquivo.txt

# Cadastrar referência
./fallcrate cadastrar /tmp/teste

# Verificar sem alterações (código 0)
./fallcrate verificar /tmp/teste

# Modificar arquivo e verificar novamente (código 1)
echo "modificado" > /tmp/teste/arquivo.txt
./fallcrate verificar /tmp/teste

# Adicionar arquivo novo e verificar
echo "novo" > /tmp/teste/novo.txt
./fallcrate verificar /tmp/teste

# Remover arquivo e verificar
rm /tmp/teste/arquivo.txt
./fallcrate verificar /tmp/teste
```
