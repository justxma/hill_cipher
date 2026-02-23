#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 37

int convert_char_to_int(char letter){
	if(letter == '.') return 36;
	if(isdigit(letter)) return (int)letter - '0';
	return (int)letter - 55;
}

void convert_string_matrix(char *string , int matrix[][1])
{
	for(int i = 0 ; i < (int)strlen(string) ; i++){
		matrix[i][0] = convert_char_to_int(string[i]);
	}
}

void convert_key_matrix(char *string  , int matrix[][3] , int counter){
	for (int i = 0; i < (int)strlen(string); i++)
	{
		matrix[counter][i] = convert_char_to_int(string[i]);
	}
}

void matrix_multiplication(int result[][1] , int square_matrix[][3] , int coloumn_matrix[][1]){
	for(int i = 0 ; i < 3 ; i++){
		for(int k = 0 ; k < 3 ; k++){
			result[i][0] += square_matrix[i][k] * coloumn_matrix[k][0]; 
		}
	}
}

char convert_int_char(int number){
	if(number == 36) return '.';
	if(number >= 0 && number <= 9) return (char)(number + '0');
	return (char)(number + 55);
}

// int determinant(int matrix[][3]){
// 	return ((matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[1][0] * matrix[2][1] * matrix[0][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) - (matrix[0][2] * matrix[1][1] * matrix[2][0])-(matrix[1][0] * matrix[0][1] * matrix[2][2])-(matrix[2][1] * matrix[1][2] * matrix[0][0]));
// }

// void decryption(int result_matrix[][1] , int key_matrix[][3]){
// 	if(determinant(key_matrix) != 0){
// 		int invers_multiplic = abs(determinant(key_matrix)) % ALPHABET_LENGTH;
// 		int a = 
// 	} else {
// 		printf("Nu se poate decripta textul , det(matrix) = 0!\n");
// 		return ;
// 	}
// }

int main(){
	int plain_text_capacity = 10;
	int plain_text_size = 0;
	char *plain_text = malloc(plain_text_capacity * sizeof(char));
	if(!plain_text){
		printf("Eroare la alocarea memoriei pentru plain_text!\n");
		return 0;
	}

	int key_capacity = 10;
	int key_size = 0;
	char *key = malloc(key_capacity * sizeof(char));
	if(!key){
		printf("Eroare la alocarea memoriei pentru cheie!\n");
		free(plain_text);
		return 0;
	}

	printf("Introduceti cheia de criptare : ");
	int aux;
	while ((aux = getchar()) && aux != '\n')
	{
		if (key_size + 1 == key_capacity)
		{
			key_capacity *= 2;
			char *temp_key = realloc(key, key_capacity * sizeof(char));
			if (!temp_key)
			{
				printf("Eroare la realocare memoriei pentru key!\n");
				return 0;
			}
			key = temp_key;
		}
		key[key_size++] = aux;
	}
	key[key_size] = '\0';
	int key_matrix[3][3];
	int counter = 0;
	char *temp_cheie = malloc(3 * sizeof(char));
	for (int i = 0; i < (int)strlen(key); i += 3)
	{
		temp_cheie = strncpy(temp_cheie, key + i, 3);
		printf("%s\n", temp_cheie);
		convert_key_matrix(temp_cheie , key_matrix , counter);
		counter++;
		// for (int i = 0; i < (int)strlen(temp_cheie); i++)
		// {
		// 	printf("%d\n", initial_matrix[i][0]);
		// }
		// convert 3 letter text to coloumn matrix
		// encription algoritm
	}
	for(int i = 0 ; i < 3 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			printf("%d " , key_matrix[i][j]);
		}
		printf("\n");
	}
	//convert_key_to_matrix

	int result_matrix[3][1];
	FILE *file_ptr = fopen("cripted_message.txt" , "w");
	if(!file_ptr){
		printf("Eroare la deschiderea fisierului cripted_messages.txt!\n");
		return 0;
	}
	FILE *decrypt_file = fopen("decrypted_message.txt" , "a+");
	if(!decrypt_file){
		printf("Eroare la deschiderea fisierului decrypted_message.txt!\n");
		return 0;
	}

	printf("Introduceti textul : ");
	int litera;
	while((litera = getchar()) && litera != '\n'){
		if(plain_text_size + 1 == plain_text_capacity){
			plain_text_capacity *= 2;
			char *temp_plain = realloc(plain_text , plain_text_capacity * sizeof(char));
			if(!temp_plain){
				printf("Eroare la realocare memoriei!\n");
				free(plain_text);
				return 0;
			}
			plain_text = temp_plain;
		}
		plain_text[plain_text_size++] = litera;
	}
	plain_text[plain_text_size] = '\0';
	printf("Plain text entered : %s\n" , plain_text);
	printf("Plain text length : %ld\n" , strlen(plain_text));
	char *temp = malloc(3 * sizeof(char));
	for (int i = 0; i < (int)strlen(plain_text); i += 3)
	{
		temp = strncpy(temp, plain_text + i, 3);
		printf("%s\n", temp);
		int initial_matrix[3][1];
		convert_string_matrix(temp , initial_matrix);
		// for(int i = 0 ; i < (int)strlen(temp) ; i++){
		// 	printf("%d\n" , initial_matrix[i][0]);
		// }
		//convert 3 letter text to coloumn matrix
		//encription algoritm
		matrix_multiplication(result_matrix , key_matrix , initial_matrix);
		for(int i = 0 ; i < 3 ; i++){
			result_matrix[i][0] %= ALPHABET_LENGTH;
		}
		for(int i = 0 ; i < 3 ; i++){
			fprintf(file_ptr , "%c" , convert_int_char(result_matrix[i][0]));
		}
		printf("\n");
		//convert
	}

	//decryption

	free(temp);
	return 0;
}