<?php
include_once(FileUp2("security/.admin/security_func.inc"));

//onma, 1.6.2004, funckce pro evidenci pisemnosti.....
Function VratSuperOdbor( $odbor=0 ) {
   $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
   $prac = $USER_INFO["PRACOVISTE"];
   if (!$prac) $prac = 0;

  return $prac;
}

Function GetGroupsInSuperOdbor()
{
  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo(); 
  $odbor = $USER_INFO["GROUP_ID"];
  $id=$odbor;
  //$last_odbor=0;
  while ($id>0) {
    $a=$id;
//    echo "ID je $id ";Flush();
    $last_odbor[$id]=$id;
     if (!$id=GetParentGroup($id)) break;
  }
  //echo "nad odbor je".$last_odbor;
  return $last_odbor;
}

function getSelectDataEed($select) {
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


Function GetAllGroupsInSuperOdbor($id)
{
  //if ($id<1)
  //  $id=VratSuperOdbor();
  $sql='select id from security_group where parent_group_id='.$id;
//  echo $sql."<br/>"; Flush();
  $q=new DB_POSTA;
  $q->query($sql);
  while ($q->Next_Record()) {
    $id=$q->Record['ID'];
//    echo "ID je $id ";Flush();
    $last_odbor[$id]=$id;
    $last_odbor2=GetAllGroupsInSuperOdbor($id);
     if (count($last_odbor2)>0)
       $last_odbor=array_merge($last_odbor,$last_odbor2);
     if (!$id=GetParentGroup($id)) break;
     //$last_odbor=
  }
  //echo "nad odbor je".$last_odbor;
  return $last_odbor;
}


Function VratSNazevSkupiny($id)
{
  if ($id>0)
  {
    $q=new DB_POSTA;
    $q->query('SELECT name from security_group where id='.$id);
    $q->Next_Record();
    return $q->Record['NAME'];
  }
  else return 0;
}

Function UkazOdbor($id,$zkratka=false,$altnazev=false,$vratodbor=false)
{
  $res="&nbsp;";
  If ($id=='') {$id=0;}


  $q=new DB_POSTA;
  if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id])) {
   	$id_odboru=$GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id]["ID_ODBOR"];
    $zkrac_odbor=$GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id]["ZKRATKA"];
    $alt_nazev=$GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id]["ALTNAZEV"];
  }
  else {
  $sql = 'select * from cis_posta_odbory where id='.$id;
  $q->query($sql);
	$q->Next_Record();
	$id_odboru=$q->Record["ID_ODBOR"];
  $zkrac_odbor=$q->Record["ZKRATKA"];
  $alt_nazev=$q->Record["ALTNAZEV"];
  }

  If ($id_odboru=="") {$id_odboru=0;}

  if ($GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$id_odboru]) {
  	$odbor=$GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$id_odboru]["NAME"];
  }
  else {
  $sql = 'select * from security_group where id='.$id_odboru;
  $q->query($sql);
	$q->Next_Record();
    $GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$id_odboru] = $q->Record;
	$odbor=$q->Record["NAME"];
  }
  $res=$odbor;
	
	If ($zkratka) $res=$zkrac_odbor; 
	If ($altnazev && $alt_nazev) $res=$alt_nazev; 
	If ($vratodbor) $res=$id_odboru; 

//  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($id,false,true,1); 
//  $odbor = $USER_INFO["ODBOR"]; 
	
  return $res;
}
/*
Function UkazOdbor($id)
{
  $res="&nbsp;";
  If ($id=='') {$id=0;}
  $q=new DB_DEFAULT;
  $sql = 'select * from cis_posta_odbory where id='.$id;
  $q->query($sql);
	$q->Next_Record();
	$id_odboru=$q->Record["ID_ODBOR"];
  If ($id_odboru=="") {$id_odboru=0;}
  $sql = 'select * from security_group where id='.$id_odboru;
  $q->query($sql);
	$q->Next_Record();
	$odbor=$q->Record["NAME"];

//  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($id,false,true,1); 
//  $odbor = $USER_INFO["ODBOR"]; 
	
	$res=$odbor;
  return $res;
}
*/

