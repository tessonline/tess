<?php
session_start();
/*
  if (isset($JOIN_ID) && ($GUIDE_ID == 0)):
    SetCookie("COOK_JOIN_ID", $JOIN_ID);
  endif;  
*/

//    SetCookie("IDP2","", time() - 3600);



if ($prijemci<>"") {
SetCookie("GUIDE_NAME_MOJE", $GUIDE_NAME);
SetCookie("GUIDE_PATH_MOJE", $GUIDE_PATH);
  SetCookie("PRIJEMCI2",$prijemci);
}
if ($prijemci==",") {  SetCookie("PRIJEMCI2","");}

If ($GLOBALS["obalka_zadano"]) SetCookie("obalka",$GLOBALS["obalka_zadano"]);
If ($GLOBALS["doruceni_zadano"]) SetCookie("doruceni",$GLOBALS["doruceni_zadano"]);

?>
