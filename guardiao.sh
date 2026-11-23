#!/bin/bash

PROGRAMA="./fallcrate"

if [ ! -f "$PROGRAMA" ]; then
    echo "Erro: o executável '$PROGRAMA' não foi encontrado."
    echo "Execute 'make' para compilar a aplicação."
    exit 2
fi

if [ $# -lt 2 ]; then
    echo "Uso: $0 <cadastrar|verificar> <diretorio>"
    exit 2
fi

COMANDO="$1"
DIRETORIO="$2"

echo "============================================"
echo "       FallCrate - Guardião de Arquivos"
echo "============================================"
echo ""

case "$COMANDO" in
    cadastrar)
        echo "Iniciando cadastro da referência..."
        echo ""
        $PROGRAMA cadastrar "$DIRETORIO"
        resultado=$?

        echo ""
        case "$resultado" in
            0)
                echo "[OK] Referência cadastrada com sucesso."
                ;;
            *)
                echo "[ERRO] Falha durante o cadastro."
                exit 2
                ;;
        esac
        ;;

    verificar)
        echo "Iniciando verificação de integridade..."
        echo ""
        $PROGRAMA verificar "$DIRETORIO"
        resultado=$?

        echo ""
        case "$resultado" in
            0)
                echo "[OK] Nenhuma alteração detectada."
                ;;
            1)
                echo "[ALERTA] Alterações detectadas nos arquivos!"
                ;;
            *)
                echo "[ERRO] Falha durante a verificação."
                exit 2
                ;;
        esac
        ;;

    *)
        echo "Erro: comando desconhecido '$COMANDO'."
        echo "Comandos disponíveis: cadastrar, verificar"
        exit 2
        ;;
esac

echo ""
echo "============================================"
exit $resultado
