#include "HuffmanCode.h"

Arbol crearNodo(Dato valor){
    Arbol arbol=(Arbol) malloc(sizeof(Elemento_De_Arbol_Binario));
    if(arbol==NULL){
        perror("No hay memoria para tu nodo");
    } else{
        arbol->izq=NULL;
        arbol->der=NULL;
        arbol->info=valor;
    }
    return arbol;
}


//Funcion devuelve la raiz del arbol creado
/**
 * @param raiz Nueva raiz con Hijo izquierdo e hijo derecho, con valorRaiz como clave
 * @param Hizq  Nodo que se coloca a la izquierda del nuevo nodo raiz, previamente creado o NULL
 * @param Hder Nodo ue se coloca a la derecha del nuevo nodo raiz, previamente creado o NULL
 */
void nuevoArbol(Arbol* raiz, Arbol Hizq, Arbol Hder, Dato valorRaiz){ 
    (*raiz) = crearNodo(valorRaiz);
    (*raiz)->der=Hder;
    (*raiz)->izq=Hizq;
}

/**
* @param raiz Raiz del subarbol donde se contara la profundidad
*/
int profundidadArbol(Arbol raiz){ 
    if(!raiz){
        return 0;
    } else{
        int profundidadIzq, profundidadDerecha;
        profundidadIzq=profundidadArbol(raiz->izq);
        profundidadDerecha=profundidadArbol(raiz->der);
        if(profundidadIzq>profundidadDerecha)
            return profundidadIzq+1;
        else 
            return profundidadDerecha+1;
    }
}

void contarHojas(Arbol raiz, int* contadorHojas){
    if(raiz){
        contarHojas(raiz->izq,contadorHojas);
        contarHojas(raiz->der, contadorHojas);
        if(raiz->izq==NULL && raiz->der==NULL)
            (*contadorHojas)++;
    }
}

void preOrden(Arbol raiz){ 
    if(raiz){
		printf("letra:%c-frec:%d,",raiz->info.caracter, raiz->info.frecuencia);
		preOrden(raiz->izq);
		preOrden(raiz->der);
	}
}

void posOrden(Arbol raiz){ 
	if(raiz){
		posOrden(raiz->izq);
		posOrden(raiz->der);
		printf("letra:%c-frec:%d,",raiz->info.caracter, raiz->info.frecuencia);
	}
}

void inOrden(Arbol raiz){ 
	if(raiz){
		inOrden(raiz->izq);
		printf("letra:%c-frec:%d,",raiz->info.caracter, raiz->info.frecuencia);
		inOrden(raiz->der);
	}
}

void eliminarArbol(Arbol* raiz){ 
    if(*raiz){
        eliminarArbol(&((*raiz)->izq));
        eliminarArbol(&((*raiz)->der));
        free(*raiz);
		*raiz=NULL;
    }
}

void buscarNodo(Arbol raiz, Dato valor, Arbol* nodoEncontrado){ 
    if(raiz){
        if(raiz->info.frecuencia==valor.frecuencia){
            *nodoEncontrado=raiz;       //Aqui se sobre escribe el valor nulo, por el valor encontrado.
        } else if(valor.frecuencia>raiz->info.frecuencia){
            buscarNodo(raiz->der, valor, nodoEncontrado);
        } else{
            buscarNodo(raiz->izq, valor, nodoEncontrado);
        }
    } 
}


void ingresarNodo(Arbol* raiz, Dato valor){ 
    if(!(*raiz)){
        (*raiz)=crearNodo(valor);
    } else if(valor.frecuencia<(*raiz)->info.frecuencia){
        ingresarNodo(&((*raiz)->izq),valor);
    } else if(valor.frecuencia>=(*raiz)->info.frecuencia){
        ingresarNodo(&((*raiz)->der),valor);
    }
}


void eliminarNodo(Arbol* raiz, Dato valor){ 
    if((*raiz)){
		Arbol aux=(*raiz);
		if(valor.frecuencia==(*raiz)->info.frecuencia){
			printf("\nSe encontro el nodo con el valor %d\n", (*raiz)->info.frecuencia);
			if(aux->izq==NULL){
				*raiz=aux->der;
			} else if (aux->der==NULL){
				*raiz=aux->izq;
			} else{
				reemplazar(&aux);
			}
			free(aux);
			aux=NULL;
		}else if(valor.frecuencia<(*raiz)->info.frecuencia)
			eliminarNodo(&((*raiz)->izq),valor);
		else if(valor.frecuencia>(*raiz)->info.frecuencia)
			eliminarNodo(&((*raiz)->der),valor);
	}
}


