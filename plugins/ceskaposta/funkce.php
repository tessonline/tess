<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2("schvalovani/.admin/schvalovani.inc"));
require(FileUp2(".admin/security_name.inc"));
//require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2("html_header_title.inc"));
set_time_limit(0);
Function NactiPisemnosti($protokol_id,$datum_od,$datum_do,$odbor) {
  $where="";
  If ($GLOBALS["CONFIG"]["DB"]=='psql')
  {
    $where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."')";
    $where.=" AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."')";
  }
  If ($GLOBALS["CONFIG"]["DB"]=='mssql')
  {
    $where.=" CONVERT(datetime,datum_podatelna_prijeti,104) >= CONVERT(datetime,'".$GLOBALS["DATUM_OD"]."',104)";
    $where.=" AND CONVERT(datetime,datum_podatelna_prijeti,104) <= CONVERT(datetime,'".$GLOBALS["DATUM_DO"]."',104)";
  }

  If ($GLOBALS['CONFIG_POSTA_CESKAPOSTA']['DO_PROTOKOLU_JEN_CK'] && !HasRole('podatelna-odbor')) {
      $where = " 1=1 "; //pokud jsem velka podatelna a predavam dokumenty pres CK, pak nemusim zohlednovat datum.
  }


  $where.=" AND stornovano is null";
  
  //jen odeslane pisemnosti
  $where.=" AND odeslana_posta='t'";
  //jen pisemnosti na ceskou postu
  $where.=" AND vlastnich_rukou='1'";

  //bez vlastnich zaznamu
  $where.=" AND ODES_TYP<>'Z'";

  //bez vlastnich zaznamu
  $where.=" AND datum_vypraveni is null";

  //bez vlastnich zaznamu
  $where.=" AND (kopie is null or kopie=0)";


  $where.=" AND superodbor in(".EedTools::VratSuperOdbor().")";
  //jen dokuemnty, ktere jsou zvazene?parametr v configu
  If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) $where.=" AND hmotnost is not null";
  If ($GLOBALS['CONFIG_POSTA_CESKAPOSTA']['DO_PROTOKOLU_JEN_CK']) {

    If ($GLOBALS['CONFIG_POSTA_CESKAPOSTA']['PODATELNA_ODBOR_BEZ_CK'] && HasRole('podatelna-odbor'))
      $where .= " ";
    else
      $where .= " AND DATUM_PREDANI_VEN is not null";
  }


  //a ktere tedy obalky, hle obycejne se tam neeviduji
  $where2=" AND ((doporucene='1') or (doporucene='2') or (doporucene='3') or (doporucene='4') or (doporucene='5') or (doporucene='C') or (doporucene='Z'))";
  $where3=" AND (doporucene='Z')";
  
  If ($odbor<>'') {
    $odbory = array();
    $odbory[] = $odbor;
    $user_obj = LoadClass('EedUser', 11);
    $unity = $user_obj->VratOdborZSpisUzlu($odbor);
    $podrizene_unity = $user_obj->VratPodrizeneUnity($unity);
    foreach($podrizene_unity as $unita => $val) {
      $temp = $user_obj->VratSpisUzelZOdboru($unita);
      if ($temp['ID']>0) $odbory[] = $temp['ID'];
    }


    $unity = $user_obj->VratOdborZSpisUzlu($odbor);
    $podrizene_unity = $user_obj->VratNadrizeneUnity($unity);
    foreach($podrizene_unity as $unita => $val) {
      $temp = $user_obj->VratSpisUzelZOdboru($unita);
      if ($temp['ID']>0) $odbory[] = $temp['ID'];
    }

    $where.=" AND odbor IN (".implode(',',$odbory).")";
  }
  
  $q=new DB_POSTA;
  $w=new DB_POSTA;
  $a=new DB_POSTA;
  $sql = 'select * from posta_cis_ceskaposta where id='.$GLOBALS['ID'];
  $a->query($sql); $a->Next_Record();
  $protokol_text = $a->Record[PROTOKOL].'/'.$a->Record[ROK];

  if ($GLOBALS['CONFIG_POSTA']['PLUGINS']['deniky']['enabled'] && $a->Record['MAIN_DOC']>0) {
    $main_doc = $a->Record['MAIN_DOC'];
    if ($main_doc == 1) $main_doc = "0,1";
    $where .= " and main_doc in (".$main_doc.")";
  }

  if ($GLOBALS["CONFIG"]["CPOST_VAZIT"])
    $sql='select * from posta where '.$where.$where2.' ORDER BY xertec_id';
  else
    $sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,datum_podatelna_prijeti';
  $q->query($sql);
  $pridavany_dokument=array();
  while ($q->Next_Record()) {
    $id=$q->Record["ID"];
    $doc = LoadSingleton('EedDokument', $id);
    $CISLO_JEDNACI = $doc->cislo_jednaci;

    $pridavany_dokument[]=$id;
    $ev_cislo=$q->Record["EV_CISLO"];
    $rok=$q->Record["ROK"];
    $doporucene=$q->Record["DOPORUCENE"];
    //zjistime, jestli uz pisemnost nebyla zarazena do nejakyho protokolu
    $sql='select * from posta_cis_ceskaposta_id i left join posta_cis_ceskaposta c ON c.id=i.protokol_id where pisemnost_id='.$id;
//    echo $sql;
    $w->query($sql);
    $pocet=$w->Num_Rows();
    $w->Next_Record();
    if (JeVeSchvaleni($id))
    {
      //pisemnost uz tam je, tak to jenom vypisem...
      echo '<b>Dokument '.$id.' ('.$CISLO_JEDNACI.') je ve schvalovacím procesu!!! nepřidávám</b><br/>';
    
    }
    else
    {
      If ($pocet>0)
      {
        //pisemnost uz tam je, tak to jenom vypisem...
        echo 'Dokument '.$id.' ('.$CISLO_JEDNACI.') je v pořádku uveden na protokolu č. '.$w->Record[PROTOKOL].'/'.$w->Record[ROK].'<br/>';
      }
      else
      {
        echo '<b>Zařazuji dokument ('.$CISLO_JEDNACI.') </b><br/>';
        $sqla="insert into posta_cis_ceskaposta_id VALUES (".$protokol_id.",".$id.",'".$doporucene."')";
  //      echo $sqla;
        $w->query($sqla);    
      }
    }
  }
  $zarazene_dokumenty=array();
  $sql='select * from posta_cis_ceskaposta where id='.$protokol_id;
  $w->query($sql); $w->Next_Record(); $protokol=$w->Record['PROTOKOL'];
  $sql='select * from posta_cis_ceskaposta_id where protokol_id='.$protokol_id;
  $w->query($sql);
  while ($w->Next_Record()) $zarazene_dokumenty[]=$w->Record["PISEMNOST_ID"];

  $vymazat= array_diff($zarazene_dokumenty,$pridavany_dokument);
  if (is_array($vymazat)) 
    while (list($key,$val)=each($vymazat)) {
      $sql='select * from posta where id='.$val;
      $q->query($sql);
      $q->Next_Record();
      $doc = LoadSingleton('EedDokument', $val);
      $CISLO_JEDNACI = $doc->cislo_jednaci;

      echo '<b>Vymazávám dokument '.$q->Record["ID"].' ('.$CISLO_JEDNACI.'), nesplňuje podmínky pro tento protokol.</b><br/>';
      $sql='delete from posta_cis_ceskaposta_id where protokol_id='.$protokol_id.' and pisemnost_id='.$val;
//      echo $sql."<br/>";
      $q->query($sql);
    } 
//  echo "<input type='button' class='button btn' value='Hotovo, vrátit se' onclick='history.go(-1)'>";
  echo "<input type='button' class='btn' value='Hotovo, vrátit se' onclick='document.location.href=\"brow.php\"'>";
}

Function Vytisknuto($protokol)
{
  $LAST_TIME=Date('d.m.Y H:i:s');
  $q=new DB_POSTA;
  $sql="update posta_cis_ceskaposta set datum_vytisteni='".$LAST_TIME."' where id=".$protokol;
  //echo $sql;
  $q->query($sql);
  echo "<script>history.go(-1)</script>";
}

If ($GLOBALS[typ]==1) NactiPisemnosti($GLOBALS["ID"],$GLOBALS["DATUM_OD"],$GLOBALS["DATUM_DO"],$GLOBALS["ODBOR"]);
If ($GLOBALS[typ]==2) Vytisknuto($GLOBALS["ID"]);


require(FileUp2("html_footer.inc"));

?>
