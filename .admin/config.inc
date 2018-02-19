<?php
include_once(FileUp2(".admin/db/db_default.inc"));

include_once(FileUp2('.admin/security_obj.inc'));
require_once(FileUp2('.admin/classes/EedTools.inc'));
include_once(FileUp2('.admin/classes/EedCeskaPosta.inc'));
include_once(FileUp2('.admin/classes/EedLog.inc'));
include_once(FileUp2('.admin/classes/EedTransakce.inc'));

mb_internal_encoding("UTF-8");


$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();

if ($USER_INFO["NAMEDB"])
  $GLOBALS["POSTA_SECURITY"]=new Security_Obj($USER_INFO["NAMEDB"]);
else
  $GLOBALS["POSTA_SECURITY"]=$GLOBALS["TMAPY_SECURITY"];


//require(FileUp2('ost/posta/.config/config_posta.inc'));
//$GLOBALS["POSTA_SECURITY"]=$GLOBALS["TMAPY_SECURITY"];

if (!$USER_INFO["NAMEDB"])
  require(FileUp2('ost/posta/.config/config_posta.inc'));
else
{
  $config_file='ost/posta/.config_'.$USER_INFO["NAMEDB"].'/config_posta.inc';
  //echo $config_file;
  require(FileUp2($config_file));

}




if (!(function_exists('LoadClass'))) {
  function LoadClass($class, $add=array()) {
    if (class_exists($class)) $ret = new $class($add);
    else {
      require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/'.$class.'.inc');
      $ret = new $class($add);
      
    }
    return $ret;
  }
}

if (!(function_exists('LoadSingleton'))) {
  function LoadSingleton($class, $add=array()) {
    if (!class_exists($class)) {
      require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/'.$class.'.inc');
    } 
    switch ($class) {
      case 'EedSpisovna':
        $ret = EedSpisovna::getInstance($add);
        break;
      case 'EedDokument':
        $ret = EedDokument::getInstance($add);
        break;
      case 'EedSpisovnaSimple':
        $ret = EedSpisovnaSimple::getInstance($add);
        break;
      default:
        $ret = false;
    } 
    return $ret;
  }
}
