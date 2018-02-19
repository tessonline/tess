<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

if (!$GLOBALS['EDIT_ID']) $GLOBALS['EDIT_ID']=$GLOBALS['DELETE_ID'];

  $GLOBALS['ID'] = $GLOBALS['DELETE_ID'];
  include('.admin/has_access.inc');
  if (!MaPristupKSmazaniDokumentu($GLOBALS['ID'])) {
  	EedTools::MaPristupKDokumentu($bbb, 'storno dokumentu');

  }


//echo "<span class='caption'>Stornování záznamu</span>";
//Table(array("sql"=>"select * from posta where id=".$GLOBALS[DELETE_ID],"setvars"=>true, "nocaption"=>true, "nopaging"=>true, "showcount"=>$showcount, "showedit"=>false, "showdelete"=>false, "noprint"=>true, "noexport"=>true, "noaccesscondition"=>true, "showaccess"=>true, "noshowrelation"=>true, "noshowinsert2clip"=>true, "noshowrelationbreak"=>true));

Table(array(
  "tablename" => "delete",
  'sql' => 'select * from posta where id=' . $GLOBALS[DELETE_ID],
  'modaldialogs' => false,
  'schema_file' => '.admin/table_schema_simple.inc',
  'setvars' => true,
  'showhistory' => true,
  'showupload' => false,
  'showedit' => false,
  'showinfo' => false,
  'showdelete' => false,
  'select_id' => 'ID' ,
  'unsetvars' => true ,
));

echo "<form method='get' id='frm_moje' name='frm_moje'>";
echo "<input type='hidden' name='ID' value='$GLOBALS[DELETE_ID]'>";
echo '
<div class="form dark-color"> 
<div class="form-body"> <div class="form-row">
<div class="form-item"> <label class="form-label" for="field">Důvod stornování: </label>
 <div class="form-field-wrapper"> <div class="form-field">
 <input  id="storno" placeholder="napište důvod storna"  value="" type="text" name="duvod" size="80" maxlength="80">
 </div> </div> </div>

<p><a class="btn btn-loading"><span class="btn-spinner"></span>
<input type="submit" class="btn" value="Skutečně stornovat tento dokument">';
echo '</p>
</div></div></div>';
echo "</form>";

echo '
<script type="text/javascript">
  document.getElementById("frm_moje").onsubmit = function() {
    if (!document.getElementById("storno").value) {
      alert("Musí být vyplněn důvod");
      return false;
    }
    var action = "services/spisovka/zneplatnit.php?cacheid=";
    var elements = document.getElementById("frm_moje").elements;
    for (i=0; i<elements.length; i++){
      action = action + "&" + elements[i].name + "=" + elements[i].value;
    }
    window.opener.NewWindowAgenda(action);
    return false;
 }
</script>
';


require(FileUp2("html_footer.inc"));

?>
