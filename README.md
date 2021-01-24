# Autómata Finito Determinista Traductor

Práctica I de la asignatura Traductores de Lenguajes de Programación de la Escuela Técnica Superior de Ingeniería de Sistemas Informáticos (UPM). 

## ¿Cómo funciona?

Una vez realizado de forma manuscrita los autómatas se dispone su configuración en un fichero de texto cuya estructura es la siguiente:

En las cinco primeras líneas del fichero se han especificado los datos necesarios relativos al alfabeto y a los estados: longitud del alfabeto, letras del alfabeto, número de estados, estados finales y numero de estados finales. Esta información se ha leído en las primeras líneas de código y se ha guardado en variables o en estructuras de datos reservando memoria dinámica.

Después, se ha incluido una especie de tabla o matriz de transiciones en la que se ha optado por separar las posibles columnas para que quedaran unas debajo de otras, obteniendo subtablas con una encabezado que contiene la letra del alfabeto. Esto se ha hecho por simplificar la lectura con 𝑓𝑠𝑐𝑎𝑛𝑓, de esta forma no hay que preocuparse por la longitud a priori que deba tener una línea del fichero.

En dicha tabla se han colocado a la izquierda todos los estados del autómata y en la columna los estados donde se transita con la letra colocada en el encabezado, así como la traducción asociada a dicha transición. Esta organización en forma de subtabla se ha repetido hacia abajo tantas veces como letras tenía el alfabeto.

Nótese que en caso de que no hubiera transición posible desde un estado determinado se ha incluido el valor ‘-1’; y para el caso de no haber traducción asociada se ha utilizado el símbolo ‘*’.

## Autómatas

### a.txt

<img src="https://render.githubusercontent.com/render/math?math=L = \{ab^na : n\geq0\}">
<img src="https://render.githubusercontent.com/render/math?math=T(M) = \{c^{n%2B3} : n\geq1\}">

### b.txt

<img src="https://render.githubusercontent.com/render/math?math=L = \{a^nb(ca)^{2k}w : n, k\geq0, w\in\{a,b\}^*\}">
<img src="https://render.githubusercontent.com/render/math?math=T(M) = \{10^{k%2B1}1^m : k\geq0, m = |w|\}">

### c.txt

<img src="https://render.githubusercontent.com/render/math?math=L = \{w\in\{a, b\}^* : w\hspace{2mm}no\hspace{2mm}termina\hspace{2mm}en\hspace{2mm}b\}">
<img src="https://render.githubusercontent.com/render/math?math=T(M) = \{x\in\{0, 1\}^* : el\hspace{2mm}valor\hspace{2mm}binario\hspace{2mm}de\hspace{2mm}x\hspace{2mm}es\hspace{2mm}par\}">
