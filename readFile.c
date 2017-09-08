
#include <stdio.h>
#include <stdlib.h>
// Lee caracter por caracter y quita los 00 y divide los casos de entrada

int main()
{
	FILE *archivo;
	int caracter;
	int caso = 1;

	archivo = fopen("entrada.txt","r");

	if (archivo == NULL)
        {
            printf("\nError de apertura del archivo. \n\n");
        }
        else
        {
             while((caracter = fgetc(archivo)) != EOF)
             {
                printf("\nCaso #");printf("%i",caso);printf("\n\n");    // Para saber la parte del archivo que estoy leyendo
                while(((caracter = fgetc(archivo)) != '0') || ((caracter = fgetc(archivo)) == EOF) )
                {
                printf("%c",caracter);
                }
                caracter = fgetc(archivo);                              // Para saltarme el otro cero
                caso += 1;
             }

        }
        fclose(archivo);
	return 0;
}
