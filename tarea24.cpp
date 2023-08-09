/*Utilizando el lenguaje C++, resuelva los siguientes ejercicios:

1) Codifique los algoritmos de ordenación: secuencial, burbuja, shell, quick sort. Agregue la rutina para medir el tiempo de ejecución de una función. (Realizado en clases)

2) Mida los tiempos de ejecución de los algoritmos de ordenación del punto 1, para 10, 20, 30, 40 y 50 elementos. Registre sus resultados en un documento de Excel.
En el mismo documento de Excel, escriba la conclusión referente al tiempo de ejecución empleado por los algoritmos al ordenar un vector con pocos elementos.
3) Mida los tiempos de ejecución de los algoritmos de ordenación del punto 1, para 1000, 5000, 10000, 25000, 50000 y 70000 elementos. Registre sus resultados en una hoja de Excel. ¿Qué puede concluir, luego de registrar los resultados?
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

void imprimirVector(int vector[], int tamanio )
{
    cout << endl <<"Los elementos del vector son: ";
    for(int k=0; k<tamanio; k++)
    {
        cout << vector[k] << " - ";
    }
}

void intercambiar(int &a, int&b)
{
    int aux = a;
    a = b;
    b = aux;
}

void ordenacionSecuencial(int vector[], int MAX)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = i+1; j < MAX; j++)
        {
            if (vector[i]>vector[j])
            {   
                int aux = vector[i];
                vector[i] = vector[j];
                vector[j] = aux;
            }
            
        }
        
    }
    
}

void ordenBurbuja(int vector[], int MAX){
    int i=0,j=0;
    int aux;
    for(i=1;i<MAX;i++)
    {    
        for(j=0;j<(MAX-i);j++)
        {
            if(vector[j]>vector[j+1])
            {
                aux=vector[j];
                vector[j]=vector[j+1];
                vector[j+1]=aux;
            }
        }
    }    
}

void ordenBurbujaMejorado(int arreglo[], int tamano)
{
    int comparaciones = tamano;
    bool termino = false;
    for (int i = 0; i<(tamano-1) ; i++)
    {
        if (termino)
            break;
        termino = true;
        for (int j = 0; j<comparaciones-1 ; j++)
            if(arreglo[j] > arreglo[j+1])
            {
                intercambiar(arreglo[j],arreglo[j+1]);
                termino = false;
            }
        comparaciones--;
    }
}

void OrdenamientoQuicksort(int a[], int primerValor, int ultimoValor)
{
    int central, i, j, pivote;
    central= (primerValor+ultimoValor)/2; //Posicion central del arreglo
    pivote= a[central]; //Capturar el valor medio del arreglo
    i = primerValor;
    j = ultimoValor;
    do
    {
        //Separando en dos partes el arreglo
        while(a[i] < pivote) i++; //Separando los valores menores al pivote
        while(a[j] > pivote) j--; //Separando los valores mayores al pivote
        if(i<=j)
        {
            int temporal;
            temporal = a[i];
            a[i] = a[j];
            a[j] = temporal;
            i++;
            j--;
        }
    }
    while(i<=j);
    if (primerValor < j)
        OrdenamientoQuicksort(a, primerValor, j);
    if (i < ultimoValor)
        OrdenamientoQuicksort(a, i, ultimoValor);
}

void ordenShell(int a[], int n){
    int ints,i,aux;
    bool band;
    ints=n;
    while(ints>1)
    {
        ints=ints/2;
        band=true;
        while(band==true)
        {
            band=false;
            i=0;
            while((i+ints)<n)
            {
                if(a[i]>a[i + ints])
                {
                    aux=a[i];
                    a[i]=a[i + ints];
                    a[i + ints]=aux;
                    band=true;
                }
                i++;
            }
        }
    }
}

void ordenShellOptima3(int a[], int n)
{
    int i,j,inc;
    int temp;
    for(inc=1;inc<n;inc=inc*3+1);
    while(inc>0)
    {
        for(i=inc;i<n;i++)
        {
            j=i;
            temp=a[i];
            while((j>=inc)&&(a[j-inc]>temp))
            {
                a[j]=a[j-inc];
                j=j-inc;
            }
            a[j]=temp;
        }
        inc=inc/2;
    }
}

main ()
{
    LARGE_INTEGER t_ini, t_fin;
    double secs;

    srand(time(NULL));
    const int MAX = 20;
    int vectorsecuencial[MAX];
    int vectorburbuja[MAX];
    int vectorburbujaOp[MAX];
    int vectorquickshort[MAX];
    int vectorshell[MAX];
    int vectorshellOp[MAX];

    for(int k=0; k<MAX; k++)
    {
        int num=1+rand()%(10000);
        vectorsecuencial[k]=num;
        vectorburbuja[k]=num;
        vectorburbujaOp[k]=num;
        vectorquickshort[k]=num;
        vectorshell[k]=num;
        vectorshellOp[k]=num;
    }

    // BEYOTA
    QueryPerformanceCounter(&t_ini);
    ordenacionSecuencial(vectorsecuencial, MAX);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo empleado por el algoritmo secuencial "<<secs * 1000.0;

    // BURBUJA
    QueryPerformanceCounter(&t_ini);
    ordenBurbuja(vectorburbuja, MAX);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo empleado por el algoritmo burbuja " <<secs * 1000.0;

    // BURBUJA OP
    QueryPerformanceCounter(&t_ini);
    ordenBurbujaMejorado(vectorburbujaOp, MAX);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo empleado por el algoritmo burbuja optimizado " <<secs * 1000.0;

    // Mojo Mojo
    QueryPerformanceCounter(&t_ini);
    OrdenamientoQuicksort(vectorquickshort, 0, MAX-1);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo empleado por el algoritmo quick short " <<secs * 1000.0;
        
    // BOMBOM
    QueryPerformanceCounter(&t_ini);
    ordenShell(vectorshell, MAX);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo empleado por el algoritmo shell " <<secs * 1000.0;
    
    // BOMBOM OP
    QueryPerformanceCounter(&t_ini);
    ordenShellOptima3(vectorshellOp, MAX);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo empleado por el algoritmo shell optimizado " <<secs * 1000.0;


    return 0;
}