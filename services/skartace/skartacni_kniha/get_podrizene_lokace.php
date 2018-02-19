<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require(FileUp2("html_header_full.inc"));

$id = $GLOBALS['ID'];
$name = $GLOBALS['NAME'];

$q = new DB_POSTA;
$sql = "select count(*) as POCET from posta_spisovna_cis_lokace where id_parent =".$id;
$q->query($sql);
$q->next_record();

list($p1, $p2, $p3) = split('[_]', $name);
if (!$p3) {
  $p3=0;
  ?>
  <script type="text/javascript">
  
  var lokace_id = $('input[name=\'LOKACE_ID\']', window.parent.document);
  var lokace_select = $('select[name=\'LOKACE_SELECT\']', window.parent.document);
  lokace_id.val(lokace_select.val());
  </script>

  <?php 
  
}
$p3++;
?>
  <script type="text/javascript">
  var lokace_text = $('input[name=\'LOKACE_TEXT\']', window.parent.document);
  var lokace_id = $('input[name=\'LOKACE_ID\']', window.parent.document);
  var pos = <?php echo $p3; ?>;
  if (pos>0)
  for (i = (pos); i < 10; i++) { 
	    try {
    	  var lokace_select = $('select[name=\'LOKACE_SELECT_'+i+'\']', window.parent.document);
		    lokace_select.parent().parent().parent().parent().remove();
	    } catch(err) {
	    }
	}
  </script>

<?php 

//vratime dalsi ofselect jako append, pokud neexistuje, vyplnime vybranou hodnotu do LOKACE_TEXT a nastavime hidden LOKACE_ID
if ($q->Record['POCET']>0) {
  $select_row = '<div class="form-row"><div class="form-item"><div class="form-field-wrapper"><div class="form-field">';  
  $podrizene_lokace = getSelectDataEed(new of_select_lokace(array("parent"=>$id, "insertnull"=>true)));
  $select_row.= "<select name = \"LOKACE_SELECT_".($p3)."\" onchange=\"zmenaLokace(this);\"><option value=\"\"></option>"; 
  while (list($key,$val)=each($podrizene_lokace))
    $select_row.="<option value=\"".$key."\">".$val."</option>";
    $select_row.="</select>";
    $select_row.='</div></div></div></div>';
  ?>
  <script type="text/javascript">
		lokace_text.val('');
		lokace_id.val('0');
  	$('.form-body', window.parent.document).append('<?php echo $select_row; ?>');
  </script>
  <?php 
} else {
  $sql = "select plna_cesta from posta_spisovna_cis_lokace where id =".$id;
  $q->query($sql);
  $q->next_record();
  ?>
  <script type="text/javascript">
  	lokace_text.val('<?php echo $q->Record['PLNA_CESTA']; ?>');
  	lokace_id.val('<?php echo $id; ?>');
  </script>
  <?php 
}


