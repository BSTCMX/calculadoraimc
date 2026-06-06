#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT_DIR="$ROOT/web/wasm"

mkdir -p "$OUT_DIR"

emcc "$ROOT/src/imc_core.c" "$ROOT/src/imc_wasm.c" \
  -o "$OUT_DIR/imc.js" \
  -s WASM=1 \
  -s EXPORT_ES6=1 \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=createImcModule \
  -s EXPORTED_FUNCTIONS='["_wasm_validar","_wasm_calcular","_wasm_categoria","_wasm_requiere_alerta"]' \
  -s EXPORTED_RUNTIME_METHODS='["cwrap"]' \
  -O2

echo "WASM generado en $OUT_DIR"
