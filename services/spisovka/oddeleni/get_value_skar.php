<?php
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_full.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/el/of_odbory_.inc"));
$hodnota=$hod;
//Die(Jsme tam);
if ($skartace<>'') {

	$kody = VratVecneSkupiny($skartace, 0, array(), array('jen_aktivni' => 1));
	$subzak = "<option value=\"\"></option>";
	foreach($kody as $id => $kod) {
		if ($kod['TYP'] ==2) {
			$text_full = str_replace('?', '-', $kod['CELY_NAZEV']);
			if (strlen($text_full)>120) {
				$mezera = strpos($text_full,' ', 120);
				if ($mezera<1) $mezera = 120;
				$text = substr($text_full, 0, $mezera);
			}
			else $text = $text_full;
			$text = str_replace('"','', $text);
			$text = str_replace(chr(10),'', $text);
			$text = str_replace(chr(13),'', $text);
			
			$text_full = str_replace('"','', $text_full);
			$text_full = str_replace(chr(10),'', $text_full);
			$text_full = str_replace(chr(13),'', $text_full);
				
			$opt .= "<option value=\"".$kod['ID']."\" title=\"".$text_full."\"> ".$text." - ".$kod['SKAR_ZNAK']."/".$kod['DOBA']."</option>";
		}
		
	}
/*
	$sql = "select * from cis_posta_skartace where nadrazene_id='".$skartace."' AND aktivni=1 order by text asc";
echo $sql;
  $opt = "";
  $q = new DB_POSTA;
  $q->query($sql);
  while ($q->Next_Record()) {

    $text = $q->Record['KOD'] . ' - ' . $q->Record['TEXT'];


    if ($q->Record['TYP'] == 2) {
        $opt .= "<option value=\"".$q->Record['ID']."\" title=\"".$text_full."\"> ".$text." - ".$q->Record['SKAR_ZNAK']."/".$q->Record['DOBA']."</option>";
    }
  }
*/
  $subzak .= $opt;

  $subzak = str_replace("'","",$subzak);
    
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
       if ($('select[name=SKARTACE]', window.parent.document)) {
         var skar = $('select[name=SKARTACE]', window.parent.document);
         skar.empty();
         skar.append('<?php echo $subzak;?>');
       }
//       var spn = window.parent.document.getElementById("<?php echo $vysledek;?>2");
//       if (spn) {
//         spn.innerHTML = '<?php echo $subzak;?>';
//       }
    //-->
    </script>
    <?php
}

require(FileUp2("html_footer.inc"));
?>

