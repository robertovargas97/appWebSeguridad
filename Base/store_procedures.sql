--  CHANGE testdb for your db name

ALTER TABLE `testdb`.`Comentarios` 
DROP FOREIGN KEY `FK_Correo`;
;


USE `testdb`;
DROP procedure IF EXISTS `add_comment`;

USE `testdb`;
DROP procedure IF EXISTS `testdb`.`add_comment`;
;

DELIMITER $$
USE `testdb`$$
CREATE DEFINER=`admin`@`localhost` PROCEDURE `add_comment`(
	IN u_name nvarchar(80),
    IN u_email nvarchar(100),
    IN u_comment_type nvarchar(15),
    IN u_comment nvarchar(400))
BEGIN
	DECLARE creation_date datetime DEFAULT now();
	IF u_email IS NULL OR u_email = '' THEN
		SET u_email = 'default@email.com';
		END IF;
        
    INSERT INTO
    Comentarios (`nombreCompleto`, `correoFK`, `tipoDeComentario`, `comentario`, `fechaDeCreacion`)
	VALUES
    (
        u_name,
        u_email,
        u_comment_type,
        u_comment,
        creation_date
    );
END$$

CREATE DEFINER=`admin`@`localhost` PROCEDURE `add_product`(
	IN u_nombre varchar(50),
    IN u_precio int,
    IN u_descripcion varchar(200),
    IN u_categoria varchar(50))
BEGIN
	DECLARE creation_date datetime DEFAULT now();
	IF u_email IS NULL OR u_email = '' THEN
		SET u_email = 'default@email.com';
		END IF;
        
    INSERT INTO
    Producto (`nombre`, `precio`, `descripcion`, `categoria`)
	VALUES
    (
        u_nombre,
        u_precio,
        u_descripcion,
        u_categoria,
    );
END$$


DELIMITER ;
;

