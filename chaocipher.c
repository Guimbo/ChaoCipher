#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
 /*
 Constantes uma melhor leitura do código
 Utilizados para saber se os valores das chaves devem ser impressas no console/terminal
*/
#define TRUE 1
#define FALSE 0
//Constantes para indetificação do modo de criptografia ou decriptografia que será utilizado
#define ENCRYPT 11
#define DECRYPT 12
 
 //Chaves utilizadas para criptação do texto de entrda
const char *l_alphabet = "HXUCZVAMDSLKPEFJRIGTWOBNYQ";
const char *r_alphabet = "PTLNBQDEOYSFAVZKGJRIHWXUMC";

//Variavel para percorrer cada elemento do vetor
int i;
//Variavel para percorrer cada elemento do vetor
int j;
//Variavel utilizada para salvar a posição do CHAR dentro das chaves encryptadoras 
//equivalente ao CHAR da string de entrada
int indexFound;
//Variavel responsável por armazenar para o tamanho da entrada a ser encriptada ou decriptada
int textLength;


/**
 * Encripta ou Decripta o valor passado na entrada e salvando o resultado na string de saída
 * @param in endereço do vetor com a string a ser ecriptada
 * @param out endereço do vetor onde o resultado da criptografia será salvo
 * @param mode seleção que irá demonstrar a função se a string de entrada deve ser criptografada ou decriptografada
 * @param show_steps sinal que, se habilitado, imprime os resultados das permutações nas chaves de criptografia
*/
void chao(const char *in, char *out, int mode, int show_steps) {
    
    char store;
    char left[27], right[27], temp[27];
    strcpy(left, l_alphabet);
    strcpy(right, r_alphabet);
    temp[26] = '\0';

    //Pecorre o valor em in
    for (i = 0; i < textLength; ++i ) {
        if (show_steps) printf("%s  %s\n", left, right);
        if (mode == ENCRYPT) {
            indexFound = strchr(right, in[i]) - right;
            out[i] = left[indexFound];
        }
        else {
            indexFound = strchr(left, in[i]) - left;
            out[i] = right[indexFound];
        }
        if (i == textLength - 1) break;
 
        /* Permutação na chave esquerda */
 
        for (j = indexFound; j < 26; ++j) temp[j - indexFound] = left[j];
        for (j = 0; j < indexFound; ++j) temp[26 - indexFound + j] = left[j];
        store = temp[1];
        for (j = 2; j < 14; ++j) temp[j - 1] = temp[j];
        temp[13] = store;
        strcpy(left, temp);
 
        /* Permutação na chave direita */
 
        for (j = indexFound; j < 26; ++j) temp[j - indexFound] = right[j];
        for (j = 0; j < indexFound; ++j) temp[26 - indexFound + j] = right[j];
        store = temp[0];
        for (j = 1; j < 26; ++j) temp[j - 1] = temp[j];
        temp[25] = store;
        store = temp[2];
        for (j = 3; j < 14; ++j) temp[j - 1] = temp[j];
        temp[13] = store;
        strcpy(right, temp);
    }
}
 
int main(int argc, char const *argv[]) {

    //Obtem o tamanho do vetor de entrada
    int textLength = atoi(argv[1]);
    //Obtem a string de entrada
    const char *plain_text = argv[2];

    //Reserva o espaço de memória do tamanho da string criptografada
    char *cipher_text = malloc(textLength + 1);
    //Reserva o espaço de memória do tamanho da string para decriptografia
    char *plain_text2 = malloc(textLength + 1);

    printf("The original plaintext is : %s\n", plain_text);
    printf("\nThe left and right alphabets after each permutation during encryption are :\n\n");

    //Chamada do método de criptografia com o modo de cripatação e exibição das chaves de criptografia
    chao(plain_text, cipher_text, ENCRYPT, TRUE);
    printf("\nThe ciphertext is : %s\n", cipher_text);
    //Chamada do método de criptografia com o modo de decripatação
    chao(cipher_text, plain_text2, DECRYPT, FALSE);
    printf("\nThe recovered plaintext is : %s\n", plain_text2);

    //Libera o espaço da memória reservado anteriormento para o texto criptografado
    free(cipher_text);
    //Libera o espaço da memória reservado anteriormento para o texto decriptografado
    free(plain_text2);

    return 0;
}