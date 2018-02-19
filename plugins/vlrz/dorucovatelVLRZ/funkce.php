<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/schvalovani.inc"));
require(FileUp2(".admin/security_name.inc"));
//require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2("html_header_full.inc"));

Function NactiPisemnosti($protokol_id,$datum_od,$datum_do,$odbor)
{
  $where="";
  If ($GLOBALS["CONFIG"]["DB"]=='psql')
  {
    $where.=" (DATUM_PODATELNA_PRIJETI,) >= ('".$GLOBALS["DATUM_OD"]."',)";
    $where.=" AND (DATUM_PODATELNA_PRIJETI,) <= ('".$GLOBALS["DATUM_DO"]."',)";
  }
  If ($GLOBALS["CONFIG"]["DB"]=='mssql')
  {
    $where.=" CONVERT(datetime,datum_podatelna_prijeti,104)>CONVERT(datetime,'".$GLOBALS["DATUM_OD"]."',104)";
    $where.=" AND CONVERT(datetime,datum_podatelna_prijeti,104)<CONVERT(datetime,'".$GLOBALS["DATUM_DO"]."',104)";
  }

  $where.=" AND stornovano is null";
  
  //jen odeslane pisemnosti
  $where.=" AND odeslana_posta='t'";
  //jen pisemnosti na ceskou postu
  $where.=" AND vlastnich_rukou='2'";

  //bez vlastnich zaznamu
  $where.=" AND ODES_TYP<>'Z'";

  $where.=" AND superodbor in(".VratSuperOdbor().")";

  //jen dokuemnty, ktere jsou zvazene?parametr v configu
//  If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) $where.=" AND hmotnost is not null";
  //a ktere tedy obalky, hle obycejne se tam neeviduji
  $where2=" AND ((doporucene='1') or (doporucene='2') or (doporucene='3') or (doporucene='4') or (doporucene='5'))";
  $where3=" AND (doporucene='Z')";

  
  If ($odbor<>'')
    $where.=" AND odbor IN (".$odbor.")";
  
  $q=new DB_POSTA;
  $w=new DB_POSTA;
  If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
    $sql='select * from posta where '.$where.$where2.' ORDER BY xertec_id';
  else
    $sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,datum_podatelna_prijeti';
  $q->query($sql);
  $pridavany_dokument=array();
  while ($q->Next_Record())
  {
    $id=$q->Record["ID"];
    $pridavany_dokument[]=$id;
    $ev_cislo=$q->Record["EV_CISLO"];
    $rok=$q->Record["ROK"];
    $doporucene=$q->Record["DOPORUCENE"];
    //zjistime, jestli uz pisemnost nebyla zarazena do nejakyho protokolu
    $sql='select * from posta_cis_dorucovatel_id where pisemnost_id='.$id;
//    echo $sql;
    $w->query($sql);
    $pocet=$w->Num_Rows();
    $w->Next_Record();
    if (JeVeSchvaleni($id))

    {
      //pisemnost uz tam je, tak to jenom vypisem...
      echo 'Dokument '.$id.' je ve schvalovacím procesu!!! nepřidávám<br/>';
    
    }
    else
    {
//    echo $pocet;
      If ($pocet>0)
      {
        //pisemnost uz tam je, tak to jenom vypisem...
        echo 'Dokument '.$id.' je již zařazen v protokolu č. '.$w->Record[PROTOKOL_ID].'<br/>';
      }
      else
      {
        echo 'Zařazuji dokument '.$ev_cislo.'/'.$rok.' <br/>';
        $sqla="insert into posta_cis_dorucovatel_id VALUES (".$protokol_id.",".$id.",'".$doporucene."')";
  //      echo $sqla;
        $w->query($sqla);    
      }
    }
  }
  $zarazene_dokumenty=array();
  $sql='select * from posta_cis_dorucovatel where id='.$protokol_id;
  $w->query($sql); $w->Next_Record(); $protokol=$w->Record['PROTOKOL'];
  $sql='select * from posta_cis_dorucovatel_id where protokol_id='.$protokol_id;
  $w->query($sql);
  while ($w->Next_Record()) $zarazene_dokumenty[]=$w->Record["PISEMNOST_ID"];

  $vymazat= array_diff($zarazene_dokumenty,$pridavany_dokument);
  if (is_array($vymazat)) 
    while (list($key,$val)=each($vymazat))
    {
      $sql='select ev_cislo,rok from posta where id='.$val;
      $q->query($sql);
      $q->Next_Record();
      echo 'Vymazávám dokument '.$q->Record["ID"].', nesplňuje podmínky pro tento protokol.<br/>';
      $sql='delete from posta_cis_dorucovatel_id where protokol_id='.$protokol_id.' and pisemnost_id='.$val;
//      echo $sql."<br/>";
      $q->query($sql);
    } 
  echo "<input type='button' class='button btn' value='Hotovo, vrátit se' onclick='history.go(-1)'>";
}

Function Vytisknuto($protokol)
{
  $LAST_TIME=Date('d.m.Y H:m:i');
  $q=new DB_POSTA;
  $sql="update posta_cis_dorucovatel set datum_vytisteni='".$LAST_TIME."' where id=".$protokol;
  $q->query($sql);
  echo "<script>history.go(-1)</script>";
}

If ($GLOBALS[typ]==1) NactiPisemnosti($GLOBALS["ID"],$GLOBALS["DATUM_OD"],$GLOBALS["DATUM_DO"],$GLOBALS["ODBOR"]);
If ($GLOBALS[typ]==2) Vytisknuto($GLOBALS["ID"]);


require(FileUp2("html_footer.inc"));

?>
