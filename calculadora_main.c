// Aluno: Érico Chen
// Q1 - 30/08/2024 - 18:05
// Q2 - 30/08/2024 - 18:15
// Q2 modificacao - 30/08/2024 - 18:20
// Q3 - 30/08/2024 - 18:30

#include <stdio.h>
#include <math.h>

void intToBinary(int number);
void intToOctal(int number);
void intToHex(int number);
void intToBCD(int number);
void mostrarBinario(unsigned short valor);
void decimalParaComplemento2(int number);
void printFloatBits(float number);
void printDoubleBits(double number);

int main(){
    int number, number_1;
    float float_number;
    double double_number;

    printf("\nDigite o número decimal(-32768 a 32767) para conversão: ");
    scanf("%d", &number);
     
    intToBinary(number);
    intToOctal(number);
    intToHex(number);
    intToBCD(number);

    printf("\nDigite o número decimal(-32768 a 32767) para complemento a 2: ");
    scanf("%d", &number_1);
    decimalParaComplemento2(number_1);

    printf("\nDigite um número real decimal para float: ");
    scanf("%f", &float_number);

    printFloatBits(float_number);

    printf("\nDigite um número real decimal para double: ");
    scanf("%lf", &double_number);

    printDoubleBits(double_number);

    return 0;
}

void intToBinary(int number){
    int binario[32];
    int i = 0;
    int aux_1 = number;
    int aux_2 = number;
    printf("\nConvertendo %d(base 10) para binário:", number);
    while(number>0){
        binario[i] = number%2;
        aux_2 = number/2;
        printf("\n%d/2 = %d | Resto = %d", number, aux_2, binario[i]);
        number = number / 2;
        i++;
    }
    printf("\nO número %d (base 10) em binário: ", aux_1);
    for(int x = i - 1; x>=0; x--){
        printf("%d", binario[x]);
    }
    printf("\n");
}

void intToOctal(int number){
    int octal[32];
    int i = 0;
    int aux_1 = number;
    int aux_2 = number;
    printf("\nConvertendo %d(base 10) para octal:", number);
    while(number>0){
        octal[i] = number%8;
        aux_2 = number/8;
        printf("\n%d/8 = %d | Resto = %d", number, aux_2, octal[i]);
        number = number / 8;
        i++;
    }
    printf("\nO número %d (base 10) em octal: ", aux_1);
    for(int x = i - 1; x>=0; x--){
        printf("%d", octal[x]);
    }
    printf("\n");
}

void intToHex(int number){
    int hex[32];
    int i = 0;
    int aux_1 = number;
    int aux_2 = number;
    printf("\nConvertendo %d(base 10) para hexadecimal:", number);
    while(number>0){
        hex[i] = number%16;
        aux_2 = number/16;
        int resto = number % 16;
        if (resto < 10) {
            hex[i] = 48 + resto;
        } else {
            hex[i] = 55 + resto;
        }
        printf("\n%d/8 = %d | Resto = %d", number, aux_2, hex[i]);
        number = number / 16;
        i++;
    }
    printf("\nConvertendo o valor do resto na tabela ASCII...");
    printf("\nO número %d (base 10) em hexadecimal: ", aux_1);
    for(int x = i - 1; x>=0; x--){
        printf("%c", hex[x]);
    }
    printf("\n");
}

void intToBCD(int number){
    if (number < 0) {
        printf("Número inválido. Digite um número inteiro não negativo.\n");
        return;
    }

    printf("\nPassos da conversão para BCD:\n"); 
    while (number > 0) {
        int digito = number % 10;
        printf("Dígito: %d -> ", digito);

        // Converte o dígito para BCD (4 bits)
        for (int i = 3; i >= 0; i--) {
            printf("%d", (digito >> i) & 1);
        }
        printf("\n");

        number = number / 10;
    }
    printf("\n");
}

void mostrarBinario(unsigned short valor) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (valor >> i) & 1);
    }
    printf("\n");
}


void decimalParaComplemento2(int number) {
    unsigned short valor;
    if (number < -32768 || number > 32767) {
        printf("Número fora do intervalo de 16 bits com sinal.\n");
        return;
    }

    printf("Número decimal: %d\n", number);
    
    if (number >= 0) {
        valor = (unsigned short)number;
        printf("Representação binária direta (para números positivos): ");
        mostrarBinario(valor);
    } else {
        printf("Passos para calcular o complemento a 2 para o número negativo:\n");
        int numPositivo = -number;
        printf("Número positivo correspondente: %d\n", numPositivo);

        unsigned short binarioPositivo = (unsigned short)numPositivo;
        printf("Representação binária do número positivo: ");
        mostrarBinario(binarioPositivo);

        unsigned short invertido = ~binarioPositivo;
        printf("Bits invertidos: ");
        mostrarBinario(invertido);

        valor = invertido + 1;
        printf("Complemento a 2 (invertido + 1): ");
        mostrarBinario(valor);
    }

    printf("Representação final em complemento a 2 de 16 bits: ");
    mostrarBinario(valor);
}

void printFloatBits(float number) {
    unsigned int* p = (unsigned int*)&number;
    unsigned int bits = *p;

    
    printf("Float: %f\n", number);
    printf("Bits: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);
    }
    printf("\n");

    
    int sinal = (bits >> 31) & 1;
    printf("Bit de Sinal: %d\n", sinal);

    int expoente = ((bits >> 23) & 0xFF) - 127;
    printf("Expoente com viés: %d\n", expoente + 127);
    printf("Expoente (com viés subtraído): %d\n", expoente);

    unsigned int frac = bits & 0x7FFFFF;
    printf("Fração: ");
    for (int i = 22; i >= 0; i--) {
        printf("%d", (frac >> i) & 1);
    }
    printf("\n");
}
void printDoubleBits(double number) {
    unsigned long long* p = (unsigned long long*)&number;
    unsigned long long bits = *p;

    printf("Double: %lf\n", number);
    printf("Bits: ");
    for (int i = 63; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);
    }
    printf("\n");

    int sinal = (bits >> 63) & 1;
    printf("Bit de Sinal: %d\n", sinal);

    int expoente = ((bits >> 52) & 0x7FF) - 1023;
    printf("Expoente com viés: %d\n", expoente + 1023);
    printf("Expoente (com viés subtraído): %d\n", expoente);

    unsigned long long frac = bits & 0xFFFFFFFFFFFFF;
    printf("Fração: ");
    for (int i = 51; i >= 0; i--) {
        printf("%d", (frac >> i) & 1);
    }
    printf("\n");
}