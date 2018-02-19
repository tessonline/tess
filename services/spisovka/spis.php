<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require(FileUp2("html_header_full.inc"));
$puvodniid=$id;
echo "<span class=\"caption\">Přehled spisu $cislo_spisu1/$cislo_spisu2</span><br/><br/><p class=text>";

Function UkazSpis($cislo_spisu1,$cislo_spisu2)
{
  $q=new DB_POSTA;
  $a=new DB_POSTA;
  $dalsipodspis="";
  $q->query ("select * from posta where cislo_spisu1='$cislo_spisu1' and cislo_spisu2='$cislo_spisu2' order by EV_CISLO ");
  while($q->next_record())
    {    
    If ($q->Record["ID_PUVODNI"]==0)
      {
      $ID=$q->Record["ID"];
      $JMENO=$q->Record["ODESL_JMENO"];
      $PRIJMENI=$q->Record["ODESL_PRIJMENI"];
      $VEC=$q->Record["VEC"];
      $CISLO_SPISU1=$q->Record["CISLO_SPISU1"];
      $CISLO_SPISU2=$q->Record["CISLO_SPISU2"];
      $PODCISLO_SPISU=$q->Record["PODCISLO_SPISU"];
      If ($q->Record["PUVODNI_SPIS"]<>"") {$dalsipodspis=$q->Record["PUVODNI_SPIS"];}
      If ($PODCISLO_SPISU==0) {$text=$CISLO_SPISU1."/".$CISLO_SPISU2;} else {$text=$CISLO_SPISU1."/".$CISLO_SPISU2."/".$PODCISLO_SPISU;}  
      $DATUM_PODATELNA_PRIJETI=$q->Record["DATUM_PODATELNA_PRIJETI"];
      If ($q->Record["ODES_TYP"]=="A") {$jmeno="anonym";}
      If ($q->Record["ODES_TYP"]=="P") {$jmeno=$PRIJMENI.", IČO (".$JMENO.")";}
      If (($q->Record["ODES_TYP"]<>"A") and ($q->Record["ODES_TYP"]<>"P")) {$jmeno=$JMENO." ".$PRIJMENI;}
      If ($q->Record["ODESLANA_POSTA"]=="f") {$barva='blue';} else {$barva='green';} 
      echo "<p><font color=$barva><b>$text</b></font> dne <b>$DATUM_PODATELNA_PRIJETI</b> - $jmeno - <b>$VEC</b><br/>";
      $a->query ("select * from posta where id_puvodni=$ID order by podcislo_spisu");
      while($a->next_record())
        {    
         echo "&nbsp;<img src='".FileUp2("images/editor/tree_end.gif")."'>&nbsp;";
          $JMENO=$a->Record["ODESL_JMENO"];
          $PRIJMENI=$a->Record["ODESL_PRIJMENI"];
          $VEC=$a->Record["VEC"];
          $DATUM_PODATELNA_PRIJETI=$a->Record["DATUM_PODATELNA_PRIJETI"];
          $CISLO_SPISU1=$a->Record["CISLO_SPISU1"];
          $CISLO_SPISU2=$a->Record["CISLO_SPISU2"];
          $PODCISLO_SPISU=$a->Record["PODCISLO_SPISU"];
          If ($a->Record["PUVODNI_SPIS"]<>"") {$dalsipodspis=$q->Record["PUVODNI_SPIS"];}
          If ($a->Record["ODES_TYP"]=="A") {$jmeno="anonym";}
          If ($q->Record["ODES_TYP"]=="P") {$jmeno=$PRIJMENI.", IČO (".$JMENO.")";}
          If (($a->Record["ODES_TYP"]<>"A") and ($a->Record["ODES_TYP"]<>"P")) {$jmeno=$JMENO." ".$PRIJMENI;}
          If ($a->Record["ODESLANA_POSTA"]=="f") {$barva='blue';} else {$barva='green';} 
          echo "<font color=$barva><b>$CISLO_SPISU1/$CISLO_SPISU2/$PODCISLO_SPISU</b></font> dne <b>$DATUM_PODATELNA_PRIJETI</b> - $jmeno - <b>$VEC</b> <br/>";
        }
      }
    echo "</p>";
    }
  return $dalsipodspis;
}

echo "<script>\n";
echo "<!--\n";
echo "  function newfrom2(id) {\n";
echo "  newwindow = window.open('./services/spisovka/dalsi_spis/edit.php?edit&EDIT_ID='+id, 'agenda_nova', 'height=200,width=300,scrollbars,resizable');\n";
echo "  newwindow.focus();\n";
echo "  }\n";
echo "//-->\n";
echo "</script>\n";

$jetam=UkazSpis($cislo_spisu1,$cislo_spisu2);

If ($jetam<>"")
{
echo "<span class=\"caption\">Sloučeno se spisem $jetam</span><br/>";
$oddel=explode("/",$jetam);
//echo $oddel[0]."x".$oddel[1];
$a=UkazSpis($oddel[0],$oddel[1]);
}
If ($jetam=="")
$puvodni_spis=$cislo_spisu1."/".$cislo_spisu2;
  $q=new DB_POSTA;
  $q->query ("select * from posta where puvodni_spis='$puvodni_spis' ");
  while($q->next_record())
    { 

echo "<span class=\"caption\">Sloučeno se spisem ".$q->Record["CISLO_SPISU1"]."/".$q->Record["CISLO_SPISU2"]."</span><br/>";
  UkazSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"]);

}
echo "
<center><input type=\"button\" onClick=\"
history.go(-1);
\" value=\"Zpět do seznamu\" class=\"button\" align=center></center>

<br/><b><font color=blue>Modře - příchozí pošta</font>, 
<font color=green>Zeleně - odchozí pošta</font></b><br/><br/><br/>";

    echo "<input type=button class=button onclick=\"javascript:newfrom2(".$puvodniid.")\" value='Přiřadit dva spisy k sobě'>";

?>
