#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAM_LINEA 16

int cCHL();
int leecturaFicheroMemoria ();
int lecturaFicheroBinario();

typedef struct {
 unsigned char ETQ;
 unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

int main(){
    int globaltime = 0;
    int numfallos = 0;
    int label = 0xFF;
    int lin = 0x23F;
    unsigned char Simul_RAM[4096];
    T_CACHE_LINE tcl[16];

    cCHL(tcl, label, lin);

    printf("PRINT DE TABLA\n");
    for(int k=0; k<16; k++){
        printf("CACHE LINE %d\n", k+1);
        printf("ETQ:%X ", tcl[k].ETQ);
        printf("Data ");
        for (int t = 0; t < 15; t++){
            printf("%X ", tcl[k].Data[t]);
        }
        printf("\n");
    }

    leecturaFicheroMemoria();
    return 0;
}

cCHL(T_CACHE_LINE cachelines[16], int val_lab, int val_lin){
    for(int i=0; i<16; i++){
        cachelines[i].ETQ= (unsigned char)val_lab;
        for (int j = 0; j < 15; j++){
            cachelines[i].Data[j]= (unsigned char)val_lin;
        }
    }
    return 0;
}

int mt(T_CACHE_LINE cachelines[16]){
    printf("PRINT DE TABLA\n");
    for(int k=0; k<16; k++){
        printf("CACHE LINE %d\n", k+1);
        printf("ETQ:%X ", cachelines[k].ETQ);
        printf("Data ");
        for (int t = 0; t < 15; t++){
            printf("%X ", cachelines[k].Data[t]);
        }
        printf("\n");
    }
    return 0;
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

lecturaFicheroBinario(){
    FILE * fichero2;
    fichero2 = fopen("CONTENTS_RAM.bin", "rb");
    unsigned char buffer[4096];

    if(fichero2!=NULL){

        fread(buffer,sizeof(buffer),1,fichero2);

        for(int i = 0; i<4096; i++){
            printf("%c",buffer[i]);// prints a series of bytes %u para numeros
        }
            
    }else{
        printf("El archivo seleccionado es inexistente\n");
        exit(-1);
    }
    return buffer;
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
    printf(bloque);
    printf("\n");
}