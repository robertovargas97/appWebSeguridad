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

DELIMITER ;
;

