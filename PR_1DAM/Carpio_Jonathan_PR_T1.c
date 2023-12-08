// Importamos nuestra libreria stdio -> para entrada y salida de texto
#include <stdio.h>
// Importamos la libreria string.h para utilizar strcmp , strcpy , strtok ,
#include <string.h>
// Importamos la libreria stdlib.h para utilizar atoi () que cambia de un número a string
#include <stdlib.h>
// Importamos la libreria locale.h para utilizar los caracteres especiales de ASCII
#include <locale.h>
#include <wchar.h>
// Importamos la libreria windows.h para abrir la funcion system
#include <windows.h>
// Utilizmos dos variables constantes una para el array y otra para el maximo de caracteres
#define MAXC 50
#define MAXARRAY 100
// Ir debugueando poco a poco con los printf.
// Declaramos nuestra estructura.
struct peliculasYseries{
	char titulo[MAXC];
	char tipo[MAXC];
	int duracion;
	char plataforma[MAXC];
	char imagen[MAXC];
	int fecha;
};
// Declaración de mis Funciones para apartado 1 , 2 y 3 <-------------------------
int menu();
int leerFichero(struct peliculasYseries info[]);
int pedirInfo(struct peliculasYseries info[],int numeroPeliculas);
void mostrarArray(struct peliculasYseries info[],int numeroPeliculas);

// Declaro la función para el apartado 3 <-------------------------------------
void elegirDato(struct peliculasYseries info[],int numeroPeliculas);

// Declaro la función para el apartado 4 <--------------------------------------	
int caso4();
void ordenarPlataforma(struct peliculasYseries info[],int numeroPeliculas);
void ordenarTipo(struct peliculasYseries info[],int numeroPeliculas);
void ordenarTitulo(struct peliculasYseries info[],int numeroPeliculas); 

// Función para apartado 5. <---------------------------------------
void crearEspecifico(struct peliculasYseries info[],int numeroPeliculas);

//Función para apartado 6 <--------------------------------------------------
void crearHtml(struct  peliculasYseries info[], int numeroPeliculas);
void archivosHtml(struct  peliculasYseries info[], int numeroPeliculas);
void mostrarOrdenado(struct peliculasYseries info[MAXARRAY],int numeroPeliculas);

