<?php

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/config.inc"));


$is_history = In_Array($form_params["formtype"], array($f_history));
$is_info = In_Array($form_params["formtype"], array($f_info));



class of_select_workflow extends of_select {
  // Constructor
  
  function of_select_workflow($a) {
    $workflow = array (
      array('value' => '1', 'label' => 'změna dat'),
    //  array('value' => '2', 'label' => 'změna dat2'),
       array('value' => '2', 'label' => 'založ schvalovací proces')
    );
    
    if ($GLOBALS['CONFIG']['WORKFLOW_POLOZKY_FORMULARE']) 
      $workflow[] = array('value' => '3', 'label' => 'nové pole formuláře');
    
    //definuje dostupne workflow pro dany druh dokumenu
    $workflow_typ = array (
      "muj druh doc" => array (1,3),
      "faktura" => array (1),
      "smlouva"=> array (2)
      );
    
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    foreach ($workflow as $w) {
      // pokud je definovany atribut typ_posty vrati pouze workflow definovana v poli $workflow_typ pro dany typ posty, jinak vraci vsechna workflow
      unset($a["typ_posty"]);
      if (isset($a["typ_posty"])) {
        $key = $a["typ_posty"];
        if (isset($workflow_typ[$key])) {
          if (in_array($w['value'], $workflow_typ[$key])) {
            $this->options[] = array('value' => $w['value'], 'label' => $w['label']);
          }
        }
      } else
      $this->options[] = array('value' => $w['value'], 'label' => $w['label']);

    }
  }
}

class  of_select_datovy_typ extends of_select {
  // Constructor
  
  function of_select_datovy_typ($a) {
    
    $datove_typy = array (
      array('value' => 'text', 'label' => 'text'),
      array('value' => 'text_number', 'label' => 'číslo')
    );
    
    $this->setup_element($a);
    $this->options = array();
    foreach ($datove_typy as $d) 
      $this->options[] = array('value' => $d['value'], 'label' => $d['label']);
  }
  
}

class of_select_promenna extends of_select {
  // Constructor
  
  function of_select_promenna($a) {
    
   /* $sql = "SELECT a.id,a.nazev FROM cis_posta_promenne a";
    $db = new DB_POSTA;
    $db->query($sql);
    
    $nazvy = array();
    while ($db->Next_record()) {    
      $key = $db->Record['ID'];
      $value = $db->Record['NAZEV'];
      $nazvy[$key] = $value; 
    }*/
    
    $nazvy = array(
      'DATUM_PODATELNA_PRIJETI' => 'Datum přijetí/vytvoření',
      'DATUM_VYRIZENI'=> 'Datum vyřízení',
      'VEC' => 'Věc',
      'ODBOR' => 'Vyřizující spisový uzel',
      'TYP_DOKUMENTU' => 'Typ dokumentu',
      'REFERENT' => 'Zpracovatel',
      'ODES_TYP' => 'Typ odesilatele/adresáta',
      'ODESL_ODBOR' => 'Interní pošta: Adresát -spis.uzel',
      'ODESL_PRAC2' => 'Interní pošta: Adresát - zpracovatel',
      'ODESL_OSLOVENI' => 'Adresa: Oslovení',
      'ODESL_TITUL' => 'Adresa: Titul před',
      'ODESL_PRIJMENI' => 'Adresa: Příjmení',
      'ODESL_JMENO' => 'Adresa: Jméno fyzické osoby',
      'ODESL_PRIJMENI_FIRMA' => 'Adresa: Název organizace/firmy',
      'ODESL_EMAIL' => 'Adresa: E-mail',
      'ODESL_ULICE' => 'Adresa: Ulice',
      'ODESL_CP' => 'Adresa: číslo popisné',
      'ODESL_COR' => 'Adresa: číslo orientační',
      'ODESL_PSC' => 'Adresa: PSČ',
      'ODESL_POSTA' => 'Adresa: Město',
      'ODESL_DATSCHRANKA' => 'Adresa: Datová schránka',
      'VLASTNICH_RUKOU' => 'Způsob vypravení',
      'VYRIZENO' => 'Způsob vyřízení',
      'DOPORUCENE' => 'Obálka',
      'POZNAMKA' => 'Poznámka',
      'OBALKA_NEVRACET' => 'Nevracet',
      'OBALKA_10DNI' => 'Jen 10 dní',
      
    );

    $spolecne_udaje = array ('VEC','DATUM_PODATELNA_PRIJETI','ODES_TYP','TYP_DOKUMENTU','POZNAMKA');
    $odchozi = array(
      'ODESL_ODBOR',
      'ODESL_PRAC2',
      'ODESL_ODBOR',
      'ODESL_OSLOVENI',
      'ODESL_TITUL',
      'ODESL_PRIJMENI',
      'ODESL_JMENO',
      'ODESL_PRIJMENI_FIRMA',
      'ODESL_EMAIL',
      'ODESL_ULICE',
      'ODESL_CP',
      'ODESL_COR',
      'ODESL_PSC',
      'ODESL_POSTA',
      'ODESL_DATSCHRANKA',
      'VLASTNICH_RUKOU',
      'DOPORUCENE',
      'OBALKA_NEVRACET',
      'OBALKA_10DNI',
    );
    $prichozi = array('ODBOR','REFERENT','VYRIZENO','DATUM_VYRIZENI');
    
    //definuje dostupne promenne pro dany typ workflow druh dokumentu (P = prichozi, O = odchozi)
    $promenne = array (
      1 => array("P" => array_merge($spolecne_udaje,$prichozi),"O" => array_merge($spolecne_udaje,$odchozi)),
    //  2 => $dalsi_udaje,
    //  3 => $adresat,
    );
    
    $this->setup_element($a);
    $this->options = array();
    
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    
    // pokud je definovan atribut workflow, vrati pouze promenne definovane v poli $promenne pro dane workflow, jinak vraci promenne pod klicem 1 v poli promenne     
    if (isset($a["workflow"])) $workflow =$a["workflow"]; else $workflow = 1;
    
    //pokud je definovana promenna dokument, vrati pouze promenne definovane pro dany dokument
    if (isset($a["dokument"])) $dokument = $a["dokument"]; else $dokument = "";
    foreach ($promenne as $key => $p_arr) {
      if ($key==$workflow)
        foreach($p_arr as $key_doc => $p) {
          //pokud je definovano rozdeleni na prichozi a odchozi dokument
          if (is_array($p)) {
            if ($dokument=="") {
              foreach($p as $p2) {
                isset($nazvy[$p2])?$label=$nazvy[$p2]:$label=$p2;
                $this->options[] = array('value' => $p2, 'label' => $label);
                
              } 
            } else {
              if ($key_doc == $dokument) {
                foreach($p as $p2) {
                  isset($nazvy[$p2])?$label=$nazvy[$p2]:$label=$p2;
                  $this->options[] = array('value' => $p2, 'label' => $label);
                }
              }
            }
            
            
          } else {
            isset($nazvy[$p])?$label=$nazvy[$p]:$label=$p;
            $this->options[] = array('value' => $p, 'label' => $label);
          }
        }
      

    }
    $this->options = array_unique($this->options,SORT_REGULAR);    

  }
}



