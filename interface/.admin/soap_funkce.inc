<?php
//pomocne funkce
$button_back = "<input type=\"button\" value=\"".$GLOBALS["RESOURCE_STRING"]["button_back"]."\" onClick=\"javascript:window.history.go(-1)\" class=\"button\">\n";
$button_close = "<input type=\"button\" value=\"".$GLOBALS["RESOURCE_STRING"]["button_close"]."\" onClick=\"javascript:window.close();\" class=\"button\">\n";
$img_odchozi="<img src=\"".FileUp2('images/odchozi.gif')."\" alt=\"Odchozí dokument\">";
$img_prichozi="<img src=\"".FileUp2('images/prichozi.gif')."\" alt=\"Příchozí dokument\">";

$typ_odesl_unispis = array('Fyzicka', 'Pravnicka', 'OVM', 'PFO','OVM_EXEKUT','OVM_NOTAR');
$typ_odesl_tess = array('O', 'P', 'U', 'F', 'E', 'N');

$typ_odesl_tess2unispis = array(
  'O' => 'FO',
  'P' => 'PO',
  'U' => 'OVM',
  'F' => 'PFO',
  'E' => 'OVM_EXEKUT',
  'N' => 'OVM_NOTAR',
);


$typ_odesl_unispis2tess = array(
  'Fyzicka' => 'O',
  'Pravnicka' => 'P',
  'OVM' => 'U',
  'PFO' => 'F',
  'OVM_EXEKUT' => 'E',
  'OVM_NOTAR' => 'N',
);

if (!function_exists('ConvertDatumToString')) {
  function ConvertDatumToString($val) {
    if ($val) {
      $d1 = explode("T",$val);
      $dt = explode('+',$d1[1]);
      $d2 = explode("-",$d1[0]);
      $time = explode(':',$dt[0]);

      $timeS = explode('.', $time[2]);
      $retval = $d2[0]."-".$d2[1]."-".$d2[2]." ".$time[0].":".$time[1].":".$timeS[0];
    }
    return $retval;
  }
}

if (!function_exists('ConvertDatumToXML')) {
  function ConvertDatumToXML($val, $time = true) {
    if ($val) {

      $d1 = explode(" ",$val);
      $dd = explode("-",$d1[0]);
      if (strlen($dd[1])==1) $dd[1]="0".$dd[1];
      if (strlen($dd[0])==1) $dd[0]="0".$dd[0];
      if ($time) $retval = $dd[0]."-".$dd[1]."-".$dd[2]."T".$d1[1].":00";
      else $retval = $dd[0]."-".$dd[1]."-".$dd[2];
    }
    return $retval;
  }
}

if (!function_exists('TxtEncoding4Soap')) {
  function TxtEncoding4Soap($txt){
    $txt = str_replace('&', '&amp;', $txt);
    return $txt;

  	$from = $GLOBALS["POSTA_SECURITY"]->Security->configuration['charset'];
  //  return iconv($from, 'UTF-8', $txt);
    return iconv('ISO-8859-2', 'UTF-8', $txt);
  }
}

if (!function_exists('TxtEncodingFromSoap')) {
  function TxtEncodingFromSoap($txt){
    return $txt;
  //  $to = $GLOBALS["POSTA_SECURITY"]->Security->configuration['charset'];
  //  return iconv('UTF-8','ISO-8859-2//TRANSLIT' , $txt);
  }
}

if (!function_exists('VratVysledek')) {
  Function VratVysledek($pole)
  {
     if ($pole['RESULT']=='ERROR')
     return new soap_fault('ERROR', '', $pole['DESCRIPTION'], $ns);
     else
     return $pole;
  }
}

if (!function_exists('VratChybu')) {
  Function VratChybu($session_id,$app,$text)
  {
    if (!$software_id=JeNalogovan($session_id)) $software_id='SOAP';
    $text='('.$app.') - '.$text;
    WriteLog($software_id,$text,$session_id,1);
    $text=TxtEncoding4Soap($text);
    return new soap_fault('ERROR', '', $text, $ns);
  }
}

if (!function_exists('VratChybuBP')) {
  Function VratChybuBP($session_id,$app,$text)
  {
    if (!$software_id=JeNalogovan($session_id)) $software_id='SOAP';
    $text='('.$app.') - '.$text;
    WriteLog($software_id,$text,$session_id,1);
    $text=TxtEncoding4Soap($text);
    return new soapfault('ERROR',$text);
  }
}

if (!function_exists('WriteLog')) {
  Function WriteLog($sw,$text,$session_id='',$chyba=0)
  {
    static $q;
    if (!$q) $q=new DB_POSTA;
    $datum=Date('d.m.Y H:i:s');
    $sql = "INSERT INTO posta_interface_log (datum,sw,popis,session_id,chyba) VALUES ('".$datum."','".$sw."','".substr($text,0,2550)."','$session_id',$chyba)";
    $q->query($sql);
  }
}

if (!function_exists('WriteHTTPlog')) {
  Function WriteHTTPlog($hash,$request,$response, $sw = '')
  {
    //if ($response<>'') echo $response;
    $request = str_replace("'","",$request);
    $response = str_replace("'","",$response);
    static $q;
    if (!$q) $q=new DB_POSTA;
    $sql = "select id from posta_interface_log where session_id like '".$hash."'";
    $q->query($sql);
    if ($q->Num_Rows()==0)
    {
      $sql = "INSERT INTO posta_interface_log (sw,session_id,request,response) VALUES ('".$sw."','".$hash."','".$request."','".$response."')";
  //echo $sql;
      $q->query($sql);
    }
    $sql = "update posta_interface_log set session_id=session_id ";
    //if ($request<>'')
      $sql.=", request='".($request)."'";
    //if ($response<>'')
      $sql.=", response='".($response)."'";
    //$sql.=" where session_id ='".$hash."'";
    $q->query($sql);
  }
}

if (!function_exists('VymazSessions')) {
  Function VymazSessions()
  {
    static $q;
    if (!$q) $q=new DB_POSTA;
    $timeoutseconds = 60*30;
    $timeout=$timestamp-$timeoutseconds;
    $sql = "DELETE FROM posta_interface_login WHERE cas<$timeout";
    $q->query($sql);
  }
}

if (!function_exists('JeNalogovan')) {
  Function JeNalogovan($session_id)
  {
    VymazSessions();
    static $q;
    if (!$q) $q=new DB_POSTA;
    $timeoutseconds = 60*30;
    $timeout=$timestamp-$timeoutseconds;
    $sql = "select * from posta_interface_login WHERE session_id like '".$session_id."'";
    $q->query($sql);
    $q->Next_Record();
    If (trim($q->Record["SW"])) return $q->Record["SW"]; else return false;
  }
}

if (!function_exists('GetSkartaceId')) {
  Function GetSkartaceId($id,$software)
  {
    //jdeme najit ID skartacniho kodu
    $sql_skartace="select id from cis_posta_skartace where text like '".$id." %'";
    $a=new DB_POSTA;
    $a->query($sql_skartace);
    $pocet=$a->Num_Rows();
    $a->Next_Record();
    If ($pocet==1) $skartace=$a->Record["ID"]; else $skartace=0;

    $text='(FCE) - Hledam spisznak k '.$id.' - nalezeno ID '.$skartace.'';
    if ($skartace==0)
      WriteLog($software,$text,$session_id,1);
    else
      WriteLog($software,$text,$session_id);
    return $skartace;

  }
}
