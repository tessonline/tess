<?php
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_full.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/el/of_odbory_.inc"));
//Die(Jsme tam);
$q = new DB_POSTA;
if ($GLOBALS['SPIS_ID']<>'') {

  $opt = '';
  $a = 1;
  $sql = 'select * from posta_cis_typ_spis_soucasti where spis_id=' . $GLOBALS['SPIS_ID'];
echo $sql;
  $q->query($sql);
  while ($q->Next_Record()) {
    $opt .= "<option value=\"" . $a ."\">" . $q->Record['NAZEV'] ."</option>";
    $a ++;
  }


  $subzak = str_replace("'","",$opt);
    
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
       if ($('select[name=VYBRANA_SOUCAST]', window.parent.document)) {
         var skar = $('select[name=VYBRANA_SOUCAST]', window.parent.document);
         skar.empty();
         skar.append('<?php echo $subzak;?>');
       }
    //-->
    </script>
    <?php
}

require(FileUp2("html_footer.inc"));
?>

