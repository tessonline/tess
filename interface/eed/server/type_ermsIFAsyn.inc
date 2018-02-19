<?php

/*$server->wsdl->addComplexType(
  'tUdalosti','complexType','struct','sequence','',
  array(
    //doplnit
  )
);
*/
$server->wsdl->addComplexType(
  'tUdalosti','complexType','array','sequence','',
  array(
    'VypraveniZalozeni'=>array('name'=>'VypraveniZalozeni', 'type'=>'tns:tDokumentZaevidovaniVypraveni', 'minOccurs'=>'0'),
    'VypraveniZruseni'=>array('name'=>'VypraveniZruseni', 'type'=>'tns:tDokumentZruseniVypraveni', 'minOccurs'=>'0'),

    'SouborZalozeni'=>array('name'=>'SouborZalozeni', 'type'=>'tns:tDokumentZaevidovaniSouboru', 'minOccurs'=>'0'),
    'SouborNovaVerze'=>array('name'=>'SouborNovaVerze', 'type'=>'tns:tDokumentZaevidovaniSouboru', 'minOccurs'=>'0'),

    'DokumentUprava'=>array('name'=>'DokumentUprava', 'type'=>'tns:tDokumentUprava', 'minOccurs'=>'0'),
    'DokumentZruseni'=>array('name'=>'DokumentZruseni', 'type'=>'tns:tDokumentZruseni', 'minOccurs'=>'0'),
    'DokumentVlozeniDoSpisu'=>array('name'=>'DokumentVlozeniDoSpisu', 'type'=>'tns:tDokumentVlozeniDoSpisu', 'minOccurs'=>'0'),
    'DokumentVyjmutiZeSpisu'=>array('name'=>'DokumentVyjmutiZeSpisu', 'type'=>'tns:tDokumentVyjmutiZeSpisu', 'minOccurs'=>'0'),

    'SpisUprava'=>array('name'=>'SpisUprava', 'type'=>'tns:tSpisUprava', 'minOccurs'=>'0'),
    'SpisVyrizeni'=>array('name'=>'SpisVyrizeni', 'type'=>'tns:tSpisVyrizeni', 'minOccurs'=>'0'),
  )

//    'SouborZruseni'=>array('name'=>'SouborZruseni', 'type'=>'tns:tDokumentZaevidovaniSouboru', 'minOccurs'=>'0'),
//    'SouborNovaVerze'=>array('name'=>'SouborNovaVerze', 'type'=>'tns:tDokumentZaevidovaniSouboru', 'minOccurs'=>'0'),
);

