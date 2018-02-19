<?php


require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/upload_.inc"));
include_once(FileUp2("interface/.admin/upload_funkce.inc"));

$GLOBALS["RESOURCE_STRING"]["button_save"] = 'podepsat';

$soubory=array();
$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS['EDIT_ID']); 
$a=0;
while (list($key,$val)=each($upload_records))
{
  if (strpos($val[NAME],'.pdf') || strpos($val[NAME],'.PDF')) 
  { 
    $res='<a href=# onclick="return EditShowAtt(event,'.$val[ID].',\'ifrm_doc\');" target="ifrm_doc" class="pages">';
    $res.=$val[NAME]."</a>";
    $soubory[$a]['FILE_NAME']=$res;
    $soubory[$a]['FILE_ID']=$val[ID];
    if (!JePodepsanyDokument($val)) $soubory[$a]['FILE_NAME']="<img src=\"".FileUp2('images/alert.gif')."\" border=\"0\" title=\"PDF dokument není podepsán\">".$soubory[$a]['FILE_NAME'];
    $a++;
  }
  $GLOBALS['POCET_SOUBORU'] = $a;
}
$options=array();
if (count($soubory)==0) Die("Není žádný PDF dokument k podepsání");
if (count($soubory)==1) $checked='checked="checked"'; else $checked='';
while(list($key,$val)=each($soubory)) {
  $options[$val[FILE_NAME]]=$val[FILE_ID];
}

  $GLOBALS['SOUBOR_ID'] = $val['FILE_ID'];
    $FORM_CONFIG["schema"][] = array("elements"=>array(
             array(
                  "type"=>"radio",
                  "name"=>"SOUBOR_ID[]",
                  "value"=>$val[FILE_ID],
//                  "val"=>$val[FILE_ID],
      					  "options"=>$options,
      					  "add"=>$checked,
  )),
          "label"=>$val['FILE_NAME']);

  

if (strlen($GLOBALS[CONFIG_POSTA][PODPIS][podepsani_misto])>2) 
    $misto_podepsani=$GLOBALS[CONFIG_POSTA][PODPIS][podepsani_misto]; 
  else
    $misto_podepsani=$GLOBALS[CONFIG][URAD].' '.$GLOBALS[CONFIG][MESTO];

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"TIMESTAMP")),
                   "visible"=>HasRole('muze-razitko') && $GLOBALS[CONFIG][VKLADAT_TIMESTAMP],
                   "label"=>"Přidat časové razítko:");
   
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"VIDITELNY","value"=>$GLOBALS[CONFIG][VKLADAT_DEFAULTNE_VIDITELNY_PODPIS])),
                   "label"=>"Vložit viditelný podpis:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_pozice_viditelny_podpis", "name"=>"POZICE_VIDITELNY")),
                   "label"=>"Pozice podpisu:");


$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_duvod", "name"=>"DUVOD_PODEPSANI"),
                   array( "type"=>"text", "name"=>"MISTO_PODEPSANI","size"=>50,"value"=>$misto_podepsani)),
                   "format"=>"DUVOD_PODEPSANI...'&nbsp;&nbsp;&nbsp;v:&nbsp;'...MISTO_PODEPSANI",
                   "label"=>"Důvod podepsání:");
   
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"hidden", "name"=>"KONTAKTNI_INFO","value"=>UkazUsera($id_user,0,1),"frozen"=>true)),
                   "label"=>"");
$GLOBALS["POSTA_ID"]=$GLOBALS["EDIT_ID"]; $options=array();


//$FORM_CONFIG["schema"][] = array( "label"=>"a po podpisu předat k podepsání:");

include_once(GetAgendaPath('POSTA',false,false).'/services/spisovka/schvaleni/.admin/form_schema.inc');

/*$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"hidden", "name"=>"DOKUMENT_ID","value"=>$GLOBALS[EDIT_ID])),
                   "label"=>"Kontaktní informace:");

*/

echo "<script>
function EditShowAtt(e,id,target){
  var script = '/ost/posta/ug_file.php?upload_modul=table&_set_sess_cache_limit_=1';
  if (e.ctrlKey){
    script = script + '&edit&show_typ=1&EDIT_ID='+id;
    var param = 'height=430,width=580,'
    target = 'FileAtt';
  }else{
    script = script + '&FILE_ID='+id;
    var param = 'menubar,status,titlebar,toolbar,';
  }
  var d = new Date();
  newwindow = window.open(script+'&cacheid='+d.getTime(),target,param+'left=100,top=50,scrollbars,resizable');
  newwindow.focus();
  e.cancelBubble=true;
  return false;
}
</script>";
