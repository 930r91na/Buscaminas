/******************************************************************************
BUSCAMINAS (archivos 1)
*******************************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<time.h>
//INICIO DECLARACION DE VARIABLES GLOBALES
int filas, columnas, nuMinas, puntosParaGanar;
int MINAS=42;//ASCII de asterisco
FILE *archivoPuntajes;

//FIN DECLARACION DE VARIABLES GLOBALES


//INICIO FUNCION MENU
void menu_niveles()
{
    int nivel;
      do{
         printf("\nSeleccione su nivel:\n 1-Facil\n 2-Medio \n 3-Dificil\n ");
            scanf("%d", &nivel);
                switch(nivel)
                    {
                        case 1:
                            filas=5;
                            columnas=4;
                            nuMinas=5;
                            puntosParaGanar=25;
                                break;
                        case 2:
                            filas=6;
                            columnas=5;
                            nuMinas=10;
                            puntosParaGanar=50;
                                break;
                        case 3:
                            filas=7;
                            columnas=6;
                            nuMinas=20;
                            puntosParaGanar=100;
                                break;
                    }
        }while(nivel!=1&&nivel!=2&&nivel!=3);//Validación de nivel si no es 1, 2,3 vuelve a aparecer el menu
              
}
//FIN FUNCION MENU

//INICIO IMPRESION TABLERO
void impresion_tablero(int a[filas][columnas], int b[filas][columnas])
{
     int conteoMinasFilas[filas];
     int conteoMinas=0;
                for (int i=0;i<filas;i++)
                {
                    for (int j=0;j<columnas;j++)
                    {
                        if(a[i][j]==MINAS)
                        {
                            conteoMinas++;          
                        }  
                    }
                    conteoMinasFilas[i]=conteoMinas;
                    conteoMinas=0;
                }
                
      //Inicio impresion de tablero 
        // Encabezado horizontal
        printf("    ");
         for (int m = 0; m <= columnas-1; m++) 
            {
            printf("|  %d  ",m);
            }
         printf("|\n");
         for (int m = 0; m <= columnas; m++) {
            printf("------");
          }
          printf("\n");
        
        // Fin encabezado horizontal 
            for (int i=0;i<filas;i++)
            {
                    printf("| %d ",i);//Encabezado vertical
                for (int j=0;j<columnas;j++)
                {
                    printf("|  %c  ",b[i][j]);
                }
                    printf("| El numero de minas en esta fila es de  %d ",conteoMinasFilas[i]);
                    printf("\n");
            }
}
    //Fin impresion de tablero
//FIN IMPRESION TABLERO

//INICIO GENERADOR DE MINAS 
void generador_minAleatorias(int a[filas][columnas])
{
    // inicio vaciado de tablero 
    for (int i=0;i<filas;i++)
                {
                    for (int j=0;j<columnas;j++)
                    {
                       a[i][j]=168;//esto hace que se vacien las minas de los juegos anteriores
                    }
                }
    //fin vaciado tablero
    
    //Inicio bombas aleatorias: Se asignan segun el nuMinas posiciones aleatorias
        srand(time(NULL));
            
            int i=0;
            while(i<nuMinas)
            {
                int fil_Aleatoria=rand()%(filas-1);
                int col_Aleatoria=rand()%(columnas-1);
                if(a[fil_Aleatoria][col_Aleatoria]!=MINAS)
                {
                    i++;
                    a[fil_Aleatoria][col_Aleatoria]=MINAS;
                }
            }
    //Fin bombas aleatorias: Se asignan segun el nuMinas posiciones aleatorias
}
//FIN GENERADOR DE MINAS

//INICIO GENERADOR DE TABLERO DESCUBIERTO
void generador_tablero_descubierto(int a[filas][columnas])//Esta funcion genera la matriz de las respuestas o como se vería el tablero completamente descubierto
{
    //INICIO MINAS CERCA DE CADA RECUADRO
    int conteoMinasCercanas=0;//Asi si no hay minas cercanas se muestra 0 
    for (int i=0;i<filas;i++)
        {
            for (int j=0;j<columnas;j++)//Escaneo de cada casilla
            {
                if(a[i][j]!=MINAS)
                {
                //Se comprueba en cada uno de los 8 espacios que estan alrededor de uno si existe una bomba 
                    if (a[i-1][j-1]==MINAS){
                        if(i-1>=0&&j-1>=0&&i-1<filas&&j-1<columnas){//Los ifs de dentro es para asegurarse que sean ubicaciones validas de la matriz
                           conteoMinasCercanas++; 
                        }
                    }
                    if (a[i-1][j]==MINAS){
                        if(i-1>=0&&j>=0&&i-1<filas&&j<columnas){
                           conteoMinasCercanas++; 
                        }
                    }
                    if (a[i-1][j+1]==MINAS){
                        if(i-1>=0&&j+1>=0&&i-1<filas&&j+1<columnas){
                           conteoMinasCercanas++; 
                        }
                    }
                    if (a[i][j-1]==MINAS){
                        if(i>=0&&j-1>=0&&i<filas&&j-1<columnas){
                           conteoMinasCercanas++; 
                        }
                    }
                    if (a[i][j+1]==MINAS){
                        if(i>=0&&j+1>=0&&i<filas&&j+1<columnas){
                           conteoMinasCercanas++; 
                        }
                    }
                    if (a[i+1][j-1]==MINAS){
                        if(i+1>=0&&j-1>=0&&i+1<filas&&j-1<columnas){
                           conteoMinasCercanas++; 
                        }
                    }
                    if (a[i+1][j]==MINAS){
                        if(i+1>=0&&j>=0&&i+1<filas&&j<columnas){
                           conteoMinasCercanas++; 
                        }
                    }
                    if (a[i+1][j+1]==MINAS){
                        if(i+1>=0&&j+1>=0&&i+1<filas&&j+1<columnas){
                           conteoMinasCercanas++; 
                        }
                    }
                    a[i][j]=conteoMinasCercanas+48;//ASCII de 0 es 48
                    conteoMinasCercanas=0;//Para que no se acumule el valor entre cada espacio
                }
            }
        }
    //FIN MINAS CERCA DE RECUADRO
    
     //impresion_tablero(a, a); // quitar de modo comentario si se desean ver las respuestas
}
//FIN GENERADOR DE TABLERO DESCUBIERTO

//INICIO GENERADOR DE TABLERO CUBIERTO
void generador_tablero_cubierto(int a[filas][columnas], int b[filas][columnas])
{
    for (int i=0;i<filas;i++)
            {
                for (int j=0;j<columnas;j++)
                {
                    b[i][j]=168;//codigo ascii de interrogación TODA LA MATRIZ TOMA ESTE VALOR
                }
            }
    impresion_tablero(a,b);
}
//FIN GENERADOR DE TABLERO CUBIERTO

//INICIO MOVIMIENTO
int movimiento()
{
    int accion;
      printf("\nElige acción a realizar: \n1.Descubrir casilla\n2.Marcar casilla\n");
        scanf("%d",&accion);  
    //validacion de opciones
    
    return accion;
}
//FIN MOVIMIENTO

//INICIO DESCUBRIR CASILLAS
int descubrir_casillas(int filadescubierta,int columnadescubierta, int respuestas[filas][columnas], int mostrar[filas][columnas])
{
        int repetircasilla=1;
        if(respuestas[filadescubierta][columnadescubierta]==mostrar[filadescubierta][columnadescubierta]){
            printf("\nUsted ya destapo esta casilla\n");
            repetircasilla=0;
        }else{
            mostrar[filadescubierta][columnadescubierta]=respuestas[filadescubierta][columnadescubierta]; 
            impresion_tablero(respuestas, mostrar);
        }
        return repetircasilla;//Regresa este valor ya que si es movimiento repetido se multiplicara por 0 invalidando los puntos y por eso se inicializa en 1 porque en ese se valida la puntuacion
    }
//FIN DESCUBRIR CASILLAS

//INICIO CALCULO PUNTAJE
int ir_calculando_puntaje(int filadescubierta,int columnadescubierta, int respuestas[filas][columnas])
{
    int correcto=0;
    if(respuestas[filadescubierta][columnadescubierta]!=MINAS){
        correcto=1;
    }
    return correcto;
    
}
//FIN CALCULO PUNTAJE

//INICIO MARCAR CASILLAS
void marcar_casillas(int filaSeleccionada,int columanaSeleccionada, int respuestas[filas][columnas], int mostrar[filas][columnas])
{
            mostrar[filaSeleccionada][columanaSeleccionada]=33;//ASCII (!)  
            impresion_tablero(respuestas, mostrar);
    }
//FIN MARCAR CASILLAS

//INICIA A JUGAR
int jugar()
{
    int tablero[filas][columnas];//Declaracion del tablero descubierto o con respuestas
    int tableroCub[filas][columnas];//Declaracion de tabolero cubierto
    generador_minAleatorias(tablero);
    generador_tablero_descubierto(tablero);//Respuestas
    generador_tablero_cubierto(tablero,tableroCub);
                    
    int estatusPartida=1;//1 significa seguir en el juego 0 significa muerte
    int puntaje=0;
    do{
        int fila_elegida, columna_elegida;
        do{
                printf("\nQue casilla va a cambiar:  ");
            printf("\nInserte fila:");
                scanf("%d", &fila_elegida);
            printf("\nInserte columna:");
                scanf("%d", &columna_elegida);  
        }while(!(fila_elegida>=0&&fila_elegida<filas&&columna_elegida>=0&&columna_elegida<columnas));//Validacion de filas y columnas
                            
        switch(movimiento())
        {
            case 1:
            
            puntaje=puntaje + ir_calculando_puntaje(fila_elegida,columna_elegida,tablero)*descubrir_casillas(fila_elegida,columna_elegida,tablero,tableroCub)*5;
            //Ambos valores de retorno de las funciones validan la obtencion de puntos 
            if(ir_calculando_puntaje(fila_elegida,columna_elegida,tablero)==0){
                printf("------FIN DEL JUEGO-----\n");
                
                printf("\n\n------------LAS RESPUESTAS-----------\n\n");//Se imprime el tablero descubierto para que el jugador pueda ver todas las bombas
                impresion_tablero(tablero,tablero);
                estatusPartida=0;
            }//Si se pierde
                                    
            if(puntaje==puntosParaGanar){
                        printf("\n¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡HA GANADO!!!!!!!!!!!!!!!!!!!");
                estatusPartida=0; 
            }
                                    
            printf("\nTU PUNTAJE: %d",puntaje);
                                    
                break;
            case 2:
            marcar_casillas(fila_elegida,columna_elegida,tablero,tableroCub);
                break;
        }
        
    }while(estatusPartida!=0);
    
    return puntaje;
}
//FIN DE A JUGAR

//INICIO FUNCIONES DE ARCHIVO

void LlenarArchivo(int puntajePart)
    {
        archivoPuntajes=fopen("PuntuacionesColeccion.txt","a");
        fprintf(archivoPuntajes,"Puntuación de partida: %d\n",puntajePart);//26 caracteres por oracion SITUACIOOOOON
        fclose(archivoPuntajes);
    }
    
void LeerArchivo()
    {
        archivoPuntajes=fopen("PuntuacionesColeccion.txt","r");
        char caracteres[1000];  
          while(feof(archivoPuntajes) == 0)  //navegar el archivo de principio a fin secuencialmente
          {
                if(caracteres!=""){//se evita el vacio
                fflush(stdin);
                printf("%s",caracteres);//impresion de las cadenas (palabras)
                }
                fgets(caracteres,27,archivoPuntajes); //obtener de los caracteres-palabras
                
            }
    
            fclose(archivoPuntajes); //cierre de archivo
    }

//FIN FUNCIONES DE ARCHIVO
//INICIO MAIN---------------
int main()
{
printf("\n\n.------------ BiEnVeNiDoS a BuScAmInAs--------------.\n");
printf("\nPor Georgina Zeron \n\n");
    int JuegosJugados;
    int opcionMenu;
    int volverMenu;

    do
    {
       do
        {
        printf("\n~~~~~~~~~~~~~~~~~~~~MENU PRINCIPAL~~~~~~~~~~~~~~~~~~~~");
        printf("\nSeleccione lo que desea hacer:\n 1-Jugar\n 2-Ver puntuaciones anteriores \n 3-Salir\n ");
        scanf("%d", &opcionMenu);
            switch(opcionMenu)
            {
                case 1:
                    {
                    menu_niveles();
        
                        LlenarArchivo(jugar());//generar archivo
                        
                        volverMenu=100;//Regresa a Menu principal
                    break;
                    }
                //puntuaciones
                case 2:
                    {
                    printf("\nPUNTACIONES------------\n Desde la mas antigua\n");
                    archivoPuntajes=fopen("PuntuacionesColeccion.txt","a");
                 
                    fclose(archivoPuntajes);//por si no se ha creado el archivo
                    
                    LeerArchivo();
                    volverMenu=100;//Regresa a Menu principal
                    break;
                    }
                //fin puntuaciones
                case 3:
                    {
                    printf("Usted salio del juego");
                    volverMenu=-1;
                    break;
                    }
            }
            
        }while(opcionMenu!=1&&opcionMenu!=2&&opcionMenu!=3);//Validacion de opcionMenu si no es 1, 2,3 vuelve a aparecer el menu  
    }while(volverMenu==100);
    
return 0;
}   
//FIN MAIN---------------