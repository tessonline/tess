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
      "elements"=>array(array("type"=>"select_superodbor","name"=>"SUPERODBOR", "required"=>true)),
      "label"=>$GLOBALS['CONFIG']['NAZEV_SUPERODBOR']
    ),

    array(
      "label"=>"Přístupy do web. služby DR:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"SERVER_USERNAME", "required"=>true)),
      "label"=>"Uživatel pro WS:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"SERVER_PASSWD", "required"=>true)),
      "label"=>"Heslo pro WS:"
    ),

    array(
      "label"=>"Přístupy pro klienta DR:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"KLIENT_URL", "required"=>false, "size"=>100)),
      "label"=>"URL WSDL aplikace:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"KLIENT_ENDPOINT", "required"=>false, "size"=>100,tooltip=>'pokud klient nemá správně definováno WSDL, uveďte pouze endpoint služby')),
      "label"=>"URL endpoint aplikace:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"KLIENT_USERNAME", "required"=>false)),
      "label"=>"Uživatel pro WS:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"KLIENT_PASSWD", "required"=>false)),
      "label"=>"Heslo pro WS:"
    ),
    array(
      "elements"=>array(array("type"=>"checkbox","name"=>"KLIENT_AUTHEN", "required"=>false)),
      "label"=>"Autentizace pomocí basic autentizace (default je přes header soap zprávy):"
    ),
    array(
      "elements"=>array(array("type"=>"checkbox","name"=>"KLIENT_MUZO", "required"=>false)),
      "label"=>"Zprávy se odesílají do MUZO (speciální klient):"
    ),
    array(
      "label"=>"Notifikace:"
    ),
    array(
      "elements"=>array(array("type"=>"text","name"=>"EMAILY", "required"=>false, "size"=>100,tooltip=>'lze zadat více adres oddělených čárkou')),
      "label"=>"E-mail adresa:"
    ),

  )
);    

