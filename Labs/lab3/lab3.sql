CREATE VIEW vCOMPANY (COMPANY) AS SELECT DISTINCT * FROM customers;

SELECT DISTINCT * FROM customers;

ALTER VIEW vCOMPANY RENAME COLUMN company_name TO companyN;

SELECT * FROM vCOMPANY;

CREATE OR REPLACE VIEW vCOMPANY AS SELECT * FROM customers WHERE last_name!='Andreev' WITH CHECK OPTION;

INSERT INTO vCOMPANY VALUES (17,'LAB3','Nikulin','Danila','Moscow','35686','89268389478');
INSERT INTO vCOMPANY VALUES (18,'LAB31','Andreev','Danila','Moscow','37886','89266797878');

CREATE VIEW vTEST AS SELECT order_id, customers.last_name, customers.first_name, customers.address, order_date, ship_date
FROM orders JOIN customers
ON orders.customer_id = customers.customers_id;

SELECT * FROM vTEST;

ALTER VIEW vCOMPANY SET (check_option='cascaded');

DROP VIEW vCOMPANY;

CREATE ROLE Test_creator WITH
	NOLOGIN
	NOSUPERUSER
	CREATEDB
	CREATEROLE
	INHERIT
	NOREPLICATION
	CONNECTION LIMIT -1
	PASSWORD 'xxxxxx';
	
CREATE USER user1;
CREATE USER user2;


GRANT Test_creator to user1;
GRANT Test_creator to user2;

GRANT SELECT ON TABLE customers TO read_only_role;
GRANT SELECT, INSERT, UPDATE, DELETE on TABLE customers TO read_write_role;

GRANT ALL PRIVILEGES ON TABLE customers TO user1;

REVOKE INSERT FROM user1;

ALTER USER user1 PASSWORD '12345';


CREATE ROLE nodel WITH 
	NOLOGIN
	NOS
	NOCREATEDB
	NOCREATEROLE
	INHERIT
	NOREPLICATION;

CREATE ROLE testdel2 LOGIN PASSWORD 'qwerty';

GRANT nodel to testdel2;
GRANT SELECT, INSERT, UPDATE on table customers to testdel2;
DELETE FROM customers WHERE address = 'Moscow';