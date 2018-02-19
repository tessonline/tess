<?php


 $FORM_CONFIG["schema"][] = array(   
            "label"=>"Skutečně chcete smazat spis?");
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"SPIS_ID","value"=>$GLOBALS[spis_id]),
          ),
            "format"=>"'<br/>
            <center>
            <input name=\"__\" value=\"  Ano  \" class=\"btn\" type=\"submit\" />
&nbsp;&nbsp;&nbsp;<input name=\"___\" value=\"  Ne  \" type=\"button\" class=\"btn\" onclick=\"parent.$.fancybox.close();\" /></center>'",
            "label"=>"   ");		



?>
