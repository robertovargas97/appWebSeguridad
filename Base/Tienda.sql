CREATE TABLE Persona(

correo NVARCHAR(50) NOT NULL,
nombre NVARCHAR(50) NOT NULL,
apellido NVARCHAR(50) NOT NULL,
telefono INT NOT NULL,

CONSTRAINT Correo_Persona_PK PRIMARY KEY(correo)
);


CREATE TABLE Producto(

codigoProducto INT NOT NULL /* AUTO_INCREMENT*/,
nombre NVARCHAR(50) NOT NULL,
precio INT NOT NULL,
descripcion NVARCHAR(200) NOT NULL,
CONSTRAINT Codigo_Producto_PK PRIMARY KEY(codigoProducto)
);


CREATE TABLE ProductoEnCarrito(

idPCarrito INT NOT NULL  AUTO_INCREMENT,
correoFK NVARCHAR(50) NOT NULL,
codigoProductoFK INT NOT NULL,
CONSTRAINT idPCarrito_PK PRIMARY KEY(idPCarrito),
CONSTRAINT FK_Correo_PCarrito FOREIGN KEY (correoFK) REFERENCES Persona(correo) ON UPDATE CASCADE ON DELETE CASCADE,
CONSTRAINT FK_CodigoProducto_PCarrito FOREIGN KEY (codigoProductoFK) REFERENCES Producto(codigoProducto) ON UPDATE CASCADE ON DELETE CASCADE,
);


--El nombre de esto?
CREATE TABLE Tabla(

correoFK NVARCHAR(50) NOT NULL,
contraseņa NVARCHAR(8) NOT NULL,
CONSTRAINT Correo_Tabla_PK PRIMARY KEY(correoFK),
CONSTRAINT FK_Correo_Tabla FOREIGN KEY (correoFK) REFERENCES Persona(correo) ON UPDATE CASCADE ON DELETE CASCADE
);


CREATE TABLE Comentarios(

correoFK NVARCHAR(50) NOT NULL,
nombreCompleto NVARCHAR(50) NULL,
tipoDeComentario NVARCHAR(17) NOT NULL,
fechaDeCreacion DATETIME NOT NULL,
CONSTRAINT Correo_Comentarios_PK PRIMARY KEY(correoFK, fechaDeCreacion), /*Para que sea unico*/
CONSTRAINT FK_Correo FOREIGN KEY (correoFK) REFERENCES Persona(correo) ON UPDATE CASCADE ON DELETE CASCADE
);


