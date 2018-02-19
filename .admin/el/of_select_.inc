<?php
if (!IsFileIncluded(__FILE__."user")):


include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
// include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_add.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_other.inc");
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/el/of_odbory_.inc"));
require_once(FileUp2(".admin/el/of_select2.inc"));
require_once(FileUp2(".admin/config.inc"));
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/oth_funkce_2D.inc"));

$is_history = In_Array($form_params["formtype"], array($f_history));
$is_info = In_Array($form_params["formtype"], array($f_info));

class of_select_typ_posty extends of_select {
  // Constructor
  function of_select_typ_posty($a) {
    $this->setup_element($a);
    $this->options = array();
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $uid = $USER_INFO["ID"];
    $odbor=array();
    $spisuzel=array();
    if ($GLOBALS['REFERENT'])
      $GLOBALS['rerefent']=$GLOBALS['REFERENT'];
      else
        $GLOBALS["referent"]=$uid; //referent malymi pismeny, aby pak nebyl vybran ve vyberu
        //    If (In_Array($form_params["formtype"], array($f_filter, $f_filter_all))) //musio se ukazovat i v editaci
        //$pole=OdborPrac($GLOBALS['referent']);
        $userObj = LoadClass('EedUser', $GLOBALS['referent']);
        $odbor = $userObj->VratSpisUzelzOdboru($userObj->odbor_id);
        //    $pole['odbor'] = $odbor['ID'];
        //      print_r($pole['odbor']);
        //      $odbor=UkazOdbor($pole['odbor'],0,0,1);
        //      $odbor=$pole['odbor'];
        $nadrazene_odbory=VratNadrizeneOdbory($odbor['ID']);
        $odbor=array_flip($nadrazene_odbory);
        
        if (count($odbor)>0) {
          foreach ($odbor as $odbor_temp) {
            $spisuzel[] = VratOdbor($odbor_temp);
          }
        }

        $id_check_ids = is_array($GLOBALS[$a['name']]) ? $GLOBALS[$a['name']] : array($GLOBALS[$a['name']]);
        
        foreach($id_check_ids as $key => $number_test) {
          if (!is_numeric($number_test))
            unset($id_check_ids[$key]);
        }
        
        $id_check_ids_string = implode(",",$id_check_ids);
        
        $id_check = (sizeof($id_check_ids)>0) ? " or id in (".$id_check_ids_string.")": "";
        //$id_check = ($GLOBALS[$a['name']]!="") ? " or id in (".$id_check_ids.")": "";
        $neaktivni = " and (neaktivni is false ".$id_check.") and (neaktivni_agenda is false ".$id_check.")";
       
        $app =" where id_agendy is not null".$neaktivni;
        
        
        $b = array();
        $agendy = new of_select_agenda_dokumentu($b);
        $id_ag = $agendy->options[0]["value"];
        if ( $a["default_agenda"] == true && $id_ag>0) {
          $app = " where id_agendy=".$id_ag.$neaktivni;
        }
        
        if (isset($GLOBALS['doc']) && $GLOBALS['doc']>0 && is_string($GLOBALS['doc'])) {
          $app = " where id_agendy=".$GLOBALS['doc'].$neaktivni;
        }
        
        if (isset($a["agenda_id"]) && $a["agenda_id"]>0) {
          $app = " where id_agendy=".$a["agenda_id"].$neaktivni;
        }
        
        
        
        if (HasRole('spravce')||HasRole('lokalni-spravce')||HasRole('editace_vse_pracoviste')) {
          $sql = "SELECT id,nazev FROM cis_posta_typ a ".$app." ORDER BY a.poradi asc,a.id asc";
        }
        else {
          if (count($spisuzel) > 0)
            $sql = "SELECT a.id,a.nazev FROM cis_posta_typ a where id_agendy is not null and (a.odbor in (".implode(',',$spisuzel).") or a.odbor is null) ".$neaktivni." ORDER BY a.poradi asc,a.id asc";
            else
              $sql = "SELECT a.id,a.nazev FROM cis_posta_typ a  ".$app." ORDER BY poradi asc,id asc";
        }
        
        if ($GLOBALS["HISTORY_TABLE_IDENT_COLUM"]=='NEW') $a['selectfull'] = 1; //kvuli transakcnimu protokolu
        
        
        if ($a['selectfull']) {
          $sql = "SELECT a.id,a.nazev FROM cis_posta_typ a  ".$app." ORDER BY a.poradi asc,a.id asc";
        }
        //    $this->of_select($a);
        $db = new DB_POSTA;
        $db->query($sql);
        
        if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
        
        while ($db->Next_record()) {
          
          $id = $db->Record['ID'];
          $add = '';
          if ($a["selected"]==$id) $add = 'selected="selected"';
     //     if ((isset($a['agendacount'])&& $a['agendacount']>0)||!HasRole('editace_vse_pracoviste'))
       $this->options[] = array(
            'value' => $id,
            'label' => $db->Record['NAZEV'],
            'add' => $add,
            //        'add'   => 'data-lhuta=' . (isset($a['lhuta'][$id]) ? $a['lhuta'][$id] : '""' )
          );
        }
  }
}


//class of_select_agenda_dokumentu extends of_select_db {
  class of_select_agenda_dokumentu extends of_select2 {
  // Constructor
  function of_select_agenda_dokumentu($a) {
    $this->setup_element($a);
    $this->width = '350px';
    $spravce = HasRole('spravce');
    $lokalni_spravce = HasRole('lokalni-spravce');
    $podatelna = HasRole('editace_vse_pracoviste');
    
    if ($a['name']!="") $agd = VratAgenduDokumentu($GLOBALS['TYP_POSTY']);
    $id_check = ($agd) ? " or a.id=".$agd: "";
    $add_agenda = ($agd) ? " or a.id=".$agd: "";
    $neaktivni = " and (a.neaktivni is false ".$id_check.")";
    
    //if ($a['agenda'] =="POSTA") {
    if ((HasRole('spravce')||$a['puvodni']==true)&&(!$podatelna)) {
      $add = " where a.id_superodbor is not null";
    }
    else
      $add = ' where a.id_superodbor='.EedTools::VratSuperOdbor();
      
      
      //agenda, ktera se ma pridat, prestoze na ni uzivatel nema prava

      if (isset($a["addagenda"]) && $a[addagenda]>0) {
        $add_agenda = " OR a.id=".$a["addagenda"]." ";
      }
      
      /*if ($podatelna) {
        $add= " where a.id_superodbor =". EedTools::VratSuperOdbor();
      }*/
      
      
      
      //if (($a['filter']=="true"||$a['superodbor'])&&!$podatelna) {
        if (($a['filter']=="true"||$a['superodbor'])) {
          
        $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
      
        $pole=OdborPrac($USER_INFO['ID']);
        $odbor=UkazOdbor($pole['odbor'],0,0,1);
        $nadrazene_odbory=VratNadrizeneOdbory($odbor);
        $odbor=array_flip($nadrazene_odbory);
        
        if (count($odbor)>0) {
          foreach ($odbor as $odbor_temp) {
            $spisuzel[] = VratOdbor($odbor_temp);
          }
        }
        else $spisuzel[0] = 0;
        
     /*   $odbor = array();
        $odbor[]=VratOdbor($USER_INFO['GROUP_ID']);
        if ($odbor[0]==-1) $odbor[0] = 0;*/
        
        
        $odbor_where2 = "";
        $app_where = "";
        $odbor_where = " and (b.id_odbor in(".implode(",",$spisuzel).") or b.id_odbor is null)";
        if (!$lokalni_spravce && !$podatelna)
          $odbor_where2 = $odbor_where;
          
          if (!$spravce)
            $app_where=" AND ((a.id_superodbor is null ".$odbor_where." ) OR a.ID_SUPERODBOR IN (". EedTools::VratSuperOdbor() ."))".$odbor_where2;
            
            if ($a['superodbor']&&!$a['jen_odbor'])
              $app_where=" AND (a.id_superodbor is null OR a.ID_SUPERODBOR = ".$a['superodbor'].")";
              
              $q = "SELECT distinct a.id, a.nazev, a.poradi FROM CIS_POSTA_AGENDA a right join cis_posta_typ t on a.id=t.id_agendy left join 
              cis_posta_typ_odbor b on t.id = b.id_posta_typ
        WHERE a.id is not null ".$app_where.$add_agenda.$neaktivni." ORDER BY a.PORADI";
      } else
        
        
        $q = '(SELECT id,nazev,poradi FROM cis_posta_agenda WHERE id_superodbor IS NULL)
        UNION (select a.id,a.nazev,a.poradi+1000 FROM cis_posta_agenda a'.$add.$add_agenda.$neaktivni. ')  ORDER BY poradi asc';
        
        $this->DB_Sql = new DB_POSTA;
        $this->DB_Sql->query($q);
        
        /*SELECT from agendy where superodbor is null order by poradi asc UNION
         SELECT from agendy where superodbor=X order by poradi asc*/
        
        while ($this->DB_Sql->Next_Record())
        {
          $this->options[] = array('value' => $this->DB_Sql->Record['ID'], 'label' => $this->DB_Sql->Record['NAZEV']);
        }
        
       // $this->init_db();
        
  }
}


