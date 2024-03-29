CREATE TABLE Persona(

correo VARCHAR(50) NOT NULL,
nombre VARCHAR(50) NOT NULL,
apellido VARCHAR(50) NOT NULL,
telefono INT NOT NULL,
direccion VARCHAR(400) NOT NULL,
CONSTRAINT Correo_Persona_PK PRIMARY KEY(correo)
);


CREATE TABLE Producto(

codigoProducto INT NOT NULL  AUTO_INCREMENT,
nombre VARCHAR(50) NOT NULL,
precio VARCHAR(50) NOT NULL,
descripcion VARCHAR(200) NOT NULL,
categoria VARCHAR(50) NOT NULL,
CONSTRAINT Codigo_Producto_PK PRIMARY KEY(codigoProducto)
);


CREATE TABLE ProductoEnCarrito(

idPCarrito INT NOT NULL  AUTO_INCREMENT,
correoFK VARCHAR(50) NOT NULL,
codigoProductoFK INT NOT NULL,
CONSTRAINT idPCarrito_PK PRIMARY KEY(idPCarrito)
);



CREATE TABLE Tabla (
  correo VARCHAR(50) NOT NULL,
  pass VARCHAR(100) NOT NULL,
  salt VARCHAR(4) NOT NULL,
  PRIMARY KEY ( correo ) );


CREATE TABLE Comentarios(

correoFK VARCHAR(50) NOT NULL,
nombreCompleto VARCHAR(50) NULL,
tipoDeComentario VARCHAR(17) NOT NULL,
fechaDeCreacion DATETIME NOT NULL,
comentario VARCHAR(400) NOT NULL,
CONSTRAINT Correo_Comentarios_PK PRIMARY KEY(correoFK, fechaDeCreacion) /*Para que sea unico*/
);


-- INSERT INTO Persona(correo, nombre, apellido, telefono, direccion) VALUES('hellen@gmail.com', 'Hellen', 'Fernandez', 88888888, 'Alajuela, San Ramon, San Isidro');
-- INSERT INTO Persona(correo, nombre, apellido, telefono, direccion) VALUES('tefi@gmail.com', 'Stephanie', 'Leiton', 88988888, 'Alajuela, San Ramon, San Ramon');

-- INSERT INTO Tabla(correo,pass,salt) VALUES('hellen@gmail.com', 'password', 'aaaa');
-- INSERT INTO Tabla(correo,pass,salt) VALUES('tefi@gmail.com', '1234', 'asde');

-- INSERT INTO Producto(nombre,precio, descripcion) VALUES('Tennis Adidas', 45660,'Tennis nuevas de mujer talla 37', 'Deporte');
-- INSERT INTO Producto(nombre,precio, descripcion) VALUES('Jarra Iron Man', 8500,'Jarra de Iron man, bonito detalle para regalar', 'Regalos');

-- INSERT INTO ProductoEnCarrito(correoFK, codigoProductoFK) VALUES('hellen@gmail.com', 1);
-- INSERT INTO ProductoEnCarrito(correoFK, codigoProductoFK) VALUES('tefi@gmail.com', 2);

-- INSERT INTO Comentarios(correoFK, nombreCompleto, tipoDeComentario,comentario,fechaDeCreacion) VALUES( 'hellen@gmail.com','Hellen Fernandez','Retroalimentacion', 'Me encanto mi nuevo rompecabezas',CURRENT_DATE);

