ďťż-- Do tabulky se ukladaji zaznamy pri ukladani datovych zprav do EED
-- dm - data message
CREATE TABLE posta_ds_dm_timestamp
(
  id serial NOT NULL,
  dm_id integer NOT NULL, -- ID datove zpravy
  "timestamp" timestamp with time zone NOT NULL -- casove razitko ulozeni datove zpravy do EED
)
WITH (
  OIDS=TRUE
);

-- Do tabulky obsahuje zaznamy, ktere slouzi jako filtry pro ukladani datovych zprav do EED
CREATE TABLE posta_ds_filtry
(
  id serial NOT NULL,
  dm_item character varying(64), -- polozka datove zpravy (dm - data message)
  dm_item_compared_values character varying(1024), -- hodnoty, kterych muze polozka datove zpravy nabyvat
  priority smallint, -- priorita filtru
  ed_item_superodbor integer, -- hodnota polozky elektronickeho dokumentu 'zarizeni' (ed - electronic document)
  ed_item_odbor integer, -- hodnota polozky elektronickeho dokumentu 'odbor'
  ed_item_referent integer -- hodnota polozky elektronickeho dokumentu 'zpracovatel'
)
WITH (
  OIDS=TRUE
);