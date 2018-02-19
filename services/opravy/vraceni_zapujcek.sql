update posta_spisovna_zapujcky set vraceno='2014-07-10' where id in (

select id from posta_spisovna_zapujcky where vraceno is null and id in ( select zapujcka_id from posta_spisovna_zapujcky_id where posta_id in (select id from posta where status=-3))

);