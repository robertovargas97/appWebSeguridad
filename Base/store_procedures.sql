--  CHANGE MarketPlaceDB for your db name


USE `MarketPlaceDB`;
DROP procedure IF EXISTS `add_comment`;

USE `MarketPlaceDB`;
DROP procedure IF EXISTS `MarketPlaceDB`.`add_comment`;
;

DELIMITER $$
USE `MarketPlaceDB`$$
CREATE DEFINER=`seguridad`@`localhost` PROCEDURE `add_comment`(
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

CREATE DEFINER=`seguridad`@`localhost` PROCEDURE `add_product`(
	IN u_nombre varchar(50),
    IN u_precio int,
    IN u_descripcion varchar(200),
    IN u_categoria varchar(50))
BEGIN   
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

-- Add User Procedure --
USE `MarketPlaceDB`;
DROP procedure IF EXISTS `add_user`;

USE `MarketPlaceDB`;
DROP procedure IF EXISTS `MarketPlaceDB`.`add_user`;
;

DELIMITER $$
USE `MarketPlaceDB`$$
CREATE DEFINER=`seguridad`@`localhost` PROCEDURE `add_user`(
	IN u_name nvarchar(80),
    IN u_last_name nvarchar(80),
    IN u_email nvarchar(100),
    IN u_pass nvarchar(80),
    IN u_phone_number nvarchar(15),
    IN u_address nvarchar(400)
)
BEGIN

	INSERT INTO
    Persona (`nombre`, `apellido`, `correo`, `telefono`, `direccion`)
	VALUES
    (
        u_name,
        u_last_name,
        u_email,
        u_phone_number,
        u_address
        
    );
    
    INSERT INTO
    Tabla (`correoFK`, `contrasena`)
	VALUES( u_email, u_pass );

END$$

DELIMITER ;
;

-- Procedura to get the user salt
USE `MarketPlaceDB`$$
DROP procedure IF EXISTS `get_user_salt`;

DELIMITER $$
USE `MarketPlaceDB`$$
CREATE PROCEDURE `get_user_salt` (in u_email varchar(50))
BEGIN

SELECT salt
FROM Tabla
WHERE correo = u_email;

END$$

DELIMITER ;

-- Procedure to verify login

USE `MarketPlaceDB`;
DROP procedure IF EXISTS `verify_login`;

DELIMITER $$
USE USE `MarketPlaceDB`$$
CREATE PROCEDURE `verify_login` (in u_email varchar(50), in u_pass varchar(100))
BEGIN

SELECT correo
FROM Tabla
WHERE correo = u_email AND pass = u_pass;

END$$

DELIMITER ;







