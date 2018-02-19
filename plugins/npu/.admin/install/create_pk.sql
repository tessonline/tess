create table posta_npu_pam_katalog (
  id serial,
  jid int,
  typ_id smallint,
  pk_id int
);

alter table posta_npu_pam_katalog add owner_id int;
alter table posta_npu_pam_katalog add last_date date;
alter table posta_npu_pam_katalog add last_time varchar(10);


CREATE  INDEX "jid_posta_npu_pam_katalog_key" on "posta_npu_pam_katalog" (jid);
CREATE  INDEX "typ_pk_posta_npu_pam_katalog_key" on "posta_npu_pam_katalog" (typ_id,pk_id);
CREATE  INDEX "jid_typ_pk_posta_npu_pam_katalog_key" on "posta_npu_pam_katalog" (jid,typ_id,pk_id);


