<?php
$GLOBALS['CONFIG_POSTA']['PLUGIN_UK'] = array(
  'SQL_STUDENT' => "select * from ssl_osoby_studenti os 
      left join ssl_per_kontakt pk on (pk.id_osoba=os.cislo_uk)
    left join ssl_val_kontakt vk on (pk.val_kontakt=vk.val_kontakt)
    where cislo_uk='WHOIS_NUMBER'",
  'SQL_PRAC' => "select * from ssl_job_zamestnani os
      left join ssl_per_kontakt pk on (pk.id_osoba=os.cislo_uk)
    left join ssl_val_kontakt vk on (pk.val_kontakt=vk.val_kontakt)
    where cislo_uk='WHOIS_NUMBER'"
);

