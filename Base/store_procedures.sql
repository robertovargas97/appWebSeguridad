--  CHANGE MarketPlaceDB for your db name

ALTER TABLE `MarketPlaceDB`.`Comentarios` 
DROP FOREIGN KEY `FK_Correo`;
;


USE `MarketPlaceDB`;
DROP procedure IF EXISTS `add_comment`;

USE `MarketPlaceDB`;
DROP procedure IF EXISTS `MarketPlaceDB`.`add_comment`;
;

DELIMITER $$
USE `MarketPlaceDB`$$
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





