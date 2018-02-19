<?php

 $FORM_CONFIG["schema"][] = array("label"=>"Údaje z XERTECu:");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"HMOTNOST"),   
            array( "type"=>"text", "name"=>"CENA"),   
						),
						"format"=>"HMOTNOST...'&nbsp;g&nbsp;&nbsp;&nbsp;Cena:&nbsp;'...CENA...'&nbsp;Kč'",
            "label"=>"Váha zásilky:");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_druh_zasilky", "name"=>"DRUH_ZASILKY"),   
            array( "type"=>"select_ano_ne", "name"=>"DRUHE_DODANI"),   
						),
						"format"=>"DRUH_ZASILKY...'&nbsp;&nbsp;&nbsp;Druhé dodání:&nbsp;'...DRUHE_DODANI",
            "label"=>"Druh zásilky:");		

?>						
