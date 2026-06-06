/*
 * Nombre:   Jorge Leal Cornejo
 * Matricula: ES251115052
 * Grupo:  DS-DIIS-2601-B2-002
 * Actividad: DIIS_U3_AC_JOLC - Calculadora de Salud Nutricional (IMC)
 */

#include <stdio.h>

#include "imc_core.h"

static void mostrar_encabezado(void) {
    printf("=== Calculadora de Salud Nutricional (IMC) ===\n\n");
    printf("Nombre:   Jorge Leal Cornejo\n");
    printf("Matricula: ES251115052\n");
    printf("Grupo:    DS-DIIS-2601-B2-002\n");
    printf("Actividad: DIIS_U3_AC_JOLC\n\n");
}

static void mostrar_menu(void) {
    printf("Menu:\n");
    printf("  1. Calcular IMC\n");
    printf("  2. Salir\n");
    printf("Seleccione una opcion: ");
}

static int leer_opcion_menu(void) {
    int opcion = 0;
    if (scanf("%d", &opcion) != 1) {
        return -1;
    }
    return opcion;
}

static int leer_flotante_positivo(const char *etiqueta, float *valor) {
    printf("%s", etiqueta);
    if (scanf("%f", valor) != 1) {
        printf("Error: ingrese un valor numerico valido.\n");
        return 0;
    }
    if (*valor <= 0.0f) {
        printf("Error: el valor debe ser mayor que cero.\n");
        return 0;
    }
    return 1;
}

static int ejecutar_calculo(void) {
    float peso_kg = 0.0f;
    float estatura_m = 0.0f;
    float imc = 0.0f;
    ImcClasificacion resultado;

    if (!leer_flotante_positivo("Ingrese el peso en kilogramos (kg): ", &peso_kg)) {
        return 0;
    }

    if (!leer_flotante_positivo("Ingrese la estatura en metros (m): ", &estatura_m)) {
        return 0;
    }

    if (!imc_validar_entrada(peso_kg, estatura_m)) {
        printf("Error: el valor debe ser mayor que cero.\n");
        return 0;
    }

    imc = imc_calcular(peso_kg, estatura_m);
    resultado = imc_clasificar(imc);

    printf("\n--- Resultado ---\n");
    printf("IMC: %.2f\n", imc);
    printf("Categoria: %s\n", imc_nombre_categoria(resultado.categoria));

    if (resultado.requiere_alerta) {
        printf("\nALERTA: El resultado indica un posible riesgo para la salud.\n");
        printf("Consulte a un profesional de la salud para una evaluacion adecuada.\n");
    }

    printf("\n");
    return 1;
}

static void limpiar_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void) {
    int opcion = 0;
    int continuar = 1;

    mostrar_encabezado();

    while (continuar) {
        mostrar_menu();

        opcion = leer_opcion_menu();
        if (opcion == -1) {
            printf("Error: ingrese una opcion valida.\n\n");
            limpiar_entrada();
            continue;
        }

        switch (opcion) {
            case 1:
                ejecutar_calculo();
                break;
            case 2:
                printf("Gracias por usar la calculadora. Hasta luego.\n");
                continuar = 0;
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n\n");
                break;
        }
    }

    return 0;
}