/*class of_select_agenda_dokumentu2 extends of_select_db {

function of_select_agenda_dokumentu2($a) {
$this->setup_element($a);
$sql = "SELECT id,agenda FROM cis_posta_agenda ORDER BY agenda asc";
$db = new DB_POSTA;
$db->query($sql);
$sel="";
if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
$GLOBALS['AGENDA_DOKUMENTU'] = VratAgenduDokumentu($GLOBALS['TYP_POSTY']);
while ($db->Next_record()) {
$id = $db->Record['ID'];
$sel = "";
if ($GLOBALS['AGENDA_DOKUMENTU'] == $id) $sel = "SELECTED";
$this->options[] = array(
'value' => $id,
'label' => $db->Record['AGENDA'],
'add' => $sel,
);
}
}
}*/

class of_select_odes_typ extends of_select_db {
  // Constructor
  function of_select_odes_typ($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT kod,nazev FROM posta_cis_adresati WHERE aktivni=1 ORDER BY poradi asc, id asc");
    $this->init_db();
  }
}
class of_select_druh_prijeti extends of_select {
  // Constructor
  function of_select_druh_prijeti($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "1", 'label' => "písemně");
    $this->options[] = array('value' => "2", 'label' => "osobně");
    $this->options[] = array('value' => "3", 'label' => "elektronicky");
    
    
    //    $this->options[] = array('value' => "4", 'label' => "faxem");
    //    If (In_Array($form_params["formtype"], array($f_filter, $f_filter_all)))  $this->options[] = array('value' => "X", 'label' => "Vnitřní pošta");
    
    //    					  "options_sep" => "&nbsp;",
  }
}


