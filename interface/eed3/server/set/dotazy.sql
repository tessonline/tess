Vymaz identifikatoru:
--------------------
update posta set dalsi_id_agenda = NULL,dalsi_id_spis_agenda = NULL;
update upload_files set external_id = NULL;

Test:
----
select * from posta where id = 571579;
update posta set dalsi_id_agenda = id where id = 571579;