<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/db/db_default_reg.inc"));
@require_once(FileUp2("html_header_full.inc"));
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;

If ($typ=='O')
{
  $q=new DB_DEFAULT_REG;
  $sql="select id from obyvatele where prijmeni ilike '%".$prijmeni."%' and jmeno ilike '%".$jmeno."%'";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  
  If ($pocet==0)
  {Die ("<h2 align=center>Člověk nenalezen!</h2>");}
  
  If ($pocet==1)
  {
  $q->Next_Record();
  $id=$q->Record["ID"];
  echo "
  
  <script language=\"JavaScript\" type=\"text/javascript\">
  <!--
  document.location.href=\"./guide/obyvatele/page2.inc?SELECT_ID=".$id."&prefix=".$prefix."&typ=".$typ."\";
  //-->
  </script>
  ";
  
  }
  
  If ($pocet>1)
  { 
  $where="AND prijmeni ilike '%".$prijmeni."%' and jmeno ilike '%".$jmeno."%'";
     $count=Table(array(
              "appendwhere"=>$where,
              "showselect"=>true,
              "showaccess"=>true,
              "showguide"=>true,
              "agenda"=>"OBYVATELE",
              "table_name"=>"OBYVATELE",
              "multipleselect"=>false,
              "multipleselectsupport"=>true,
              "showdelete"=>false,
              "showedit"=>false,
              "setvars"=>false, 
              "unsetvars"=>array("except"=>array("ID")),
//  						"action"=>"./guide/obyvatele/page2.inc",
  						));  
  }
}

If ($typ=='P')
{
  $q=new DB_DEFAULT_REG;
  $sql="select id from organizace where nazev ilike '%".$prijmeni."%'";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  
  If ($pocet==0)
  {Die ("<h2 align=center>Firma nenalezena!</h2>");}
  
  If ($pocet==1)
  {
  $q->Next_Record();
  $id=$q->Record["ID"];
  echo "
  
  <script language=\"JavaScript\" type=\"text/javascript\">
  <!--
  document.location.href=\"./guide/obyvatele/page2.inc?SELECT_ID=".$id."&prefix=".$prefix."&typ=".$typ."\";
  //-->
  </script>
  ";
  
  }
  
  If ($pocet>1)
  { 
  $where="AND nazev ilike '%".$prijmeni."%'";
     $count=Table(array(
              "appendwhere"=>$where,
              "showselect"=>true,
              "showaccess"=>true,
              "showguide"=>true,
              "agenda"=>"ORGANIZACE",
              "multipleselect"=>false,
              "multipleselectsupport"=>true,
              "showdelete"=>false,
              "showedit"=>false,
              "setvars"=>false, 
              "unsetvars"=>array("except"=>array("ID")),
//  						"action"=>"./guide/obyvatele/page2.inc",
  						));  
  }
}
//Die($pocet);
?>
