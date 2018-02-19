<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('html_header_full.inc'));

$files_to_convert = array();

$cj_obj = LoadClass('EedCj',$DOC_ID);
echo '<h1>Soubory k autorizované konverzi '.$cj_obj->cislo_jednaci.'</h1>';
$docs = $cj_obj->GetDocsInCj($DOC_ID);
echo '<table class="table-body" cellpadding="5"><thead>';
echo '<tr><th>JID</th><th>Soubor</th><th>konverze</th></tr></thead>';
foreach($docs as $docID) {
  $files = LoadClass('EedUpload', $docID);
  foreach($files->uplobj_records as $file) {
    $soubor = strtolower($file['NAME']);
    if (strpos($soubor, '.pdf')) {
      if ($odd == 'odd') $odd = 'even'; else $odd = 'odd';
      echo '<tr  class="brow table-row-'.$odd.'"><td>'.$docID.'</td><td>'.$file['NAME'].'</td><td class="table-cell-btn">'.KonverzeDoListinne($file['ID'], $docID, $file['NAME']).'</td></tr>';
    }
  }
}
echo '</table>';
//print_r($files_to_convert);

function KonverzeDoListinne($id, $doc_id = 0, $name) {
  $name = strtolower($name);
  if (strpos($name, '.pdf')) {
    $href = "<a href=\"javascript:uploadKonverze('".$id."','".$doc_id."')\"><img src=\"" .  FileUpImage('images/save') . "\" border=\"0\" title=\"Autorizovaná konverze z elektronické do listinné podoby dokumentu z moci úřední\"></a>";
  }
  return $href;
}

echo "<script>
  function uploadKonverze(id,doc_id) {
    window.opener.NewWindowAgenda('/ost/posta/plugins/konverze/index.php?cmd=KonvezeEL&RECORD_ID='+id+'&DOC_ID='+doc_id+'&cacheid=');
  }
 //-->
</script>
";

echo '<p><input type="button" class="btn" onclick="parent.$.fancybox.close();" value="Zavřít okno"></p>';

require(FileUp2('html_footer.inc'));
