#!/bin/bash

# Diretório onde estão os ficheiros
TEST_DIR="."

# Lista de ficheiros .dgo na pasta
FILES=($(ls "$TEST_DIR"/*.dgo 2>/dev/null))

# Caminho para o executável do gocompiler
GOCOMPILER="../gocompiler/gocompiler"

# Contador para acompanhar o progresso
INDEX=0

echo "Iniciando os testes... Pressione Enter para executar o próximo teste."
while [ $INDEX -lt ${#FILES[@]} ]; do
    DGO_FILE="${FILES[$INDEX]}"
    OUT_FILE="${DGO_FILE%.dgo}.out"
    LL_FILE="${DGO_FILE%.dgo}.ll"

    echo "Executando teste: $DGO_FILE"
    
    # Gerar o código LLVM com o gocompiler
    $GOCOMPILER < "$DGO_FILE" > "$LL_FILE"

    # Verificar se o arquivo .out existe
    if [ -f "$OUT_FILE" ]; then
        # Executar o código LLVM gerado com lli e comparar com o arquivo .out
        lli "$LL_FILE" | diff "$OUT_FILE" -
    else
        echo "Aviso: Arquivo correspondente .out não encontrado para $DGO_FILE"
    fi

    # Aguardar Enter antes de continuar
    read -p "Pressione Enter para o próximo teste..." -r

    # Incrementar índice para o próximo ficheiro
    INDEX=$((INDEX + 1))
done

echo "Todos os testes foram executados."
