#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Transicion {
	
	int estado_inicial;
	int estado_final;
	char traduccion[20];
	char letra; //esta es la letra del alfabeto con la que se transita de un estado a otro

};

int leerAutomata(FILE *, struct Transicion*, int*, int, char*);

int main(void){
	
	int num_estados = 0, finales= 0;
	int *final = NULL;
	char *alfabeto = NULL;
	FILE *fp = NULL;
	struct Transicion *transiciones = NULL;
	int longitud=0, i=0, j=0, t=0, resul=1;
	
	if((fp=fopen("a.txt", "r"))==NULL){
		printf("Error al abrir el fichero\n");
		exit(-1);
	}
	

	fscanf(fp, "Longitud del alfabeto: %i\n", &longitud);
	//aaprintf("%i\n", longitud);

	alfabeto = (char*)malloc(longitud*sizeof(char));

	fscanf(fp, "Letras del alfabeto: ");
	for(i = 0; i<longitud; i++)
		fscanf(fp, "%c ", &alfabeto[i]);

	fscanf(fp, "Numero de estados: %i\n", &num_estados);
//	printf("%i\n", num_estados);
	fscanf(fp, "Numero de estados finales: %i\n", &finales);
//	printf("%i\n", finales);


	final = (int*)malloc(finales*sizeof(int)); //array para los estados finales
	fscanf(fp, "Estados finales: ");

	for(i=0; i<finales; i++)
		fscanf(fp, "%i ", &final[i]);
	
	transiciones =(struct Transicion *)malloc((num_estados*longitud)*sizeof(struct Transicion));

	char letra = ' '; //para recuperar del fichero la letra del alfabeto correspondiente una parte de la tabla
	i = 0;

	while ((t < num_estados*longitud + longitud) && (i < num_estados *longitud) && resul != 0){ 
		
		if(t > 0){ //leo una fila real de la tabla de transiciones --> paso al sguiente struct
			resul = leerAutomata(fp, &transiciones[i], &t, num_estados, &letra);
			transiciones[i].letra = letra;
			//printf("Numero de orden: %i\n", i);
				if(t>0) i++; //t se modifica en la llamada, por eso se tiene que comprobar otra vez el valor para a
								// para avanzar en el array de structs, (array de transiciones)
		}else if(t==0)
			resul = leerAutomata(fp, &transiciones[i], &t, num_estados, &letra);

		t++;
	}

	char c;
	int estado_actual = 0;
	bool en_alfabeto = true, hay_transicion = true;
	char traduccion[50];
	j = 0;


	while((c = getchar()) != '\n' && en_alfabeto && hay_transicion){

		en_alfabeto = false;

		for(i = 0; i<longitud; i++){
			if(c == alfabeto[i])
				en_alfabeto = true;
		}

		if(en_alfabeto){

			for(i = 0; i<longitud; i++){
				if(transiciones[(estado_actual) + i*num_estados].letra == c){

					if(transiciones[(estado_actual) + i*num_estados].estado_final == -1)//no hay transicion posible
						hay_transicion = false;
					else{

						if(transiciones[(estado_actual) +i*num_estados].traduccion[0] != '*'){
							strcat(traduccion, transiciones[(estado_actual) +i*num_estados].traduccion);
							j++;
						}
					}
					estado_actual = transiciones[(estado_actual)+i*num_estados].estado_final; //transito
				}
			}
		}
	}

	bool es_final = false;

	for(i=0; i<finales; i++){
		if(estado_actual == final[i])
			es_final = true;
	}
	if((en_alfabeto && hay_transicion) && es_final) 
		printf("La cadena pertenece al lenguaje L y su traduccion es: %s\n", traduccion);
	else printf("La cadena no se acepta\n");
	
	fclose(fp);
	free(final);
	free(transiciones);
	
	return 0;
}

int leerAutomata(FILE *f, struct Transicion *t, int* time, int estados, char* l){

	if(*time == estados + 1) *time = 0;
	
	if(*time == 0 ){
	
		if(fscanf(f, "\t%c", &(*l))!=EOF)
			return 1;
		else return 0;
	}
	else{
		if((fscanf(f, "%i\t%i %s", &t->estado_inicial, &t->estado_final, &t->traduccion))!=EOF){
			
			//printf("%i --> %i, %s\n", t->estado_inicial, t->estado_final, t->traduccion);
			return 1;
		}
		else return 0;
	}
}

