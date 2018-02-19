<?php
  
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"file", "name"=>"UPLOAD_FILE"),
		           array( "type"=>"hidden", "name"=>"SKARTACNI_RIZENI_ID"),
		
				),
                   "label"=>"soubor s XML importem:");


// z duvodu, aby se v tagu form pridalo enctype="multipart/form-data" viz. ooohforms.inc
$f->isfile = true;