class of_select_nastaveni_pristupy_rozsah extends of_select {
  // Constructor
  function of_select_nastaveni_pristupy_rozsah($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "V", 'label' => "jen vybrané");
    $this->options[] = array('value' => "C", 'label' => "celý spis");
    
    
    //    $this->options[] = array('value' => "4", 'label' => "faxem");
    //    If (In_Array($form_params["formtype"], array($f_filter, $f_filter_all)))  $this->options[] = array('value' => "X", 'label' => "Vnitřní pošta");
    
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_statnisprava extends of_select {
  // Constructor
  function of_select_statnisprava($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "1", 'label' => "Město ".$GLOBALS["CONFIG"]["MESTO"]);
    $this->options[] = array('value' => "2", 'label' => $GLOBALS["CONFIG"]["URAD"]." ".$GLOBALS["CONFIG"]["MESTO"]);
    // If (In_Array($form_params["formtype"], array($f_filter, $f_filter_all)))  $this->options[] = array('value' => "X", 'label' => "Vnitřní pošta");
    
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_stav_posty extends of_select {
  // Constructor
  function of_select_stav_posty($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    //     $this->options[] = array('value' => "R", 'label' => "příchozí dokument, který je na podatelně");
    //     $this->options[] = array('value' => "Z", 'label' => "příchozí dokument, který čeká na zpracování vedoucím spisového uzlu");
    //     $this->options[] = array('value' => "M", 'label' => "příchozí dokument, který je zpracován vedoucím, čeká na přečtení zpracovatelem");
    // //    $this->options[] = array('value' => "S", 'label' => "příchozí pošta, která je vyřízená");
    //     $this->options[] = array('value' => "P", 'label' => "příchozí dokument, který není vyřízen a je 5 dnů do konce lhůty k vyřízení");
    //     $this->options[] = array('value' => "C", 'label' => "příchozí dokument, který není vyřízen a je překročena lhůta k vyřízení");
    $this->options[] = array('value' => "RR", 'label' => "příchozí dokument, který má vyplněno pole Rekomando");
    $this->options[] = array('value' => "H", 'label' => "odchozí dokument, kde chybí datum u doručenky");
    $this->options[] = array('value' => "S", 'label' => "dokument, kde není zadán spisový znak");
    //    $this->options[] = array('value' => "U", 'label' => "dokument, který není uložen ve spisu");
    $this->options[] = array('value' => "SS", 'label' => "dokument, který byl stornován");
    $this->options[] = array('value' => "CJ", 'label' => "dokument, u kterého bylo přeevidováno číslo jednací");
    if (HasRole('cteni_vse_pracoviste') || HasRole('cteni_admin')) $this->options[] = array('value' => "SO", 'label' => "dokument, který byl předán na jiné zařízení");
    $this->options[] = array('value' => "V", 'label' => "příchozí dokument, kde není zadán způsob vyřízení");
    $this->options[] = array('value' => "PV", 'label' => "pozdě vyřízené čj.");
    //    					  "options_sep" => "&nbsp;",
  }
}



class of_select_typ_odeslani extends of_select {
  // Constructor
  function of_select_typ_odeslani($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    reset($GLOBALS["CONFIG"]["TYP_ODESLANI"]);
    while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"]))
      $this->options[] = array('value' => $val['VALUE'], 'label' => $val['LABEL']);
      
  }
}

class of_select_druh_odeslani extends of_select {
  // Constructor
  function of_select_druh_odeslani($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    reset($GLOBALS["CONFIG"]["DRUH_ODESLANI"]);
    while (list($key,$val)=each($GLOBALS["CONFIG"]["DRUH_ODESLANI"])) {
      
    /*  if 
      (
        (
          (($val['VALUE']==5)&&HasRole('vypraveni-email')) ||  // elektronicky
          (($val['VALUE']==6)&&HasRole('vypraveni-int-posta')) ||  // interni postou
          (($val['VALUE']==9)&&HasRole('vypraveni-ds'))     // datovou schrankou
        ) ||
        (
            !in_array($val['VALUE'], array(5,6,9))
        ) ||
        (  
            !$a['omez_prava']
        )
       )*/
      $this->options[] = array('value' => $val['VALUE'], 'label' => $val['LABEL']);
    }
  }
}


class of_select_odbor extends of_select_db {
  // Constructor
  function of_select_odbor($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    //    $this->DB_Sql->query("SELECT DISTINCT id,name FROM security_group WHERE (type_group=1) and (name<>'T-MAPY') ORDER BY name");
    //    $this->DB_Sql->query("SELECT DISTINCT o.id,g.description FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor ORDER BY g.description");
    //    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    //      $this->DB_Sql->query("SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".VratSuperOdbor()."ORDER BY g.name");
    //      $this->DB_Sql->query("SELECT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE o.superodbor=".VratSuperOdbor()."ORDER BY o.poradi");
    
    if (HasRole('podatelna')||HasRole('spravce')||HasRole('zmena-odboru-nahoru') || HasRole('zmena-spisoveho-uzlu') ||  !$GLOBALS['ODBOR']||$GLOBALS['TYP_POSTY_EDITACE'])
    {
      if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
      if ($a["vratcele"] || HasRole('zmena_spisoveho_uzlu')) $polex=VratSpisUzly(0);
      else $polex=VratSpisUzly(EedTools::VratSuperOdbor());
      
    }
    elseif ((HasRole('vedouci-odbor')||HasRole('podatelna-odbor')) && !$is_filter && $GLOBALS['ODBOR'])   {
      //      $nadrizene_odbory=VratNadrizeneOdbory(UkazOdbor($GLOBALS['ODBOR'],0,0,1));
      $nadrizene_odbory=VratNadrizeneOdbory(UkazOdbor(VratOdbor(),0,0,1));
      $prvni_nadrizeny=key($nadrizene_odbory);
      //      echo $prvni_nadrizeny;
      $pole_pom=VratSpisUzly($prvni_nadrizeny);
      $polex[key($nadrizene_odbory)]=current($nadrizene_odbory); //musime pridat na zacatek aktualni odbor
      while (list($key,$val)=each($pole_pom)) //prekreslime
        $polex[$key]="&nbsp;&nbsp;&nbsp;".$val;
        
    }
    elseif (HasRole('zpracovatel') && !$is_filter && $GLOBALS['ODBOR'])  {
      //      $nadrizene_odbory=VratNadrizeneOdbory(UkazOdbor($GLOBALS['ODBOR'],0,0,1));
      $nadrizene_odbory=VratNadrizeneOdbory(UkazOdbor(VratOdbor(),0,0,1));
      $prvni_nadrizeny=key($nadrizene_odbory);
      //      echo $prvni_nadrizeny;
      
      $pole_pom=VratSpisUzly($prvni_nadrizeny);
      $polex[key($nadrizene_odbory)]=current($nadrizene_odbory); //musime pridat na zacatek aktualni odbor
      while (list($key,$val)=each($pole_pom)) //prekreslime
        $polex[$key]="&nbsp;&nbsp;&nbsp;".$val;
    }
    while (list($key,$val)=@each($polex))
    {
      $odb = EedTools::VratOdborId($key);
      if ($GLOBALS['AKTIVNI_SPISUZLY'][$key] == 0)
        $add = "DISABLED\" disabled=\"disabled\" DISABLED ";
        else $add ='';
        $this->options[] = array('value' => $odb, 'label' => $val, 'style' => $add);
    }

    //    $this->init_db();
    //  print_r($this->options);
  }
}

/*class of_select_vsechny_spisuzly extends of_select_db {
  // Constructor
  function of_select_vsechny_spisuzly($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    if (HasRole('zmena-spisoveho-uzlu') || HasRole('spisovna-odbor')) {
      $nadrizene_odbory=VratNadrizeneOdbory(UkazOdbor(VratOdbor(),0,0,1));
      $prvni_nadrizeny=key($nadrizene_odbory);
      
      $EedUser = LoadClass('EedUser',0);
      $polex_temp=VratSpisUzly($prvni_nadrizeny);
      $polex[$prvni_nadrizeny] = $EedUser->GetUnitName($prvni_nadrizeny);
      foreach($polex_temp as $key => $val)
        $polex[$key] = $val;
        //      $polex = array_merge_recursive($polex_temp, $nadrizene_odbory);
    }
    else {
      $polex= VratSpisUzly(UkazOdbor(VratOdbor(),0,0,1));
    }
    
      
      if ($GLOBALS["HISTORY_TABLE_IDENT_COLUM"]=='NEW') $a['selectfull'] = 1; //kvuli transakcnimu protokolu
      
      if (HasRole('cteni_admin')) $polex=VratSpisUzly(0);
      if (HasRole('spravce')) $polex=VratSpisUzly(0);

      if (HasRole('cteni_vse_pracoviste') || HasRole('lokalni-spravce') || HasRole('zmena-spisoveho-uzlu-nahoru')) {
        $polex=VratSpisUzly(EedTools::VratSuperOdbor());
      }
     
      if ($a['superodbor']>0) $polex = VratSpisUzly($a['superodbor']);
      
      if ($a["selectfull"]) $polex=VratSpisUzly(0);

      $this->options = array();
      
      if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
      while (list($key,$val)=each($polex)) {
        $odbor = VratOdbor($key);
        if ($a['frozen']) $val = str_replace('&nbsp;', '', $val);
        if ($GLOBALS['AKTIVNI_SPISUZLY'][$key] == 0) {
          if ($a["not_disabled"])
          $add = "DISABLED\" disabled=\"disabled\" DISABLED ";
        }
          else $add ='';
        if ($a['enable_disabled']) $add = '';
          $this->options[] = array('value' => VratOdbor($key), 'label' => $val, 'style' => $add);
      }
      
      //    $this->init_db();
  }
  
}*/


class of_select_vsechny_spisuzly extends of_select_db {
  
  var $spisuzly = array();
  
  function nbspPrefix($depth) {
    $prefix = "";
    for ($i=0;$i<$depth;$i++) {
      $prefix.="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
    }
    return $prefix;
  }
  
  function addItemToList($polex,$item) {
    $depth = $item['DEPTH'];
    $parent_id = $item['ID2'];
    $item['DESCRIPTION'] = $this->nbspPrefix($depth).$item['DESCRIPTION'];
    $item['NAME'] = $this->nbspPrefix($depth).$item['NAME'];
//    $item['DESCRIPTION'] = $this->nbspPrefix($depth).$item['DESCRIPTION'];
    $depth++;
    $this->spisuzly[] = $item;
    foreach ($polex as $item) {
      if (($item['DEPTH'] == $depth)&&($item['PARENT_GROUP_ID']==$parent_id)) {
        $this->addItemToList($polex,$item);  
      }
    }
  }
  
  // Constructor
  function of_select_vsechny_spisuzly($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $odbor = VratOdbor(); //test
    $uodbor = UkazOdbor($odbor); //test
   // $parent_group_id = 0;

 
    if ($GLOBALS["HISTORY_TABLE_IDENT_COLUM"]=='NEW') $a['selectfull'] = 1; //kvuli transakcnimu protokolu
    
    //if (HasRole('cteni_admin')) $polex=VratSpisUzly(0); defaultne 0
    //if (HasRole('spravce')) $polex=VratSpisUzly(0); defaultne 0
    
    if (HasRole('spravce') ||HasRole('cteni_admin')||HasRole('spisovna')||HasRole('access_all')) {
      $parent_group_id = 0;
    }
    elseif (HasRole('cteni_vse_pracoviste') || HasRole('lokalni-spravce') || HasRole('zmena-spisoveho-uzlu-nahoru')) {
      //luma 8.12.2017
      $EedUser = LoadClass('EedUser',0);
      $spis_uzel = $EedUser->VratSpisUzelZOdboru(EedTools::VratSuperOdbor());
      $parent_group_id  = $spis_uzel['ID_ODBOR'];      
    }  
    elseif (HasRole('zmena-spisoveho-uzlu') || HasRole('spisovna-odbor') || HasRole('spravce-odbor-sablony')) {
      //luma 8.12.2017
      $nadrizene_odbory=VratNadrizeneOdbory(UkazOdbor(VratOdbor(),0,0,1));
      $prvni_nadrizeny=key($nadrizene_odbory);
      $EedUser = LoadClass('EedUser',0);
      $spis_uzel = $EedUser->VratSpisUzelZOdboru($prvni_nadrizeny);
      $parent_group_id  = $spis_uzel['ID_ODBOR'];
    }
    
    if ($a['superodbor']>0) $parent_group_id = $a['superodbor'];
    if ($a["selectfull"]) $parent_group_id = 0;
    
    $id_or_parent_id = ($parent_group_id == 0) ? "parent_group_id" : "id";
    
    //$sql = "WITH RECURSIVE t AS (SELECT id,parent_group_id, description, name, 0 depth FROM security_group WHERE  parent_group_id = ".$parent_group_id." and type_group = 1"
    $sql = "WITH RECURSIVE t AS (SELECT id,parent_group_id, description, name, 0 depth FROM security_group WHERE  ".$id_or_parent_id." = ".$parent_group_id." and type_group = 1"
        ." UNION ALL SELECT g.id,g.parent_group_id,g.description, g.name, t.depth+1 FROM security_group g"
        ." JOIN t    ON g.parent_group_id = t.id)"
        ." SELECT cpo.id,tt.description,tt.name,cpo.aktivni,tt.depth,tt.id as id2,tt.parent_group_id  FROM t tt"
        ." LEFT JOIN cis_posta_odbory cpo ON tt.id=cpo.id_odbor"
        ." WHERE cpo.id is not null and tt.description is not null and tt.description != ''";

    $this->DB_Sql->query($sql);
    $polex = array();
    while ($this->DB_Sql->Next_Record()) {
      $polex[] = $this->DB_Sql->Record;
    }
    
    foreach ($polex as $item) {
      if ($item['DEPTH'] == 0)
      $this->addItemToList($polex,$item);      
    }    
    
    $this->options = array();
    
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    foreach ($this->spisuzly as $item) {
//      $val = $item['DESCRIPTION'];
      $val = $item['NAME'];
      $key = $item['ID2'];
      if ($a['frozen']) $val = str_replace('&nbsp;', '', $val);
      if ($GLOBALS['AKTIVNI_SPISUZLY'][$key] == 0) {
        if ($a["not_disabled"])
          $add = "DISABLED\" disabled=\"disabled\" DISABLED ";
      }
      else $add ='';
      if ($a['enable_disabled']) $add = '';
      $this->options[] = array('value' => $item['ID'], 'label' => $val, 'style' => $add);
    }
    
    //    $this->init_db();
  }
  
}


class of_select_interni_spisuzly extends of_select_db {
  // Constructor
  function of_select_interni_spisuzly($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;

    $polex = VratSpisUzly(0);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    while (list($key,$val)=each($polex)) {
      //$odbor = VratOdbor($key);
      if ($a['frozen']) $val = str_replace('&nbsp;', '', $val);
      if ($GLOBALS['AKTIVNI_SPISUZLY'][$key] == 0)
        $add = "\"DISABLED\" disabled=\"disabled\" DISABLED ";
        else $add ='';
        if ($a['enable_disabled']) $add = '';
//        $this->options[] = array('value' => VratOdbor($key), 'label' => $val, 'style' => $add);
        $this->options[] = array('value' => $key, 'label' => $val, 'style' => $add);
    }

    //    $this->init_db();
  }

}

class of_select_interni_spisuzly2 extends of_select2 {
  // Constructor
  function of_select_interni_spisuzly2($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $polex = VratSpisUzly(0,0,array(),$a['abbr']);
    $this->options = array();
    $this->width = '350px';
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    while (list($key,$val)=each($polex)) {
      if ($a['frozen']) $val = str_replace('&nbsp;', '', $val);
      if ($GLOBALS['AKTIVNI_SPISUZLY'][$key] == 0)
        $add = "DISABLED\" disabled=\"disabled\" DISABLED ";
        else $add ='';
      $value = $key;
      //$value = $GLOBALS['MAP_ODBOR'][$key];
      //        $val = str_replace('&nbsp;','', $val);
      if ($add) $value .='" ' . $add;
        $this->options[] = array('value' => $value, 'label' => $val, 'style' => $add);
    }
    //    $this->init_db();
  }
}


class of_select_superodbor extends of_select_db {
  // Constructor
  function of_select_superodbor($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $this->DB_Sql->query("SELECT DISTINCT g.id,g.name, g.poradi FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=0 or g.parent_group_id is null ORDER BY g.poradi, g.id");
    $this->init_db();
  }
}

class of_select_superodbor_prefix extends of_select_db {
  // Constructor
  function of_select_superodbor_prefix($a) {
    $this->setup_element($a);
    $this->options = array();
    
    $sql = "SELECT DISTINCT g.id,g.name, g.poradi FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=0 or g.parent_group_id is null and g.id>0 ORDER BY g.poradi, g.id";
    $db = new DB_POSTA;
    $dbx = new DB_POSTA;
    $db->query($sql);
    
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    
    while ($db->Next_Record()) {
      $sqlx = "select * from posta_konfigurace where superodbor=" . $db->Record['ID'] . " and parametr='prefix_id'";
      $dbx->query($sqlx);
      if ($dbx->Num_Rows() == 1) {
        $dbx->Next_Record();
        
        $this->options[] = array(
          'value' => $db->Record['ID'],
          'label' => $dbx->Record['HODNOTA'],
        );
      }
    }
  }
}

class of_select_multiodbor extends of_select_db {
  // Constructor
  function of_select_multiodbor($a) {
    $this->setup_element($a);
    $this->options = array();
    $pole=VratMultiOdbory(0);
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $polex=VratMultiOdbory();
    while (list($key,$val)=each($polex))
      $this->options[] = array('value' => $key, 'label' => $val);
      if ($a["vcetne_adr"]) $this->options[] = array('value' => "-1", 'label' => "VŠEM ředitelům");
      if ($a["vcetne_adr"]) $this->options[] = array('value' => "-2", 'label' => "VŠEM POI");
      
  }
}

class of_select_spisuzly extends of_select_db {
  // Constructor
  function of_select_spisuzly($a) {
    $this->setup_element($a);
    $this->options = array();
    //$pole=VratMultiOdbory(0);
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $polex=VratSpisUzly();
    while (list($key,$val)=each($polex))
    {
      //  	  $this->options[] = array('value' => $key, 'label' => $val);
      if (substr($val,0,1)=="&")
        $this->options[] = array('value' => $key, 'label' => $val);
        else
          $this->options[] = array('value' => $key, 'label' => $val,"style" => "color:white; font-weight: bold;background: gray; padding: 2; ");
          
    }
    //    if ($a["vcetne_adr"]) $this->options[] = array('value' => "-1", 'label' => "VŠEM ředitelům");
    //if ($a["vcetne_adr"]) $this->options[] = array('value' => "-2", 'label' => "VŠEM POI");
    
  }
}

class of_select_skartace extends of_select2 {
  // Constructor
  function of_select_skartace($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $w=new DB_POSTA;
    $ww=new DB_POSTA;
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    if ($GLOBALS['SKARTACE'] && !is_array($GLOBALS['SKARTACE'])){
      $sql = "select main_id as id from cis_posta_skartace where id=".$GLOBALS['SKARTACE']; // nacteme cislo skartacniho planu
    }
    else {
      $sql = "select id from posta_cis_skartace_main where aktivni=1 and superodbor=" . $USER_INFO['PRACOVISTE']; //zjistime, jestli neni spisovy plan pro me pracoviste
      $w->query($sql);
      if ($w->Num_Rows() == 0) {
        $sql = "select id from posta_cis_skartace_main where aktivni=1 and superodbor is null";
      }

    }
    $w->query($sql);
    $w->Next_Record();
    $skartacni_plan=$w->Record['ID'] ? $w->Record['ID'] : 1;
    if ($USER_INFO["GROUP_ID"]) {
      $sql = "SELECT * FROM cis_posta_odbory where id_odbor = '".$USER_INFO["GROUP_ID"]."'";
      //    echo $sql;
      $w->query ($sql);
      $w->next_record();
      $prava=$w->Record["PRAVA"];
    }
    else {
      $prava = array();
    }
    $kody=array();
    $kody=@explode(':',$prava);
    $wherekody=@implode(',',$kody);
    $wherekody=substr($wherekody,0,-1);
    
    //If ($a[ukazjenaktivni])
    $appendsql='AND aktivni=1 ';
    $add_column = "text,skar_znak,doba,kod";
    
    if($GLOBALS['SKARTACE']>0) $appendsql .= " OR ID IN (".$GLOBALS['SKARTACE'].")";
    If ($wherekody=="")
    $sql_select="SELECT id, $add_column FROM CIS_POSTA_SKARTACE WHERE (main_id=$skartacni_plan)  ".$appendsql." ".$append_where." ORDER BY kod,text";
    else
      $sql_select="SELECT id, $add_column FROM CIS_POSTA_SKARTACE where (main_id=$skartacni_plan) and kod IN (".$wherekody.") ".$appendsql." ".$append_where." ORDER BY kod,text";
      
      If (HasRole('spravce') || $is_history || $is_info)
      $sql_select="SELECT id, $add_column FROM CIS_POSTA_SKARTACE where (main_id=$skartacni_plan)  ORDER BY kod,text";
      //vypiseme nazev skartacniho planu
      $sql = "select * from posta_cis_skartace_main where id=".$skartacni_plan." limit 1";
      if ($a['fullselect']) {
        $sql = "select * from posta_cis_skartace_main order by id desc"; //vyhledavame, vypise vsechny spisove plany
      }
      $ww->query($sql);
      $znaky = VratVecneSkupiny(0,0,array(), array('jen_main_id'=>$skartacni_plan, 'jen_aktivni'=>1));

      while ($ww->Next_Record())
      {
        $text=$ww->Record['NAZEV'].", platnost";
        if ($ww->Record['PLATNOST_OD']) $text.=" od ".$ww->dbdate2str($ww->Record['PLATNOST_OD']);
        if ($ww->Record['PLATNOST_DO']) $text.=" do ".$ww->dbdate2str($ww->Record['PLATNOST_DO']);
        $this->options[] = array('value' => 0 . $add, 'label' => $text);
        
        if ($a['fullselect']) {$sql_select = "select * from cis_posta_skartace where main_id=".$ww->Record['ID']." and $appendsql order by priorita,kod,text";}
        
        foreach($znaky as $znak)
        {
          
          $text = $znak['CELY_NAZEV'];
          $text_full = str_replace('?', '-', $text);
          if (strlen($text)>130) {
            $mezera = strpos($text_full,' ', 130);
            if ($mezera<1) $mezera = 130;
            $text = mb_substr($text_full, 0, $mezera);
          }
          if ($znak['TYP'] == 1 && !$a['no_frozen']) {
            $add = "DISABLED disabled=\"disabled\" \"";
            //$this->options[] = array('value' => $znak['ID'], 'label' => $text,"add" => " DISABLED disabled=\"disabled\"","style" => "color:black; font-weight: bold;background: white;\" DISABLED disabled='disabled'");
            $this->options[] = array('value' => $znak['ID'] . '" ' . $add, 'label' => $text );
          }
          else
          {
            $add="";
            $kod_text = $text." - ".$znak['SKAR_ZNAK']."/".$znak['DOBA'];
            if ($a['frozen']) $kod_text = str_replace('&nbsp;', '', $kod_text);
            
            $this->options[] = array('value' => $znak['ID'], 'label' => $kod_text, "style"=>"\" title=\"".$text_full."\"");
          }
        }
      }
      //$this->init_db();
  }
}

class of_select_skartace_typ extends of_select {
  // Constructor
  function of_select_skartace_typ($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "1", 'label' => "Věcná skupina");
    $this->options[] = array('value' => "2", 'label' => "Spisový znak");
  }
}


class of_select_vecna_skupina extends of_select_db {
  // Constructor
  function of_select_vecna_skupina($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("select id,kod || ' ' || substr(text,0,80) from cis_posta_skartace where typ in (1) order by id asc");
    $this->init_db();
  }
}

class of_select_skartace_kod extends of_select {
  // Constructor
  function of_select_skartace_kod($a) {

    $w = new DB_POSTA;
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $sql = "select id from posta_cis_skartace_main where aktivni=1 and superodbor=" . $USER_INFO['PRACOVISTE']; //zjistime, jestli neni spisovy plan pro me pracoviste
    $w->query($sql);
    if ($w->Num_Rows() == 0) {
      $sql = "select id from posta_cis_skartace_main where aktivni=1 and superodbor is null";
    }

    $w->query($sql);
    $w->Next_Record();
    $skartacni_plan=$w->Record['ID'] ? $w->Record['ID'] : 1;

    $pole = VratVecneSkupiny(0,0, array(), array('jen_viditelne'=>true, 'jen_vs' =>true, 'jen_main_id' => $skartacni_plan));
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    foreach ($pole as $key => $val)
      $this->options[] = array('value' => $val['ID'], 'label' => $val['CELY_NAZEV']);
  }
}

class of_select_referent extends of_select_db {
  // Constructor
  function of_select_referent($a) {
    global $user_obj;
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    
    //    if (HasRole('vedouci-odd') && $GLOBALS['ODDELENI']<1) $GLOBALS["ODDELENI"]=VratOdbor();
    
    //echo "tadfy".$GLOBALS['ODDELENI'];
    If (In_Array($form_params["formtype"], array($f_edit)) || In_Array($form_params["formtype"], array($f_info)))
    {
      if ($GLOBALS['ODBOR']>0 && !is_array($GLOBALS['ODBOR'])) {
        $odbor = $GLOBALS['ODBOR'];
      }
      else  {
        $pole=OdborPrac($USER_INFO['ID']);
        $odbor=$pole['odbor'];
        if (HasRole('spravce')) {
          $odbor = EedTools::VratOdbor();
        }
      }
      
      if ($a['set_odbor']) $odbor = intval($a['set_odbor']); //kvuli interni poste
      
      if (!$odbor) $odbor = 0; //Mantis 527
      
      if (isset($a['odbor'])) {
        $pole = VratPracovniky(0,1,$a['odbor']);
      }
      else {
        $pole = VratPracovniky($odbor,1);
      }
      $prac = array_flip($pole);
      
      if (count($prac)>0)
        $where.=" OR u.id IN (".implode(',',$prac).")";
        
    }
    
    If (HasRole('vedouci-odbor') || HasRole('vedouci-odd') ||$GLOBALS["POSTA_SECURITY"]->IsUserInGroups('posta-vedouci-odbor-r') || HasRole('podatelna')) {
      //      If ((GetParentGroup($USER_INFO["GROUP_ID"]))>0)
      //        $where=" OR g.parent_group_id=".GetParentGroup($USER_INFO["GROUP_ID"])." or g.id=".GetParentGroup($USER_INFO["GROUP_ID"]);
      //      else
      $where.=" OR g.parent_group_id=".$odbor." or g.id=".$odbor;
      
    }
    If (HasRole('omezeni-zpracovatele'))
    {
      $where=" OR u.id=".$USER_INFO["ID"];
    }
    //If (!HasRole('spravce'))
    {
      $sql = "SELECT u.id,u.lname || ' ' || u.fname FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id where (1=2 $where) and active ORDER BY lname";
    }
    
    //    If ($a['fullselect'] || (HasRole('podatelna') && In_Array($form_params["formtype"], array($f_filter, $f_filter_all))))
    //    If (($a['fullselect'] || (HasRole('podatelna') && $GLOBALS['VYHLEDAVANI'])) && (!HasRole('lokalni-spravce'))) {
    If (($a['fullselect'] || (HasRole('podatelna') && $GLOBALS['VYHLEDAVANI'])) ) {
      if ($GLOBALS['CONFIG']['VYHLEDAVANI_NAPRIC_DB']) {
        $where ="or 1=1 and lname<>''";
      }
      else {
        $EedUser = LoadClass('EedUser',0);
        
        if (HasRole('zpracovat-odbor')) {
          $id = GetParentGroup($EedUser->VratOdborZSpisUzlu($odbor));
          if ($id>0) {
            $odbor = $EedUser->VratSpisUzelZOdboru($id);
            $odbor =  $odbor['ID'];
          }
        }
        
        $nadrazene_odbory=VratNadrizeneOdbory($odbor);
        
        if (HasRole('podatelna') || HasRole('lokalni-spravce')) {
          $podrazene_odbory=VratMultiOdbory(EedTools::VratSuperOdbor());
          $odbor=array_flip($nadrazene_odbory);
          $odbor2=array_flip($podrazene_odbory);
        }
        else {
          $podrazene_odbory=VratMultiOdbory($odbor);
          if (count($podrazene_odbory) == 0) $podrazene_odbory[$odbor] = $odbor;
          $odbor=array();
          $odbor2=array_flip($podrazene_odbory);
        }
        
        
        $odbor_celkem=array_merge($odbor,$odbor2);
        
        while (list($key,$val)=each($odbor_celkem)) {
          //          $odbor_hledej=UkazOdbor($val);
          $odbor_hledej=$EedUser->VratOdborZSpisUzlu($val);
          if (!$odbor_hledej || $odbor_hledej == 0) $odbor_hledej = $val;
          $where.=" OR g.parent_group_id=".$odbor_hledej." or g.id=".$odbor_hledej;
        }
      }
      if (HasRole('cteni_admin')) {
        $where .= " OR 1=1 ";
      }
      
      //      $sql = "SELECT u.id,u.lname || ' ' || u.fname FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id where (1=2 $where) and active ORDER BY lname"
      //vypiseme i ty, co jsou neaktivni
      $sql = "SELECT u.id,u.lname || ' ' || u.fname, case WHEN active THEN '' ELSE ' - neaktivní' END FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id where (1=2 $where and lname<>'') ORDER BY lname";
      ;
      
      
    }
    if ($a['jenUser']) {
      $sql = "SELECT u.id,u.lname || ' ' || u.fname FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id WHERE u.id=".$USER_INFO["ID"];
    }
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query($sql);
    $this->init_db();
  }
}

class of_select_referent_spisuzel extends of_select {
  // Constructor
  function of_select_referent_spisuzel($a) {
    $this->setup_element($a);
    $this->options = array();
    
    $w = new DB_POSTA;
    $x = new DB_POSTA;
    //    $sql = "SELECT DISTINCT g.id, o.id as id_uzel, g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor ORDER BY g.id";
    //    $w->query($sql);
    //    while($w->Next_Record()) {
    //      $uzel_id = $w->Record['ID_UZEL'];
    //      $group_id = $w->Record['ID'];
    
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $sql = "SELECT u.id,u.lname || ' ' || u.fname,g.id as UZEL_ID FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id where  active ORDER BY lname";
    $x->query($sql);
    while($x->Next_Record()) {
      $this->options[] = array(
        'value' => $x->Record[ID],
        'label' => $x->Record[LNAME] . ' ' . $x->Record[FNAME],
        "add" => "data-uzel-id=" . $x->Record['UZEL_ID'],
        //"style" => "color:white; font-weight: bold;background: gray;",
      );
    }
  }
}


class of_select_referentak extends of_select_db {
  // Constructor
  function of_select_referentak($a) {
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    If (!HasRole('spravce')) {$sql = "SELECT id,lname FROM security_user where group_id=".$USER_INFO["GROUP_ID"]." ORDER BY lname";}
    else
    {$sql = "SELECT id,lname || ' ' || fname FROM security_user ORDER BY lname";}
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query($sql);
    $this->init_db();
  }
}

class of_select_multiple_prijemce extends of_select_db {
  // Constructor
  function of_select_multiple_prijemce($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT id,odesl_prijmeni || ' ' || odesl_jmeno || ' ' || odesl_titul || ', ' || odesl_ulice || ' ' || odesl_cp || ', ' || odesl_posta FROM cis_posta_prijemci ORDER BY id");
    $this->init_db();
  }
}
class of_select_druh_zasilky extends of_select {
  // Constructor
  function of_select_druh_zasilky($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "1", 'label' => "Obyčejně");
    $this->options[] = array('value' => "0", 'label' => "Psaní");
    $this->options[] = array('value' => "1", 'label' => "Cenné psaní");
    $this->options[] = array('value' => "2", 'label' => "Doporučené psaní");
    $this->options[] = array('value' => "3", 'label' => "Psaní standard / za 6.40 /");
    $this->options[] = array('value' => "4", 'label' => "Psaní obchodní");
    $this->options[] = array('value' => "5", 'label' => "balíky");
    $this->options[] = array('value' => "6", 'label' => "cenné balíky");
    $this->options[] = array('value' => "7", 'label' => "doporučené balíky");
    $this->options[] = array('value' => "8", 'label' => "poukázka");
    $this->options[] = array('value' => "9", 'label' => "EMS");
    $this->options[] = array('value' => "10", 'label' => "jiný druh - poštovné nastaveno uživatelem /DSET na stroji /");
  }
}
class of_select_ano_ne extends of_select {
  // Constructor
  function of_select_ano_ne($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    
    $this->options[] = array('value' => "1", 'label' => "Ano");
    $this->options[] = array('value' => "0", 'label' => "Ne");
  }
}

