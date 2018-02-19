CREATE TABLE posta_spisovna_cis_lokace (
	id serial,
	id_parent integer,
	nazev varchar(30),
	plna_cesta text
);

CREATE INDEX "plna_cesta_posta_spisovna_cis_lokace_key" on "posta_spisovna_cis_lokace" (plna_cesta);

alter table posta_spisovna_cis_lokace add spisovna_id int4;
CREATE INDEX "spisovna_id_posta_spisovna_cis_lokace_key" on "posta_spisovna_cis_lokace" (spisovna_id);
