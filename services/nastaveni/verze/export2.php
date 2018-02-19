<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2("html_header_full.inc"));

$filename='EED_changelog.csv';

$q=new DB_DEFAULT;
$sql='select * from posta_version order by datum';
$q->query($sql);

$text="";
while ($q->Next_Record())
{
//  $text='~'.$q->Record[CISLO]."|".$q->Record[DATUM]."|".$q->Record[PLUGIN]."|\"".$q->Record[POPIS]."\"|\"".$q->Record[OPRAVY]."\"".PHP_EOL.$text;
  $text='~'.$q->Record[CISLO]."|".$q->Record[DATUM]."|".$q->Record[PLUGIN]."|".$q->Record[POPIS]."|".$q->Record[OPRAVY]."".PHP_EOL.$text;
}

$text = iconv("utf-8","cp1250",$text);

$filepath = GetAgendaPath('POSTA',false,false)."/.admin/changelog/".$filename;

file_put_contents($filepath,$text);

chmod($filepath,0777);

/*header("Cache-Control: public, must-revalidate");
header("Pragma: hack");

header('Content-disposition: attachment; filename='.$filename);
header('Content-length: '.strlen($text));
echo $text;*/