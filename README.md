IPMPAIS
=======
Optimización de los pesos de los puntajes de admisión a una carrera
universitaria

Introducción
---
IPMPAIS (Identificando Puntajes Mínimos para el Plan Académico de Ingeniería
de Sistemas), es una herramienta que permite hacer una estimación de los
puntajes mínimos y sus ponderaciones para la inscripción a los programas
académicos de pregrado en la Universidad del Valle.

Archivos
---

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


Requerimientos
---

Nombre          | Version | Opcional
:--             | :--:    | --:
[codeblocks]    | 13.12   | Si
[doxygen]       | 1.8     | Si
[graphviz]      | 2.36    | No (*)
[libpq]         | 9.3     | No
[wxformbuilder] | 9.3     | Si (**)
[wxwidgets]     | 2.8     | No

(*) Para los graficos en la documentación
(**) Para editar la interfaz grafica


Compilacion
---

``g++ -c -Wall `wx-config --cxxflags` -O2 -I./src -I/usr/include/postgresql src/algoritmogenetico/*.cpp src/datos/*.cpp src/gui/*.cpp src/ipmpais/*.cpp``

``g++ -o puntajesMinimos *.o  -s -lpq `wx-config --libs` ``


Generar documentación
---
`doxygen doc/Doxyfile`

[codeblocks]:http://www.codeblocks.org/
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[libpq]:http://www.postgresql.org/docs/9.3/static/libpq.html
[wxformbuilder]:http://sourceforge.net/projects/wxformbuilder/
[wxwidgets]:http://www.wxwidgets.org/
[graphviz]:http://www.graphviz.org/
