<?php
  
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"file", "name"=>"UPLOAD_FILE")),
                   "label"=>"soubor s CSV importem:");

    $FORM_CONFIG["schema"][] = array("elements"=>array(
                   array( "type"=>"select_spisovna", "name"=>"SPISOVNA_ID","insertnull"=>true,'label'=>'Spisovna','required'=>true),
                   array( "type"=>"hidden", "name"=>"REGISTRATURA","value"=>-1),
                   array( "type"=>"hidden", "name"=>"DIGITALNI","value"=>0),
                   array( "type"=>"hidden", "name"=>"DOKUMENT_ID"),
                ),
      );


// z duvodu, aby se v tagu form pridalo enctype="multipart/form-data" viz. ooohforms.inc
$f->isfile = true;
