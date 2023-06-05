select products.name, comands.name AS Comand_name, company.name AS Company_name, versions.name AS Version_name from products JOIN comands ON products.comand_id = comands.id JOIN company ON products.company_id= company.id JOIN (SELECT product_id, MAX(version_date) as max_date FROM versions GROUP BY product_id) v_max ON v_max.product_id = products.id JOIN versions ON products.id = versions.product_id AND v_max.max_date = versions.version_date;


insert into products (name, comand_id, company_id) values(?,?,?);

select company.id AS Company_id, c.id AS Comand_id, c.name AS Comand_name from company JOIN comands c on company.comand_id = c.id WHERE company.name = '+ui->leCompanyNameProduct->text()+';

insert into versions (name, version_date, product_id) values ('0.0.1', current_date,(select MAX(products.id) from products))";

SELECT products.id FROM products JOIN comands c on products.comand_id = c.id JOIN company c2 on products.company_id = c2.id WHERE products.name = '"+ui->twProduct->item(currow,0)->text()+"' AND c.id = (SELECT comands.id from comands WHERE comands.name ='"+ui->twProduct->item(currow,1)->text()+"') AND c2.id = (SELECT company.id from company WHERE company.name ='"+ui->twProduct->item(currow,2)->text()+"');

delete from products where id =  + select_product_id;

DELETE FROM versions WHERE product_id =  + select_product_id

update products SET comand_id = " + select_product_id + "WHERE product_id = " + select_comand_id;

select comands.id from comands JOIN company c on comands.id = c.comand_id WHERE c.id = " + select_product_id;

select products.name, comands.name AS Comand_name, company.name AS Company_name, versions.name AS Version_name from products JOIN comands ON products.comand_id = comands.id JOIN company ON products.company_id= company.id JOIN (SELECT product_id, MAX(version_date) as max_date FROM versions GROUP BY product_id) v_max ON v_max.product_id = products.id JOIN versions ON products.id = versions.product_id AND v_max.max_date = versions.version_date WHERE products.name ='" + ui->leProductNameSearch->text() + "'";


