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
    ├── bin (la aplicación ejecutable)
    ├── doc
    │   ├── html (documentación, API, diagrama de clases)
    │   │    └──  index.html  (es el punto de entrada de la documentación)
    │   ├─ 2013-05-02_IPMPAIS_Informe_Final.pdf    (informe final del proyecto de investigación)
    │   └─ 2013-05-03_IPMPAIS_manual_de_usuario.pdf   (manual de usuario)
    ├── src (Código fuente)
    │   ├── *.h, *.cpp (clases en C++ de este proyecto)
    │   ├── *.fbp (interfase gráfica de este proyecto)
    │   ├── test_* (Las clases de test unitario para el componente principal del proyecto, que es el algoritmo genético)
    │   └── PuntajesMinimos.cbp (Configuración de compilacion del proyecto para IDE codeblocks
    ├── Doxyfile (Configuración para generar la documentación)
    ├── github.txt (URL de donde bajar todo el proyecto)
    ├── database.md (documentación de la base de datos)
    └── README.md (este archivo)


## Requerimientos

Nombre          | Versión | Opcional
:--             | :--:    | --:
[codeblocks]    | 13.12   | Si
[doxygen]       | 1.8     | Si
[g++]           | 4.8.2   | No
[graphviz]      | 2.36    | No (\*)
[libpq]         | 9.3     | No
[wxformbuilder] | 9.3     | Si (\*\*)
[wxwidgets]     | 2.8     | No

(\*) Para los graficos en la documentación
(\*\*) Para editar la interfaz grafica


## Compilacion

``g++ -c -Wall `wx-config --cxxflags` -O2 -I./src -I/usr/include/postgresql src/*.cpp``

``g++ -o puntajesMinimos *.o  -s -lpq `wx-config --libs` ``


## Generar documentación
`doxygen Doxyfile`

## Base de datos
Descripción de la base de datos en [database.md](database.md).

[codeblocks]:http://www.codeblocks.org/
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[g++]:https://www.gnu.org/software/gcc/releases.html
[libpq]:http://www.postgresql.org/docs/9.3/static/libpq.html
[wxformbuilder]:http://sourceforge.net/projects/wxformbuilder/
[wxwidgets]:http://www.wxwidgets.org/
[graphviz]:http://www.graphviz.org/