Function UkazOtocUsera($id) {
  return UkazUsera($id,false,false,true);
}

Function UkazUsera($id,$zkratka=false,$tituly=false,$otoc=false)
{
  If (($id=="")or($id==0)) {$res="  ";}
	else
	{

    //$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($id,true,true,1);
    if (isset($GLOBALS['POSTA_OPT']['SECURITY_USER'][$id])) {
      $USER_INFO=$GLOBALS['POSTA_OPT']['SECURITY_USER'][$id];

    }
    else {
    $q=new DB_DEFAULT;
    $sql='select login_name as login, short as short, lname as lname, fname as fname, title_1 as title1, title_2 as title2, email as email, phone as phone, group_id as group_id from security_user where id='.$id;
    $q->query($sql);
    $q->Next_Record();
      $GLOBALS['POSTA_OPT']['SECURITY_USER'][$id] = $q->Record;
    $USER_INFO=$q->Record;
    }
    If ($zkratka)
      If ($USER_INFO["SHORT"]<>'') $REFERENT=$USER_INFO["SHORT"]; else $REFERENT = mb_strtoupper(mb_substr($USER_INFO["LNAME"],0,2, "utf-8"), "utf-8");
    else 
      $REFERENT = ($otoc) ? $USER_INFO["LNAME"].' '.$USER_INFO["FNAME"] : $USER_INFO["FNAME"].' '.$USER_INFO["LNAME"];
  If ($tituly && $USER_INFO["TITLE1"]) $REFERENT = $USER_INFO["TITLE1"]." ".$REFERENT;
  If ($tituly && $USER_INFO["TITLE2"]) $REFERENT = $REFERENT." ".$USER_INFO["TITLE2"];
  	$res=$REFERENT;
	}
//	$res=$id;
  return $res;
}

Function NajdiVedouciho($id)
{
  $odbor=UkazOdbor($id,0,0,1);
  $sql = 'select * from security_user where vedouci=1 and group_id='.$odbor;
  $q=new DB_DEFAULT;
  $q->query($sql);
  If ($q->Num_Rows()>0) {$q->Next_Record(); return $q->Record["ID"];}
  else return '';
}


function vratFiltrovaneAgendy($id_superodbor) {
  $q=new DB_POSTA;
  $res = array();
  $sql = '(SELECT id,nazev,poradi FROM cis_posta_agenda WHERE id_superodbor IS NULL)
        UNION (select a.id,a.nazev,a.poradi+1000 FROM cis_posta_agenda a where a.id_superodbor='.$id_superodbor.')';
  $q->query($sql);
  while ($q->next_record())
  {
    $res[$q->Record["ID"]] = $q->Record["NAZEV"];
    //$res[]['label'] = $q->Record["nazev"];
  }
  return $res;
}

Function VratOdbor($odbor_zadal=0)
{
  $w=new DB_POSTA;
  if (!$odbor_zadal) {
    $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo(); 
    if (!$USER_INFO["GROUP_ID"]) return -1;
    $odbor = $USER_INFO["GROUP_ID"];
    $id = $odbor;
    $last_odbor = 0;
    while ($odbor_zadal==0) {
      $a=$id;
      $last_odbor=$id;
      if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$last_odbor])) $odbor_zadal = $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$last_odbor];
      else {
      $w->query ("SELECT id from cis_posta_odbory where id_odbor=".$last_odbor);
//    	echo "SELECT id from cis_posta_odbory where id_odbor=".$last_odbor." xxx ";
      $w->Next_Record();
      $odbor_zadal=$w->Record['ID'];
        $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$last_odbor] = $odbor_zadal;
      }