$server->wsdl->addComplexType(
  'tSpisUprava','complexType','array','sequence','',
  array(
    'ProfilSpisu'=>array('name'=>'ProfilSpasa', 'type'=>'tns:tProfilSpisu', 'nillable'=>'false'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'tSpisVyrizeni','complexType','array','sequence','',
  array(
    'SpisId'=>array('name'=>'SpisId', 'type'=>'tns:tIdSpisu', 'nillable'=>'false'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
    'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tSpisDoplnujiciData', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'tSpisDoplnujiciData','complexType','array','sequence','',
  array(
    'ZpusobVyrizeni'=>array('name'=>'ZpusobVyrizeni', 'type'=>'xsd:string', 'minOccurs'=>'0'),
    'DatumCasVyrizeni'=>array('name'=>'DatumCasVyrizeni', 'type'=>'xsd:dateTime'),
  )
);


$server->wsdl->addComplexType(
  'tDokumentVlozeniDoSpisu','complexType','array','sequence','',
  array(
    'SpisId'=>array('name'=>'SpisId', 'type'=>'tns:tIdSpisu', 'nillable'=>'false', 'minOccurs'=>'0'),
    'DokumentyVlozene'=>array('name'=>'DokumentyVlozene', 'type'=>'tns:tDokumentyVlozene', 'nillable'=>'false', 'minOccurs'=>'0'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'tDokumentVyjmutiZeSpisu','complexType','array','sequence','',
  array(
    'SpisId'=>array('name'=>'SpisId', 'type'=>'tns:tIdSpisu', 'nillable'=>'false', 'minOccurs'=>'0'),
    'DokumentyVlozene'=>array('name'=>'DokumentyVlozene', 'type'=>'tns:tDokumentyVlozene', 'nillable'=>'false', 'minOccurs'=>'0'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'tDokumentyVlozene','complexType','array','sequence','',
  array(
    'DokumentUplnyVlozeny'=>array('name'=>'DokumentUplnyVlozeny', 'type'=>'tns:tDokumentUplnyVlozeny', 'nillable'=>'true', 'minOccurs'=>'0'),
    'DokumentIdVlozeny'=>array('name'=>'DokumentIdVlozeny', 'type'=>'tns:tDokumentIdVlozeny', 'nillable'=>'true', 'minOccurs'=>'0'),
  )
);


$server->wsdl->addComplexType(
  'tDokumentUplnyVlozeny','complexType','array','sequence','',
  array(
    'VlastniDokument'=>array('name'=>'VlastniDokument', 'type'=>'tns:tDokument', 'minOccurs'=>'0'),
    'DorucenyDokument'=>array('name'=>'DorucenyDokument', 'type'=>'tns:tDokument', 'minOccurs'=>'0'),
    'PoradiVeSpisu'=>array('name'=>'PoradiVeSpisu', 'type'=>'xsd:int', 'minOccurs'=>'0'),
    'StavZarazeniDoSpisu'=>array('name'=>'StavZarazeniDoSpisu', 'type'=>'xsd:string', 'nillable'=>'false'),
  )
);


$server->wsdl->addComplexType(
  'tDokumentIdVlozeny','complexType','array','sequence','',
  array(
    'IdDokument'=>array('name'=>'IdDokument', 'type'=>'tns:tIdDokument', 'nillable'=>'false'),
    'PoradiVeSpisu'=>array('name'=>'PoradiVeSpisu', 'type'=>'xsd:int', 'minOccurs'=>'0'),
    'StavZarazeniDoSpisu'=>array('name'=>'StavZarazeniDoSpisu', 'type'=>'xsd:string', 'nillable'=>'false'),
  )
);

$server->wsdl->addComplexType(
  'tDokumentZruseni','complexType','array','sequence','',
  array(
    'DokumentZruseni'=>array('name'=>'DokumentZruseni', 'type'=>'tns:tIdDokument', 'nillable'=>'false'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'tDokumentUprava','complexType','array','sequence','',
  array(
    'ProfilDokumentuUprava'=>array('name'=>'ProfilDokumentuUprava', 'type'=>'tns:tDokument', 'nillable'=>'false'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'tDokumentZaevidovaniVypraveni','complexType','array','sequence','',
  array(
    'DokumentZaevidovaniVypraveni'=>array('name'=>'DokumentZaevidovaniVypraveni', 'type'=>'tns:DokumentZaevidovaniVypraveni', 'nillable'=>'false'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'DokumentZaevidovaniVypraveni','complexType','array','sequence','',
  array(
    'IdDokument'=>array('name'=>'IdDokument','type'=>'tns:tIdDokument', 'nillable'=>'false'),
    'Vypraveni'=>array('name'=>'Vypraveni', 'type'=>'tns:tZasilkaOdchozi', 'nillable'=>'false'),
  )
);




$server->wsdl->addComplexType(
  'tDokumentZruseniVypraveni','complexType','array','sequence','',
  array(
    'DokumentZruseniVypraveni'=>array('name'=>'DokumentZruseniVypraveni', 'type'=>'tns:tDokumentZruseniVypraveni', 'nillable'=>'false'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);

$server->wsdl->addComplexType(
  'tDokumentZruseniVypraveni','complexType','array','sequence','',
  array(
    'IdDokument'=>array('name'=>'IdDokument','type'=>'tns:tIdDokument', 'nillable'=>'false'),
    'Vypraveni'=>array('name'=>'Vypraveni', 'type'=>'tns:tZasilkaOdchozi', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);






$server->wsdl->addComplexType(
  'tDokumentZaevidovaniSouboru','complexType','array','sequence','',
  array(
    'DokumentZaevidovaniSouboru'=>array('name'=>'DokumentZaevidovaniSouboru', 'type'=>'tns:DokumentZaevidovaniSouboru', 'nillable'=>'false'),
    'Autorizace'=>array('name'=>'Autorizace', 'type'=>'tns:tAutorizace', 'nillable'=>'false'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
  )
);


$server->wsdl->addComplexType(
  'DokumentZaevidovaniSouboru','complexType','array','sequence','',
  array(
    'IdDokument'=>array('name'=>'IdDokument','type'=>'tns:tIdDokument', 'nillable'=>'false'),
    'Soubory'=>array('name'=>'Soubory','type'=>'tns:tFilesArray'),
  )
);




/*
DokumentZaevidovaniSouboru
arraty IdDokument a Soubory
*/
