<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_obj.inc")); 
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$datum=date('d.m.Y H:m');
include_once(FileUp2("html_header_full.inc")); 

$zapujcka_id=$id;
$sql="select posta_id from posta_spisovna_zapujcky_id where zapujcka_id=".$id;
$skartace=array();
$q=new DB_POSTA;
$a=new DB_POSTA;
$q->query($sql);
while ($q->Next_Record())
{
  $skartace[]=$q->Record['POSTA_ID'];
} 
$skartace=array_unique($skartace);

$sql="select spis_vyrizen from posta where id=".$skartace[0];
//echo $sql;
$q->query($sql); $q->Next_Record();


if (strlen($q->Record['SPIS_VYRIZEN'])<2) 
{
  echo "<br/><br/><span class='caption'>Chyba:  Dané čj. není uzavřeno!!!</span><br/>";

}
else
{
  $sql="select spisovna_id from posta_spisovna_zapujcky where id=".$id;
  //echo $sql;
  $q->query($sql); $q->Next_Record();
  $spisovna_id=$q->Record['SPISOVNA_ID'];
  if ($spisovna_id<1) $spisovna_id=1;
}

//print_r($skartace);

//while (list($key,$val)=each($skartace))
{
  
  $sqla='select * from posta where id in ('.implode(',',$skartace).')';
//    echo $sqla;
  $a->query($sqla);
  $a->Next_Record();
  $id=$a->Record['ID'];
  $cs1=$a->Record['CISLO_SPISU1'];
  $cs2=$a->Record['CISLO_SPISU2'];
  $skartace[]=$a->Record['ID'];
  $skartace_id=$a->Record['SKARTACE'];
  $skar_pole=Skartace_Pole($skartace_id);
//    print_r($skar_pole);
  $dokument_id=$a->Record['ID'];
  $vec=$a->Record['VEC'];
  $pocet_listu_celkem=$a->Record['POCET_LISTU'];
  $pocet_priloh = $a->Record["POCET_PRILOH"];
  $druh_priloh = $a->Record["DRUH_PRILOH"];

  $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;

  $sql='select listu from posta_spisobal where posta_id='.$a->Record['ID'];
//    echo $sql;
  $q->query($sql); $q->Next_Record();
  $pocet=$q->Record['LISTU']; if (!$pocet) $pocet==0; 
  if ($pocet>0) $pocet_listu_celkem=$pocet_listu_celkem+$pocet; //pricteme spis obal a prehled
  
  $datum_uzavreni=explode("-",$a->Record['SPIS_VYRIZEN']);
  $rok_uzavreni=$datum_uzavreni[0];
  $rok_skartace=$rok_uzavreni+$skar_pole[doba]+1;

  while ($a->Next_Record()) 
  {
    $skartace[]=$a->Record['ID'];
    $pocet_listu = $a->Record["POCET_LISTU"];
    $pocet_priloh = $a->Record["POCET_PRILOH"];
    $druh_priloh = $a->Record["DRUH_PRILOH"];
//      if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D' || $a->Record['ODES_TYP']=='X') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci
    if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci

    $pocet_listu_celkem=$pocet_listu_celkem+$pocet_listu;
    $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;

    
    $sql='select listu from posta_spisobal where posta_id='.$a->Record['ID'];
//      echo $sql;
    $q->query($sql); $q->Next_Record();
    $pocet=$q->Record['LISTU']; if (!$pocet) $pocet==0; 
    if ($pocet>0) $pocet_listu_celkem=$pocet_listu_celkem+$pocet; //pricteme spis obal a prehled
  }


//tady pricist pripadne prebal
  $prilohy="";
  while (list($key,$val)=each($pocet_priloh_celkem)) if ($val>0) $prilohy.="$key: $val<br/>";
  //echo "$celkem x $pocitadlo - ";
  if ($pricist_listy && $pocitadlo==$celkem) 
  {
    $pocet_listu_celkem=$pocet_listu_celkem+$pricist_listy; //echo "Pricitam";
  }
}
//Die('Pocet listu je '.$pocet_listu_celkem);


if ($skutecne_vratit) 
{ 
  while (list($key,$val)=each($skartace))
  {
    if ($val>0)
    {
      $sql="update posta SET status=-3,spisovna_id=$spisovna_id,last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$val;
      $q->query($sql);
      //echo $sql;
    }
  }
  $sql="update posta_spisovna_zapujcky set vraceno='".Date('Y-m-d')."',vraceno_komu=$id_user where id=".$zapujcka_id;
  $q->query($sql);
  $sql="update posta_spisovna set listu='".$pocet_listu_celkem."',prilohy='".$prilohy."',last_date='".Date('Y-m-d')."' where cislo_spisu1=".$cs1." and cislo_spisu2=".$cs2;
  $q->query($sql);
  //Die();
  
  echo "<br/><br/><span class='caption'>Hotovo, dokumenty byly vráceny zpět do spisovny</span><br/>";

echo "
<input type='button' onclick='document.location.href=\"brow.php\";' value='Vrátit se' class='button btn'>";
}
else
{
  echo "<h1>Bude vráceno celkem listů: ".$pocet_listu_celkem."</h1>";
echo "
<input type='button' onclick='document.location.href=\"vratit.php?id=$zapujcka_id&skutecne_vratit=1\";' value='Skutečně vrátit' class='button btn'>";
}
include_once(FileUp2("html_footer.inc")); 

