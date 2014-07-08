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

#include "matematicas.h"

Matematicas *Matematicas::una_sola_vez = 0;   // Para hacer el singleton


Matematicas::Matematicas(double errorFlotante)
  : errorFlotante(errorFlotante), N(624), M(397), K(0x9908B0DFU)
{
  state = new uint32 [N+1];
  srand(1);
}


Matematicas::~Matematicas()
{
  delete [] state;
}


Matematicas *Matematicas::crear(uint32 semilla, double errorFlotante)
{
  if(una_sola_vez == 0)
  {
    una_sola_vez = new Matematicas(errorFlotante);
    una_sola_vez->srand(semilla);
  }
  return una_sola_vez;
}


int Matematicas::log2(int x)
{
  if(x<=0)
    return -1;

  unsigned int cuenta = 0;

  // 1 byte = 8 bits
  while(cuenta < 8*sizeof(x))
  {
    x = x >> 1;
    if(x == 0)
      break;
    cuenta++;
  }

  return cuenta;
}


int Matematicas::log2ceil(int x)
{
  return log2(x - 1) + 1;
}


int Matematicas::bits(int x)
{
  return log2(x>0?x:-x) + 1;
}


int Matematicas::minimo(int a, int b)
{
  if(a < b)
    return a;
  return b;
}


int Matematicas::maximo(int a, int b)
{
  if(a > b)
    return a;
  return b;
}


void Matematicas::srand(uint32 semilla)
{
  if(semilla == 0)
    semilla = time(0);
  Matematicas::seedMT(semilla);
}


int Matematicas::rand()
{
  return Matematicas::randomMT() & randMax();
}


int Matematicas::intMax()
{
  return int(0x7FFFFFFF);
}


int Matematicas::randMax()
{
  return int(0x7FFFFFFF);
}


int Matematicas::randInt()
{
  return rand();
}


int Matematicas::randInt(int valorMinimo, int valorMaximo, bool abiertoALaIzquierda, bool abiertoALaDerecha)
{
  if(abiertoALaIzquierda)
    valorMinimo++;
  if( ! abiertoALaDerecha)
    valorMaximo++;

  if(valorMinimo >= valorMaximo)
    return valorMinimo;

  /*
     Todo el siguiente artificio se hace para evitar sesgos con el operador % cuando el divisor
     no es potencia de dos. Funciona así: el valor aleatorio se extrae a partir del rango (diferencia
     entre valor máximo y mínimo) sumadose después al valor mínimo. El rango se modifica a la potencia
     exacta de dos que sea igual o superior a él. Con un bucle while se eliminan los posibles
     resultados que, quedando dentro del rango modificado, quedan por fuera del rango real.
  */
  int rango = valorMaximo - valorMinimo;
  int bits = log2(rango - 1) + 1;
  int modulo = 1 << bits;  // pow(2, bits);
  int prueba;
  do
  {
    prueba = Matematicas::rand() % modulo; // No hay sesgo porque modulo es potencia de 2
  }while(prueba >= rango);

  return valorMinimo + prueba;
}


int Matematicas::randInt(int valorMaximo, bool abiertoALaIzquierda, bool abiertoALaDerecha)
{
  return randInt(0, valorMaximo, abiertoALaIzquierda, abiertoALaDerecha);
}


double Matematicas::randDouble(double valorMinimo, double valorMaximo, bool abiertoALaIzquierda, bool abiertoALaDerecha)
{
  if(valorMinimo >= valorMaximo)
    return valorMinimo;

  int cte1;
  if(abiertoALaIzquierda)
    cte1 = 1;
  else
    cte1 = 0;

  int cte2;
  if(abiertoALaDerecha)
    cte2 = 1;
  else
    cte2 = 0;

  double rango = valorMaximo - valorMinimo;
  return valorMinimo +  rango * (cte1+randInt(randMax()-cte1-cte2))/double(randMax());
}


// Método Polar dscrito en el libro de [Ross 1988]
double Matematicas::randGaussiano(double valorMedio, double valorMinimo, double valorMaximo, bool abiertoALaIzquierda, bool abiertoALaDerecha, double desviacionTipica)
{
  double v1, v2, s, resultado;

  if(desviacionTipica == 0)
    return valorMedio;

  for(int contador = 0; contador < 100; contador++)
  {
    do
    {
      v1 = 2 * randDouble(0,1) - 1;
      v2 = 2 * randDouble(0,1) - 1;
      s = v1 * v1 + v2 * v2;
    }
    while(s >= 1.0 or s == 0);

    resultado = sqrt((-2 * log(s)) / s) * v1;

    resultado = valorMedio + desviacionTipica * resultado;

    if(abiertoALaIzquierda)
    {
      if(abiertoALaDerecha)
      {
        if(valorMinimo < resultado and resultado < valorMaximo)
          return resultado;
      }
      else
      {
        if(valorMinimo < resultado and resultado <= valorMaximo)
          return resultado;
      }
    }
    else
    {
      if(abiertoALaDerecha)
      {
        if(valorMinimo <= resultado and resultado < valorMaximo)
          return resultado;
      }
      else
      {
        if(valorMinimo <= resultado and resultado <= valorMaximo)
          return resultado;
      }
    }
  }

  // Esto es una pequeña chapuza, para evitar un posible bucle infinito.
  // En realidad, no es tan chapuza. Es bastante razonable, pues casi no introduce sesgo.
  return randDouble(valorMinimo, valorMaximo, abiertoALaIzquierda, abiertoALaDerecha);
}


