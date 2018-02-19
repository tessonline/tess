<?php
NewWindow(array("fname" => "Agenda", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit"));


Function MuzeDuverne($id, $owner_id) {
   global $USER_INFO;
   static $q;
   $muze_duverne = false;
   if (!$q) $q = new DB_POSTA;
   $sql = 'select referent,private,superodbor from posta where id='.$id;
   $q->query($sql); $q->Next_Record(); $data=$q->Record;

  if ($owner_id == $USER_INFO['ID']) $muze_duverne = true;
//  if ($data['REFERENT'] == $USER_INFO['ID']) $muze_duverne = true;

  if (HasRole("cist-dokument-do-vlastnich-rukou")) $muze_duverne = true;

  return $muze_duverne;
}

Function Url2FileEed($id, $id_h, $directory, $name, $typefile) {
  static $upl;
  $koncovka = end(explode('.', $name));

  $href = Url2File($id, $id_h, $directory, $name, $typefile);
  if ($GLOBALS['CONFIG']['USE_CUL_ONLINE_EDIT'] && strpos($href, 'href') && in_array(strtolower($typefile), $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['STORAGE']['CUL_Service']['onlineEdit'])) {
    if (!$upl) $upl = Upload(array(
              'create_only_objects' => true,
              'agenda' => 'POSTA',
              'noshowheader'=>true)
            );

    $url = $upl['table']->stg_obj->onlineEdit($GLOBALS['DIRECTORY']);
    if ($url) $href .= '&nbsp;<a href="' . $url . '" target="ifrm_doc" title="Otevřít pro online editaci dokumentu"><img src="'.FileUp2('ost/posta/images/editpen.gif').'"></a>';
    else $href = $name;
    return $href;
  }
  else
  return $href;
}

function FormatujNazev($nazev) {
  return $nazev;
}

function ConvertPdf($id, $doc_id = 0, $name, $converted = 0) {
  $koncovka = end(explode('.', $name));
  $doc = LoadClass('EedDokument', $doc_id);
  if (in_array(strtolower($koncovka), $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['CONVERT_TYPES']) && $doc->status>1 && $converted == 0)
    $href = "<a href=\"javascript:uploadConvert('".$id."','".$doc_id."')\"><img src=\"" .  FileUpImage('images/pdf') . "\" border=\"0\" title=\"Převod souboru do PDF\"></a>";
  else
    $href = "";
  if ($converted == 1) $href = "<img src=\"" .  FileUpImage('images/ok') . "\" border=\"0\" title=\"Soubor je již převeden.\">";

  if ($GLOBALS['PRIVATE'] == 'y' && !MuzeDuverne($id, $GLOBALS['OWNER_ID'])) $href = '';

  return $href;
}

function KonverzeDoListinne($id, $doc_id = 0, $name) {
  $name = strtolower($name);
  if (strpos($name, '.pdf')) {
    $href = "<a href=\"javascript:uploadKonverze('".$id."','".$doc_id."')\"><img src=\"" .  FileUpImage('images/save') . "\" border=\"0\" title=\"Autorizovaná konverze z elektronické do listinné podoby dokumentu z moci úřední\"></a>";
  }
  return $href;
}

echo "<script>
  function uploadConvert(id,doc_id) {
    NewWindowAgenda('/ost/posta/ug_func.php?cmd=convert&RECORD_ID='+id+'&DOC_ID='+doc_id+'&cacheid=');
  }
  function uploadKonverze(id,doc_id) {
    NewWindowAgenda('/ost/posta/plugins/konverze/index.php?cmd=KonvezeEL&RECORD_ID='+id+'&DOC_ID='+doc_id+'&cacheid=');
  }
 //-->
</script>
";

