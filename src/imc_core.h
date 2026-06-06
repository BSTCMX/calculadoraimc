#ifndef IMC_CORE_H
#define IMC_CORE_H

typedef enum {
    IMC_CAT_BAJO_PESO = 0,
    IMC_CAT_PESO_NORMAL = 1,
    IMC_CAT_SOBREPESO = 2,
    IMC_CAT_OBESIDAD = 3
} ImcCategoria;

typedef struct {
    ImcCategoria categoria;
    int requiere_alerta;
} ImcClasificacion;

int imc_validar_entrada(float peso_kg, float estatura_m);
float imc_calcular(float peso_kg, float estatura_m);
ImcClasificacion imc_clasificar(float imc);
const char *imc_nombre_categoria(ImcCategoria categoria);

#endif
