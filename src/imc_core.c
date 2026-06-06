#include "imc_core.h"

int imc_validar_entrada(float peso_kg, float estatura_m) {
    if (peso_kg <= 0.0f || estatura_m <= 0.0f) {
        return 0;
    }
    return 1;
}

float imc_calcular(float peso_kg, float estatura_m) {
    return peso_kg / (estatura_m * estatura_m);
}

ImcClasificacion imc_clasificar(float imc) {
    if (imc < 18.5f) {
        return (ImcClasificacion){IMC_CAT_BAJO_PESO, 1};
    }
    if (imc <= 24.9f) {
        return (ImcClasificacion){IMC_CAT_PESO_NORMAL, 0};
    }
    if (imc <= 29.9f) {
        return (ImcClasificacion){IMC_CAT_SOBREPESO, 1};
    }
    return (ImcClasificacion){IMC_CAT_OBESIDAD, 1};
}

const char *imc_nombre_categoria(ImcCategoria categoria) {
    switch (categoria) {
        case IMC_CAT_BAJO_PESO:
            return "Bajo peso";
        case IMC_CAT_PESO_NORMAL:
            return "Peso normal";
        case IMC_CAT_SOBREPESO:
            return "Sobrepeso";
        case IMC_CAT_OBESIDAD:
            return "Obesidad";
        default:
            return "Desconocido";
    }
}
