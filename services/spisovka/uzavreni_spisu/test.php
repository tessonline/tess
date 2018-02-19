<?php
require_once("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/run2_.inc"));

$upl = LoadClass('EedUpload', 500077468);

$valid_files = array('xml','pdf','png','tiff','tif','jpeg','jpg','gif','mpg','mpg2','avi','mp3','wab','pcm','xnkm');


foreach($upl->uplobj_records as $soubor) {
  $koncovka = end(explode('.', basename($soubor['NAME'])));
  if (!in_array(strtolower($koncovka), $valid_files)) {
    echo "Musime konvertovat";
    //$seznam = $upl->ConvertFile('podpis.doc');
  }
  print_r($koncovka);
}

//$seznam = $upl->ConvertFile('podpis.doc');
//print_r($seznam);