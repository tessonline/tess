<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 

include_once(FileUp2(".admin/db/db_posta.inc"));

$CONFIG["DB_NAME"] = "DB_POSTA";

$CONFIG["ADRESA_KOD"] = "ADRESA_KOD";
$CONFIG["COBCE_KOD"] = "COBCE_KOD";
$CONFIG["ULICE_KOD"] = "ULICE_KOD";
$CONFIG["H_ULICE_KOD"] = "H_ULICE_KOD";

//$CONFIG["DEFAULT_OBEC"] = 569810;


$CONFIG["IDENT_PREFIX"] = "UIRADR_";
$CONFIG["TABLE_PREFIX"] = "ui_";

$CONFIG["DEFAULT_LANG"] = "cz_win";

$CONFIG["SHOW_LV_DETAIL"] = false;
$CONFIG["SHOW_REPORTS"] = false;
$CONFIG["SHOW_MAP"] = false;

//$htp = $HTTPS?"https://":"http://";
//$tms_server = $htp.$GLOBALS["HTTP_HOST"].'/tms';
/*
$CONFIG["MAP_TMS"] = "TMS_HKCP";
$CONFIG["TMS_SUFFIX"] = "_HKCP";
$CONFIG["TMS_CLIENT_TYPE"] = "mmhk";
$CONFIG["TMS_CLIENT_LANG"] = "cz_utf-8";
$CONFIG["TMS_SERVER"] = '/tms';
//$CONFIG["TMS_SERVER"] = $tms_server;
//$CONFIG["TMS_SERVER"] = "http://mm-hk.tmapserver.cz/tms";
$CONFIG["TMS_STRANGE_OPENER"] = false;

$CONFIG["MAP_THEME"] = "budovy";
$CONFIG["MAP_THEME2"] = "ulice2";
$CONFIG["MAP_THEME_FIELD"] = "OBJEKT_KOD";
$CONFIG["MAP_THEME_FIELD2"] = "ULICE_KOD";
$CONFIG["MAP_PIN_COLOR"] = "\$FF";
$CONFIG["MAP_CONDITION"] = 'Map_condition';
$CONFIG["MAP_ERROR_MSG_VAL"] = "Nebyl vybrán ádný objekt !";

$CONFIG["MAP_TMV_INDEX_LAYER"]="M:\geodata\mapy_stredmer\mapa_cp_10tis\budovy_b.shp";
*/
$GLOBALS["CONFIG"] = $CONFIG;

if (!function_exists(Map_condition)) {
  function Map_condition ($params){
    return true;
  }
}

?>