//      echo $odbor_zadal."<br/>";
      if ($odbor_zadal>0) {$odbor=$last_odbor; break;}
       if (!$id=GetParentGroup($id)) break;
    }
    if (HasRole('zpracovat-odbor')) {
      $id = GetParentGroup($odbor);
      if ($id>0) $odbor = $id;
    }
    
  }
  else
    $odbor=$odbor_zadal;




  if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$odbor])) return $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$odbor];
  
  $w->query ("SELECT id from cis_posta_odbory where id_odbor=".$odbor);
  $w->Next_Record();
  $odbor2=$w->Record["ID"];
  if (!$odbor2) $odbor2 = 0;
  $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$odbor] = $odbor2;

  return $odbor2;
}
/*
Function VratOdbor($odbor_zadal=0)
{
  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo(); 
  $odbor = $USER_INFO["GROUP_ID"];
  $odbor2 = $USER_INFO["GROUP"];
  If ($odbor_zadal<>0) $odbor=$odbor_zadal;
  $w=new DB_POSTA;
  $w->query ("SELECT id from cis_posta_odbory where id_odbor=".$odbor);
	//echo "SELECT id from cis_posta_odbory where id_odbor=".$odbor;
  $w->Next_Record();
  $odbor=$w->Record["ID"];
  return $odbor;
}
*/
Function PrevedCPnaID($cislo,$oddelovac="") {
  include_once ($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
  require_once (FileUp2('.admin/el/of_select_.inc'));
  if (strpos($cislo, '-')) $oddelovac = '-';
  if (strpos($cislo, '/')) $oddelovac = '/';
  $cislo = str_replace('*', '%', $cislo);
  $cislo = str_replace($GLOBALS['CONFIG']['ID_PREFIX'], '', $cislo);

  if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) {
    $prefix_arr = getSelectDataEed(new of_select_superodbor_prefix(array()));
    foreach($prefix_arr as $prefix) {
      $cislo = str_replace($prefix, '', $cislo);
    }
  }

  if ($oddelovac) list($cp1,$cp2,$cp3)=explode($oddelovac,$cislo);
  If ($cp1 && $cp2 && $cp3)
  {
    $cp1=(int)$cp1; $cp2=(int)$cp2; $cp3=(int)$cp3; 
    $sql='select id from posta where superodbor='.$cp1.' and ev_cislo='.$cp2.' and rok='.$cp3.'';
    static $xxx;
    If (!$xxx) $xxx=new DB_POSTA;
    $xxx->query($sql);
    //$xxx->Next_Record();
    If ($xxx->Num_Rows()==1) {$xxx->Next_Record(); $res=$xxx->Record["ID"];}
    else
      $res=0;
  }

  if (!$cp1 && $cislo) {
    $sql="select dokument_id from posta_carovekody where ck like '".$cislo."'";
    static $xxx;
    If (!$xxx) $xxx=new DB_POSTA;
    $xxx->query($sql);
    //$xxx->Next_Record();
    If ($xxx->Num_Rows()==1) {$xxx->Next_Record(); $res=$xxx->Record["DOKUMENT_ID"]; return $res;}
    else
      $res=0;
  }

  if (!$cp1 && $cislo) {
    $sql="select posta_id from posta_cis_ceskaposta_ck where ck like '".$cislo."'";
    static $xxx;
    If (!$xxx) $xxx=new DB_POSTA;
    $xxx->query($sql);
    //$xxx->Next_Record();
    If ($xxx->Num_Rows()==1) {$xxx->Next_Record(); $res=$xxx->Record["POSTA_ID"]; return $res;}
    else
      $res=0;
  }

  If ($cp1 && $cp2 && !$cp3) {
    $sql='select id from posta where ev_cislo='.$cp1.' and rok='.$cp2.'';
    static $xxx;
    If (!$xxx) $xxx=new DB_POSTA;
    $xxx->query($sql);
    //$xxx->Next_Record();
    If ($xxx->Num_Rows()>0) {$xxx->Next_Record(); $res=$xxx->Record["ID"];}
    else
      $res=0;
  }

  if (!$cp1 && $cislo) {
    if (strpos($cislo, "%")===false)
    $cislo = (int) $cislo;
    //$sql="select id from posta where id ='".$cislo."'";
    $sql="select id from posta where id::varchar like '".$cislo."'";
    static $xxx;
    If (!$xxx) $xxx=new DB_POSTA;
    $xxx->query($sql);
    //$xxx->Next_Record();
    If ($xxx->Num_Rows()==1) {$xxx->Next_Record(); $res=$xxx->Record["ID"];}
    else
    if ($xxx->Num_Rows()>1) {
      $res = array();
      while ($xxx->Next_Record()) {
         $res[]=$xxx->Record["ID"];
        
      }
    }
    else
      $res=0;

  }
  return $res;
}

