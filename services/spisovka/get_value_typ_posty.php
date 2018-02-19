<?php
$hod=$hodnota;
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/el/of_odbory_.inc"));
include_once(FileUp2(".admin/security_name.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_full.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));
$hodnota=$hod;
$q = new DB_POSTA;
$hodnoty = array();
//$GLOBALS['TYP_POSTY'] = "";
If (!$AGENDA) $AGENDA=0;
if  (strpos($AGENDA, ',') !== false) {
  $AGENDA_array = explode(',',$AGENDA);
  foreach ($AGENDA_array as $typ) {
    $result = VratTypDokumentu($typ,$smer_dokumentu);
    $hodnoty = array_merge($result,$hodnoty);
  }
  $hodnoty = array_unique($hodnoty);
  asort($hodnoty);
} else
  $hodnoty=VratTypDokumentu($AGENDA,$smer_dokumentu);
  $podatelna = HasRole('editace_vse_pracoviste');
  if (($AGENDA=='null')&&(HasRole('editace_vse_pracoviste'))) {
    //$REM_BLANK = 0;
    $hodnoty = array();
  }
  
  if ($REM_BLANK<>1)
    //if ($BLANK==1)
      $subzak = "<option value=\"\"></option>";
      //else
      //$subzak = "";
      $opt = "";
      while (list($key,$val)=each($hodnoty)) {
        if (($GLOBALS["hodnota"]==$key)&&($BLANK!=1)) $add_text=' SELECTED'; else $add_text='';
        $opt .= "<option value=\"".$key."\"$add_text>".$val."</option>";
      }
      $subzak .= $opt;
      ?>
    <script language="JavaScript" type="text/javascript">
       if ($('select[name=\'<?php echo $vysledek;?>\']', window.parent.document)) {
           
         var typ_dokumentu = $('select[name=\'<?php echo $vysledek;?>\']', window.parent.document);
         typ_dokumentu.empty();
         typ_dokumentu.append('<?php echo $subzak;?>');
         if ('<?php echo $zmenatypposty;?>'!='false') {
           	typ_dokumentu.trigger('change');
           }
       }
    //  var spn = window.parent.document.getElementById("<?php echo $vysledek;?>2");
    //   if (spn) {
    //     spn.innerHTML = '<?php echo $subzak;?>';
    //   }
    </script>
    <?php
//require(FileUp2("html_footer.inc"));
?>

