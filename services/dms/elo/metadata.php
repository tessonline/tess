<?php
//chdir(GetAgendaPath('POSTA',0,0));
include_once(FileUp2('.config/config_posta.inc'));
include_once(FileUp2('.admin/oth_funkce.inc'));


if ($GLOBALS['RECORD_ID']) 
{
  $q=new DB_POSTA;
  $sql='select * from posta where id='.$GLOBALS['RECORD_ID'];
  $q->query($sql);
  $q->Next_Record();
  
  If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
  {
    $cj1=$q->Record["CISLO_JEDNACI1"];
    $cj2=$q->Record["CISLO_JEDNACI2"];
    $podcislo=-1;
    $cislo_jednaci=strip_tags(FormatCJednaci($q->Record["CISLO_JEDNACI1"],$q->Record["CISLO_JEDNACI2"],$q->Record["REFERENT"],$q->Record["ODBOR"]));
  }
  else
  {
    $cj1=$q->Record["CISLO_SPISU1"];
    $cj2=$q->Record["CISLO_SPISU2"];
    $podcislo=$q->Record['PODCISLO_SPISU'];
    $cislo_jednaci=strip_tags(FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],'',$q->Record["PODCISLO_SPISU"]));
  }
  $USER_INFO_LAST = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($q->Record['LAST_USER_ID'],false,true,1);
  if ($q->Record['REFERENT']>0)
  {
    $USER_INFO_PRAC = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($q->Record['REFERENT'],false,true,1);
    $prac = $USER_INFO_PRAC['LOGIN'];
  }
  else
    $prac=0;
  $USER_INFO_LAST['LOGIN'] = $USER_INFO_LAST['LOGIN']?$USER_INFO_LAST['LOGIN']:'anonymous';
  $data['file_id']=$file_dctm_id;
  $data['cj']=TxtEncoding4Soap($cislo_jednaci);
  $data['cev']=$q->Record['ID'];
  $data['last_user_login']=$USER_INFO_LAST['LOGIN'];
  $data['odbor']=UkazOdbor($q->Record[ODBOR]);
  $data['oddeleni']=UkazOdbor($q->Record[ODBOR]);
  $data['zpracovatel_login']=$prac?$prac:'';
  $data['poradove_cislo']=$cj1;
  $data['rok']=$cj2;
  $data['poradi']=$podcislo;
}
