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
### Instalar crypto para las necesidades criptograficas del app (Ubuntu)
- Ver doc aqui : https://www.cryptopp.com/wiki/Linux#apt-get

```js
apt-cache pkgnames | grep -i crypto++
```

- Lo anterior mostrara algo como lo siguiente : 
```js
libcrypto++6
libcrypto++-utils
libcrypto++-dev
libcrypto++-doc
libcrypto++6-dbg
```

- Aca utilice las versiones mostradas por el comando anterior
```js
sudo apt-get install libcrypto++6 libcrypto++6-dbg libcrypto++-dev
```


### Instalar crypto para las necesidades criptograficas del app (Centos)
- Ver doc aqui : https://www.cryptopp.com/wiki/Linux#apt-get

```js
yum search all crypto++
```

- Lo anterior mostrara algo como lo siguiente : 
```js
libcrypto++3
libcrypto++-utils
libcrypto++-dev
libcrypto++-doc
libcrypto++3-dbg
```

- Aca utilice las versiones mostradas por el comando anterior
```js
sudo yum install libcrypto++3 libcrypto++3-dbg libcrypto++-dev
```


### Instalar cgicc para las necesidades de cookies (Ubuntu)
```js
apt-cache pkgnames | grep -i cgicc
```

- Lo anterior mostrara algo como lo siguiente : 
```js
libcgicc3
libcgicc-dev
libcgicc-doc
```

- Aca utilice las versiones mostradas por el comando anterior
```js
 sudo apt-get install libcgicc3 libcgicc-dev libcgicc-doc
```

### Instalar cgicc para las necesidades de cookies (Centos)
- Doc : http://www.yolinux.com/TUTORIALS/LinuxTutorialC++CGI.html

```js
curl ftp.gnu.org/gnu/cgicc/cgicc-3.2.15.tar.gz --output cgicc-3.2.15.tar.gz
```

```js
tar xzf cgicc-3.2.15.tar.gz
```

```js
./configure --prefix=/usr
```

```js
sudo make install
```

### Compilar para cookies
```js
g++ src/cookies/set_cookies.cc -o set_cookies.cgi -w -std=c++11 -lcgicc
```

```js
src/cookies/get_cookies.cc -o get_cookies.cgi -w -std=c++11 -lcgicc
```

- Si compila, pero no corre entonces sustituya ```-lcgicc``` por ```-l:libcgicc.a```