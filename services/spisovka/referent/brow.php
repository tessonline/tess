<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
/*
if ($GLOBALS['POSTA_ID'])
{
  $q=new DB_POSTA;
  $sql='select * from posta where id='.$GLOBALS['POSTA_ID'];
  $q->query($sql); $q->Next_Record();
  $vec=$q->Record['VEC']; $referent=UkazUsera($q->Record['REFERENT']);
  echo "<span class='text'>Prvotní zpracovatel:&nbsp;<b>$referent</b>&nbsp;&nbsp;&nbsp;Věc:&nbsp;<b>".$vec."</b></span>";
}
*/

$GLOBALS['ID']=$GLOBALS['POSTA_ID'];
//Table(array("showaccess" => true,"appendwhere"=>$where2,"showhistory"=>true,"showdelete"=>false));  

NewWindow(array("fname"=>"", "name"=>"vicereferentu", "header"=>true, "cache"=>false, "window"=>"edit"));
echo "<form name=\"frm_pf_parc\" method=\"GET\">\n";
echo "<input type=\"submit\" class='button btn' value=\"Další zpracovatel\" onClick=\"NewWindow('edit.php?insert&POSTA_ID=".$GLOBALS["POSTA_ID"]."');return false;\">\n";
echo "<input type=\"button\" class='button btn' value=\"Zavřít\" onClick=\"Zavri();\">\n";
echo "</form>";
echo '
   <script language="JavaScript" type="text/javascript">
    <!--
    function Zavri()
    {
      window.opener.document.location.reload();
      window.close();
    }
//      window.close();
    //-->
    </script>
  ';
require(FileUp2("html_footer.inc"));
?>
