#!/bin/bash

# Diretório onde estão os ficheiros
TEST_DIR="."

# Lista de ficheiros .dgo na pasta
FILES=($(ls "$TEST_DIR"/*.dgo 2>/dev/null))

# Caminho para o executável do gocompiler
GOCOMPILER="../gocompiler_245/gocompiler"

# Contador para acompanhar o progresso
INDEX=0

echo "Iniciando os testes... Pressione Enter para executar o próximo teste."
while [ $INDEX -lt ${#FILES[@]} ]; do
    DGO_FILE="${FILES[$INDEX]}"
    OUT_FILE="${DGO_FILE%.dgo}.out"

    echo "Executando teste: $DGO_FILE"
    if [ -f "$OUT_FILE" ]; then
        # Usar sort apenas se o nome do arquivo contiver "errors"
        if [[ "$DGO_FILE" == *errors* ]]; then
            $GOCOMPILER -s < "$DGO_FILE" | sort | diff "$OUT_FILE" -
        else
            $GOCOMPILER -s < "$DGO_FILE" | diff "$OUT_FILE" -
        fi
    else
        echo "Aviso: Arquivo correspondente .out não encontrado para $DGO_FILE"
    fi

    # Aguardar Enter antes de continuar
    read -p "Pressione Enter para o próximo teste..." -r

    # Incrementar índice para o próximo ficheiro
    INDEX=$((INDEX + 1))
done

echo "Todos os testes foram executados."