//Nodo será en un principio el nodo a eliminar (solicitado por el usuario),
//Despues se convertira en el nodo más pequeño, para que este sea quien se elimine.
void reemplazar(Arbol* nodo){ 
    Arbol nodoMinimo, nodoAnterior;
    nodoAnterior=*nodo;
    //Se busca el valor más pequeño en el sub arbol derecho
    nodoMinimo=(*nodo)->der;
    while(nodoMinimo->izq!=NULL){ 
        nodoAnterior=nodoMinimo;
        nodoMinimo=nodoMinimo->izq;
    }
	//Se respalda el valor pequeño para despues asignarse al nodo raiz
    Dato aux=nodoMinimo->info;
	//Se asigna un valor muy pequeño provisional, ya que en cualquier caso de que 
	//el valor más pequeño resulte ser el mismo valor que el que se desea eliminar esto provocará un 
	//bucle infinito
	(*nodo)->info.frecuencia=0;
    //Se borra el nodo minimo
    eliminarNodo(nodo,nodoMinimo->info);
	 //Se reemplaza el nodo a eliminar por el nodo con valor más pequeño
	(*nodo)->info=aux;
    //Se marca el nodominimo para eliminación    
    *nodo=nodoMinimo;
}

Arbol deleteNodeBST(Arbol raiz, Dato valor) {
  // Return el mismo arbol si es que esta vacio
  if (raiz == NULL) 
	  return raiz;

  // Encontrando el nodo para eliminarse 
  if (valor.frecuencia < raiz->info.frecuencia)
    raiz->izq = deleteNodeBST(raiz->izq, valor);
  else if (valor.frecuencia > raiz->info.frecuencia)
    raiz->der = deleteNodeBST(raiz->der, valor);
  else {
	  //Se evalua caso de que el nodo a eliminar tenga un hijo o 0 hijos
    if (raiz->izq == NULL) {
      Arbol temp = raiz->der;
      free(raiz);
      return temp;
    } else if (raiz->der == NULL) {
      Arbol temp = raiz->izq;
      free(raiz);
      return temp;
    }
    // En caso de que se tengan dos hijos
    Arbol temp = nodoMinimo(raiz->der);
    // Reemplaza el nodo solicitado por el usuario por el más pequeño del subarbol derecho
    raiz->info = temp->info;
    // Elimina el nodo más pequeño del sub-arbol derecho, utilizado para remplazar al nodo eliminado por el usuario
    raiz->der = deleteNodeBST(raiz->der, temp->info);
  }
  return raiz;
}


// Funcion para encontrar el valor más pequeño de un arbol
Arbol nodoMinimo(Arbol nodo) {
  Arbol actual = nodo;
  // Buscamos en todos los subarboles izquierdos
  while (actual && actual->izq != NULL)
    actual = actual->izq;
  return actual;
}

//Funciones Huffman
void ordenar(Arbol* arreglo, int tam){
    int i,j;
    struct nodo* temp;
    for(i=1; i<tam;i++){
        for(j=0; j<tam-1; j++){
            if(arreglo[j]->info.frecuencia > arreglo[j+1]->info.frecuencia){
                temp=arreglo[j];
                arreglo[j]=arreglo[j+1];
                arreglo[j+1]=temp;
            }
        }
    }
}

/**
 * @param r raiz del arbol completo donde se buscará el nodo
 * @param codigo Arreglo donde se guardara el código del caracter
 * @param n pos en el arreglo de codigos, una pos por cada nivel que se recorre
 */
void asignaCodigo(Arbol r, int codigo[], int n, FILE * codigo_salida){
    int i;
    if((r->izq==NULL) && (r->der==NULL)){
        fprintf(codigo_salida,"\n\t%c Codigo: ",r->info.caracter);
        for(i=0; i< n; i++){
           fprintf(codigo_salida,"%d", codigo[i]);
        }
    }else{
        codigo[n]=0; //Suponemos que siempre ira por la izquierda
        n++;
        asignaCodigo(r->izq,codigo,n, codigo_salida);
        codigo[n-1]=1; //Por si el recorrido tuvo que ser por la derecha
        asignaCodigo(r->der,codigo,n, codigo_salida);
    }
}

//lista doblemente enlazada

void crearLista(Lista* lista, int* error){
    *lista=NULL;//*lista=0
    *error=0;
}

