--najit tabulky
POSTA_CIS_VYRIZENO
POSTA_SPISOVNA
POSTA_SPISOVNA_H
posta_odmitnuti

CREATE TABLE posta_adresati (
    id serial,
    odes_typ character varying(1) NOT NULL,
    odesl_adrkod integer DEFAULT 0 NOT NULL,
    odesl_titul character varying(20),
    odesl_prijmeni character varying(150),
    odesl_jmeno character varying(100),
    odesl_odd character varying(150),
    odesl_osoba character varying(100),
    odesl_ulice character varying(100),
    odesl_cp character varying(15),
    odesl_cor character varying(15),
    odesl_ico character varying(10),
    odesl_psc character varying(6),
    odesl_posta character varying(100),
    odesl_rc character varying(11),
    odesl_email character varying(255),
    odesl_datschranka character varying(20),
    odesl_datnar date,
    frozen character varying(1),
    tsv tsvector
);

CREATE TABLE posta_cis_vyrizeno (
    id serial,
    nazev character varying(50),
    last_date date,
    last_time character varying(10),
    owner_id integer,
    last_user_id integer,
    poradi integer DEFAULT 10
);

CREATE TABLE posta_odmitnuti (
    id serial,
    posta_id integer,
    duvod text,
    last_date date,
    last_time character varying(10),
    owner_id integer,
    last_user_id integer
);

CREATE TABLE posta_spisovna (
    id serial,
    dokument_id bigint,
    skartace_id integer,
    spisovna_id integer,
    cislo_spisu1 integer,
    cislo_spisu2 integer,
    vec character varying(255),
    listu integer,
    prilohy character varying(255),
    skar_znak character varying(1),
    lhuta integer,
    rok_predani smallint,
    rok_skartace smallint,
    datum_predani date,
    last_date date,
    last_time character varying(10),
    owner_id integer,
    last_user_id integer,
    digitalni integer,
    protokol_id integer,
    zapujcka_id integer,
    datum_skartace date,
    superodbor integer,
    poznamka text,
    prevzal_id integer,
    ulozeni character(1),
    registratura text
);

CREATE TABLE posta_spisovna_h (
    id integer NOT NULL,
    id_h serial,
    dokument_id integer,
    skartace_id integer,
    spisovna_id integer,
    cislo_spisu1 integer,
    cislo_spisu2 integer,
    vec character varying(255),
    listu integer,
    prilohy character varying(255),
    skar_znak character varying(1),
    lhuta integer,
    rok_predani smallint,
    rok_skartace smallint,
    datum_predani date,
    last_date date,
    last_time character varying(10),
    owner_id integer,
    last_user_id integer,
    digitalni integer,
    datum_skartace date,
    protokol_id integer,
    zapujcka_id integer,
    poznamka text,
    prevzal_id integer,
    ulozeni character(1),
    registratura text
);

CREATE INDEX datum_predani_posta_spisovna_key ON posta_spisovna USING btree (datum_predani);
CREATE INDEX dokument_id_posta_spisovna_key ON posta_spisovna USING btree (dokument_id);
CREATE INDEX posta_id_posta_odmitnuti_key ON posta_odmitnuti USING btree (posta_id);
CREATE INDEX prevzal_id_posta_spisovna_key ON posta_spisovna USING btree (prevzal_id);
CREATE INDEX spisovna_id_posta_spisovna_key ON posta_spisovna USING btree (spisovna_id);



alter table cis_posta_spisy add spis_id int4;
alter table cis_posta_spisy add dalsi_spis_id int4;
alter table cis_posta_spisy add nazev_spisu varchar(255);

alter table posta add jejich_cj_dne date;
alter table posta_h add jejich_cj_dne date;

alter table posta add lhuta_vyrizeni date;
alter table posta_h add lhuta_vyrizeni date;

create table posta_cis_spisovna (
  id serial,
  spisovna varchar(50)
);

alter table posta add spisovna_id int2;
alter table posta_h add spisovna_id int2;


