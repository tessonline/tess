<?php

$uk = new DB_POSTA;
$sql = 'select * from posta where id=' . $GLOBALS['doc_id'];
$uk->query($sql);
$uk->Next_Record();

$data = explode(chr(13), $uk->Record['POZNAMKA']);

$replace = array(
  'PREDCHOZI' => 'Rodné příjmení: ',
  'FAKULTA' => 'Fakulta: ',
  'PROGRAM' => 'Studijní program: ',
  'OBOR' => 'Obor: ',
  'FORMA' => 'Forma: ',
  'ROK' => 'Studium od: '
);

echo "<TABLE>";
foreach($data as $parametr) {
  list($kod, $hodnota) = explode('=', trim($parametr));
  if ($hodnota == 'P') $hodnota = 'prezenční';
  if ($hodnota == 'K') $hodnota = 'kombinovaná';
  if ($hodnota == 'D') $hodnota = 'distanční';
  echo '<tr><td>' . $replace[$kod]  . '&nbsp;</td><td><b>' . $hodnota .'</b></td></tr>';

}
echo "</table>";
//plugins/uk/edit_stitek.php
echo '<a class="btn" href="#" onclick="NewWindowStitek(\'plugins/uk/stitek_typovy_spis/edit.php?edit&EDIT_ID='.$GLOBALS['doc_id'].'\')">Tisknout údaje typového spisu</a>&nbsp;';


//NewWindowAgendaSpis

NewWindow(array("fname" => "Stitek", "name" => "Stitek", "header" => true, "cache" => false, "window" => "edit"));
