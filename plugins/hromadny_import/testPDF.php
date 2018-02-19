<?php
require('tmapy_config.inc');
require(FileUp2(".admin/upload_.inc"));

//guids doc souboru
$files = array(
  'c65a7525-e5ab-4dc1-babd-556112e0cb40',
  '36370b08-4f4e-4ad2-84d5-a12e10c44cf0'
);


$uplobj = Upload(array(
          'create_only_objects' => true,
          'agenda' => 'POSTA',
          'noshowheader'=>true)
        );


$pdf = $uplobj['table']->stg_obj->mergeFiles( $files );

Header("Content-Type: application/pdf");
Header("Content-Disposition: attachment;filename=vystup.pdf");

echo $pdf;