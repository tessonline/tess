CREATE TABLE posta_one_click (

  document_id integer, -- identifikator EED dokumentu
  task_id integer, -- identifikator ukolu ve sluzbe 1click
  
  CONSTRAINT posta_one_click_pk PRIMARY KEY (document_id, task_id)
  
) WITH (OIDS = TRUE);
