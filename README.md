# appWebSeguridad
Esta es la tarea del curso de seguridad de sistemas computacionales I semestre 2021

### Ejemplos de comandos para compilar

```js
g++ src/login.cc utils/utils.cc -o login.cgi -w
```

```js
g++ src/home.cc utils/utils.cc -o home.cgi -w 
```

```js
g++ src/add_comment.cc utils/utils.cc utils/db_connection.cc -o add_comment.cgi -w `mysql_config --cflags --libs
```

### Para instalar mysql connector

- https://aaronxu17.github.io/blog/install-mysql-connector/


### Comando para compilar el archivo con mysql
```js
g++ utils/db_connection.cc utils/utils.cc  `mysql_config --cflags --libs` -w
```
### Ejemplos de cosas con mysql connector
```js
https://github.com/hholzgra/connector-c-examples
```

### Compilar con make
Para compilar todos los .cc de la carpeta src/ (Agregar en el makefile nuevos .cc en caso de agregar nuevos):
```js
make app
```

Para borrar todos los .cgi creados tras correr make app (Agregar en el makefile nuevos .cgi en caso de agregar nuevos):
```js
make clean
```

Para compilar componentes individualmente:
```js
make home
make login
make register
.
.
.
etc
```