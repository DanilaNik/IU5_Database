--все данные из таблицы
SELECT * FROM customers;

--из некоторых столбцов таблицы
SELECT company_name, phone FROM customers;

--сортировка данных
SELECT product_name, product_price FROM products
ORDER BY product_price desc;

--ограничения на выборку
SELECT * FROM customers 
WHERE company_name = 'TREK' OR company_name = 'MERIDA'

--операторы сравнения
SELECT product_name FROM products
WHERE product_price < '100000';

--between
SELECT product_name FROM products
WHERE product_price BETWEEN '50000' AND '200000';

--in
SELECT * FROM products WHERE product_id in (1,2,3,4,5);

--like
SELECT * FROM customers WHERE company_name LIKE 'T%';

--is null
SELECT * FROM products WHERE product_price IS NOT NULL;

--агрегатные функции
SELECT MIN(product_price) FROM products;

--having
SELECT product_price FROM products 
	GROUP BY product_price
	HAVING MAX(product_price) < '100000';
	

--distinct
SELECT DISTINCT in_stock FROM products ORDER BY in_stock;

--exists
SELECT product_name FROM products
WHERE EXISTS (SELECT customers_id FROM customers);

--case
SELECT product_name, 
	CASE WHEN products.in_stock > 5 THEN 'many'
		ELSE 'a few'
	END
FROM products;

--задания по варианту
--1
SELECT order_id, customers.last_name, customers.first_name, customers.address, order_date, ship_date
FROM orders JOIN customers
ON orders.customer_id = customers.customers_id order by ship_date; 

--2
SELECT last_name, first_name, address, phone
FROM customers JOIN orders
ON orders.customer_id = customers.customers_id where orders.status = '+' order by last_name desc; 

--доп
SELECT product_name FROM products WHERE product_id not in (SELECT product_id from items);
