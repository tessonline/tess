alter table cis_posta_typ add poradi int default 10;
alter table POSTA_CIS_VYRIZENO add poradi int default 10;


  create table posta_cis_ceskaposta_ck (
    id serial,
    posta_id int4,
    rok int4,
    kod varchar(3),
    podaci_id int4,
    ck varchar(20),
    stav int2
  );



CREATE  INDEX "posta_id_posta_cis_ceskaposta_ck_key" on "posta_cis_ceskaposta_ck" (posta_id);

alter table cis_posta_spisy add arch int2 default 0;

CREATE TABLE posta_cis_adresati (
    id serial,
    kod character varying(3),
    nazev character varying(50),
    aktivni int2 default 0,
    last_date date,
    last_time character varying(10),
    owner_id integer,
    last_user_id integer,
    poradi integer DEFAULT 10
);

insert into posta_cis_adresati VALUES (1,'P','Právnická osoba',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (2,'U','Orgán veřejné moci',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (3,'F','Podnikající fyzická osoba',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (4,'O','Fyzická osoba',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (5,'S','Interní pošta',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (6,'N','Notář',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (7,'B','Advokát',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (8,'E','Exekutor',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (9,'T','Patentový zástupce',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (10,'D','Daňový poradce',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (11,'A','Anonym',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (12,'V','Veřejnost',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (13,'Z','Vlastní záznam',1,'2014-10-23','10:00:00',1612,1612);
insert into posta_cis_adresati VALUES (14,'M','E-mail',1,'2014-10-23','10:00:00',1612,1612);

alter table cis_posta_spisy add nazev_spisu varchar(255);


-- drop table posta_transakce;
create table posta_transakce (
  id serial,
  doc_id int4,
  jmeno varchar(255),
  typ varchar(25),
  text text,
  last_user_id int4,
  last_time timestamp without time zone  default now()
);

