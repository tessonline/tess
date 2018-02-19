<?php

Function ShowOdkaz($typ,$id)
{
  if ($typ==1) 
  {
    $href="http://monumnet.npu.cz/pamfond/list.php?IdReg=".$id;
    $url="<a href='".$href."' target='okno_$typ'>MonumNet</a>";
  }
  if ($typ==2) 
  {
    global $img;
    if (!$img) $img=FileUp2('images/globe.gif');
    //$href="http://gis.up.npu.cz/tms/npu_gmaps/index.php?Values=".$id."&Theme=kpz&Field=IDOB_PG&Command=SelByFld&MinScale=5000&Zoom=ToExtent&client_lang=cz_win&strange_opener=1";
    $href="http://gis.up.npu.cz/tms/npu_uz/index.php?client_type=map_resize&Project=TMS_NPU_UZIDENT&interface=tmv&Values=".$id."&Theme=pagis&Field=IDREG&Command=SelByFld&MinScale=2000&Zoom=ToExtent&client_lang=cz_win";
    $url="<a href='".$href."' target='okno_$typ'><img src='".$img."' border=0></a>";
//http://gis.up.npu.cz/tms/npu_gmaps/#c=1801135%252C6309278&z=15&l=gmStr&p=pam&
  }
  return $url;
}
/*
Function DatumArchivace($datum,$odhad)
{
  $q=new DB_POSTA;
  $res=$q->dbdate2str($datum);
  if ($odhad==1) 
  {
    global $img_alert;
    if (!$img_alert) $img_alert=FileUp2('images/alert.gif');
    $res.="<img src='".$img_alert."' border=0 title='odhad'>";
  }
  return $res;
}
*/
//    array( field=>"ODESL_PRIJMENI...'&nbsp;'...ODESL_JMENO...' '...ODESL_ICO...' ,'...ODESL_ULICE...'&nbsp;'...ODESL_CP...','...ODESL_PSC...'&nbsp;'...ODESL_POSTA", label=>"Adresa"),
$TABLE_CONFIG = array(
//  "callback"=> "ChangeClassBarva",
  "schema" => array( 
    array( field=>"EXT_ID", label=>"externí ID","width"=>"10%"),
    array( field=>"NAZEV_SPISU", label=>"Jmenný název","width"=>"30%"),
    array( field=>"KATASTR", label=>"Katastr","width"=>"20%"),
//    array( field=>"DATUMARCHIVACE(DATUM_ARCHIVACE,DATUM_ARCHIVACE_ODHAD)", label=>"Datum archivace","width"=>"20%"),
    array( field=>"ShowOdkaz('1',EXT_ID)", label=>"systém","class"=>"image"),
    array( field=>"ShowOdkaz('2',EXT_ID)", label=>"mapa","class"=>"image"),
    
  )
 );
//}

?>
