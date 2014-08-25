/*
  Archivo: matematicas.h
  Licencia: GNU-GPL
  Fecha creacion: 30 de octubre de 2003
  Fecha ultima modificacion: 10 de marzo de 2012
  Version: 0.4
  Copyright: (C) 2003-2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC, Universidad del Valle, Cali, Colombia)
*/


/**
  \class Matematicas
  \brief Funciones matemáticas que no están en las librerías estándar de C ni C++

  Ofrece unas cuentas funciones matemáticas que no están en las librerías estándar de C ni C++.
  El algoritmo que genera secuencias de números aleatorios es el Mersenne Twister tomado de internet
  y adaptado a C++, convirtiéndolo en una clase SINGLETON.

  Relaciones con otras clases y objetos:
    - Es un SINGLETON, para que la secuencia de números aleatorios sea única en toda la
      aplicación (para evitar malas interacciones entre varios objetos usando el
      generador de números aleatorios). NOTA: Esto se podría haber resuelto de otra forma mejor, que
      es dando a cada objeto que lo pida su propio generador aleatorio, pero inicializado con una semilla
      distinta y distinta cada vez que se ejecute (eso es lo dificil de lograr).
    .
*/

#ifndef MATEMATICAS_H
#define MATEMATICAS_H

#include <time.h>
#include <stdlib.h>
#include <math.h>

#ifndef uint32
typedef unsigned long int uint32;
#endif

