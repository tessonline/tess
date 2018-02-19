<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2('.admin/upload_fce_.inc'));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/zaloz.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/dorucenka.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
//include_once(FileUp2('.admin/db/db_upload.inc'));
include_once(FileUp2("/interface/.admin/soap_funkce.inc"));
require_once(FileUp2("/interface/.admin/upload_funkce.inc"));
include(FileUp2(".admin/security_obj.inc"));
//$sql="update posta set spis_vyrizen=NULL,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID   where cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2."";

if (!HasRole('vypraveni-int-posta')) die('Přístup zamítnut.');


$q=new DB_POSTA;
$sql = "select * from posta_vnitrni_adresati";
$q->query($sql);
while ($q->Next_Record()) {
  

/*  $odesl_ulice=$odbor_x;
  $odesl_osoba=$referent_x;
  $odesl_odd=$oddeleni_x;*/
  
 /* $class = LoadClass('EedUser', 0);
  $odbor_id = EedTools::VratIdOdbor($xxx->Record["ODESL_ULICE"]);
  $unity = $class->VratNadrizeneUnity($odbor_id);
  $so = html_entity_decode(end($unity)*/
  $odesl_array = array(
    "odesl_odd" => "",
    "odesl_osoba" => $q->Record['ZPRACOVATEL'],     
    "odesl_ulice" => $q->Record['ORGANIZACNI_VYBOR'],
  );
  
    $id_puvodni = $GLOBALS[ID];
    $GLOBALS['noveID'] = ZalozNovyDokument($GLOBALS[ID],1,1,$odesl_array);
    
    EedTools::MaPristupKDokumentu($id_puvodni, 'vypraveni interni posty');
    
    $datum_prijeti=date('d.m.Y H:i:s');
    
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $id_user=$USER_INFO["ID"];
    $LAST_USER_ID=$id_user;
    $OWNER_ID=$id_user;
    $LAST_TIME=Date('H:m:i');
    $LAST_DATE=Date('Y-m-d');
    
    $sql="update posta set datum_vypraveni='$datum_prijeti',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$id_puvodni;
    //$q=new DB_POSTA;
    $q->query($sql);
    NastavStatus($id_puvodni, $id_user);
    
    reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
    foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
      if ($plug['enabled']){
        $file = FileUp2('plugins/'.$plug['dir'].'/services/spisovka/odesli_end.php');
    		if (File_Exists($file)) include($file);
      }
    }
    
    //pokud neni tento parametr, zalozime dorucenku ihned...
    if (!$GLOBALS['CONFIG']['INTERNI_DORUCENKA_AZ_PO_PREVZETI'])
      VytvorDorucenku($id_puvodni);
}

?>
<script language="JavaScript" type="text/javascript">
<!--
  window.parent.location.reload();
  window.close();
//-->
</script>

