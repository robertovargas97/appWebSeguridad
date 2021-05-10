# appWebSeguridad
Esta es la tarea del curso de seguridad de sistemas computacionales I semestre 2021

### Ejemplos de comandos para compilar

```js
g++ src/login.cc utils/utils.cc -o login.cgi -w
```

```js
g++ src/home.cc utils/utils.cc -o home.cgi -w 
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
