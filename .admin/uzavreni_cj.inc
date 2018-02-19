<?php

$GLOBALS['chyby'] = array();

//zfo je tu proto, aby se nekonvertovalo... krome dorucenka.zfo, ktera je taxativne uvedena pri hlednai
//$valid_files = array('xml','pdf','png','tiff','tif','jpeg','jpg','gif','mpg','mpg2','avi','mp3','wab','pcm','xnkm','zfo');
$valid_files = array('xml','png','tiff','tif','jpeg','jpg','gif','mpg','mpg2','avi','mp3','wab','pcm','xnkm','zfo');


function LzeUzavritCj($spis_id) {
  global $valid_files;

  $EedCj = LoadClass('EedCj', $spis_id);
  $docIDS = $EedCj->GetDocsInCj($spis_id);
  $musime_konvertovat = false;
  $files_to_convert = array();
  $files_not_converted = array();
  foreach($docIDS as $doc) {

    $eed_doc = LoadClass('EedDokument', $doc);

    if ($eed_doc->typ_dokumentu == 'D') {
      $upl = LoadClass('EedUpload', $doc);

      foreach($upl->uplobj_records as $soubor) {
        $koncovka = strtolower(end(explode('.', basename($soubor['NAME']))));
        if ((!in_array(strtolower($koncovka), $valid_files) || ($soubor['NAME'] == 'dorucenka.zfo')) && $soubor['CONVERTED'] == 0) {
          $musime_konvertovat = true;
          $files_to_convert[$soubor['ID']] = array('name'=>$soubor['NAME'], 'id'=>$eed_doc->barcode);
          if ($_GET['skutecne_konvertovat'] == 1) {
            if (!$convert = $upl->ConvertFile($soubor['NAME'])) $files_not_converted[$soubor['ID']] = $soubor['NAME'];
          }

        }
      }
    }

  }
  if ($_GET['skutecne_konvertovat'] == 1) $musime_konvertovat = false;

  if ($musime_konvertovat) {
    include_once(FileUp2('html_header_full.inc'));
    echo '<h1>Konverze dokumentů</h1>';
    echo '<p>U následujících digitálních dokumentů musí být konvertovány přílohy do výstupního formátu:</p>';
    foreach($files_to_convert as $id => $val)
      echo $val['id'] . ' - soubor: ' . $val['name'] . '<br/>';

    echo '<p><form method="get" action=""><input type="hidden" name="skutecne_konvertovat" value="1">';
    echo '<input type="hidden" name="spis_id" value="'.$spis_id.'">';
    echo '<input type="submit" value="   Skutečně provést   " class="btn">';
    echo '</form></p>';
    echo '<table height="300"><tr><td><p></p></td></tr></table>';
    include_once(FileUp2('html_footer.inc'));
    Die();
  }

  if (count($files_not_converted)>0) {
    include_once(FileUp2('html_header_full.inc'));
      echo '<h1>Konverze dokumentů</h1>';
    echo '<p>U následujících digitálních dokumentů došlo k chybě při konverzi:</p>';
    foreach($files_to_convert as $id => $val)
      echo $val['id'] . ' - soubor: ' . $val['name'] . '<br/>';

//    echo '<p>Proveďte konverzi ručně.</p>';
    echo '<p>Proveďte uzavření později (soubory se mezitím zpracovávají na pozadí).</p>';
    echo '<p><form method="get" action=""><input type="hidden" name="skutecne_konvertovat" value="1">';
    echo '<input type="button" onclick="window.opener.document.location.reload();" value="   Zavřít   " class="btn">';
    echo '</form></p>';
    include_once(FileUp2('html_footer.inc'));
    Die();
  }

  reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
  foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
    if ($plug['enabled']){
      $file = FileUp2('plugins/'.$plug['dir'].'/.admin/uzavreni_cj_end.inc');
  		if (File_Exists($file)) include($file);
    }
  }

  return $chyba;
}

