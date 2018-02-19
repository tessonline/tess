DB:
--

ALTER TABLE posta ADD COLUMN dalsi_id_agenda character varying(100);
ALTER TABLE posta_h ADD COLUMN dalsi_id_agenda character varying(100);

ALTER TABLE posta ADD COLUMN dalsi_id_spis_agenda character varying(100);
ALTER TABLE posta_h ADD COLUMN dalsi_id_spis_agenda character varying(100);

ALTER TABLE upload_files ADD COLUMN external_id character varying(20);
ALTER TABLE upload_files_h ADD COLUMN external_id character varying(20);

ALTER TABLE files ADD COLUMN external_id character varying(100);
ALTER TABLE files_h ADD COLUMN external_id character varying(100);

//update posta set dalsi_id_agenda = dalsi_id_agenda_old; 

ALTER TABLE posta ALTER COLUMN dalsi_id_agenda TYPE character varying(100);
ALTER TABLE posta_h ALTER COLUMN dalsi_id_agenda TYPE character varying(100);

ALTER TABLE posta ALTER COLUMN dalsi_id_spis_agenda TYPE character varying(100);
ALTER TABLE posta_h ALTER COLUMN dalsi_id_spis_agenda TYPE character varying(100);