class of_select_vita extends of_select {
  // Constructor
  function of_select_vita($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "0", 'label' => "dokument se vyřizuje v elektronické spisové službě");
    
    
    if (is_array($GLOBALS['CONFIG_POSTA']['of_select_add']['of_select_vita'])) {
      foreach ($GLOBALS['CONFIG_POSTA']['of_select_add']['of_select_vita'] as $item) {
        if ($item['fullselect'] == 0)
          $this->options[] = array("value"=> $item['value'], "label"=> $item['label']);
          
      }
    }
    
    If ($a["fullselect"])
    {
      $this->options[] = array('value' => "102", 'label' => "dokument se vyřizuje v ext. programu");
      
      $this->options[] = array('value' => "102", 'label' => "dokument byl vyřízen v ext. programu");
      if (is_array($GLOBALS['CONFIG_POSTA']['of_select_add']['of_select_vita'])) {
        foreach ($GLOBALS['CONFIG_POSTA']['of_select_add']['of_select_vita'] as $item) {
          if ($item['fullselect'] == 1)
            $this->options[] = array("value"=> $item['value'], "label"=> $item['label']);
            
        }
      }
      
    }
  }
  
}
class of_select_ulozeno extends of_select_db {
  // Constructor
  function of_select_ulozeno($a) {
    $this->setup_element($a);
    $GLOBALS["ODBOR"]=$GLOBALS["ODBOR"]?$GLOBALS["ODBOR"]:0;
    If (HasRole('spravce'))
    {
      $sql = "SELECT a.id,a.ulozeno || '-' || b.zkratka FROM cis_posta_ulozeno a LEFT JOIN cis_posta_odbory b ON a.odbor=b.id ORDER BY ulozeno";
    }
    else
    {
      $GLOBALS["ODBOR"]=$GLOBALS["ODBOR"]?$GLOBALS["ODBOR"]:0;
      $sql = "SELECT id,ulozeno FROM cis_posta_ulozeno where odbor=".$GLOBALS["ODBOR"]." ORDER BY ulozeno";
    }
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query($sql);
    $this->init_db();
  }
}

