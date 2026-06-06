#include <emscripten/emscripten.h>

#include "imc_core.h"

EMSCRIPTEN_KEEPALIVE
int wasm_validar(float peso_kg, float estatura_m) {
    return imc_validar_entrada(peso_kg, estatura_m);
}

EMSCRIPTEN_KEEPALIVE
float wasm_calcular(float peso_kg, float estatura_m) {
    return imc_calcular(peso_kg, estatura_m);
}

EMSCRIPTEN_KEEPALIVE
int wasm_categoria(float imc) {
    return (int)imc_clasificar(imc).categoria;
}

EMSCRIPTEN_KEEPALIVE
int wasm_requiere_alerta(float imc) {
    return imc_clasificar(imc).requiere_alerta;
}