void insertarElementoFrente(Lista* lista, int* error, struct Elemento element){   
    struct Elemento* nuevoElemento= (struct Elemento*) malloc(sizeof(struct Elemento));
    if(nuevoElemento==NULL){
        perror("Memoria insuficiente");
        *error=-2;
    }else{
        nuevoElemento->dato=element.dato;
        nuevoElemento->posicion=-1;
        nuevoElemento->siguiente=*lista;
        *lista=nuevoElemento;
        
        Lista cursor=*lista;
        while(cursor!=NULL){
            cursor->posicion++;
            cursor=cursor->siguiente;
        }
        *error=0;
    }
}
 

void insertarElementoFinal(Lista* lista, int* error, struct Elemento element){ 
    struct Elemento* nuevoElemento= (struct Elemento*) malloc(sizeof(struct Elemento));
    if(nuevoElemento==NULL){
        perror("Memoria insuficiente");
        *error=-2;
    }else{
        nuevoElemento->dato=element.dato;
        nuevoElemento->posicion=-1;
        nuevoElemento->siguiente=*lista;
        *lista=nuevoElemento;
        
        Lista cursor=*lista;
        while(cursor!=NULL){
            cursor->posicion++;
            cursor=cursor->siguiente;
        }
        *error=0;
    }
}

void insertarElementoPos(Lista* lista, int* error, struct Elemento element, int pos){  

}

void extraerElementoFrente(Lista* lista, int* error, struct Elemento* element){  
    if(!estaVacia(*lista, error)){
        element->dato=(*lista)->dato;
        struct Elemento* aux=*lista;
        *lista=aux->siguiente;
        free(aux);
        aux=*lista;
        while(aux!=NULL){
            aux->posicion--;
            aux=aux->siguiente;
        }
        *error=0;
    } else{
        puts("Lista vacia, no hay elementos que extraer");
    }
}

void extraerElementoFinal(Lista* lista, int* error, struct Elemento* element){  
    Lista actual=*lista;
    Lista anterior=NULL;
    if(!estaVacia(*lista,error)){
        while(actual->siguiente!=NULL){
            anterior=actual;
            actual=actual->siguiente;
        }
        if(actual==*lista){
            *lista=actual->siguiente;
        } else{
            anterior->siguiente=actual->siguiente;
        }
        element->dato=actual->dato;
        anterior->siguiente=NULL;
        actual->anterior=NULL;
        free(actual);
        *error=0;
        if(estaVacia(*lista,error)){
            *error=-1;
            puts("Se extrajo el ultimo elemento");
        }
    } else{
        printf("Lista, vacia.No hay elementos que extraer");
    }
}

void extraerElementoPos(Lista* lista, int* error, struct Elemento* element, int pos){ 

}
   
bool estaVacia(Lista lista, int* error){    
    if(lista==NULL){
        *error=-1;
        return true;
    } else{
        *error=0;
        return false;
    }
}

int obtenerLongitud(Lista list, int* error){    
    int contador=0;
    if(estaVacia(list,error)){
        return contador;
    } else{
        while(list!=NULL){
            list=list->siguiente;
            contador++;
        }
        return contador;
    }
}

void recorrerLista(Lista list, int* error){   
    while (list != NULL) {
        printf("%c ", list->dato->info.caracter);//!----------------------------------
        list = list->siguiente;
    }
}

void borrarLista(Lista* list, int* error){    
    Lista actual;
    while(*list!=NULL){
        actual=*list;
        *list=(*list)->siguiente;
        free(actual);
    }
    list=NULL;
    *error=0;
}

//merge
struct Elemento* SortedMerge(struct Elemento* a, struct Elemento* b)
{
    struct Elemento* result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
 
    /* Pick either a or b, and recur */
    if (a->dato->info.frecuencia <= b->dato->info.frecuencia) { //!---------------------------------------------
        result = a;
        result->siguiente = SortedMerge(a->siguiente, b);
    }
    else {
        result = b;
        result->siguiente = SortedMerge(a, b->siguiente);
    }
    return (result);
}

