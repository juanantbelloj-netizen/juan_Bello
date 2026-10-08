#include <stdio.h>

#define TOLERANCIA     1e-12   /* precisión relativa del resultado          */
#define MAX_ITERACIONES 2000   /* tope de seguridad para el ciclo           */

/* ---------- Funciones auxiliares ---------- */

static double valor_absoluto(double x)
{
    return (x < 0) ? -x : x;
}

/* Eleva un número al cuadrado: x^2 */
static double elevar_al_cuadrado(double x)
{
    return x * x;
}

/*
 * Raíz cuadrada con el método babilónico (Newton-Raphson), sin usar math.h.
 *
 * Idea: si x es una estimación de raíz(n), entonces n/x está al otro lado
 * de la raíz. El promedio de ambos es una mejor estimación:
 *
 *        x_nuevo = (x + n / x) / 2
 *
 * Se repite hasta que la diferencia entre dos estimaciones sucesivas
 * sea menor que la tolerancia.
 *
 * Devuelve 0 si el cálculo es válido y -1 si n es negativo.
 */
static int raiz_cuadrada(double n, double *resultado)
{
    if (n < 0) {
        return -1;              /* no existe raíz real de un negativo */
    }
    if (n == 0) {
        *resultado = 0;
        return 0;
    }

    double x = (n >= 1) ? n / 2 : 1;   /* estimación inicial */
    double x_nuevo;
    int i;

    for (i = 0; i < MAX_ITERACIONES; i++) {
        x_nuevo = (x + n / x) / 2;
        if (valor_absoluto(x_nuevo - x) <= TOLERANCIA * x_nuevo) {
            x = x_nuevo;
            break;
        }
        x = x_nuevo;
    }

    *resultado = x;
    return 0;
}

/* ---------- Entrada de datos ---------- */

static void limpiar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static double leer_numero(const char *mensaje)
{
    double valor;
    printf("%s", mensaje);
    while (scanf("%lf", &valor) != 1) {
        limpiar_buffer();
        printf("Entrada invalida. %s", mensaje);
    }
    return valor;
}

static void mostrar_menu(void)
{
    printf("\n========== CALCULADORA ==========\n");
    printf(" 1. Suma\n");
    printf(" 2. Resta\n");
    printf(" 3. Multiplicacion\n");
    printf(" 4. Division\n");
    printf(" 5. Elevar al cuadrado (x^2)\n");
    printf(" 6. Raiz cuadrada (algoritmo de Newton)\n");
    printf(" 0. Salir\n");
    printf("=================================\n");
    printf("Opcion: ");
}

/* ---------- Programa principal ---------- */

int main(void)
{
    int opcion;
    double a, b, r;

    do {
        mostrar_menu();
        if (scanf("%d", &opcion) != 1) {
            limpiar_buffer();
            printf("Opcion invalida.\n");
            opcion = -1;
            continue;
        }

        switch (opcion) {
        case 1:
            a = leer_numero("Primer numero: ");
            b = leer_numero("Segundo numero: ");
            printf("Resultado: %g + %g = %g\n", a, b, a + b);
            break;

        case 2:
            a = leer_numero("Primer numero: ");
            b = leer_numero("Segundo numero: ");
            printf("Resultado: %g - %g = %g\n", a, b, a - b);
            break;

        case 3:
            a = leer_numero("Primer numero: ");
            b = leer_numero("Segundo numero: ");
            printf("Resultado: %g * %g = %g\n", a, b, a * b);
            break;

        case 4:
            a = leer_numero("Dividendo: ");
            b = leer_numero("Divisor: ");
            if (b == 0) {
                printf("Error: no se puede dividir entre cero.\n");
            } else {
                printf("Resultado: %g / %g = %g\n", a, b, a / b);
            }
            break;

        case 5:
            a = leer_numero("Numero: ");
            printf("Resultado: %g^2 = %g\n", a, elevar_al_cuadrado(a));
            break;

        case 6:
            a = leer_numero("Numero: ");
            if (raiz_cuadrada(a, &r) != 0) {
                printf("Error: no existe raiz cuadrada real de un numero negativo.\n");
            } else {
                printf("Resultado: raiz(%g) = %.10g\n", a, r);
            }
            break;

        case 0:
            printf("Hasta luego.\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