class of_select_oddeleni extends of_select_db {
  // Constructor
  function of_select_oddeleni($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    if (!$GLOBALS["ODBOR"])
    //If (HasRole('spravce') || HasRole('podatelna'))
    {
      $pole=VratOddeleni();
    }
    else
    {
      $pole=VratOddeleni($GLOBALS["ODBOR"]);
    }
    while (list($key,$val)=each($pole))
      $this->options[] = array('value' => $key, 'label' => $val);
  }
}


class of_select_jine extends of_select_db {
  // Constructor
  function of_select_jine($a) {
    $this->setup_element($a);
    $GLOBALS["ODBOR"]=$GLOBALS["ODBOR"]?$GLOBALS["ODBOR"]:0;
    //If (HasRole('spravce'))
    {
      //       $sql = "SELECT a.id,a.jine || '-' || b.zkratka FROM cis_posta_jine ORDER BY id";
      $sql = "SELECT id,jine FROM cis_posta_jine ORDER BY id";
    }
    //     else
    //     {
    //       $GLOBALS["ODBOR"]=$GLOBALS["ODBOR"]?$GLOBALS["ODBOR"]:0;
    //       $sql = "SELECT id,jine FROM cis_posta_jine where odbor=".$GLOBALS["ODBOR"]." ORDER BY jine";
    //     }
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query($sql);
    $this->init_db();
  }
}

