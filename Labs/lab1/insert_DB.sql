--1
INSERT INTO comands (Name,Comand_Email) VALUES 
('Search','search@gmail.com'),
('Windows','windows@microsoft.com'),
('Retail','retail@amazon.com'),
('Cloud','cloud@ibm.com'),
('Graphics','graphics@nvidia.com');


--2
INSERT INTO company (Name,Company_Email,Comand_ID) VALUES 
('Google','info@google.com',1),
('Microsoft','info@microsoft.com',2),
('Amazon','info@amazon.com',3),
('Facebook','info@facebook.com',4),
('Oracle','info@oracle.com',5);


--3
INSERT INTO developers (FIO,Email,Phone,Post,Working_mode,Comand_ID) VALUES 
('John Smith','john.smith@gmail.com','+1 123 456 7890','Software Engineer','Full-time',1),
('Sarah Johnson','sarah.johnson@hotmail.com','+1 234 567 8901','UI/UX Designer','Part-time',1),
('Michael Brown','michael.brown@yahoo.com','+1 345 678 9012','Database Admin','Full-time',1),
('Jennifer Davis','jennifer.davis@gmail.com','+1 456 789 0123','Project Manager','Full-time',2),
('Emily Garcia','emily.garcia@hotmail.com','+1 678 901 2345','Front-end Developer','Full-time',2),
('Jacob Martinez','jacob.martinez@yahoo.com','+1 789 012 3456','Back-end Developer','Full-time',2),
('Emma Anderson','emma.anderson@gmail.com','+1 890 123 4567','Mobile Developer','Part-time',3),
('Ethan Taylor','ethan.taylor@hotmail.com','+1 901 234 5678','QA Engineer','Full-time',3),
('Madison Jackson','madison.jackson@gmail.com','+1 012 345 6789','Data Analyst','Part-time',3),
('Nicholas Brown','nicholas.brown@hotmail.com','+1 123 456 7892','Software Engineer','Full-time',4),
('Isabella Davis','isabella.davis@yahoo.com','+1 234 567 8911','UI/UX Designer','Part-time',4),
('Alexander Wilson','alexander.wilson@gmail.com','+1 345 678 9112','Database Admin','Full-time',4),
('Victoria Lee','victoria.lee@hotmail.com','+1 456 789 1123','Project Manager','Part-time',5),
('Benjamin Thompson','benjamin.thompson@gmail.com','+1 567 890 1234','Software Developer','Part-time',5),
('Eric Chen','eric.chen@hotmail.com','+1 345 78 9312','Back-end Developer','Part-time',5);


--4
INSERT INTO products (Name,Comand_ID,Company_ID) VALUES 
('Google Search',1,1),
('Windows 11',2,1),
('Adobe Creative Cloud',3,2),
('Amazon Prime',4,2),
('Facebook Messenger',5,3),
('Oracle Database',1,3),
('IBM Cloud',2,4),
('Netflix Originals',3,4),
('Cisco Networking',4,5),
('SAP ERP',5,5);


--5
INSERT INTO versions (Name,Version_date,Product_id) VALUES 
('1.0.0','2022-01-01',1),
('2.0.0','2022-02-01',1),
('1.0.0','2022-03-01',2),
('3.0.0','2022-04-01',2),
('1.0.0','2022-05-01',3),
('4.0.0','2022-06-01',3),
('1.0.0','2022-07-01',4),
('2.0.0','2022-08-01',4),
('1.0.0','2022-09-01',5),
('2.0.0','2022-10-01',5),
('1.0.0','2022-11-01',6),
('2.0.0','2022-12-01',6),
('1.0.0','2023-01-01',7),
('1.1.0','2023-01-25',7),
('1.0.0','2023-02-01',8),
('1.0.7','2023-02-10',8),
('1.1.0','2023-02-05',9),
('2.1.0','2023-02-15',9),
('1.0.1','2023-03-01',10),
('2.2.0','2023-03-20',10);


--6
INSERT INTO working (Developer_ID,Version_ID) VALUES 
(1,1),
(2,2),
(4,3),
(5,4),
(7,5),
(8,6),
(10,7),
(11,8),
(13,9),
(14,10),
(2,11),
(3,12),
(5,13),
(6,14),
(8,15),
(9,16),
(11,17),
(12,18),
(14,19),
(15,20);