Function VratOddeleni($odbor=0)
{
  //fce vrati vsechna oddeleni z daneho odboru, nebo ze vsech odboru (pokud neni zadana hodnota)
  static $xxx;
  $res=array();
  If (!$xxx) $xxx=new DB_POSTA;

  if ($odbor>0) 
    $sql="SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".UkazOdbor($odbor,0,0,1)." ORDER BY g.name";
  else
    $sql="SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id IN (SELECT id from security_group WHERE parent_group_id=".VratSuperOdbor().") ORDER BY g.name";

  $xxx->query($sql);
	while ($xxx->next_record()) 
  {
    $id=$xxx->Record["ID"];
    $res[$id]=$xxx->Record["NAME"];
  }
  return $res;
}

Function VratPracovniky($odbor=0,$podrizene=0,$group_id=0)
{
  //fce vrati vsechny pracovniky z daneho odboru/oddeleni, nebo vsechny (pokud neni zadana hodnota)
  static $xxx;
  $res=array();
  If (!$xxx) $xxx=new DB_POSTA;
/*
  $odbor2=UkazOdbor($odbor,0,0,1);
   //u odboru dopocitame pracovniky z oddeleni
   $podrazene_odbory=VratMultiOdbory($odbor2);
   $odbor2=array_flip($podrazene_odbory);
   $odbor_celkem=array_merge(array($odbor),$odbor2);

    while (list($key,$val)=each($odbor_celkem))
    {
      $odbor_hledej=UkazOdbor($val,0,0,1);
      $where.=" OR g.parent_group_id=".$odbor_hledej." or g.id=".$odbor_hledej;
    }
*/
      if ($group_id>0) 
        $odbor=$group_id;
      else
      {
        $odbor2=UkazOdbor($odbor,0,0,1);
        $odbor=$odbor2;
      }
       //u odboru dopocitame pracovniky z oddeleni
       $podrazene_odbory=VratMultiOdbory($odbor);
       $odbor2=array_flip($podrazene_odbory);
       
       $odbor_celkem=array_merge(array($odbor),$odbor2);

        while (list($key,$val)=each($odbor_celkem))
        {
//          $odbor_hledej=UkazOdbor($val,0,0,1);
          $odbor_hledej=$val;
          $where.=" OR g.parent_group_id=".$odbor_hledej." or g.id=".$odbor_hledej;
        }

/*
 If ((GetParentGroup($odbor2))<1)
   $where=" OR g.parent_group_id=".$odbor2." or g.id=".$odbor2;
*/      
  if ($odbor>0) 
    $sql="SELECT u.id,u.lname || ' ' || u.fname as jmeno FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id where (1=0 $where) and active ORDER BY lname";
  else
    $sql="SELECT u.id,u.lname || ' ' || u.fname as jmeno FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id  and active  ORDER BY lname";
  $xxx->query($sql);
	while ($xxx->next_record()) {
    $id=$xxx->Record["ID"];
    if (strlen($xxx->Record['JMENO'])>2) $res[$id]=$xxx->Record["JMENO"];
  }
  return $res;
}