bool Matematicas::randBool()
{
  return (Matematicas::rand() % 2) ? true : false;
}


/* Funciones protected */


uint32 Matematicas::hiBit(uint32 u)
{
  return u & 0x80000000U;
}


uint32 Matematicas::loBit(uint32 u)
{
  return u & 0x00000001U;
}


uint32 Matematicas::loBits(uint32 u)
{
  return u & 0x7FFFFFFFU;
}

uint32 Matematicas::mixBits(uint32 u, uint32 v)
{
  return hiBit(u) | loBits(v);
}


void Matematicas::seedMT(uint32 seed)
{
  // Los siguientes comentarios están tomados directamente del código original:
  //
  // We initialize state[0..(N-1)] via the generator
  //
  //   x_new = (69069 * x_old) mod 2^32
  //
  // from Line 15 of Table 1, p. 106, Sec. 3.3.4 of Knuth's
  // _The Art of Computer Programming_, Volume 2, 3rd ed.
  //
  // Notes (SJC): I do not know what the initial state requirements
  // of the Mersenne Twister are, but it seems this seeding generator
  // could be better.  It achieves the maximum period for its modulus
  // (2^30) iff x_initial is odd (p. 20-21, Sec. 3.2.1.2, Knuth); if
  // x_initial can be even, you have sequences like 0, 0, 0, ...;
  // 2^31, 2^31, 2^31, ...; 2^30, 2^30, 2^30, ...; 2^29, 2^29 + 2^31,
  // 2^29, 2^29 + 2^31, ..., etc. so I force seed to be odd below.
  //
  // Even if x_initial is odd, if x_initial is 1 mod 4 then
  //
  //   the          lowest bit of x is always 1,
  //   the  next-to-lowest bit of x is always 0,
  //   the 2nd-from-lowest bit of x alternates      ... 0 1 0 1 0 1 0 1 ... ,
  //   the 3rd-from-lowest bit of x 4-cycles        ... 0 1 1 0 0 1 1 0 ... ,
  //   the 4th-from-lowest bit of x has the 8-cycle ... 0 0 0 1 1 1 1 0 ... ,
  //    ...
  //
  // and if x_initial is 3 mod 4 then
  //
  //   the          lowest bit of x is always 1,
  //   the  next-to-lowest bit of x is always 1,
  //   the 2nd-from-lowest bit of x alternates      ... 0 1 0 1 0 1 0 1 ... ,
  //   the 3rd-from-lowest bit of x 4-cycles        ... 0 0 1 1 0 0 1 1 ... ,
  //   the 4th-from-lowest bit of x has the 8-cycle ... 0 0 1 1 1 1 0 0 ... ,
  //    ...
  //
  // The generator's potency (min. s>=0 with (69069-1)^s = 0 mod 2^32) is
  // 16, which seems to be alright by p. 25, Sec. 3.2.1.3 of Knuth.  It
  // also does well in the dimension 2..5 spectral tests, but it could be
  // better in dimension 6 (Line 15, Table 1, p. 106, Sec. 3.3.4, Knuth).
  //
  // Note that the random number user does not see the values generated
  // here directly since reloadMT() will always munge them first, so maybe
  // none of all of this matters.  In fact, the seed values made here could
  // even be extra-special desirable if the Mersenne Twister theory says
  // so-- that's why the only change I made is to restrict to odd seeds.
  //
  register uint32 x = (seed | 1U) & 0xFFFFFFFFU, *s = state;
  register int    j;

  for(left=0, *s++=x, j=N; --j;
    *s++ = (x*=69069U) & 0xFFFFFFFFU);
}


uint32 Matematicas::reloadMT(void)
{
  register uint32 *p0=state, *p2=state+2, *pM=state+M, s0, s1;
  register int    j;

  if(left < -1)
    seedMT(4357U);

  left=N-1, next=state+1;

  for(s0=state[0], s1=state[1], j=N-M+1; --j; s0=s1, s1=*p2++)
    *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? K : 0U);

  for(pM=state, j=M; --j; s0=s1, s1=*p2++)
    *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? K : 0U);

  s1=state[0], *p0 = *pM ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? K : 0U);
  s1 ^= (s1 >> 11);
  s1 ^= (s1 <<  7) & 0x9D2C5680U;
  s1 ^= (s1 << 15) & 0xEFC60000U;
  return s1 ^ (s1 >> 18);
}


uint32 Matematicas::randomMT(void)
{
  uint32 y;

  if(--left < 0)
    return reloadMT();

  y  = *next++;
  y ^= (y >> 11);
  y ^= (y <<  7) & 0x9D2C5680U;
  y ^= (y << 15) & 0xEFC60000U;
  return y ^ (y >> 18);
}


bool Matematicas::iguales(double unDouble, double otroDouble) const
{
  return fabs(unDouble - otroDouble) < errorFlotante;
}
