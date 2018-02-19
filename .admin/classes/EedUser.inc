<?php
require_once ('db.inc');

/**
* trida EED_doc, pro praci s uzivateli
*@author onma  
*/
class EedUser extends EED_db_object {
  
  var $id_user;
  var $login;
  var $jmeno;
  var $prijmeni;
  var $cele_jmeno;
  var $email;
  var $odbor_id;
  var $odbor_text;
  var $zarizeni_id;
  var $zarizeni_text;

  /**
  * Constructor
  * @author onma  
  * @param int $id - id usera, pokud neni, pouze inicializuje   
  */  
  function EedUser($id = 0){
//    $this->db = &Eed_db_object;
    parent::Eed_db_object();
    if ($id == 0) {
     // $ret = $this->_GetUserPole(0);
      //$id = $ret['ID'];
    }
    if ($id>0) {
      $res = $this->_GetUserPole($id);
      $this->id_user = $res['ID'];
      $this->login = $res['LOGIN_NAME'];
      $this->jmeno = $res['FNAME'];
      $this->email = $res['EMAIL'];
      $this->cele_jmeno = $res['FNAME'] . ' ' . $res['LNAME'];
      
      $this->prijmeni = $res['LNAME'];
      $this->odbor_id = $res['GROUP_ID'];
      $this->odbor_text = $this->GetUnitName($res['GROUP_ID']);
      $this->zarizeni_id = $this->getMainUnit($res['GROUP_ID']);
      $this->zarizeni_text = $this->GetUnitName($this->zarizeni_id);
    }
  }
 

  function _GetUserPole($user_id=0) {
     if ($user_id>0) {
        if (isset($GLOBALS['POSTA_OPT']['SECURITY_USER'][$user_id])) return $GLOBALS['POSTA_OPT']['SECURITY_USER'][$user_id];
        $sql = 'select * from security_user where id=' . $user_id;
        $q= new DB_POSTA; //protoze this->db konektor je pouzit jinde
        $q->query($sql);
        $q->Next_Record();
        $USER_INFO = $q->Record;
        $GLOBALS['POSTA_OPT']['SECURITY_USER'][$user_id] = $USER_INFO;
     } 
     else
       $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    return $USER_INFO;     
  }

  function GetUnit($user_id=0) {
    $user = $this->_GetUserPole($user_id); 
    return $user['GROUP_ID'];     
  }