class Matematicas
{
  public:
    /** Con esta funcion se crea el objeto singleton, o se retorna si ya estaba creado.
        @param semilla para inicializar el generador de números seudoaleatorios. Por defecto vale 0, que significa que se toma como semilla inicial un número generado a partir de la fecha y hora actual.
        @param errorFlotante Por defecto 1e-12. Si al comparar dos doubles sale menor a esto, se concluye que son iguales.
        @return el objeto singleton Matematicas.
    */
    static Matematicas *crear(uint32 semilla=0, double errorFlotante=1e-12);
    /** Destructor.
    */
    ~Matematicas();
    /** Logaritmo entero en base 2.
        Ejemplos:
          - log2(-2)=-1;
          - log2(-1)=-1;
          - log2(0)=-1;
          - log2(1)=0;
          - log2(2)=1;
          - log2(3)=1;
          - log2(4)=2;
          - log2(5)=2;
          - log2(6)=2;
          - log2(7)=2;
          - log2(8)=3; etc.
          .
        @param x El número entero del cual queremos averiguar su logaritmo en base 2.
        @return el logaritmo en base 2 del número dado.
    */
    static int log2(int x);
    /** Logaritmo entero en base 2 redondeado hacia arriba.
        Ejemplos:
          - log2ceil(-2)=0;
          - log2ceil(-1)=0;
          - log2ceil(0)=0;
          - log2ceil(1)=0;
          - log2ceil(2)=1;
          - log2ceil(3)=2;
          - log2ceil(4)=2;
          - log2ceil(5)=3;
          - log2ceil(6)=3;
          - log2ceil(7)=3;
          - log2ceil(8)=3; etc.
          .
        @param x El número entero del cual queremos averiguar su logaritmo en base 2 redondeado hacia arriba.
        @return el logaritmo en base 2 redondeado hacia arriba del número dado.
    */
    static int log2ceil(int x);
    /** Averigua cuantos bits ocupa el número dado (excluyendo el bit de signo).
        Ejemplos:
          - bits(-2)=2;
          - bits(-1)=1;
          - bits(0)=0;
          - bits(1)=1;
          - bits(2)=2;
          - bits(3)=2;
          - bits(4)=3;
          - bits(5)=3;
          - bits(6)=3;
          - bits(7)=3;
          - bits(8)=4; etc.
          .
    */
    static int bits(int x);
    /** Calcula el menor de dos números enteros.
        @param a Un número entero.
        @param b El otro número entero.
        @return el menor de los dos números enteros.
    */
    static int minimo(int a, int b);
    /** Calcula el mayor de dos números enteros.
        @param a Un número entero.
        @param b El otro número entero.
        @return el mayor de los dos números enteros.
    */
    static int maximo(int a, int b);
    /** Da un valor inicial al generador de secuencias seudoaleatorias de números.
        CAVILACIONES: Por un lado, nadie debería llamar a esta función, dado que se llama automáticamente en el constructor de Matematicas (y sólo debe ser llamada una vez, para garantizar no repeticiones y no correlaciones). Pero por otro lado, a veces conviene inicializar el generador a un valor determinado, con el objetivo de poder repetir resultados, para depurar. Quizás convenga poner dos generadores independientes (quién sabe como lograr la independencia): uno del sistema (que inicializa la semilla aleatoria únicamente en el constructor) y otro del usuario-programador (con la función srand accesible).
        @param semilla El valor inicial. Por defecto es 0, que significa que la semilla se genera
        aleatoriamente (a partir de la fecha y hora actuales).
    */
    void srand(uint32 semilla = 0);
    /** Genera el siguiente número entero positivo entre 0 (incluido) y randMax (incluido),
        de una secuencia seudoaleatoria.  La distribución es uniforme.
        @return el siguiente número de la secuencia seudoaleatoria.
    */
    int rand();
    /**
        @return el valor máximo (incluido) que puede tomar un número enteros. Si el computador y el
        compilador son de 32 bits, este número usualmente es 0x7FFFFFFF (el mayor entero positivo).
    */
    static int intMax();
    /**
        @return el valor máximo (incluido) de la secuencia seudoaleatoria de números enteros. Si
        el computador y el compilador son de 32 bits, este número usualmente es 0x7FFFFFFF (el mayor entero positivo).
    */
    static int randMax();
    /** Genera el siguiente número entero positivo entre valorMinimo (incluido si abiertoALaIzquierda
        es true) y valorMaximo (incluido si abiertoALaDerecha es true), de una secuencia seudoaleatoria.
        El rango por defecto es [valorMinimo, valorMaximo). La distribución es uniforme.
        @param valorMinimo
        @param valorMaximo
        @param abiertoALaIzquierda Por defecto, false.
        @param abiertoALaDerecha Por defecto, true.
        @return el siguiente número de la secuencia seudoaleatoria.
    */
    int randInt(int valorMinimo, int valorMaximo, bool abiertoALaIzquierda=false, bool abiertoALaDerecha=true);
    /** Genera el siguiente número entero positivo entre 0 (incluido si abiertoALaIzquierda
        es false) y valorMaximo (incluido si abiertoALaDerecha es false), de una secuencia seudoaleatoria.
        El rango por defecto es [0, valorMaximo). La distribución es uniforme.
        @param valorMaximo
        @param abiertoALaIzquierda Por defecto, false.
        @param abiertoALaDerecha Por defecto, true.
        @return el siguiente número de la secuencia seudoaleatoria.
    */
    int randInt(int valorMaximo, bool abiertoALaIzquierda=false, bool abiertoALaDerecha=true);
    /** Hace lo mismo que rand().
        @return el siguiente número de la secuencia seudoaleatoria.
    */
    int randInt();
    /** Genera el siguiente número flotante positivo entre valorMinimo (incluido si abiertoALaIzquierda
        es false) y valorMaximo (incluido si abiertoALaDerecha es false), de una secuencia seudoaleatoria.
        El rango por defecto es [valorMinimo, valorMaximo). La distribución es uniforme.
        @param valorMinimo
        @param valorMaximo
        @param abiertoALaIzquierda Por defecto, false.
        @param abiertoALaDerecha Por defecto, true.
        @return el siguiente número de la secuencia seudoaleatoria.
    */
    double randDouble(double valorMinimo, double valorMaximo, bool abiertoALaIzquierda=false, bool abiertoALaDerecha=true);
    /** Genera el siguiente número entero positivo entre valorMinimo (incluido si abiertoALaIzquierda
        es false) y valorMaximo (incluido si abiertoALaDerecha es false), de una secuencia seudoaleatoria.
        El rango por defecto es [valorMinimo, valorMaximo). La distribución es gaussiana con el valor
        medio y la desviacionTipica que se desee. La distribución está acotada entre unos valores mínimo y
        máximo por razones prácticas.
        Se emplea el método polar descrito en el libro de [Ross 1988]. Hay un pequeñísimo sesgo (el
        valorMedio sale con una probabilidad ligerísimamente mayor a la teórica, para evitar un potencial
        bucle infinito en el algoritmo).
        @param valorMedio
        @param valorMinimo
        @param valorMaximo
        @param abiertoALaIzquierda Por defecto, false.
        @param abiertoALaDerecha Por defecto, true.
        @param desviacionTipica Por defecto, 1.
        @return el siguiente número de la secuencia seudoaleatoria.
    */
    double randGaussiano(double valorMedio, double valorMinimo, double valorMaximo, bool abiertoALaIzquierda=false, bool abiertoALaDerecha=true, double desviacionTipica=1);
    /** Genera el siguiente booleano de una secuencia seudoaleatoria.
        Los valores posibles son {true, false} y son equiprobables.
        @return el siguiente booleano de la secuencia seudoaleatoria.
    */
    bool randBool();
    /** Compara dos números double. Si la diferencia absoluta es menor que errorFlotante, son iguales.
      @param unDouble
      @param otroDouble
      @return true si son iguales; y false en caso contrario
    */
    bool iguales(double unDouble, double otroDouble) const;

  private:
    double errorFlotante;
    const uint32 N;
    const uint32 M;
    const uint32 K;
    uint32 *state;
    uint32 *next;
    int left;
    Matematicas(const Matematicas &); // Constructor de copia deshabilitado
    Matematicas & operator = (const Matematicas &); // Asignacin deshabilitada
    Matematicas(double errorFlotante);  // Deshabilitado el constructor
    static Matematicas *una_sola_vez;

  protected:
    uint32 hiBit(uint32 u);
    uint32 loBit(uint32 u);
    uint32 loBits(uint32 u);
    uint32 mixBits(uint32 u, uint32 v);
    void seedMT(uint32 seed);
    uint32 reloadMT(void);
    uint32 randomMT(void);
};

#else
class Matematicas;  // Declaración adelantada
#endif


