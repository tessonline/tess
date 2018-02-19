-- Table: posta_vnitrni_adresati_nastaveni
-- Tabulka obsahuje zaznamy o vnitrnich adresatech dene skupiny

CREATE TABLE posta_nastaveni_vnitrni_adresati (
  id serial NOT NULL,
  skupina_id integer,
  organizacni_vybor integer,
  zpracovatel integer,
  CONSTRAINT fk_posta_nastaveni_vnitrni_adresati_posta_id FOREIGN KEY (skupina_id)
      REFERENCES posta_nastaveni_vnitrni_adresati_skupiny (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
) WITH OIDS;

CREATE INDEX pki_posta_nastaveni_vnitrni_adresati_id ON posta_nastaveni_vnitrni_adresati USING btree (id);
CREATE INDEX fki_posta_nastaveni_vnitrni_adresati_posta_id ON posta_nastaveni_vnitrni_adresati USING btree (skupina_id);
