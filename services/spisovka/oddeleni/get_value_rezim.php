<?php
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_full.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/status.inc"));
//Die(Jsme tam);
$q = new DB_POSTA;


if ($GLOBALS['SKARTACE_ID']<>'') {

  $skartace = Skartace_Pole($GLOBALS['SKARTACE_ID']);

  if ($skartace['znak'] == 'A') {$pismeno = "'A'"; $pismeno_alt = "'X'"; } //nebudeme nabizet, protoze bychom nabizeli stejny rezim, jak u spisoveho znaku
  if ($skartace['znak'] == 'V') {$pismeno = "'A','V'"; $pismeno_alt = "'A'"; }
  if ($skartace['znak'] == 'S') {$pismeno = " 'A','V','S'"; $pismeno_alt = "'A','V'"; }

  $where = "where (skar_lhuta>". $skartace['doba'] ." and skar_znak in ($pismeno)) OR (skar_lhuta=" . $skartace['doba'] ." and skar_znak in ($pismeno_alt))" ;


  $opt = '<option value=""></option>';
  $a = 1;
  $sql = "SELECT id,jid || ' - ' || skar_znak || '/' || skar_lhuta as NAZEV FROM posta_cis_skartacni_rezimy " . $where . " order by skar_znak asc, skar_lhuta asc";
  $q->query($sql);
  while ($q->Next_Record()) {
    $opt .= "<option value=\"" . $a ."\">" . $q->Record['NAZEV'] ."</option>";
    $a ++;
  }


  $subzak = str_replace("'","",$opt);
    
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
       if ($('select[name=REZIM_ID]', window.parent.document)) {
         var skar = $('select[name=REZIM_ID]', window.parent.document);
         skar.empty();
         skar.append('<?php echo $subzak;?>');
       }
    //-->
    </script>
    <?php
}

require(FileUp2("html_footer.inc"));
?>