// Declaramos nuestra función main que nos permitirá ejecutar el programa
main(){
	// Variables para los caracteres de ñ y interrogaciones.	
	setlocale(LC_ALL, "");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	
	// Declaramos nuestros arrays.
	struct peliculasYseries info[MAXARRAY];
	
	// Variable para la opcion elegida seguida de su contador para contar los datos metidos
	int opcion; 
	int numeroPeliculas=0;
	
	// El retorno de esta función es nuestro contador y el vuelco de datos al array
	numeroPeliculas = leerFichero(info); 	
	printf("\n\tEn nuestro registro tenemos añadidos %d datos\n",numeroPeliculas);
	do{
		// Llamamos a nuestra funcion de menu que nos retorna un valor entero ( la opción )
		opcion = menu();
		// Siempre despues del scanf para poder coger cadena
		while(getchar()!='\n'); 
		// Abrimos nuestro menu de opciones 
		switch(opcion){			
			case 1:
				// Retornamos la función con un numero entero que sera nuestro contador de las peliculas ingresadas
				numeroPeliculas = pedirInfo(info,numeroPeliculas); 
				// Le hacemos una pausa para que ponga que presiones una tecla para continuar
				system("\npause"); 
				break;
			case 2:
				system("cls");
				// Mostramos por pantalla el contenido de todo el array hast ahora
				mostrarArray(info,numeroPeliculas);
				break;
			case 3:
				// Función que recorre nuestras peliculas o series y elige que datos quieres ver
				elegirDato(info,numeroPeliculas);
				system("\npause"); 
				break;
			case 4:
				// Creamos un do/while para que repita lso casos hasta que se presiona 4
				do{
					// Llamamos a la funcion del caso 4 retornando el valor que ha recogido
					opcion = caso4();
					// hemos recogido con un scanf y ahora queremos meter cadena de caracteres.
					while(getchar()!='\n'); // No se puede poner en la función te repite la accion de pedir el numero.
					switch(opcion){
						case 1 : 
							// Función que ordena por titulo de la A-Z
							ordenarTitulo(info,numeroPeliculas);
							// Una vez ordenado lo muestro
							mostrarOrdenado(info,numeroPeliculas);
							system("\npause");
							break;
						case 2 :
							// Función que ordena por plataforma de la A-Z
							ordenarPlataforma(info,numeroPeliculas);
							// Una vez ordenado lo muestro
							mostrarOrdenado(info,numeroPeliculas);
							system("\npause");
							break;
						case 3 : 
							// Función que ordena por tipo de la A-Z
							ordenarTipo(info,numeroPeliculas);
							// Una vez ordenado lo muestro
							mostrarOrdenado(info,numeroPeliculas);
							system("\npause");
							break;
						case 4 : 
							printf("\t\tSaliendo al menu principal...\n");
							break;		
					}
				// mientras que la opción no sea igual a 4 no sale del do/while
				}while(opcion != 4); 
				break;
			case 5:
				// Llamamos a la función para que pida al usuario que meta el nombre de una pelicula y si esta en el fichero creara el html
				crearEspecifico(info,numeroPeliculas);
				break;
			case 6:
				// Llamamos a la función para crear el html general con los enlaces
				crearHtml(info,numeroPeliculas); 
				break;
			case 0:
				// Mi opción de salida
				printf("\t\tSaliendo del programa..\n");
				break;
			default:
				// Si introduce un valor que no esta en el menu entra en esta opción
				printf("\tPor favor, introduce un valor que este entre las opciones del menu.\n");
				break;
		}
	}while(opcion != 0);
}
/* -----------------------------------------------------------

						Función del Menu

--------------------------------------------------------------*/
int menu(){
		system("cls");
		int valor;
		printf(" \n\n\t\t**** ------ MENU ------- ****\n");
		printf("\n\t\t Elige sobre estas opciones\n\n");
		printf("\t\t**** ------      ------- ****\n\n");
		sleep(1);
		printf("\t 1. Agregar serie o película\n");
		printf("\t 2. Consultar listado de series y películas\n");
		printf("\t 3. Consultar serie o película\n");	
		printf("\t 4. Consultar listado de series y películas ordenado:\n");		
		printf("\t 5. Generar documento específico HTML\n");		
		printf("\t 6. Generar documentos HTML\n");
		printf("\t 0. Salir del programa..\n\n");
		sleep(1);
		printf("\t\t**** ------      ------- ****\n\n");
		printf("\t *** ¿Que opción te gustaria elegir? *** ");
		scanf("%d",&valor);
		printf("\n\n\t\t**** -------      ------ ****\n\n");
		return valor;
}
/* -----------------------------------------------------------

	Antes que nada leemos nuestro fichero y volcamos

--------------------------------------------------------------*/
int leerFichero(struct peliculasYseries info[MAXARRAY] ){
	FILE *fichero;
	fichero = fopen("Info.txt","r");
	// La variable para coger todo lo que tenga el fichero
	char linea[100];
	int numeroPeliculas = 0;
	int contadorLinea=0;
	// Mientras en el fichero no este vacio metelo en linea.
	while(fgets(linea,100,fichero) != NULL){ 
		// Elimina el salto de linea de todos los string
		strtok(linea,"\n"); 
		if(contadorLinea % 6 == 0){
			 // Lo usamos para copiar lo que tiene linea a titulo de nuestro array.
			strcpy(info[numeroPeliculas].titulo,linea);
		}else if (contadorLinea % 6 == 1){
			strcpy(info[numeroPeliculas].tipo,linea); 
		}else if (contadorLinea % 6 == 2){
			// atoi para cambiar su valor ya que con strcpy solo se usa para string
			info[numeroPeliculas].duracion = atoi(linea); 
		}else if (contadorLinea % 6 == 3){
			strcpy(info[numeroPeliculas].plataforma,linea); 
		}else if (contadorLinea % 6 == 4){
			strcpy(info[numeroPeliculas].imagen,linea);	
		}else if (contadorLinea % 6 == 5){
			info[numeroPeliculas].fecha = atoi(linea); // atoi para cambiar su valor 
			// Suma una mas a nuestras peliculas / Serie
			numeroPeliculas++;
		}
		
		// va a sumar 1 cuando hace todo Rellena el siguiente bloque del struct	
		contadorLinea++;	
	}
	fclose(fichero);
	// Retornamos el numero de peliculas
	return numeroPeliculas;
}
/* -----------------------------------------------------------

						Función del caso 1

--------------------------------------------------------------*/
// le pasamos la estructura para que lo entienda junto con el contador para que lo devuelva ( cont )
int pedirInfo(struct peliculasYseries info[MAXARRAY],int numeroPeliculas){ 
	char tituloAux[MAXC];
	char tipoAux[MAXC];
	int duracionAux;
	char plataformaAux[MAXC]; 
	char imagenAux[MAXC];
	int fechaAux;
	FILE *fichero;
	fichero=fopen("Info.txt","a");
	
	//	Recogemos datos.
	system("cls"); // Esta función limpia la pantalla
	printf("\n\n\t\t**** ------ DATOS ------- ****\n\n");
	printf("\tEscriba el título: ");	
	// Recogemos cadena con gets scanf con numeros.
	gets(tituloAux); 
	printf("\tEscriba el tipo:\n\t\t#. Película\n\t\t#. Serie \n\t");
	gets(tipoAux); 
	printf("\tEscriba la duración (min): ");
	scanf("%d",&duracionAux);
	while(getchar()!='\n');
	printf("\tEscriba la plataforma: ");
	gets(plataformaAux);
	printf("\tImagen: ");
	gets(imagenAux);
	printf("\tEscriba la fecha: ");
	scanf("%d",&fechaAux);
	while(getchar()!='\n');
	
	// Ahora imprimimos en el fichero
	// De las variables auxilares lo guardamos al fichero
	
	fprintf(fichero,"%s\n" ,tituloAux);
	fprintf(fichero,"%s\n" ,tipoAux);
	fprintf(fichero,"%d\n" ,duracionAux);
	fprintf(fichero,"%s\n" ,plataformaAux);
	fprintf(fichero,"%s\n" ,imagenAux);
	fprintf(fichero,"%d\n" ,fechaAux);
	
	// Volcamos la información al array.
	// De mi auxiliar lo meto al array en la posición que queremos
	strcpy(info[numeroPeliculas].titulo,tituloAux);
	strcpy(info[numeroPeliculas].tipo,tipoAux);
	info[numeroPeliculas].duracion = duracionAux;
	strcpy(info[numeroPeliculas].plataforma,plataformaAux);
	strcpy(info[numeroPeliculas].imagen,imagenAux);
	info[numeroPeliculas].fecha = fechaAux;
	
	//Siempre Cerramos el fichero.
	fclose(fichero);
	// Una vez realizado todo incrementaremos una pelicula y imprimimos el contador
	numeroPeliculas++;
	// Retornamos el numero de peliculas para que se vayan sumando
	return numeroPeliculas;
}
/* -----------------------------------------------------------

						Función del caso 2

--------------------------------------------------------------*/
void mostrarArray(struct peliculasYseries info[MAXARRAY],int numeroPeliculas){
 	int parar=0;
 	// Variable para recorrer el array
	int i=0; 
	// si el contador no se suma es porque no hay nada dentro del fichero
	if(numeroPeliculas==0){
		printf("Fichero Vacio , Use la opcion 1 para añadir datos..");
	 }else{
	 	// Recorremos el array de las Peliculas / Serie
		for(i=0;i<numeroPeliculas;i++){
			
			printf("\n\n\tDato %d  de datos %d..\n",i+1,numeroPeliculas);
			printf("\t****************************************************\n");
			printf("\t\t- Titulo: %s \n",info[i].titulo); 
			printf("\t\t- Tipo: %s \n",info[i].tipo);
			printf("\t\t- Duración (min): %dmin \n",info[i].duracion);
			printf("\t\t- Plataforma: %s \n",info[i].plataforma);
			printf("\t\t- Imagen: %s \n",info[i].imagen);
			printf("\t\t- Fecha:año %d \n",info[i].fecha);
			printf("\t****************************************************\n");
			printf("\t\t**************************\n");
			printf("\t\t\t***********\n");
			parar++;
			// condición para que pare cuando sea una pelicula
			if(parar%2==0){
				parar = 0;
				system("pause");
			}
		}
	
	}
	
}
/* -----------------------------------------------------------

						Función del caso 3

--------------------------------------------------------------*/
void elegirDato(struct peliculasYseries info [MAXARRAY],int numeroPeliculas){
	system("cls");
	// Variable para recorrer el for
	int contador=0;
	// Variable donde recojo el dato que escribe el usuario
	char elegido[MAXC];
	// For para mostrar los titulos de mis Peliculas/Series
	for(contador=0; contador < numeroPeliculas; contador++){
		printf("\n\t\t---------------------------------------\n");
		// Le sumo 1 al contador para que el usuario vea la opcion como 1 y no 0 del primer caso
		printf("\t\t %d ---> %s \n",contador+1,info[contador].titulo);
	}
	printf("\n\n\tEscribe el título de película / serie que quieres leer\n\n\t\t");
	gets(elegido);
	strtok(elegido,"\n");
	if(strcmpi(info[contador].titulo,elegido)>0){
		// No consigo que entre en esta opción me mata la cabeza!!!!
		printf("En el registro no se encuentra este dato\n");
	}
	else{
		// Recorro buscando la pelicula
		for(contador=0; contador < numeroPeliculas; contador++){
			// Comparo lo recogido en el gets con mis titulos y si coincide lo imprime todo
			//strcmpi no distingue entre mayusculas y minusculas
			if(strcmpi(info[contador].titulo,elegido)==0){
				printf("\t\tEstos son los datos de tu película\n\n");
				printf("\n\t\t---------------------------------------\n");
				printf("\t\t\t- Titulo: %s \n",info[contador].titulo); 
				printf("\t\t\t- Tipo: %s \n",info[contador].tipo);
				printf("\t\t\t- Duración (min): %dmin \n",info[contador].duracion);
				printf("\t\t\t- Plataforma: %s \n",info[contador].plataforma);
				printf("\t\t\t- Imagen: %s \n",info[contador].imagen);
				printf("\t\t\t- Fecha:año %d \n",info[contador].fecha);
				printf("\n\t\t---------------------------------------\n\n");
			}
		}
	}
}
void mostrarOrdenado(struct peliculasYseries info[MAXARRAY],int numeroPeliculas){
	// Variable para recorrer el array
	int i=0;
	// si el contador no se suma es porque no hay nada dentro del fichero 
	if(numeroPeliculas==0){ 
		printf("Fichero Vacio , Use la opcion 1 para añadir datos..");
	 }else{
		for(i=0;i<numeroPeliculas;i++){
		// LLamamos a lo que tenemos en el array y su variable	
			printf("\t****************************************************\n");
			printf("\t\t- Titulo: %s \n",info[i].titulo); 
			printf("\t\t- Tipo: %s \n",info[i].tipo);
			printf("\t\t- Duración (min): %dmin \n",info[i].duracion);
			printf("\t\t- Plataforma: %s \n",info[i].plataforma);
			printf("\t\t- Imagen: %s \n",info[i].imagen);
			printf("\t\t- Fecha:año %d \n",info[i].fecha);
			printf("\t****************************************************\n");
			printf("\t\t**************************\n");
			printf("\t\t\t***********\n");
		}
	}
}
/* -----------------------------------------------------------

						Función del caso 4

--------------------------------------------------------------*/
int caso4(){
	// Declaramos la funcion como entero para que la devuelva 
	int valor;
	system("cls");
		printf(" \n\n\t\t**** ------ MENU ------- ****\n");
		printf("\n\t\t Elige sobre estas opciones\n\n");
		printf("\t\t**** ------      ------- ****\n\n");
		printf("\t 1. Ordenar por Título\n");
		// Con sleep() hacemos una pausa al programa según el valor que pongamos se traduce a esos segundos de pausa
		sleep(1);
		printf("\t 2. Ordenar por plataforma\n");
		sleep(1);
		printf("\t 3. Ordenar por tipo\n");
		sleep(1);
		printf("\t 4. Salir\n");
		sleep(1);
		scanf("%d",&valor);
	// Valor es retornado
	return valor ;
}
/* -----------------------------------------------------------

					2	Función del caso 4

--------------------------------------------------------------*/
void ordenarPlataforma(struct peliculasYseries info[], int numeroPeliculas){
	// Variables para utilizar en el for
	int i , j ;
	// Declaro otro molde para guardar el valor de j y no perderlo
	struct peliculasYseries temporal;
	printf("\t\tEsta es la opción ordenado por plataforma\n\n");
	for (i=0 ; i < numeroPeliculas ; i++){
		for(j=0 ; j < numeroPeliculas; j++){
			// Comparo lo que tengo i con j y si es menor entra en el if
			if ( strcmpi(info[i].plataforma , info[j].plataforma)<0){
				// Igualo temporal a la posición J
				temporal=info[j];
				// La posición de J a I
				info[j]= info [i];
				// La posición de I ahora es la que tenia J 
				info[i]= temporal;
			}
		}
	}
}	
/* -----------------------------------------------------------

					3	Función del caso 4

--------------------------------------------------------------*/
void ordenarTipo(struct peliculasYseries info[], int numeroPeliculas){	
	int i , j ;
	struct peliculasYseries temporal;
	printf("\t\tEsta es la opción ordenado por Tipo\n\n");
	for (i=0 ; i < numeroPeliculas ; i++){
		for(j=0 ; j < numeroPeliculas; j++){
			if ( strcmpi(info[i].tipo , info[j].tipo)<0){
				temporal=info[j];
				info[j]= info [i];
				info[i]= temporal;
			}
		}
	}
}
/* -----------------------------------------------------------

					4	Función del caso 4

--------------------------------------------------------------*/
void ordenarTitulo(struct peliculasYseries info[], int numeroPeliculas){
	int i , j ;
	struct peliculasYseries temporal;
	printf("\t\tEsta es la opción ordenado por Titulo\n\n");
	for (i=0 ; i < numeroPeliculas ; i++){
		for(j=0 ; j < numeroPeliculas; j++){
			if ( strcmpi(info[i].titulo , info[j].titulo)<0){
				temporal=info[j];
				info[j]= info [i];
				info[i]= temporal;
			}
		}
	}
}
/* -----------------------------------------------------------

						Función del caso 5

--------------------------------------------------------------*/
void crearEspecifico(struct peliculasYseries info[MAXARRAY],int numeroPeliculas){
	system("cls");
	// Variable para recorrer mis for
	int contador=0;
	// Variable donde recojo el dato que elige el usuario.
	int elegido;
	// Variable que uso para guardar el nombre del titulo y evitar que aparezca en mi archivo el titulo con html
	char nombreArchivo[MAXC];
	printf("\tPor favor, marca la posición de la pelicula que quieres ver\n\n");
	// Recorro todos los titulos
	for(contador=0; contador < numeroPeliculas; contador++){
		// el +1 del contador es para que no salga en la primera pelicula el 0 si no el 1
		printf("\t\t - %d. %s\n", contador+1 , info[contador].titulo);
	}
	printf("\n\n\t¿Que dato quieres elegir? ");
	scanf("%d",&elegido);
	while(getchar()!='\n');
	// Como le sumo uno en el printf al contador aqui se lo quito para que enseñe la posición correcta del array
	//  Le copio de el array titulo.. a nombreArchivo guardando asi su datos
	strcpy(nombreArchivo,info[elegido-1].titulo);
	// Le concateno .html para crear el fichero con esa extensión
	strcat(nombreArchivo,".html");
	FILE *fichero;
	// Utilizo mi variable "aux" para no modificar la verdadera
	fichero=fopen(nombreArchivo,"w");
	printf("\tCreando documento específico de películas....\n");
	// Da una pausa de 1 segundo al programa 
	sleep(1); 
	printf("\t3.......\n");
	sleep(1);
	printf("\t\t2.......\n");
	sleep(1);
	printf("\t\t\t1.......\n");
	sleep(1);
	printf("\t\tCreado satisfactoriamente...\n\n");
	system("pause");
	// Creamos un documento tipo html en el que vamos formando todo el cuerpo mediante fprintf
	fprintf(fichero,"<!DOCTYPE html>\n");
	fprintf(fichero,"<html lang=\"es\">\n");
	fprintf(fichero,"<head>\n");
	fprintf(fichero,"\t<meta charset=\"UTF-8\">\n");
	fprintf(fichero,"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
	// Le digo que el titulo sea el nombre que haya elegido
	fprintf(fichero,"\t<title>%s</title>\n",info[elegido-1].titulo);
	fprintf(fichero,"\t<link rel=\"stylesheet\" href=\"peliculas.css\">\n");
	fprintf(fichero,"</head>\n");
	fprintf(fichero,"<body>\n");
	fprintf(fichero,"\t<h1 class=\"titulo\"> - -><span>></span> > Yelmo Jonas < <span><</span><- - </h1>\n");
	fprintf(fichero,"\t<div class=\"contenedorPrincipal\">\n");
	fprintf(fichero,"\t\t<section class=\"contenedor\">\n");
	// Enlazamos la foto al html general al clicar sobre la imagen te devuelve al inicio.
	fprintf(fichero,"\t\t\t<a href=\"general.html\"><img src=\"imagenes/%s\" alt=\"imagen \" class=\"fotos\"></a>\n</br>",info[elegido-1].imagen);
	// Por cada dato que tenemos lo vamos mostrando en el fichero / pagina web
	fprintf(fichero,"\t\t\t<p class=\"datos\">Titulo : %s</p></br>\n",info[elegido-1].titulo);
	fprintf(fichero,"\t\t\t- Titulo: %s\n</br>",info[elegido-1].titulo); 
	fprintf(fichero,"\t\t\t- Tipo: %s\n</br>",info[elegido-1].tipo);
	fprintf(fichero,"\t\t\t- Duracion (min): %dmin\n</br>",info[elegido-1].duracion);
	fprintf(fichero,"\t\t\t- Plataforma: %s\n</br>",info[elegido-1].plataforma);
	fprintf(fichero,"\t\t\t- Imagen: %s\n</br>",info[elegido-1].imagen);
	fprintf(fichero,"\t\t\t- Fecha:anio %d\n</br>",info[elegido-1].fecha);
	fprintf(fichero,"\t\t</section>\n");
	fprintf(fichero,"\t</div>\n");
	fprintf(fichero,"</body>\n"); 
	fprintf(fichero,"</html>\n");
	fclose(fichero);
	system(nombreArchivo);
}
/* -----------------------------------------------------------

						Función del caso 6

--------------------------------------------------------------*/
void crearHtml(struct peliculasYseries info[MAXARRAY],int numeroPeliculas){
	system("cls");
	int contador=0;
	FILE *fichero;
	fichero=fopen("general.html","w");
	printf("\tCreando documento de películas....\n");
	sleep(1); 
	printf("\t3.......\n");
	sleep(1);
	printf("\t\t2.......\n");
	sleep(1);
	printf("\t\t\t1.......\n");
	sleep(1);
	printf("\t\tCreado satisfactoriamente...\n\n");
	system("pause");
	fprintf(fichero,"<!DOCTYPE html>\n");
	fprintf(fichero,"<html lang=\"es\">\n");
	fprintf(fichero,"<head>\n");
	fprintf(fichero,"\t<meta charset=\"UTF-8\">\n");
	fprintf(fichero,"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
	fprintf(fichero,"\t<title>mis peliculas</title>\n");
	fprintf(fichero,"\t<link rel=\"stylesheet\" href=\"peliculas.css\">\n");
	fprintf(fichero,"</head>\n");
	fprintf(fichero,"<body>\n");
	fprintf(fichero,"\t<h1 class=\"titulo\"> - -><span>></span> > Yelmo Jonas < <span><</span><- - </h1>\n");
	fprintf(fichero,"\t<div class=\"contenedorPrincipal\">\n");
	fprintf(fichero,"\t\t<section class=\"contenedor\">\n");
	fprintf(fichero,"\t\t\t<a href=\"general.html\"><img src=\"imagenes/cine.jpg\" alt=\"primera pelicula\" class=\"fotoPrincipal\"></a>\n");
	// Metemos un for para poder recorrer el nombre de todas las peliculas y hago de ellas la lista enlazada
	for(contador=0 ; contador<numeroPeliculas; contador++){
		fprintf(fichero,"\t\t\t<p class=\"datos\"><a href=\"%s.html\">%s</p></a></br>\n",info[contador].titulo,info[contador].titulo);
	}
	fprintf(fichero,"\t\t</section>\n");
	fprintf(fichero,"\t</div>\n");
	fprintf(fichero,"</body>\n"); 
	fprintf(fichero,"</html>\n");
	fclose(fichero);
	archivosHtml(info,numeroPeliculas);
	system("general.html");
}
/* -----------------------------------------------------------

					2 Función del caso 6

--------------------------------------------------------------*/
void archivosHtml(struct  peliculasYseries info[], int numeroPeliculas){
	system("cls");
	int contador=0;
	// Declaro una variable para guardar el titulo de archivo.
	char nombreArchivo[MAXC];
	for(contador=0 ; contador < numeroPeliculas; contador++){
		// Copio del titulo al nombre del archivo y le concateno el html
		strcpy(nombreArchivo,info[contador].titulo);
		strcat(nombreArchivo,".html");
		FILE *fichero;
		fichero=fopen(nombreArchivo,"w");
		// Creamos un archivo html por cada pelicula que tenemos guardada
		fprintf(fichero,"<!DOCTYPE html>\n");
		fprintf(fichero,"<html lang=\"es\">\n");
		fprintf(fichero,"<head>\n");
		fprintf(fichero,"\t<meta charset=\"UTF-8\">\n");
		fprintf(fichero,"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
		fprintf(fichero,"\t<title>%s</title>\n",info[contador].titulo);
		fprintf(fichero,"\t<link rel=\"stylesheet\" href=\"peliculas.css\">\n");
		fprintf(fichero,"</head>\n");
		fprintf(fichero,"<body>\n");
		fprintf(fichero,"\t<h1 class=\"titulo\"> - -><span>></span> > Yelmo Jonas < <span><</span><- - </h1>\n");	
		fprintf(fichero,"\t<div class=\"contenedorPrincipal\">\n");
		fprintf(fichero,"\t\t<section class=\"contenedor\">\n");
		fprintf(fichero,"\t\t\t-<p>Pulsando en la imagen volveras al menu de Inicio</p></br>");
		fprintf(fichero,"\t\t\t<a href=\"general.html\"><img src=\"imagenes/%s\" alt=\"imagen \" class=\"fotos\"></a>\n</br>",info[contador].imagen);
		fprintf(fichero,"\t\t\t- Titulo: %s\n</br>",info[contador].titulo); 
		fprintf(fichero,"\t\t\t- Tipo: %s\n</br>",info[contador].tipo);
		fprintf(fichero,"\t\t\t- Duracion (min): %dmin\n</br>",info[contador].duracion);
		fprintf(fichero,"\t\t\t- Plataforma: %s\n</br>",info[contador].plataforma);
		fprintf(fichero,"\t\t\t- Imagen: %s\n</br>",info[contador].imagen);
		fprintf(fichero,"\t\t\t- Fecha:anio %d\n</br>",info[contador].fecha);
		fprintf(fichero,"\t</section>\n");
		fprintf(fichero,"\t</div>\n");
		fprintf(fichero,"</body>\n");
		fprintf(fichero,"</html>\n");
		fclose(fichero);
	}	
}
