CREATE TABLE IF NOT EXISTS Студенты (
        id_студента SERIAL PRIMARY KEY,
        Оценка1 INT NOT NULL,
        Оценка2 INT NOT NULL,
        Оценка3 INT NOT NULL
);
--------------------------------------------------------
INSERT INTO Студенты (Оценка1, Оценка2, Оценка3) VALUES (4, 4, 3);
INSERT INTO Студенты (Оценка1, Оценка2, Оценка3) VALUES (4, 3, 5);
INSERT INTO Студенты (Оценка1, Оценка2, Оценка3) VALUES (4, 4, 5);
--------------------------------------------------------
SELECT * FROM Студенты;
--------------------------------------------------------
CREATE OR REPLACE PROCEDURE СрБалл(x real)
LANGUAGE SQL
AS
$$
        SELECT * FROM Студенты WHERE (Оценка1 + Оценка2 + Оценка3)/3.0 > x
$$;
--------------------------------------------------------
CREATE OR REPLACE FUNCTION СрБалл_получить(x real)
RETURNS TABLE (
        id_студента INT,
        Оценка1 INT,
        Оценка2 INT,
        Оценка3 INT
)
LANGUAGE SQL
AS
$$
        SELECT * FROM Студенты WHERE (Оценка1 + Оценка2 + Оценка3)/3 > x
$$;
--------------------------------------------------------
SELECT * FROM СрБалл_получить(4.0);
--------------------------------------------------------
DROP FUNCTION СрБалл_получить(real);
--------------------------------------------------------
CREATE PROCEDURE Retake ()
   		LANGUAGE SQL
    		AS $$
			UPDATE Студенты SET Оценка3 = 3 WHERE Оценка2 = 3 AND id_студента = 2;
            $$;
			
DROP PROCEDURE Retake();
--------------------------------------------------------
call Retake();
--------------------------------------------------------
call СрБалл(1.0);
--------------------------------------------------------