function vratAgenduDokumentu($typ_posty) {
  $agenda = '';
  if ($typ_posty) {
  $sql = 'select id_agendy from cis_posta_typ where id ='.$typ_posty;
  static $xxx;
  if (!$xxx) $xxx=new DB_POSTA;
  $xxx->query($sql);
  $xxx->next_record(); 
    $agenda=$xxx->Record["ID_AGENDY"];
  }
  return $agenda;
}


Function VratTypDokumentu($agenda=0, $smer_dokumentu = null)
{
  
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $odbor=array();
  $spisuzel=array();
  if ($GLOBALS['REFERENT'])
    $GLOBALS['rerefent']=$GLOBALS['REFERENT'];
    else
      $GLOBALS["referent"]=$USER_INFO["ID"]; //referent malymi pismeny, aby pak nebyl vybran ve vyberu
  $pole=OdborPrac($GLOBALS['referent']);
  $odbor=UkazOdbor($pole['odbor'],0,0,1);
  $nadrazene_odbory=VratNadrizeneOdbory($odbor);
  $odbor=array_flip($nadrazene_odbory);
  
  $superodbor = $pole['so'];

  if (count($odbor)>0) {
    foreach ($odbor as $odbor_temp) {
      $spisuzel[] = VratOdbor($odbor_temp);
    }
  } 
  
  $left_join_workflow = "left join posta_workflow cpw on cpw.id_typ = a.id  ";
  $omezeni_workflow = "";
  if ($smer_dokumentu=="P")
  {
    $omezeni_workflow = " and (cpw.dokument = 'P' or cpw.dokument is null)";
    
  }
  elseif ($smer_dokumentu=="O")
  {
    $omezeni_workflow = " and (cpw.dokument = 'O' or cpw.dokument is null)";
  } else {
    $left_join_workflow = "";
  }
  
  $id_check_ids = is_array($GLOBALS['TYP_POSTY']) ? implode(",",$GLOBALS['TYP_POSTY']) : $GLOBALS['TYP_POSTY'];
    
  $id_check = (($GLOBALS['TYP_POSTY']!="")&&($GLOBALS['TYP_POSTY']!="undefined"))? " or (a.id in (".$id_check_ids.") and a.id_agendy=".$agenda.")": "";
  //$neaktivni = " and (neaktivni is false ".$id_check.") and (neaktivni_agenda is false ".$id_check.")";
  $neaktivni = " and (a.neaktivni is false) and (a.neaktivni_agenda is false) ";
  
  
  
  //fce vrati vsechny typy dokumentu z dane agendy
  static $xxx;
  $res=array();
  If (!$xxx) $xxx=new DB_POSTA;
  
  //cis_posta_typ cpt left join cis_posta_agenda cpa on cpa.id = cpt.id_agendy where cpt.id_agendy = 48;

  $orsuperodbor = "";
  if (HasRole('lokalni-spravce')||HasRole('editace_vse_pracoviste')) {
    $orsuperodbor = " OR (cpa.id_superodbor=".$pole['so'].") ";
  }
  
    if ($agenda>0) {
      //if (HasRole('spravce')||HasRole('lokalni-spravce')||HasRole('editace_vse_pracoviste')) {
      if (HasRole('spravce')) {
        $sql = "SELECT a.id,a.nazev FROM cis_posta_typ a ".$left_join_workflow." WHERE ((a.id_agendy=".$agenda.$neaktivni.") ".$id_check.") ".$omezeni_workflow." ORDER BY a.poradi asc,a.id asc";
     }
     else {
        if (count($spisuzel) > 0) {
          $sql = "SELECT * FROM (SELECT a.id,a.nazev, a.poradi FROM cis_posta_typ a left join cis_posta_typ_odbor b on a.id = b.id_posta_typ left join cis_posta_agenda cpa on cpa.id=a.id_agendy ".$left_join_workflow."   where ((a.id_agendy =".$agenda.$neaktivni." and ((b.id_odbor in (".implode(',',$spisuzel).") or b.id_odbor is null) ".$orsuperodbor.")) ".$id_check.") ".$omezeni_workflow.")  t ORDER BY poradi asc,id asc";
        //  $sql = "SELECT a.id,a.nazev FROM cis_posta_typ a where (id_agendy =".$agenda.$neaktivni." and (a.odbor in (".implode(',',$spisuzel).") or a.odbor is null)) ".$id_check."  ORDER BY a.poradi asc,a.id asc";
        }
        else
          $sql="SELECT a.id, a.nazev FROM cis_posta_typ a ".$left_join_workflow." WHERE ((a.id_agendy=".$agenda.$neaktivni.") ".$id_check.") ".$omezeni_workflow."  ORDER BY PORADI asc";
      }
    }
    else
      $sql="SELECT  a.id, a.nazev, a.poradi FROM cis_posta_typ a ".$left_join_workflow." WHERE ((a.id_agendy IS NOT NULL ".$neaktivni.")  ".$id_check.") ".$omezeni_workflow."  ORDER BY PORADI asc";
    var_dump($sql);
    $sql = "SELECT distinct(id),nazev FROM (".$sql.") tt"; 
   // print_r($sql);
    $xxx->query($sql);
    while ($xxx->next_record()) {
      $id=$xxx->Record["ID"];
      if (strlen($xxx->Record['NAZEV'])>2) $res[$id]=$xxx->Record["NAZEV"];
    }
    return $res;
}