  function GetNadrizenouUnit($unit_id = 0) {
    if (!$unit_id) return 0;
    if ($unit_id == 0) return 0;

    if (isset($GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id]['PARENT_GROUP_ID'])) return $GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id]['PARENT_GROUP_ID'];
    $sql = 'select * from security_group where id=' . $unit_id;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $unit = $this->db->Record; 
    $GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id] = $unit;
    return $unit['PARENT_GROUP_ID'] ? $unit['PARENT_GROUP_ID'] : 0;     
  }




  function GetUserId($user_id=0)
  {
    $user = $this->_GetUserPole($user_id); 
    return $user['ID'];     
  }

  function GetUserEmail($user_id=0)
  {
    $user = $this->_GetUserPole($user_id); 
    return $user['EMAIL'];     
  }

  function GetUserZkratka($user_id=0)
  {
    $user = $this->_GetUserPole($user_id); 
    return $user['SHORT'];     
  }

  function GetUserName($user_id=0) {
    $user = $this->_GetUserPole($user_id);
    return $user['FNAME']." ".$user['LNAME'];
  }

  function GetUserShort($user_id=0) {
    $user = $this->_GetUserPole($user_id);
    return $user['SHORT'];
  }

  function GetUserNameByLNAME($user_id=0)
  {
    $user = $this->_GetUserPole($user_id); 
    return $user['LNAME']." ".$user['FNAME'];     
  }

  
  function NajdiVedoucihoVUnite($id = 0) {
    if (!$id) return '';
  	$sql = "select * from security_user where vedouci and active and group_id=".$id;
    $this->_sql_query($sql);
    If ($this->db->Num_Rows()>0) {$this->db->Next_Record(); return $this->db->Record["ID"];}
    else return '';
  }

  function NajdiRediteleVPracovisti($id)
  {
    $utvary = $this->VratPodrizeneUnity($id); 
  	while (list($id,$val)=each($utvary))
  	{
      $sql = "select * from security_user where reditel and active and group_id=".$id;
      $this->_sql_query($sql);
      If ($this->db->Num_Rows()>0) {$this->db->Next_Record(); return $this->db->Record["ID"];}
    }
  }

  function VratPracovnikyVUnite($id) {
    if (!$id) return array();
  	$sql = "select * from security_user where active and group_id=".$id;
    $ret = array();
    $this->_sql_query($sql);
  	while ($this->db->Next_Record())
  	{
      $ret[]= $this->db->Record['ID'];
    }
    return $ret;
  }

  function _VratSpisUzly_recursive($idcko=0,$uroven=0,$pole=array())
  {
    $sql="SELECT o.id as idcko,g.id,g.name 
          FROM cis_posta_odbory o LEFT JOIN security_group g  ON g.id=o.id_odbor
          WHERE g.type_group<>3 AND g.public_group='1' AND g.parent_group_id=".$idcko;
  
    $this->_sql_query($sql);
  	$uroven++;
  	while ($this->db->Next_Record())
  	{
      $id = $this->db->Record['ID'];
  		$name=$this->db->Record['NAME'];
  		for ($a=1; $a<$uroven; $a++) 
        $pole[$id].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
  //	  $pole[$id].='<img src="'.FileUpURL('images/editor/tree_split.gif').'">&nbsp;';
  	  $pole[$id].=$name;
  		$pole=$this->_VratSpisUzly_recursive($this->db->Record['ID'], $uroven,$pole);
  	} 
  	return $pole;
  }


  function VratSpisUzly($idcko=0)
  {
    $pole = array();
		$pole = $this->_VratSpisUzly_recursive($idcko, $uroven,$pole);
  	return $pole;
  }

  function _VratPodrizeneUnity_recursive($idcko=0,$uroven=0,$pole=array())
  {
    if (!$idcko) $idcko = 0;
    $sql="SELECT g.id,g.name FROM security_group g  WHERE g.type_group<>3 AND g.public_group='1' AND g.parent_group_id=".$idcko;
    $this->_sql_query($sql);
  	$uroven++;
  	while ($this->db->Next_Record())
  	{
      $id = $this->db->Record['ID'];
  		$name=$this->db->Record['NAME'];
  		for ($a=1; $a<$uroven; $a++) 
        $pole[$id].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
  	  $pole[$id].=$name;
      $user_tmp=new EedUser();
  		$pole=$user_tmp->_VratPodrizeneUnity_recursive($this->db->Record['ID'], $uroven,$pole);
  	} 
  	return $pole;
  }

  function VratPodrizeneUnity($unit_id=0)
  {
    $pole = array();
		$pole = $this->_VratPodrizeneUnity_recursive($unit_id, 0,$pole);
  	$this->ShowDebug($pole);
  	return $pole;
  }

  function _VratNadrizeneUnity_recursive($idcko=0,$uroven=0,$pole=array())
  {
    if (!$idcko) $idcko=0;
    $sql="SELECT g.parent_group_id,g.name,g.id FROM security_group g  WHERE g.type_group<>3 AND g.public_group='1' AND g.id=".$idcko;
    $this->_sql_query($sql);
  	$uroven++;
  	while ($this->db->Next_Record())
  	{
      $id = $this->db->Record['ID'];
  		$name=$this->db->Record['NAME'];
  		for ($a=1; $a<$uroven; $a++) 
        $pole[$id].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
  	  $pole[$id].=$name;
      if ($this->db->Record['PARENT_GROUP_ID']>0)
      {
        $user_tmp=new EedUser();
    		$pole=$user_tmp->_VratNadrizeneUnity_recursive($this->db->Record['PARENT_GROUP_ID'], $uroven,$pole);
      }
  	} 
  	return $pole;
  }

  function VratNadrizeneUnity($unit_id=0)
  {
    $pole = array();
		$pole = $this->_VratNadrizeneUnity_recursive($unit_id, 0,$pole);
  	$this->ShowDebug($pole);
    return $pole;
  }

  function VratNadrizeneSpisUzlyZOdboru($unit_id=0)
  {
    $pole = array();
    $uzelPrac = $this->VratSpisUzelZOdboru($unit_id);
    if ($uzelPrac['ID']>0) $res[$uzelPrac['ID']] = $unita;
		$pole_temp = $this->_VratNadrizeneUnity_recursive($unit_id, 0,$pole);
    
    foreach($pole_temp as $unit_id => $unita) {
      $uzel = $this->VratSpisUzelZOdboru($unit_id);
      if ($uzel['ID']>0) $res[$uzel['ID']] = $unita;
    }
  	$this->ShowDebug($res);
    return $res;
  }

  function NajdiZarizeniId($unit_id = 0)  {
    $pole = array();
		$pole = $this->VratNadrizeneUnity($unit_id);
  	$this->ShowDebug($pole);
    $zarizeni_id = array_pop(array_keys($pole));
    return $zarizeni_id;
  }


  function _VratSpisovyUzel($uzel_id=0) {
    if ($uzel_id<0 || !$uzel_id) 
    {
      $this->ShowError('Není správně zadán uzel_id!');
      $uzel_id=0;
    }
    if (is_array($uzel_id)) return false;
    if ($uzel_id == 0) return false;
    if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$uzel_id])) {return $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$uzel_id];}

    $sql="SELECT * FROM cis_posta_odbory";
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      $id = $this->db->Record['ID'];
      $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id] = $this->db->Record;
      $id_odbor = $this->db->Record['ID_ODBOR'];
      $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$id_odbor] = $id;
    }

    return $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$uzel_id];
  }

  function _VratZkratkuSpisovehoUzlu($uzel_id=0) {
    if ($uzel_id<0 || !$uzel_id)  {
      $this->ShowError('Není správně zadán uzel_id!');
      $uzel_id=0;
    }
    if ($uzel_id == 0) return false;
    if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$uzel_id]['ZKRATKA'])) return $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$uzel_id]['ZKRATKA'];
    $sql="SELECT * FROM cis_posta_odbory where id=".$uzel_id;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    if (is_array($this->db->Record)) $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$uzel_id] = $this->db->Record;
    else $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$uzel_id]['ZKRATKA'] = '';
    return $this->db->Record['ZKRATKA'];
  }

  function VratSpisUzelZOdboru($odbor_id=0) {
    if ($odbor_id<0 || !$odbor_id) {
      $this->ShowError('Není správně zadán odbor_id!');
      $odbor_id=0;
    }

    if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$odbor_id])) {
      $id = $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$odbor_id];
      if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id])) return $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id];
    }

    $sql="SELECT * FROM cis_posta_odbory where id_odbor=".$odbor_id;
    
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $id = $this->db->Record['ID'];
    $id_odbor = $this->db->Record['ID_ODBOR'];
    $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY'][$id] = $this->db->Record;
    $id_odbor = $this->db->Record['ID_ODBOR'];
    $GLOBALS['POSTA_OPT']['CIS_POSTA_ODBORY']['ID_ODBOR'][$id_odbor] = $id;
    return $this->db->Record;

  }

  function VratOdborZSpisUzlu($uzel_id=0) {
    $ret = $this->_VratSpisovyUzel($uzel_id);
    return $ret['ID_ODBOR'];
  }

  function VratZkratkuUzlu($uzel_id=0) {
    $ret = $this->_VratSpisovyUzel($uzel_id);
    return $ret['ZKRATKA'];
  }


  function VratUzlyAOdborPrac($uzel_id = 0)
  {
    $unit_id = $this->VratOdborZSpisUzlu($uzel_id);
    $podrizeny_uzel[] = $uzel_id;  

    $prac[$unit_id] = $this->VratPracovnikyVUnite($unit_id);

    $odbory = $this->VratPodrizeneUnity($unit_id); 

    foreach($odbory as $odbor => $val) {
      $uzel = $this->VratSpisUzelZOdboru($odbor);
      $prac[$odbor] = $this->VratPracovnikyVUnite($odbor);
      if ($uzel['ID']>0) $podrizeny_uzel[] = $uzel['ID'];  
    }
    $ret = array(
       'odborprac'=>$prac,
       'uzel'=>$podrizeny_uzel,    
    );
    return $ret;
  }

  function VratUzlyAOdborPracZUnity($unit_id = 0)  {
    $uzel = $this->VratOdborZSpisUzlu($unit_id);
    if ($uzel['ID']>0) $podrizeny_uzel[] = $uzel['ID'];  

    $prac[$unit_id] = $this->VratPracovnikyVUnite($unit_id);

    $odbory = $this->VratPodrizeneUnity($unit_id); 

    foreach($odbory as $odbor => $val) {
      $uzel = $this->VratSpisUzelZOdboru($odbor);
      $prac[$odbor] = $this->VratPracovnikyVUnite($odbor);
      if ($uzel['ID']>0) $podrizeny_uzel[] = $uzel['ID'];  
    }
    $ret = array(
       'odborprac'=>$prac,
       'uzel'=>$podrizeny_uzel,    
    );
    return $ret;
  }

  function VratNadrizeneVedouci($prac_id = 0) {
    $pole_prac_id = array();

    $unit_id = $this->GetUnit($prac_id);
    $prac_id = $this->NajdiVedoucihoVUnite($unit_id);
    if ($prac_id > 0)
      $pole_prac_id[] = $prac_id;
    $nadrizene_unity = $this->VratNadrizeneUnity($unit_id);
    while (list($key, $val) = each($nadrizene_unity)) {
      $prac_id=$this->NajdiVedoucihoVUnite($key);
      if ($prac_id > 0)
        $pole_prac_id[] = $prac_id;
    }
    $this->ShowDebug($pole_prac_id);
    return $pole_prac_id;
  }


  function VratSpisovyUzelPracovnika($prac_id = 0)  {
    $unit_id = $this->GetUnit($prac_id);
    $uzel = $this->VratSpisUzelZOdboru($unit_id);
    if ($uzel['ID']>0) return $uzel['ID'];  

    while ($unit_id>0) {
      $unit_id = $this->GetNadrizenouUnit($unit_id);
      $uzel = $this->VratSpisUzelZOdboru($unit_id);
      if ($uzel['ID']>0) return $uzel['ID'];  
     
      
    }

    return false;
  }


}

