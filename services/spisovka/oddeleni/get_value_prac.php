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
    If (!$ODBOR) $ODBOR=0;
    if  (strpos($ODBOR, ',') !== false) {
       $odbor_array = explode(',',$ODBOR);
       foreach ($odbor_array as $o) {
         $result = VratPracovniky($o,1);
         //$hodnoty = array_merge($result,$hodnoty);
         $hodnoty = $result + $hodnoty;
       }
       $hodnoty = array_unique($hodnoty);
       asort($hodnoty);
    } else
    if (($hideall!="1")||($ODBOR<>0))  
    $hodnoty=VratPracovniky($ODBOR,1); //vcetne podrizenych
    $subzak = "<option value=\"\"></option>";
    $opt = ""; 
  		while (list($key,$val)=each($hodnoty)) {
        if (($GLOBALS["hodnota"]==$key)&&($GLOBALS["hodnota"]!='undefined')) $add_text=' SELECTED'; else $add_text='';
        $opt .= "<option value=\"".$key."\"$add_text>".$val."</option>";
    }
      $subzak .= $opt;
    ?>
    <script language="JavaScript" type="text/javascript">
       if ($('select[name=\'<?php echo $vysledek;?>\']', window.parent.document)) {
           
         var referent = $('select[name=\'<?php echo $vysledek;?>\']', window.parent.document);
         referent.empty();
         referent.append('<?php echo $subzak;?>');
       }
       var spn = window.parent.document.getElementById("<?php echo $vysledek;?>2");
       if (spn) {
         spn.innerHTML = '<?php echo $subzak;?>';
       }
    </script>
    <?php
    if (isset($_SESSION['WORKFLOW'])) {
      include(FileUp2('services/spisovka/workflow/workflow.php'));      
    }
    
require(FileUp2("html_footer.inc"));
?>

