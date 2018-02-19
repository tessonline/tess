<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2(".admin/security_.inc"));
require(FileUp2("html_header_full.inc"));

$q=new DB_POSTA;


if (!$duvod)
{

include_once(FileUp2('.admin/security_name.inc'));
include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));

  $sql="SELECT stornovano from ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." WHERE ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]."=".$GLOBALS[DELETE_ID];
  $q->query($sql); $q->Next_Record();
  if (strlen($q->Record["STORNOVANO"])<1)
  {
    echo "<h1>Stornování záznamu</h1>";
    $sql="select * from ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]."=".$GLOBALS[DELETE_ID];
    $appendwhere=" AND z.".$GLOBALS["PROPERTIES"]["AGENDA_ID"]."=".$GLOBALS[DELETE_ID];
    Table(array("appendwhere"=>$appendwhere,"setvars"=>true, "nocaption"=>true, "nopaging"=>true, "showcount"=>$showcount, "showedit"=>false, "showdelete"=>false, "noprint"=>true, "noexport"=>true, "noaccesscondition"=>true, "showaccess"=>true, "noshowrelation"=>true, "noshowinsert2clip"=>true, "noshowrelationbreak"=>true));
    echo "<form method='get' action='delete.php'>";
    echo "<input type='hidden' name='ID' value='$GLOBALS[DELETE_ID]'>";
echo '<div class="form dark-color">
<div class="form-body"> <div class="form-row">
<div class="form-item"> <label class="form-label" for="field">Důvod stornování: </label>
 <div class="form-field-wrapper"> <div class="form-field">
 <input  id="storno" placeholder="napište důvod storna"  value="" type="text" name="duvod" size="80" maxlength="100">
 </div> </div> </div>

<p><a class="btn btn-loading"><span class="btn-spinner"></span>
<input type="submit" class="btn" value="Skutečně stornovat tento dokument">';
echo '</p>
</div></div></div>';
echo "</form>";
  }
  else
  {
    echo "<span class='caption'>".$q->Record['STORNOVANO']."</span>";
  }
}
if ($duvod)
{
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:m:i');
  $LAST_DATE=Date('Y-m-d');
  $dnes=Date('d.m.Y');
  //$sql="update posta set spis_vyrizen=NULL,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID   where cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2."";
  $duvod='Dne <b>'.$dnes.'</b> v <b>'.$LAST_TIME.'</b> uživatel <b>'.$jmeno.'</b> stornoval tento záznam. Důvod: <b>'.$duvod.'</b>';

  if ($duvod=='NULL')
    $sql="UPDATE ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." SET STORNOVANO=NULL WHERE ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]."=".$ID;
  elseif ($duvod=='DELETE')
    $sql="DELETE from ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." WHERE ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]."=".$ID;
  else
  {
    $sql="UPDATE ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." SET STORNOVANO='$duvod' WHERE ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]."=".$ID;
    $q->query($sql);
//    $sql="UPDATE kvp_polozky SET STORNOVANO='$duvod' WHERE cislo_akce like '".$AKCE."'";
  }
//  echo $sql;
  $q->query($sql);
  
  echo '
   <script language="JavaScript" type="text/javascript">
    <!--
      window.opener.location.reload();
      window.close();
    //-->
    </script>
  ';

}
require(FileUp2("html_footer.inc"));

?>