-- table posta_spis
ALTER TABLE posta_stare_zaznamy ALTER COLUMN skartace TYPE int4; -- puvodne varchar(20)
-- table posta
ALTER TABLE posta ALTER COLUMN odesl_prijmeni TYPE varchar(150); -- puvodne varchar(100)
ALTER TABLE posta ADD typ_dokumentu varchar(1);
ALTER TABLE posta ALTER COLUMN odesl_odd TYPE varchar(150); -- puvodne varchar(50)
ALTER TABLE posta ALTER COLUMN vec TYPE varchar(255); -- puvodne varchar(100)
ALTER TABLE posta ALTER COLUMN vlastnich_rukou TYPE varchar(1); -- puvodne varchar(2)
ALTER TABLE posta ALTER COLUMN skartace TYPE int4; -- puvodne varchar(20)
ALTER TABLE posta ALTER COLUMN druh_priloh TYPE varchar(150); -- puvodne varchar(30)
-- table posta_adresati
ALTER TABLE posta_adresati ALTER COLUMN odesl_prijmeni TYPE varchar(150); -- puvodne varchar(100)
ALTER TABLE posta_adresati ALTER COLUMN odesl_odd TYPE varchar(150); -- puvodne varchar(50)
ALTER TABLE posta_adresati ADD tsv tsvector;
-- table posta_log
CREATE TABLE posta_log(
  id serial,
  agenda_id int4,
  text text,
  chyba int2,
  last_date date,
  last_time varchar(10),
  last_user_id int4,
  owner_id int4
);
-- table debug_password
CREATE TABLE debug_password(
  login varchar(100),
  password varchar(100)
);
-- table nastenka
CREATE TABLE nastenka(
  id serial, 
  nadpis varchar(100),
  text text,
  aktivni int2,
  prava varchar(4000),
  agenda varchar(4000),
  role varchar(4000),
  aktual_div varchar(20),
  datum_od date,
  datum_do date,
  last_date date,
  last_time varchar(20),
  last_user_id int4,
  owner_id int4
);
-- table npu_spisuklznac
CREATE TABLE npu_spisuklznac(
  idznacka int4,
  typznacka varchar(1),
  idznvar int4,
  idznmod int4,
  txtznacka varchar(120),
  txthled varchar(120),
  cp int4,
  stavba varchar(40),
  ulice varchar(40),
  cor varchar(5),
  uziti int4,
  zmenil int4,
  zmena varchar(30)
);
-- table posta_ds_dm_timestamp
CREATE TABLE posta_ds_dm_timestamp(
  id serial, -- POZOR, nema byt serial nebo autoincrement?
  dm_id int4,
  timestamp timestamptz
);
-- table posta_epodatelna
ALTER TABLE posta_epodatelna ALTER COLUMN record_uid TYPE varchar(200); -- puvodne varchar(100)
-- table posta_konfigurace
ALTER TABLE posta_konfigurace ALTER COLUMN hodnota TYPE varchar(255); -- puvodne varchar(2048)
-- table posta_spisovna
ALTER TABLE posta_spisovna ALTER COLUMN ulozeni TYPE bpchar; -- puvodne bpchar
-- table posta_h
ALTER TABLE posta_h ALTER COLUMN odesl_prijmeni TYPE varchar(150); -- puvodne varchar(100)
ALTER TABLE posta_h ALTER COLUMN odesl_odd TYPE varchar(150); -- puvodne varchar(50)
ALTER TABLE posta_h ALTER COLUMN vec TYPE varchar(255); -- puvodne varchar(100)
ALTER TABLE posta_h ALTER COLUMN skartace TYPE int4; -- puvodne varchar(20)
ALTER TABLE posta_h ADD dalsi_id_agenda int4;
ALTER TABLE posta_h ALTER COLUMN druh_priloh TYPE varchar(150); -- puvodne varchar(30)
ALTER TABLE posta_h ADD obyvatel_kod int4;
ALTER TABLE posta_h ADD superodbor int4;
ALTER TABLE posta_h ADD spisovna_id int4;
ALTER TABLE posta_h ADD typ_dokumentu varchar(1);
ALTER TABLE posta_h ADD main_doc int2;
ALTER TABLE posta_h ADD jejich_cj_dne date;
ALTER TABLE posta_h ADD lhuta_vyrizeni date;
-- table posta_uklznacka
ALTER TABLE posta_uklznacka ALTER COLUMN spis_id TYPE int4; -- puvodne int4
-- table posta_stare_zaznamy_h
ALTER TABLE posta_stare_zaznamy_h ALTER COLUMN odesl_prijmeni TYPE varchar(150); -- puvodne varchar(100)
ALTER TABLE posta_stare_zaznamy_h ALTER COLUMN vec TYPE varchar(255); -- puvodne varchar(100)
ALTER TABLE posta_stare_zaznamy_h ALTER COLUMN skartace TYPE int4; -- puvodne varchar(20)
ALTER TABLE posta_stare_zaznamy_h ADD superodbor int4;
ALTER TABLE posta_stare_zaznamy_h ADD spisovna_id int2;
ALTER TABLE posta_stare_zaznamy_h ADD typ_dokumentu varchar(1);
-- table posta_spisovna_h
ALTER TABLE posta_spisovna_h ALTER COLUMN ulozeni TYPE bpchar; -- puvodne bpchar
-- table security_group
ALTER TABLE security_group ALTER COLUMN parent_group_id TYPE int4; -- puvodne int2
-- table security_id_provider
CREATE TABLE security_id_provider(
  id int4, -- POZOR, nema byt serial nebo autoincrement?
  login varchar(100),
);
-- table security_user
-- table posta_spisovna_zapujcky
CREATE TABLE posta_spisovna_zapujcky(
  id int4, -- POZOR, nema byt serial nebo autoincrement?
  vytvoreno date,
  vraceno date,
  spisovna_id int4,
  vytvoreno_kym int4,
  pujceno_komu int4,
  vraceno_komu int4,
  superodbor int4,
  stornovano varchar(255),
  rucne int2,
  rucne_cj text,
  poznamka text
); 


