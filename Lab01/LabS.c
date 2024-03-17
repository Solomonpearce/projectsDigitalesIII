#include "LabS.h"


uint8_t *BitsToBytes(uint8_t *b, size_t length) {
    size_t num_bytes = length / BITS_PER_BYTE;

    uint8_t *B = (uint8_t *)calloc(num_bytes, sizeof(uint8_t));
    for (size_t i = 0; i < length; i++) {
        size_t byte_index = i / BITS_PER_BYTE;
        B[byte_index] |= (b[i] << (7 - (i % BITS_PER_BYTE)));
    }

    return B;
}

uint8_t *BytesToBits(uint8_t* B, int l) {
    size_t num_bytes = l * BITS_PER_BYTE;
    uint8_t *b = (uint8_t *)calloc(num_bytes, sizeof(uint8_t));
    // size_t num_bits = length * BITS_PER_BYTE;


    for (int i = 0; i < l; i++) {
        for (int j = 0; j < 8; j++) {
            b[8*i + j] = (B[i] >> j) & 1;            
        }
    }
    return b;
}

uint8_t *ByteEncode(int F[Longitud]) {
    int d = 12; // Tamaño de cada entero en bits

    // Algoritmo de codificación
    for (int i = 0; i < 256; i++) {
        int a = F[i]; // Entero a de d bits

        // Almacenar los bits de a en B
        for (int j = 0; j < d; j++) {
            Bec[i * d + j] = a % 2; // Almacenar el último bit de a en B
            a = (a - Bec[i * d + j]) / 2; // Ajustar a para la próxima iteración
        }
    }
    return Bec;
}
uint8_t *ByteDecode(uint8_t *B, int d) {

    uint8_t *b= BytesToBits(B, 256*d);
    uint8_t *F= (uint8_t *)calloc(32*d, sizeof(uint8_t));
    for (int i = 0; i < 256; i++) {
        F[i] = 0;
        for (int j = 0; j < d; j++) {
            F[i] += b[i*d + j] *((2^j)%(2^d));
        }
        
    }
    return F;
}
uint8_t *SampleNTT(uint8_t *B) {
    int i=0;
    int j=0;
    uint8_t *a= (uint8_t *)calloc(256, sizeof(uint8_t));
    while (j<256){
        int d1 =B[i]+256*(B[i+1] & 0x0F); //mascara de selección ultimos 4 bits. Equivale a tomar el modulo 16
        int d2 =(B[i+1]>>4)+16*(B[i+2] & 0x0F); //>>4 desplazamiento a derecha que equivale a dividir entre 16
        if(d1<3329){
            a[j]=d1;
            j++;
        }
        if(d2<3329 && j<256){
            a[j]=d2;
            j++;
        }
        i=i+3;
    }
    return a;

}
uint8_t *SamplePolyCBD(uint8_t *B) {
    uint8_t *f= (uint8_t *)calloc(256, sizeof(uint8_t));
   uint8_t *b = BytesToBits(B,sizeof(B));
   int x = 0;
   int y = 0;
   for (int i = 0; i < 256; i++) {
        for (int j = 0; i < 2; i++) {
            x = x + b[(2*i*2)+j];
        }
        for (int j = 0; i < 2; i++) {
            y = y+ b[(2*i*2)+j+2];
        }
        f[i] = (x) - (y % (3329));
   }
   return f;
}






int main(){
    
    // Ejemplo de cadena de bits
    // uint8_t bits[] = {1, 1, 1, 1, 1, 1, 1, 1,   // Byte 1 (MSB -> LSB)
    //                   0, 0, 0, 0, 0, 0, 1, 0,
    //                   0, 0, 0, 0, 1, 0, 0, 0,
    //                   0, 0, 0, 0, 0, 1, 0, 0};  // Byte 2 (MSB -> LSB)
    // size_t num_bits = sizeof(bits) / sizeof(bits[0]);

    // // Convertir cadena de bits a bytes
    // uint8_t *bytes = BitsToBytes(bits, num_bits);

    // // Mostrar los bytes resultantes
    // printf("Bytes resultantes:\n");
    // for (size_t i = 0; i < num_bits / BITS_PER_BYTE; i++) {
    //     printf("%01x ", bytes[i]); // se establece que la salida sea en hexadecimal de como minimo un digito.
    // }
    // printf("\n");

    // size_t num_bytes = sizeof(bytes) / sizeof(bytes[0]);
    // uint8_t *bitstoB = BytesToBits(bytes, num_bytes);
    // printf("Bits resultantes:\n");
    // for (size_t i = 0; i < num_bytes * BITS_PER_BYTE; i++) {
    //     printf("%01x ", bitstoB[i]); // se establece que la salida sea en hexadecimal de como minimo un digito.
    // }
    // printf("\n");
    // free(bitstoB);
    // free(bytes);
// prueba del algoritmo Byte Encode /////////////////////////////



    int F[Longitud]; // Ejemplo de array de enteros

    // Semilla para la generación de números aleatorios
    srand(time(NULL));

    // Llenar el vector con números aleatorios
    for (int i = 0; i < Longitud; i++) {
        F[i] = rand()% ((2^12) + 1);
    }

    printf("# aleatorios:\n");
    for (size_t i = 0; i < 10 * BITS_PER_BYTE; i++) {
        printf("%01x ", F[i]); // se establece que la salida sea en hexadecimal de como minimo un digito.
    }
    printf("\n");


    uint8_t *B = ByteEncode(F);
    size_t num_bitsE = sizeof(B) / sizeof(B[0]);
    uint8_t *Bi = BitsToBytes(B,num_bitsE);
    uint8_t *BDecode = ByteDecode(Bi, 12);
    uint8_t *RB = SampleNTT(BytesToBits(B,sizeof(B)));
    uint8_t *SP = SamplePolyCBD(B);

    printf("\n");
    printf("Bits resultantes encode:\n");
    for (size_t i = 0; i < 10 * BITS_PER_BYTE; i++) {
        printf("%01x ", Bi[i]); // se establece que la salida sea en hexadecimal de como minimo un digito.
    }
    printf("\n");

    printf("Decode:\n");
    for (size_t i = 0; i < 10 * BITS_PER_BYTE; i++) {
        printf("%01x ", BDecode[i]); // se establece que la salida sea en hexadecimal de como minimo un digito.
    }
    printf("\n");

    printf("Resultado de SampleNTT:\n");
    for (size_t i = 0; i < 10 * BITS_PER_BYTE; i++) {
        printf("%01x ", RB[i]); // se establece que la salida sea en hexadecimal de como minimo un digito.
    }
    printf("\n");

    printf("Resultado de SamplePolyCBD:\n");
    for (size_t i = 0; i < 10 * BITS_PER_BYTE; i++) {
        printf("%01x ", SP[i]); // se establece que la salida sea en hexadecimal de como minimo un digito.
    }
    printf("\n");

    free(Bi);
    free(BDecode);
    free(RB);
    free(SP);
    return 0;

}