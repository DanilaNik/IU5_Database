select * from products;
select * from customers;
CREATE OR REPLACE FUNCTION update_product_in_stock()
RETURNS TRIGGER AS
$$
BEGIN
    UPDATE products
    SET in_stock=in_stock*2
    WHERE product_id = NEW.product_id;
    RETURN NEW;
END;
$$
LANGUAGE plpgsql;
-- ---------------------------------------------------

CREATE TRIGGER update_product_in_stock_trigger
AFTER INSERT ON products
FOR EACH ROW
EXECUTE FUNCTION update_product_in_stock();
-- ПРИМЕР!!!!!
INSERT INTO products (product_id, product_name, product_price, in_stock, re_order) VALUES ('15','TRIGGERTEST', '75000', '3', 'false');
SELECT * FROM products WHERE product_name = 'TRIGGERTEST';
-- ---------------------------------------------------

select * from orders;

------Задание 1 
CREATE OR REPLACE FUNCTION Покупатели_города (city TEXT)
RETURNS TABLE (
        customers_id INT,
        company_name TEXT,
        last_name TEXT,
        first_name TEXT,
		address TEXT,
		index character varying(50),
		phone character varying(50)
)
LANGUAGE SQL
AS
$$

        SELECT customers.customers_id, company_name, last_name, first_name, address, index, phone FROM customers JOIN orders ON orders.customer_id = customers.customers_id WHERE customers.address = city;
$$;


SELECT * FROM Покупатели_города('Moscow');
------Задание 2
0CREATE OR REPLACE FUNCTION Количество_покупателей_города()
RETURNS real
LANGUAGE SQL
AS
$$ 
  select ((select count(*) from customers) - count(*)) number_of_customers from (select count(*) from (select distinct customer_id from orders) as abc group by abc.customer_id) as bcd;
$$;

select * from Количество_покупателей_города();