alter table cis_posta_predani add spis_id int8; 
alter table posta_schvalovani add poznamka2 varchar(4000);
alter table posta_schvalovani add postup int2 default (2);
alter table posta_schvalovani add stornovano varchar(255);
alter table posta_schvalovani add typschvaleni int2; 
update posta_schvalovani set typschvaleni=1 where typschvaleni is NULL;

alter table security_user add reditel boolean DEFAULT false;
alter table security_user add vedouci boolean DEFAULT false;

create table posta_czechpoint (
  id serial,
  user_id int4,
  login varchar(50),
  passwd varchar(50),
  last_user_id int4,
  owner_id int4,
  last_date date,
  last_time varchar(10)
);


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


alter table cis_posta_typ add poradi int default 10;
alter table POSTA_CIS_VYRIZENO add poradi int default 10;



alter table cis_posta_skartace add last_user_id int;
alter table cis_posta_skartace add owner_id int;
alter table cis_posta_skartace add last_date date;
alter table cis_posta_skartace add last_time varchar(10);

update cis_posta_skartace set owner_id='2510';

CREATE TABLE cis_posta_skartace_h (
    id integer ,
    kod character varying(5),
    nazev character varying(255),
    text text,
    skar_znak character varying(5),
    aktivni smallint DEFAULT 1,
    doba smallint,
    main_id smallint,
    last_user_id int,
    owner_id int,
    last_date date,
    last_time varchar(10),
    id_h serial
);

CREATE FUNCTION cis_posta_skartace_copy2history() RETURNS trigger
    LANGUAGE plpgsql
    AS $$BEGIN
  INSERT INTO cis_posta_skartace_h SELECT * FROM cis_posta_skartace WHERE id=OLD.id;
  IF TG_OP = 'DELETE' THEN
    RETURN OLD;
  ELSE
    RETURN NEW;
  END IF;
END;$$;

CREATE TRIGGER cis_posta_skartace_copy2history BEFORE UPDATE ON cis_posta_skartace FOR EACH ROW EXECUTE PROCEDURE cis_posta_skartace_copy2history();



alter table posta add kopie int2;
alter table posta_h add kopie int2;

alter table posta_cis_obalky add poradi int2;
update posta_cis_obalky set poradi=90 where poradi is null;

alter table security_group add poradi int2;
update security_group set poradi=90 where poradi is null;
