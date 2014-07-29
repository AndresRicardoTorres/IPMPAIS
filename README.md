# IPMPAIS
Optimización de los pesos de los puntajes de admisión a una carrera
universitaria

## Introducción
IPMPAIS (Identificando Puntajes Mínimos para el Plan Académico de Ingeniería
de Sistemas), es una herramienta que permite hacer una estimación de los
puntajes mínimos y sus ponderaciones para la inscripción a los programas
académicos de pregrado en la Universidad del Valle.

## Archivos

    .
    ├── codeblocks
    │   └── PuntajesMinimos.cbp (Configuración de compilacion del proyecto para
    │                            IDE codeblocks)
    ├── doc
    │   ├── Doxyfile (Configuración para generar documentación basada en el
    │   │             código fuente)
    │   └── user_manual (Manual de usuario)
    │       ├── images (Imagenes usadas para el manual de usuario)
    │       ├── manual_de_usuario.odt
    │       └── manual_de_usuario.pdf
    ├── README.md
    ├── src (Código fuente)
    │   ├── algoritmogenetico (Libreria general de algoritmos geneticos)
    │   ├── datos (Clases para el acceso a datos en diferentes formatos o
    │   │          base de datos)
    │   ├── gui (Clases con la interfaz grafica y sus eventos, los archivos
    │   │        que inician con "wx_" son generados por wxformbuilder)
    │   └── ipmpais (Clases especificas de la aplicación)
    ├── test (Pruebas)
    └── wxformbuilder (Proyectos para generar las clases de la interfaz
                      grafica)


## Requerimientos

Nombre          | Versión | Opcional
:--             | :--:    | --:
[codeblocks]    | 13.12   | Si
[doxygen]       | 1.8     | Si
[graphviz]      | 2.36    | No (*)
[libpq]         | 9.3     | No
[wxformbuilder] | 9.3     | Si (**)
[wxwidgets]     | 2.8     | No

(*) Para los graficos en la documentación
(**) Para editar la interfaz grafica


## Compilacion

