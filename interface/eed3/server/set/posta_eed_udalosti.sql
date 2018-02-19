-- drop table posta_eed_udalosti;
create table posta_eed_udalosti (
  id serial,
  cil varchar(255),
  udalost varchar(255),
  hodnoty text,
  poradi integer,
  udalostId integer,
  kod varchar(10),
  popis varchar(255),
  vlozeno timestamp,
  zpracovano varchar(20),
  chyba smallint default 0,
  predano smallint default 0
);