Function OdborPrac($id)
{
  include_once(FileUp2('.admin/el/of_odbory_.inc'));

  $user = LoadClass('EedUser', $id);
  //z ID pracovnika vrati odbor a oddeleni
  //$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($user->login);

//  $id_odbor=$USER_INFO["GROUP_ID"];
  $id_odbor=$user->odbor_id;

  //$id_odbor=GetParentGroup($USER_INFO["GROUP_ID"])?GetParentGroup($USER_INFO["GROUP_ID"]):$USER_INFO["GROUP_ID"]; 
  $odbor=VratNadrizeneOdbory($id_odbor);
  
  while (list($id_odbor_loop,$nazev)=each($odbor)) {
//    echo "<br/>onma".$id_odbor."<br/>";
    $uzly=VratSpisUzly(GetParentGroup($id_odbor_loop));
//    print_r($uzly);
    while (list($key1,$val1)=each($uzly))
      if (array_key_exists($key1,$odbor)) 
      {
//        echo "nalezen uzel".$id_odbor."<br/>";
        $uzel_nalezen=$id_odbor_loop;
        break(2);
      }
  }  
  
  if ($id_odbor>0)    
    $vrat_odbor=VratOdbor($id_odbor);
    
  $vrat_odbor=$vrat_odbor?$vrat_odbor:0;
  $vrat_oddeleni=$vrat_oddeleni?$vrat_oddeleni:0;
  $vrat_so = VratSuperOdbor($id_odbor);
  return array('odbor'=>$vrat_odbor,'oddeleni'=>$vrat_oddeleni,'so'=>$vrat_so);
}

function PopisPracovnika($id) {
  $prac = OdborPrac($id);
  return $prac;
}
  /*
   * funkce pro ziskani pole z definovaneho selectu (of_select_.inc) - ne databazovy
   * @author lumo
   * @param object objekt typu of_select
   * @return array pole hodnota->popis
   */
  function getSelectDataFull($select) {
    $result = array();
    if (is_object($select)) {
      $options = $select->options;
      if (is_array($options)) {
        foreach ($options as $option) {
          if (trim($option["value"])) {
            $result[$option["value"]] = $option;
          }
        }
      }
    }
    return $result;
  }

