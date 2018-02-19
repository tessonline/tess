<?php

function getSelectData($select) {
  $result = array();
  if (is_object($select)) {
    $options = $select->options;
    if (is_array($options)) {
      foreach ($options as $option) {
        if (trim($option["value"])) {
          $result[$option["value"]] = $option["label"];
        }
      }
    }
  }
  return $result;
}

Function NactiData($pole=array(),$druh_doc=0)
{
  require(FileUp2(".admin/config.inc"));
  
  $data=array();

  if ($pole['SUPERODBOR']) $where2=" AND SUPERODBOR IN (".$pole['SUPERODBOR'].")";
  if ($pole['ODBOR']) $where2.=" AND odbor IN (".$pole['ODBOR'].")";
  if ($pole['REFERENT']) $where2.=" AND referent IN (".$pole['REFERENT'].")";
  if ($pole['TYP_POSTY']) $where2.=" AND typ_posty IN (".$pole['TYP_POSTY'].")";
  $where=" AND odes_typ<>'X' AND datum_podatelna_prijeti like '%.".$pole['MESIC'].".".$pole['ROK']."%' ".$where2;

  $q=new DB_POSTA;
  if ($druh_doc==0)
  {
    //bez druhu dokumentu, teda kompletni data, bez druhu dokumentu pro referenta
    
    $sql="SELECT count(*) as pocet FROM posta WHERE odeslana_posta='f' ".$where;
    $q->query($sql); $q->Next_Record();
    $celkemprichozi=$q->Record["POCET"];
    if ($historie)
    {
      $sql="SELECT count(*) as pocet FROM posta_stare_zaznamy WHERE odeslana_posta='f' ".$where;
      $q->query($sql); $q->Next_Record();
      $celkemprichozi=$celkemprichozi+$q->Record["POCET"];
    }
    $data[]=array("id"=>1,"TEXT"=>'<b>Celkem příchozí</b>',"POCET"=>$celkemprichozi,"SQL"=>$sql);
    
    $sql="SELECT count(*) as pocet FROM posta WHERE odeslana_posta='t' ".$where;
    $q->query($sql); $q->Next_Record();
    $celkemprichozi=$q->Record["POCET"];
    if ($historie)
    {
      $sql="SELECT count(*) as pocet FROM posta_stare_zaznamy WHERE odeslana_posta='t' ".$where;
      $q->query($sql); $q->Next_Record();
      $celkemprichozi=$celkemprichozi+$q->Record["POCET"];
    }
    $data[]=array("id"=>1,"TEXT"=>'<b>Celkem odchozí</b>',"POCET"=>$celkemprichozi,"SQL"=>$sql);
    
    while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"]))
    {
      $id=$val['VALUE'];
      $doporucene[$id] = $val['LABEL'];
  
      $sql="SELECT count(*) as pocet FROM posta WHERE odeslana_posta='t' ".$where." AND doporucene like '".$id."'";
      $q->query($sql); $q->Next_Record();
      $celkemprichozi=$q->Record["POCET"];
      if ($historie)
      {
        $sql="SELECT count(*) as pocet FROM posta_stare_zaznamy WHERE odeslana_posta='t' ".$where." AND doporucene like '".$id."'";
        $q->query($sql); $q->Next_Record();
        $celkemprichozi=$celkemprichozi+$q->Record["POCET"];
      }
      $data[]=array("id"=>"a","TEXT"=>'&nbsp;&nbsp;&nbsp;z toho ('.$id.') '.$val['LABEL'].'',"TEXT_GRAF"=>$id,"POCET"=>$celkemprichozi,"SQL"=>$sql);
      
    }
  
    while (list($key,$val)=each($GLOBALS["CONFIG"]["DRUH_ODESLANI"]))
    {
      $id=$val['VALUE'];
      $doporucene[$id] = $val['LABEL'];
  
      $sql="SELECT count(*) as pocet FROM posta WHERE odeslana_posta='t' ".$where." AND vlastnich_rukou like '".$id."'";
      $q->query($sql); $q->Next_Record();
      $celkemprichozi=$q->Record["POCET"];
      $data[]=array("id"=>"b","TEXT"=>'<b>odesláno přes </b>('.$id.') '.$val['LABEL'].'',"TEXT_GRAF"=>$id,"POCET"=>$celkemprichozi,"SQL"=>$sql);
      if ($historie)
      {
        $sql="SELECT count(*) as pocet FROM posta_stare_zaznamy WHERE odeslana_posta='t' ".$where." AND vlastnich_rukou like '".$id."'";
        $q->query($sql); $q->Next_Record();
        $celkemprichozi=$celkemprichozi+$q->Record["POCET"];
      }
      
    }
  }
  else
  {
    $sql="select distinct typ_posty from posta where 1=1 ".$where." and typ_posty>0";
    $a=new DB_POSTA;
    $q->query($sql);
    $data=array();
    while ($q->Next_Record())
    {
      $typ=$q->Record["TYP_POSTY"]?$q->Record["TYP_POSTY"]:0;
      $sql="select nazev from cis_posta_typ where id=".$typ;
      $a->query($sql); $a->Next_Record(); $nazev=$a->Record["NAZEV"];
      $sql="SELECT count(*) as pocet FROM posta WHERE typ_posty=$typ ".$where." ";
      $a->query($sql); $a->Next_Record();
      $celkemprichozi=$a->Record["POCET"];
      $data[]=array("id"=>"c","TEXT"=>'<b></b>('.$typ.') '.$nazev.'',"TEXT_GRAF"=>$typ,"POCET"=>$celkemprichozi,"SQL"=>$sql);

    }
  }
  return $data;

}

?>
