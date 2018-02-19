dump db, prepsani sloupce skartace na integer

create table posta_cis_spisovna (
  id serial,
  spisovna varchar(50)
);

alter table posta add spisovna_id int2;
alter table posta_h add spisovna_id int2;