class of_select_typ_obalky extends of_select_db {
  // Constructor
  function of_select_typ_obalky($a) {
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    If (HasRole('spravce'))
    {
      $sql = "SELECT id,nazev FROM posta_cis_obalky ORDER BY id";
    }
    else
    {
      //$sql = "SELECT id,nazev FROM posta_cis_obalky WHERE aktivni like '1' ORDER BY id";
      $sql = "SELECT id,nazev FROM posta_cis_obalky WHERE aktivni like '1' and id_superodbor=".$USER_INFO['PRACOVISTE']." ORDER BY id";
    }
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query($sql);
    $this->init_db();
  }
}

class of_select_mesic extends of_select {
  // Constructor
  function of_select_mesic($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "1", 'label' => "Leden");
    $this->options[] = array('value' => "2", 'label' => "Únor");
    $this->options[] = array('value' => "3", 'label' => "Březen");
    $this->options[] = array('value' => "4", 'label' => "Duben");
    $this->options[] = array('value' => "5", 'label' => "Květen");
    $this->options[] = array('value' => "6", 'label' => "Červen");
    $this->options[] = array('value' => "7", 'label' => "Červenec");
    $this->options[] = array('value' => "8", 'label' => "Srpen");
    $this->options[] = array('value' => "9", 'label' => "Září");
    $this->options[] = array('value' => "10", 'label' => "Říjen");
    $this->options[] = array('value' => "11", 'label' => "Listopad");
    $this->options[] = array('value' => "12", 'label' => "Prosinec");
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_osloveni extends of_select_db {
  // Constructor
  function of_select_osloveni($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT id,nazev FROM posta_cis_osloveni ORDER BY id");
    $this->init_db();
  }
}

class of_select_rok_rocnikniha extends of_select_db {
  function of_select_rok_rocnikniha($a) {
    $where = $GLOBALS["PROPERTIES_ACCESS"]['condition_read_a'][1];
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT DISTINCT rok,rok FROM posta ORDER BY rok");
    $this->init_db();
    
  }
}


class of_select_rok extends of_select {
  function of_select_rok($a) {
    $this->setup_element($a);
    if ($a["insertnull"])
      $this->options[] = array('value' => "", 'label' => "všechny");
//      for ($a=2016; $a<=Date('Y'); $a++)
      for ($a=Date('Y'); $a>=($GLOBALS['CONFIG']['ROK_INSTALACE'] ? $GLOBALS['CONFIG']['ROK_INSTALACE'] : (Date('Y'))-10); $a--)
//      for ($a=Date('Y'); $a=>($GLOBALS['CONFIG']['ROK_INSTALACE'] ? $GLOBALS['CONFIG']['ROK_INSTALACE'] : (Date('Y'))-10); $a--)
        $this->options[] = array('value' => $a, 'label' => $a);
//       $this->options[] = array('value' => "2015", 'label' => "2015");
//       $this->options[] = array('value' => "2014", 'label' => "2014");
//       $this->options[] = array('value' => "2013", 'label' => "2013");
//       $this->options[] = array('value' => "2012", 'label' => "2012");
//       $this->options[] = array('value' => "2011", 'label' => "2011");
//       $this->options[] = array('value' => "2010", 'label' => "2010");
//       $this->options[] = array('value' => "2009", 'label' => "2009");
//       $this->options[] = array('value' => "2008", 'label' => "2008");
//       $this->options[] = array('value' => "2007", 'label' => "2007");
//       $this->options[] = array('value' => "2006", 'label' => "2006");
//       //$this->options[] = array('value' => "L", 'label' => "není určeno");
  }
}


class of_select_stitek extends of_select_db {
  function of_select_stitek($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    reset($GLOBALS["CONFIG"]["STITKY"]);
    while (list($key,$val)=each($GLOBALS["CONFIG"]["STITKY"]))
    {
      if ((isset($a['typovy_spis'])&&isset($val['TYPOVY_SPIS']))||(!isset($a['typovy_spis'])&&!isset($val['TYPOVY_SPIS'])))
      $this->options[] = array('value' => $val['VALUE'], 'label' => $val['LABEL']);
    }
  }
}

class of_select_aktivni extends of_select {
  function of_select_aktivni($a) {
    $this->setup_element($a);
    if ($a["insertnull"])
      $this->options[] = array('value' => "", 'label' => "všechny");
      $this->options[] = array('value' => "N", 'label' => "jen aktivní");
      $this->options[] = array('value' => "A", 'label' => "jen vypnuté");
      //$this->options[] = array('value' => "L", 'label' => "není určeno");
  }
}

class of_select_status extends of_select {
  function of_select_status($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"])
      $this->options[] = array('value' => "", 'label' => "nezadáno");
      $this->options[] = array('value' => "7", 'label' => "na podatelně");
      $this->options[] = array('value' => "2", 'label' => "nutné přiřadit zpracovatele");
      $this->options[] = array('value' => "3", 'label' => "zpracovatel ještě nevyřizuje");
      $this->options[] = array('value' => "4", 'label' => "vyřizuje se");
      $this->options[] = array('value' => "5", 'label' => "5 dnů do konce lhůty");
      $this->options[] = array('value' => "6", 'label' => "po lhůtě!!!");
      $this->options[] = array('value' => "11", 'label' => "ve schvalovacím procesu");
      $this->options[] = array('value' => "12", 'label' => "chybí vypravení");
  	  $this->options[] = array('value' => "13", 'label' => "předáno k vypravení");
      $this->options[] = array('value' => "101", 'label' => "v ext. programu");
      $this->options[] = array('value' => "8", 'label' => "čeká se na doručenku");
      $this->options[] = array('value' => "9", 'label' => "vyřízeno, k&nbsp;uzavření");
      $this->options[] = array('value' => "1", 'label' => $GLOBALS['CONFIG']['NAZEV_STAV_1'] ? $GLOBALS['CONFIG']['NAZEV_STAV_1'] : "uzavřeno, k&nbsp;uložení");
      $this->options[] = array('value' => "-3", 'label' => "uloženo ve spisovně");
      $this->options[] = array('value' => "-4", 'label' => "uloženo v registratuře");
      $this->options[] = array('value' => "-5", 'label' => "v delimitaci");
      $this->options[] = array('value' => "-1", 'label' => "stornováno");
      $this->options[] = array('value' => "-2", 'label' => "zničeno");
      $this->options[] = array('value' => "-6", 'label' => "archivováno");
      $this->options[] = array('value' => "-7", 'label' => "otevřený typový spis");
      $this->options[] = array('value' => "-8", 'label' => "uzavřený typový spis");
      //	  $this->options[] = array('value' => "101", 'label' => "vyřizuje se ve Vitě");
      
  }
}

class of_duvod_podepsani extends of_select {
  function of_duvod_podepsani($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"])
      $this->options[] = array('value' => "", 'label' => "nezadano");
      $this->options[] = array('value' => "-1", 'label' => "-1 stornovano");
      $this->options[] = array('value' => "-2", 'label' => "-2 zničeno");
      $this->options[] = array('value' => "-3", 'label' => "-3 ve spisovně");
      $this->options[] = array('value' => "1", 'label' => "1-vyrizeno");
      $this->options[] = array('value' => "2", 'label' => "2-zelene");
      $this->options[] = array('value' => "3", 'label' => "3-modre");
      $this->options[] = array('value' => "4", 'label' => "4-cerna");
      $this->options[] = array('value' => "5", 'label' => "5-zluta");
      $this->options[] = array('value' => "6", 'label' => "6-cervena");
      $this->options[] = array('value' => "7", 'label' => "7-na podatelne");
      $this->options[] = array('value' => "8", 'label' => "8-hneda");
      $this->options[] = array('value' => "9", 'label' => "9-neni uzavren spis (dokument je vyřízen)");
      $this->options[] = array('value' => "11", 'label' => "11-dokument je ve schvalovacím řízení");
      //	  $this->options[] = array('value' => "101", 'label' => "101-vyrizuje se ve Vite");
      
  }
}

if (strpos($GLOBALS[CONFIG_POSTA][PODPIS][podepsani_duvod],',')) {
  $GLOBALS['duvod_pole']=explode(',',$GLOBALS[CONFIG_POSTA][PODPIS][podepsani_duvod]);
  class of_select_duvod extends of_select {
    function of_select_duvod($a) {
      $this->setup_element($a);
      $this->options = array();
      while (list($key,$val)=each($GLOBALS['duvod_pole']))
        $this->options[] = array('value' => $val, 'label' => $val);
    }
  }
}
else
{
  class of_select_duvod extends of_select {
    function of_select_duvod($a) {
      $this->setup_element($a);
      $this->options = array();
      $this->options[] = array('value' => "Schvaluji tento dokument", 'label' => "Schvaluji tento dokument");
      $this->options[] = array('value' => "Prohlédl jsem tento dokument", 'label' => "Prohlédl jsem tento dokument");
      $this->options[] = array('value' => "Jsem autorem tohoto dokumentu", 'label' => "Jsem autorem tohoto dokumentu");
      $this->options[] = array('value' => "Potvrzuji správnost a úplnost tohoto dokumentu", 'label' => "Potvrzuji správnost a úplnost tohoto dokumentu");
      
    }
  }
}
class of_select_spisovna extends of_select_db {
  function of_select_spisovna($a) {
    $this->setup_element($a);
    Access(array('agenda'=>'SKARTACNI_KNIHA'));
    if (HasRole('spisovna')) $where = ' 1=1 ';
    else {
      $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
      $user = LoadClass('EedUser', $USER_INFO['ID']);
      $odbor = $user->odbor_id;
      $nadrizene_uzly = $user->VratNadrizeneSpisUzlyZOdboru($odbor);
      if (count($nadrizene_uzly)>0)
        $where = ' odbor in (' . implode(',', array_keys($nadrizene_uzly)) . ')';
        else
          $where = ' odbor in (-1)';
    }
    if ($a['add_main']) $where .= " OR odbor is null OR odbor=0 ";
    $this->DB_Sql = new DB_POSTA;
    if ($a['superodbor']>0) {
      $where.= " AND s.superodbor in (".$a["superodbor"].")";
    }
    if ($GLOBALS['CONFIG']['USE_SUPERODBOR']&&!HasRole('access_all')) {
      $sql = "SELECT id,spisovna FROM posta_cis_spisovna s WHERE superodbor=".EedTools::VratSuperOdbor()." AND ($where) ORDER BY id";
      $this->DB_Sql->query($sql);
    }
    else
      $this->DB_Sql->query("SELECT s.id,o.zkratka || ' - ' || s.spisovna FROM posta_cis_spisovna s LEFT JOIN cis_posta_odbory o ON s.superodbor=o.id_odbor WHERE  ($where) ORDER BY id");
  //    $this->DB_Sql->query("SELECT id,spisovna FROM posta_cis_spisovna where 1=1 AND ($where) ORDER BY id");
      $this->init_db();  
  }
}

class of_select_vyrizeno extends of_select_db_other {
  //class of_select_vyrizeno extends of_select {
  function of_select_vyrizeno($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->setup_element_extended($a, 'jinak');
    $db = new DB_POSTA;
    $db->query("SELECT nazev as id, nazev FROM posta_cis_vyrizeno ORDER BY poradi,id");
    while ($db->Next_record()) {
      
      $id = $db->Record['ID'];
      
      $this->options[] = array(
        'value' => $id,
        'label' => $db->Record['NAZEV'],
      );
    }
    
    //$this->init_db();
  }
}

class of_select_skartacni_pismeno extends of_select {
  // Constructor
  function of_select_skartacni_pismeno($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    //    $this->options[] = array('value' => "X", 'label' => "Město ".$GLOBALS["CONFIG"]["MESTO"]);
    $this->options[] = array('value' => "S", 'label' => "S - skartace");
    $this->options[] = array('value' => "V", 'label' => "V - výběr");
    $this->options[] = array('value' => "A", 'label' => "A - archivace");
    
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_typ_dokumentu extends of_select {
  // Constructor
  function of_select_typ_dokumentu($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    //    $this->options[] = array('value' => "X", 'label' => "Město ".$GLOBALS["CONFIG"]["MESTO"]);
    $this->options[] = array('value' => "A", 'label' => "analogový dokument");
    $this->options[] = array('value' => "D", 'label' => "digitální dokument");
    
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_typ_spisu extends of_select {
  // Constructor
  function of_select_typ_spisu($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    //    $this->options[] = array('value' => "X", 'label' => "Město ".$GLOBALS["CONFIG"]["MESTO"]);
    $this->options[] = array('value' => "A", 'label' => "analogově");
    $this->options[] = array('value' => "D", 'label' => "digitálně");
    $this->options[] = array('value' => "H", 'label' => "hybridně");
    
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_typ_ukladaciznacka extends of_select {
  // Constructor
  function of_select_typ_ukladaciznacka($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => "bez rozlišení");
    //    $this->options[] = array('value' => "X", 'label' => "Město ".$GLOBALS["CONFIG"]["MESTO"]);
    
    $this->options[] = array('value' => "L", 'label' => "lokační: misto, ves");
    $this->options[] = array('value' => "M", 'label' => "lokační: Praha, Plzeň, Brno, Ostrava");
    $this->options[] = array('value' => "P", 'label' => "jednotlivá památka 	památka");
    $this->options[] = array('value' => "S", 'label' => "jiná jednotlivá stavba");
    $this->options[] = array('value' => "V", 'label' => "ostatní");
    
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_text_ukladaciznacka extends of_select_db {
  // Constructor
  function of_select_text_ukladaciznacka($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT idznacka,txthled FROM npu_spisuklznac order by txthled");
    $this->init_db();
    
    //    					  "options_sep" => "&nbsp;",
  }
}

class of_select_prava extends of_select {
  function of_select_prava($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->options[] = array('value' => "", 'label' => "");
    $this->options[] = array('value' => "podatelna", 'label' => "za podatelnu");
    //	  $this->options[] = array('value' => "vedouci", 'label' => "za vedoucí");
    //	  $this->options[] = array('value' => "referent", 'label' => "za referenty");
    
  }
}

class of_select_stavy_filtr extends of_select {
  // Constructor
  function of_select_stavy_filtr($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->options[] = array('value' => "", 'label' => "");
    
    
    $stav =  getSelectDataEed(new of_select_status(array()));
    while (list($key,$val)=each($stav))
      $this->options[] = array('value' => $key, 'label' => $val);
      
      //	  $this->options[] = array('value' => "100", 'label' => "uzavřené");
      //	  $this->options[] = array('value' => "102", 'label' => "uzavřené, ale neuložené");
      

      if ($GLOBALS['CONFIG']['NEPRIRAZOVAT_CJ']) $this->options[] = array('value' => "199", 'label' => "bez čj.");
      $this->options[] = array('value' => "200", 'label' => "--- grupované stavy ---", 'add' =>' DISABLED disabled="disabled"' ,'style' => '');
      
      $this->options[] = array('value' => "201", 'label' => "jen příchozí");
      $this->options[] = array('value' => "202", 'label' => "jen odchozí");
      
      //	  $this->options[] = array('value' => "103", 'label' => "zpracované, ale neuzavřené");
      $this->options[] = array('value' => "204", 'label' => "nezpracované");
  	  $this->options[] = array('value' => "144", 'label' => "nezpracované (PŘEDANÉ)");
  	  $this->options[] = array('value' => "145", 'label' => "zpracované (PŘEDANÉ)");
      //	  $this->options[] = array('value' => "105", 'label' => "po lhůtě");
      $this->options[] = array('value' => "206", 'label' => "pozdě vyřízené");
      
      $this->options[] = array('value' => "210", 'label' => "nejsou ve spisu");
      $this->options[] = array('value' => "220", 'label' => "nezpracované spisy a čj");
  }
}

class of_select_dostupnost_souboru extends of_select {
  // Constructor
  function of_select_dostupnost_souboru($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->options[] = array('value' => "", 'label' => "Pro všechny");
    $this->options[] = array('value' => "y", 'label' => "Vyhrazeno");
  }
}

class of_select_adresati_skupina extends of_select {
  // Constructor
  function of_select_adresati_skupina($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->options[] = array('value' => "", 'label' => "");
    if ($a['admin']) $this->options[] = array('value' => "1", 'label' => "globální skupina");
    $this->options[] = array('value' => "2", 'label' => "lokální skupina");
  }
}

class of_select_vnitrni_adresati_skupina extends of_select_db {
  // Constructor
  function of_select_vnitrni_adresati_skupina($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $USER_ID = $USER_INFO['ID'] ? $USER_INFO['ID'] : 0;
    $this->DB_Sql->query("SELECT id, nazev FROM posta_nastaveni_vnitrni_adresati_skupiny where typ=1 or (typ=2 and owner_id=" . $USER_ID . ") ORDER BY typ, nazev");
    $this->init_db();
  }
}

class of_select_vnejsi_adresati_skupina extends of_select_db {
  // Constructor
  function of_select_vnejsi_adresati_skupina($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT id,nazev_skupiny FROM posta_nastaveni_vnejsi_adresati_skupiny ORDER BY nazev_skupiny");
    $this->init_db();
  }
}

class of_select_spisovna_zapujcky_filtry extends of_select {
  // Constructor
  function of_select_spisovna_zapujcky_filtry($a) {
    $this->setup_element($a);
    $this->options = array();
    //    if ($a["insertnull"])
    $this->options[] = array('value' => "50", 'label' => "všecny zápujčky");
    $this->options[] = array('value' => "1", 'label' => "jen vypůjčené");
    $this->options[] = array('value' => "5", 'label' => "jen vrácené");
    $this->options[] = array('value' => "-1", 'label' => "jen smazané");
  }
}

class of_select_zadost_schvaleni extends of_select {
  // Constructor
  function of_select_zadost_schvaleni($a) {
    
    $this->setup_element($a);
    $this->options = array();
    foreach($GLOBALS['CONFIG']['SCHVALOVANI'] as $key => $val) {
      if ($val['ZADOST']<>'') $this->options[] = array('value' => $val['VALUE'], 'label' => $val['ZADOST']);
      
    }
  }
}


class of_select_odpoved_schvaleni extends of_select {
  // Constructor
  function of_select_odpoved_schvaleni($a) {
    
    $this->setup_element($a);
    $this->options = array();
    foreach($GLOBALS['CONFIG']['SCHVALOVANI'] as $key => $val) {
      if ($val['ZADOST']<>'') $this->options[] = array('value' => $val['VALUE'], 'label' => $val['ODPOVED']);
      if ($val['ZADOST']=='' && $val['VALUE']>0) $this->options[] = array('value' => $val['VALUE'], 'label' => $val['ODPOVED']);
      
    }
  }
}


class of_select_pozice_viditelny_podpis extends of_select {
  // Constructor
  function of_select_pozice_viditelny_podpis($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    reset($GLOBALS["CONFIG"]["VIDITELNY_PODPIS"]);
    while (list($key,$val)=each($GLOBALS["CONFIG"]["VIDITELNY_PODPIS"]))
      $this->options[] = array("value"=>$key, "label"=>$val['NAZEV']);
  }
}


class of_select_skartacni_rizeni extends of_select_db {
  // Constructor
  function of_select_skartacni_rizeni($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    //    $this->DB_Sql->query("SELECT id,cj FROM posta_skartace where datum_uzavreni is null and superodbor in (".VratSuperOdbor().")");
    $this->DB_Sql->query("SELECT id,jid || ' - ' || cj FROM posta_skartace where datum_uzavreni is null order by id desc");
    $this->init_db();
  }
}

class of_select_skartacni_rezim extends of_select_db {
  // Constructor
  function of_select_skartacni_rezim($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    //    $this->DB_Sql->query("SELECT id,cj FROM posta_skartace where datum_uzavreni is null and superodbor in (".VratSuperOdbor().")");
    $this->DB_Sql->query("SELECT id,jid || ' - ' || skar_znak || '/' || skar_lhuta FROM posta_cis_skartacni_rezimy order by skar_znak asc, skar_lhuta asc");
    $this->init_db();
  }
}

class of_select_druh_priloh extends of_select {
  // Constructor
  function of_select_druh_priloh($a) {
    $this->setup_element($a);
    $this->options = array();
    //    if ($a["insertnull"])
    $this->options[] = array("value"=>"elektronické", "label"=>"elektronické");
    $this->options[] = array("value"=>"písemné", "label"=>"písemné");
  }
}

class of_select_typ_transakcniho_protokolu extends of_select {
  // Constructor
  function of_select_typ_transakcniho_protokolu($a) {
    $this->setup_element($a);
    $this->options = array();
    //    if ($a["insertnull"])
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"DOC", "label"=>"dokument");
    $this->options[] = array("value"=>"SPIS", "label"=>"spis");
    $this->options[] = array("value"=>"SECURITY", "label"=>"bezpečnost");
    $this->options[] = array("value"=>"SYS", "label"=>"práva,uživatelé");
    $this->options[] = array("value"=>"SPISZNAK", "label"=>"věcné skupiny");
    $this->options[] = array("value"=>"EXPORT", "label"=>"Export");
    $this->options[] = array("value"=>"KONVERZE", "label"=>"Konverze");
  }
}

class of_select_archivni_box extends of_select_db {
  // Constructor
  function of_select_archivni_box($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    if ($a['POSTA_ID']) {
      $ids = EedTools::GetArchivacniBoxy($a['POSTA_ID']);
      if (count($ids)>0) $where = 'AND id not in (' . implode(',', $ids) . ') ';
    }
    if (!HasRole('spravce')) {
      $odbor = VratOdbor();
      if (HasRole('zpracovat-odbor')) {
        $EedUser = LoadClass('EedUser',0);
        $id = GetParentGroup($EedUser->VratOdborZSpisUzlu($odbor));
        if ($id>0) {
          $odbor = $EedUser->VratSpisUzelZOdboru($id);
          $odbor =  $odbor['ID'];
        }
      }
      $where .= ' AND ODBOR in (' . $odbor . ')';
    }
    $this->DB_Sql->query("SELECT id,nazev FROM posta_spisovna_boxy WHERE 1=1 $where ORDER BY nazev asc");
    $this->init_db();
  }
}

class of_select_typovy_spis extends of_select_db {
  // Constructor
  function of_select_typovy_spis($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    
    $user = LoadClass('EedUser', $USER_INFO['ID']);
    $odbor = $user->odbor_id;
    $nadrizene_uzly = $user->VratNadrizeneSpisUzlyZOdboru($odbor);
    
    $where = ' AND (((id_superodbor is NULL or id_superodbor=' . EedTools::VratSuperOdbor().') and odbor is null) OR odbor in (' . implode(', ',array_keys ($nadrizene_uzly)) . '))';
    $this->DB_Sql->query("SELECT id,nazev FROM posta_cis_typovy_spis WHERE 1=1 $where ORDER BY id");
    $this->init_db();
  }
}

class of_select_empty extends of_select {
  // Constructor
  function of_select_empty($a) {
    $this->setup_element($a);
    $this->options = array();
    //    if ($a["insertnull"])
    $this->options[] = array("value"=>"", "label"=>" ");
  }
}


class of_select_nastaveni_kategorie extends of_select {
  // Constructor
  function of_select_nastaveni_kategorie($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"HLAVNI", "label"=>"Hlavní nastavení");
    $this->options[] = array("value"=>"SYS", "label"=>"Bezpečnost");
    $this->options[] = array("value"=>"EPODATELNA", "label"=>"Epodatelna");
    $this->options[] = array("value"=>"DS", "label"=>"Dat. schránka");
    $this->options[] = array("value"=>"PODPIS", "label"=>"modul podepisování");
    $this->options[] = array("value"=>"SCANNER", "label"=>"modul skenování");
    $this->options[] = array("value"=>"EMAILY", "label"=>"nastavení emailů");
  }
}

class of_select_nastaveni_kategorie_parametr extends of_select_db {
  // Constructor
  function of_select_nastaveni_kategorie_parametr($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $where = '';
    if (!$a['kategorie']) $a['kategorie'] = -1;
    if ($a['kategorie']) $where = " and kategorie like '" . $a['kategorie'] . "'";
    $this->DB_Sql->query("SELECT parametr,parametr FROM posta_konfigurace WHERE superodbor is null $where order by kategorie asc, parametr asc");
    $this->init_db();
  }
}

class of_select_nastaveni_typ extends of_select {
  // Constructor
  function of_select_nastaveni_typ($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"text", "label"=>"text");
    $this->options[] = array("value"=>"textarea", "label"=>"textarea");
    $this->options[] = array("value"=>"text_number", "label"=>"number");
    $this->options[] = array("value"=>"pole", "label"=>"pole");
  }
}


class of_select_dokument extends of_select {
  // Constructor
  function of_select_dokument($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
    $this->options[] = array('value' => "P", 'label' => "Příchozí");
    $this->options[] = array('value' => "O", 'label' => "Odchozí");
  }
}

class of_select_nastaveni_pristupy extends of_select {
  // Constructor
  function of_select_nastaveni_pristupy($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->options[] = array('value' => "read", 'label' => "čtení");
    $this->options[] = array('value' => "edit", 'label' => "čtení, editace");
    //    $this->options[] = array('value' => "delete", 'label' => "čtení, editace, storno");
  }
}

class of_select_lokace extends of_select_db {
  // Constructor
  function of_select_lokace($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    if ($a["parent"])
      $parent = "=".$a["parent"];
      else
        $parent = " is null";
        $spisovna = "";
        if ($a["spisovna_id"]>0)
          $spisovna = " spisovna_id=".$a["spisovna_id"]." and ";
          if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");
          $this->DB_Sql->query("select id,nazev from posta_spisovna_cis_lokace where ".$spisovna." id_parent".$parent);
          $this->init_db();
  }
}


class of_select_plugin extends of_select {
  // Constructor
  function of_select_plugin($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->options[] = array('value' => "", 'label' => "");
    foreach ($GLOBALS['CONFIG_POSTA']['PLUGINS'] as $plugin_name => $val) {
      $this->options[] = array('value' => $plugin_name, 'label' => $plugin_name);
    }
  }
}

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/el/of_select_end.inc');
    if (File_Exists($file)) include($file);
  }
}

endif;