void FrontBackSplit(struct Elemento* source, struct Elemento** frontRef, struct Elemento** backRef)
{
    struct Elemento* fast;
    struct Elemento* slow;
    slow = source;
    fast = source->siguiente;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->siguiente;
        if (fast != NULL) {
            slow = slow->siguiente;
            fast = fast->siguiente;
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->siguiente;
    slow->siguiente = NULL;
}

void MergeSort(struct Elemento** headRef)
{
    struct Elemento* head = *headRef;
    struct Elemento* a;
    struct Elemento* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->siguiente == NULL)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

void deCodificar(Arbol r, char codigo[], int n){
   
    Arbol aux = r;
    char salida[90];
    int contador = 0;

      for (int i = 0; i < n; i++)
      {
          if(codigo[i]=='1'){
              aux = aux->der;

                if((aux->izq==NULL)&&(aux->der==NULL)){
                    salida[contador] = aux->info.caracter;
                    contador++;
                    aux = r;
                }
          }
          if(codigo[i]=='0'){
              aux = aux->izq;

                if((aux->izq==NULL)&&(aux->der==NULL)){
                    salida[contador] = aux->info.caracter;
                    contador++;
                    aux = r;
                }

          }

         }
         printf("%s\n", salida);

    
}

void iniciaOperacion(int argc, char** argv){
    Arbol raiz;
    int contador,sumaFrecuencias,codigo[20];
    //Arreglo de arboles
    char letra;
    Lista list; 
    int error;
    crearLista(&list, &error);
    Arbol* arreglo=(Arbol*) malloc(sizeof(Arbol)*20);//Hasta 20 subarboles
    if(arreglo==NULL){
        perror("Se acabo la memoria para el arreglo de arboles");
        exit(1);
    }
    printf("---C%cdigo de Huffman---\n",162);
    char texto[50];
    FILE *archivo=fopen("texto.txt","r");
    if(archivo==NULL){
        puts("El archivo no se encontro");
        exit(1);
    }
    fgets(texto,35,archivo);

    fclose(archivo);
    printf("\n%s\n",texto);
    //obtenemos las frecuencias 
    int arreglo_salida [255];
    for(int i=0; i<255; i++){
        arreglo_salida[i]=0;
    }
    contador = strlen(texto);
    for(int i=0; i<contador; i++){
        arreglo_salida[texto[i]]++;
    }
    //las pasamos a las estructuras
    int n = 0;
    struct Elemento element;
    for(int i=0; i<255; i++){
        //printf("valores leidos: ca=%c, f=%d",dato,frecuencia);
        if(arreglo_salida[i]>0){
            letra = (char) i;
            Dato nuevoCar={arreglo_salida[i],letra};
            printf("El caracter es: %c y la frecuencia: %d\n",nuevoCar.caracter,nuevoCar.frecuencia);
            element.dato=crearNodo(nuevoCar); //Ingresa el arreglo con los datos al arreglo
            insertarElementoFinal(&list,&error,element);
            n++;
        }
    }

    //for(int i=0; i<n; i++){
    //    struct Elemento element;
    //    element.dato = arreglo[i];
        //pasamos el arreglo a la lista
    //    insertarElementoFinal(&list, &error, element);
    //}
    struct Elemento der;
    struct Elemento izq;
    while(n!=1){ //Mientras que no se haya construido un árbol de HUFFMAN
        MergeSort(&list);  //Ordena el arreglo
        extraerElementoFrente(&list,&error, &izq);
        extraerElementoFrente(&list,&error, &der);
        sumaFrecuencias=der.dato->info.frecuencia+izq.dato->info.frecuencia;
        Dato nuevaRaiz={sumaFrecuencias,'*'}; //Construcción del nuevo subárbol
        //nuevoArbol(raiz,arreglo[0],arreglo[1],nuevaRaiz);
        raiz = (Arbol) malloc(sizeof(Elemento_De_Arbol_Binario));
        raiz->der = der.dato;
        raiz->izq = izq.dato;
        raiz->info= nuevaRaiz;
        printf("se crea raiz: c=%c, frecSuma=%d\n", (raiz)->info.caracter,(raiz)->info.frecuencia);
        der.dato=raiz;
        insertarElementoFrente(&list,&error,der);
        n--;
        printf("la longitud: %d\n", n);
    }
    //Se le asigna el código a cada caracter que hay en el árbol de Huffman
    FILE * codigo_salida = NULL;
    codigo_salida = fopen("out.txt","w");
    if(codigo_salida == NULL){
        exit(1);
    }
    asignaCodigo(list->dato,codigo,0,codigo_salida);
    printf("\n");
    //Eliminación de árbol y liberación de memoria.
    char codigof[90] = "01101111000010110001010111000111111101100001100101010010011101100010001111011110101";
    deCodificar(raiz, codigof, 83);
    eliminarArbol(&(list->dato));
    borrarLista(&list,&error);
}