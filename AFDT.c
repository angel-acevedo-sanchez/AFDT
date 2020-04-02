#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Transicion {
	
	int estado_inicial;
	int estado_final;
	char traduccion[20];
	char letra; 

};

int leerAutomata(FILE *, struct Transicion*, int*, int, char*);

int main(void){
	
	int num_estados = 0, finales= 0;
	int *final = NULL;
	char *alfabeto = NULL;
	FILE *fp = NULL;
	struct Transicion *transiciones = NULL;
	int longitud=0, i=0, j=0, t=0, resul=1;
	char seleccion;

	
	printf("\nA continuacion se muestran los ficheros existentes: \n\n");

	printf("		Fichero a:  L = {a b^n a : n>=0}\n");
	printf("			    T(M) = {c^(n+3) : n>=1}\n\n");
	printf("		Fichero b:  L = {a^n b (ca)^2k w : n,k >=0, w pertenece {a,b}^*}\n");
	printf("			    T(M) = {1 0^(k+1) 1^m : k>=0, m = |w|}\n\n");
	printf("		Fichero c:  L = {w pertenece a {a,b}^* : w no termina en b}\n");
	printf("                            T(M) = {x pertenece a {0,1}^* : el valor en binario de x es par}\n\n");

	printf("\nEscriba 'a', 'b' o 'c', en minuscula y sin comillas para probar el automata correspondiente: ");

	scanf("%c", &seleccion);

	char path[6];

	if(seleccion == 'a' || seleccion == 'b' || seleccion == 'c'){
		path[0] = seleccion;
		path[1] = '.'; path[2]= 't'; path[3] ='x'; path[4] = 't';
	}


	if((fp=fopen(path, "r"))==NULL){
		printf("El fichero no existe o se ha producido un error\n");
		exit(-1);
	}
	
	

	fscanf(fp, "Longitud del alfabeto: %i\n", &longitud);


	alfabeto = (char*)malloc(longitud*sizeof(char));

	fscanf(fp, "Letras del alfabeto: ");
	for(i = 0; i<longitud; i++)
		fscanf(fp, "%c ", &alfabeto[i]);

	fscanf(fp, "Numero de estados: %i\n", &num_estados);
	fscanf(fp, "Numero de estados finales: %i\n", &finales);



	final = (int*)malloc(finales*sizeof(int)); 
	fscanf(fp, "Estados finales: ");

	for(i=0; i<finales; i++)
		fscanf(fp, "%i ", &final[i]);
	
	transiciones =(struct Transicion *)malloc((num_estados*longitud)*sizeof(struct Transicion));

	char letra = ' '; 
	i = 0;

	while ((t < num_estados*longitud + longitud) && (i < num_estados *longitud) && resul != 0){ 
		
		if(t > 0){ //leo una fila real de la tabla de transiciones --> paso al sguiente struct
			resul = leerAutomata(fp, &transiciones[i], &t, num_estados, &letra);
			transiciones[i].letra = letra;
	
				if(t>0) i++; 
						
		}else if(t==0) //leo el encabezado de la tabla
			resul = leerAutomata(fp, &transiciones[i], &t, num_estados, &letra);

		t++;
	}

	char c = ' ';
	int estado_actual = 0;
	bool en_alfabeto = true, hay_transicion = true;
	char traduccion[50] = "";
	j = 0;

	fflush(stdin);

	printf("\nIntroduzca la secuencia de caracteres: ");

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

	printf("\n");
	system("pause");
	
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
		if((fscanf(f, "%i\t%i %s", &t->estado_inicial, &t->estado_final, &t->traduccion))!=EOF)
			return 1;
		else return 0;
	}
}

