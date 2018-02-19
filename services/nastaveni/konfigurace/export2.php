<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2("html_header_full.inc"));

$q=new DB_POSTA;
$sql='select * from posta_konfigurace where superodbor is null';
$q->query($sql);
header("Cache-Control: public, must-revalidate");
header("Pragma: hack");

$text="";
while ($q->Next_Record())
{
  $text.=$q->Record[KATEGORIE]."|".$q->Record[TYP]."|".$q->Record[PARAMETR]."|".$q->Record[POPIS]."|||";
}

//header('Content-type: application/pdf');
header('Content-disposition: attachment; filename=nastaveni.eed');
header('Content-length: '.strlen($text));
echo $text;