``g++ -c -Wall `wx-config --cxxflags` -O2 -I./src -I/usr/include/postgresql src/algoritmogenetico/*.cpp src/datos/*.cpp src/gui/*.cpp src/ipmpais/*.cpp``

``g++ -o puntajesMinimos *.o  -s -lpq `wx-config --libs` ``


## Generar documentación
`doxygen doc/Doxyfile`

## Base de datos

Las tablas NO tienen llaves foraneas, solo llaves primarias. Dado que en varios
casos los datos no estan completos por la naturaleza de la información, no se 
requieren restrinciones de completitud de los datos, ademas el no tener llaves
foraneas acelera la inserción de los datos (Se elige velocidad ante 
restrincción de los datos).

La base de datos esta compuesta por 5 tablas, detalladas a continuación : 

### Tabla Estudiante

Contiene la información basica del estudiante, que normalmente se encuentra en
el proceso de admisiones

Columna        | Descripcion
 :--           | --:
año            | El año en que se presento la persona a admisiones
codigo         | El codigo asignado por la universidad
identificacion | El numero de documento con que se registro, sea cedula o  tarjeta de identidad
estrato        | El numero del estrato de la vivienda del aspirante
comuna         | El numero de la comuna de la vivienda del aspirante
barrio         | Barrio de la vivienda del aspirante
ciudad         | Ciudad donde vive el aspirante al momento del registro
colegio        | Nombre de la institucion donde curso el bachillerato
tipo_colegio   | El tipo de la institucion : Publica o Privada
snp            | Codigo para identificar el examen ICFES que presentó el aspirante
bio            | Puntaje de Biologia en el ICFES
cis            | Puntaje de Ciencias Sociales en el ICFES
fil            | Puntaje de Filosofia en el ICFES
fis            | Puntaje de Fisica en el ICFES
geo            | Puntaje de Geografia en el ICFES
his            | Puntaje de Historia en el ICFES
idi            | Puntaje de Idioma en el ICFES ( Normalmente Ingles )
int            | Puntaje de Asignatura Interdisciplinar en el ICFES
len            | Puntaje de Lenguaje en el ICFES
mat            | Puntaje de Matematicas en el ICFES
qui            | Puntaje de Quimica en el ICFES
ecaes_total    | Puntaje total reportado en el ECAES
componente[1-7]| Puntaje de cada componente en el ECAES

Adicionalmente, a esta tabla se le agregan columnas dinamicamente, para
representar la ultima calificación obtenida en una asignatura dada por el 
estudiante, por ejemplo si el estudiante con código 0744444 obtuvo 3.5 en la
asignatura calculo I ( el código de la asignatura es 111050M ), entonces se 
creara (si no existe) la columna "111050M" y se colocara la nota en el 
registro correspondiente al estudiante.

Se toma en cuenta solo UNA calificación para esta tabla. La calificación con 
mayor valor según la siguiente clasificación :

Valor          | Clasificacion
 :--           | --:
1              | VALIDACION
2              | HABILITACION VALIDACION
3              | EXIMIDO EXAMEN CLASF
4              | HABILITACION EXIMIDO EXAMEN CLASF
5              | EQUIVALENCIA
6              | HABILITACION EQUIVALENCIA
7              | PROFIC. EN IDIOMA EXTRANJERO
8              | HABILITACION PROFIC. EN IDIOMA EXTRANJERO
9              | NORMAL
10             | HABILITACION NORMAL
11             | REPETICION
12             | HABILITACION REPETICION
13             | SEGUNDA REPETICION
14             | HABILITACION SEGUNDA REPETICION

El tipo de la columna para la calificación dado que es posible valores como 
( I.C, E.X, A.P, C.U ) entre otros

### Tabla estudiante_creditos y estudiante_tipo

A estas tablas también se le agregan dinámicamente columnas por cada 
asignatura procesada, en la tabla estudiante_creditos se almacena la cantidad
de créditos que tenía la asignatura cuando el estudiante cursó, y la tabla
estudiante_tipo almacena la forma (Validación, habilitación, etc ) como el 
estudiante cursó la asignatura, siguendo los valores de la tabla anterior. 

### Tabla equivalencia

La tabla equivalencia almacena todas las equivalencias del plan, relacionando 
un conjunto de asignaturas con código viejo con otras con nuevo código, esto
es necesario ya que para efectos de comparar estudiantes antiguos y nuevos, los
antiguos se actualizan al pensum mas reciente. Los campos _antigua_ y _nueva_ 
contienen listas de asignaturas separadas por comas. La aplicación permite hacer
equivalencias entre :

- Una asignatura antigua y una nueva
- Dos asignaturas antiguas y una nuevas
- Una asignatura antigua y dos nuevas
- Dos asignaturas antiguas y dos nuevas

El campo _orden_ determina el orden en el que se aplicaran las equivalencias
dado que estas dependen de la fecha en las que se hayan creado y deben aplicarse
en ese orden especifico.

### Tabla calificacion 
 
La tabla calificacion contiene toda la información de registro académico, a
diferencia de la tabla estudiante, esta tabla contiene todas las calificaciones
obtenidas por un estudiante en una asignatura ( en la tabla estudiante solo esta
la ultima calificación obtenida ), esta tabla recibe los datos de las fuentes de
información, luego aplica las equivalencias (el código de la asignatura antes de
aplicase la equivalencia queda guardado en *codigo_asignatura_original* ),
además si es posible se calcula la *calificacion_numerica* para luego poder
obtener el promedio del estudiante.

[codeblocks]:http://www.codeblocks.org/
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[libpq]:http://www.postgresql.org/docs/9.3/static/libpq.html
[wxformbuilder]:http://sourceforge.net/projects/wxformbuilder/
[wxwidgets]:http://www.wxwidgets.org/
[graphviz]:http://www.graphviz.org/
