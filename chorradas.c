#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define TAM_LINEA 16
//void separarDireccion(char binario [], int modo);
int leecturaFicheroMemoria ();
void inicializarCacheLinea();
int convertirDecimal(long long);
//void convertirBinario(char linea []);

typedef struct {
 unsigned char ETQ;
 unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

unsigned char Simul_RAM [4096];

int main(){

    inicializarCacheLinea();

    lecturaFicheroBinario();
    
    leecturaFicheroMemoria ();
    return 0;
}

// Convierte a Decimal
int convertirDecimal(long long n) {
  int decimal = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    decimal += rem * pow(2, i);
    ++i;
  }

  return decimal;
}

leecturaFicheroMemoria (){
    int a;
    FILE * fichero;
    fichero = fopen("accesos_memoria.txt", "r");
    
    if(fichero != NULL){
        char lineas [5];

        //Metodo encargado de recorrer el fichero y almacenar el contenido en "lineas"
        while(fgets(lineas,sizeof(lineas),fichero)!=NULL){

            //fputs se encarga de imprimir por pantall el contenido de lineas
            //fputs(lineas, stdout);
            convertirBinario(lineas);
            printf("----------------------fin----------------------\n");
        }

    }else{
        printf("El archivo seleccionado es inexistente\n");
        exit(-1);
    }
    return 0;
}

void lecturaFicheroBinario(){
    FILE * fichero2;
    fichero2 = fopen("CONTENTS_RAM.bin", "rb");
    //unsigned char buffer[4096];

    if(fichero2!=NULL){

        fread(Simul_RAM,sizeof(Simul_RAM),1,fichero2);

        for(int i = 0; i<4096; i++){
            printf("%c",Simul_RAM[i]);// prints a series of bytes %u para numeros
        }
            
    }else{
        printf("El archivo seleccionado es inexistente\n");
        exit(-1);
    }
}

//Metodo encargado de recorrer cada uno de los caracteres y pasarlo a binario
void convertirBinario(char linea []){
    char binario[100];
    binario[0]='\0'; //borrar contenido string
    printf(linea,"\n");
    for (int i = 0; i < 3; ++i){
        if(isdigit(linea[i])){
            switch(linea[i]){
                case '0' :
                    strcat(binario,"0000");
                    break;
                case '1' :
                    strcat(binario, "0001");
                    break;
                case '2' :
                    strcat(binario, "0010");
                    break;
                case '3' :
                    strcat(binario, "0011");
                    break;
                case '4' :
                    strcat(binario, "0100");
                    break;
                case '5' :
                    strcat(binario, "0101");
                    break;
                case '6' :
                    strcat(binario, "0110");
                    break;
                case '7' :
                    strcat(binario, "0111");
                    break;
                case '8' :
                    strcat(binario, "1000");
                    break;
                case '9' :
                    strcat(binario, "1001");
                    break;
                default : printf("\nValor invalido  %c",linea[i]);
		    }
        }else{
            switch(linea[i]){
                case 'A' :
                    strcat(binario, "1010");
                    break;
                case 'B' :
                    strcat(binario, "1011");
                    break;
                case 'C' :
                    strcat(binario, "1100");
                    break;
                case 'D' :
                    strcat(binario, "1101");
                    break;
                case 'E' :
                    strcat(binario, "1110");
                    break;
                case 'F' :
                    strcat(binario, "1111");
                    break;
                default : printf("\nValor invalido  %c",linea[i]);
		    }
        }              
    }
    //Son esbozos para comprobar como dividir la direccion en etiqueta, linea..etc
    printf(binario,"\n");
    printf("\n");
    
    char etiqueta[50];
    memcpy(etiqueta,&binario[0],5);
    printf("Etiqueta\n");
    printf(etiqueta);
    printf("\n");

    char lineaaa[50];
    memcpy(lineaaa,&binario[5],3);
    printf("linea\n");
    printf(lineaaa);
    printf("\n");

    char palabra[50];
    memcpy(palabra,&binario[8],4);
    printf("palabra\n");
    printf(palabra);
    printf("\n");
   
    char bloque[100];
    memcpy(bloque,&binario[0],8);
    printf("bloque\n");
    int x = atoi(bloque);//Tenemos que pasar el string a int para quitar los ceros de delante
    printf(bloque," \n"); 
    printf(" bloque en binario = %d in decimal", convertirDecimal(x));
    printf("\n");
}


void inicializarCacheLinea(){
T_CACHE_LINE cacheLine[16];

     for(int i=0; i<15; i++){
        cacheLine[i].ETQ= (unsigned char)0xFF;
        for (int j = 0; j < 15; j++){
            cacheLine[i].Data[j]= (unsigned char)0x23;                  //MIRAR CAMBIAR 
        }
    }

    printf("%u", cacheLine[0].Data[0]);
}