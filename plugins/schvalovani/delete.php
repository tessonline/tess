<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2("html_header_full.inc"));

echo "<span class='caption'>Stornování záznamu</span>";
Table(array("sql"=>"select * from posta where id=".$GLOBALS[DELETE_ID],"setvars"=>true, "nocaption"=>true, "nopaging"=>true, "showcount"=>$showcount, "showedit"=>false, "showdelete"=>false, "noprint"=>true, "noexport"=>true, "noaccesscondition"=>true, "showaccess"=>true, "noshowrelation"=>true, "noshowinsert2clip"=>true, "noshowrelationbreak"=>true));
echo "<form method='get' action='zneplatnit.php'>";
echo "<input type='hidden' name='ID' value='$GLOBALS[DELETE_ID]'>";
echo '
<div class="form dark-color">
<div class="form-body"> <div class="form-row">
<div class="form-item"> <label class="form-label" for="field">Důvod stornování: </label>
 <div class="form-field-wrapper"> <div class="form-field">
 <input  id="storno" placeholder="napište důvod storna"  value="" type="text" name="duvod" size="80" maxlength="200">
 </div> </div> </div>

<p><a class="btn btn-loading"><span class="btn-spinner"></span>
<input type="submit" class="btn" value="Skutečně stornovat toto schvalování">';
echo '</p>
</div></div></div>';
echo "</form>";

require(FileUp2("html_footer.inc"));

?>
