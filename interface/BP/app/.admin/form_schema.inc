<?php

$FORM_CONFIG = array(
  "schema"=>array(
    array(
      "label"=>"Hlavní údaje:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"NAZEV", "required"=>true)),
      "label"=>"Název aplikace:"
    ),
    array(
      "label"=>"Přístupy do web. služby:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"USERNAME", "required"=>true)),
      "label"=>"Uživatelské jméno:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"PASSWORD", "required"=>true)),
      "label"=>"Heslo:"
    ),

    array(
      "label"=>"Nastavení identifikace:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"ZDROJ_ID", "required"=>true)),
      "label"=>"Identifikace ZDROJ_ID pro TESS:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"EXT_ZDROJ_ID", "required"=>true)),
      "label"=>"Identifikace ZDROJ_ID pro aplikaci:"
    ),

  )
);    

