<?php
  require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedSchvalovani.inc');
  $user_obj = new EedUser;

  $podrizene_unity = $user_obj->VratPodrizeneUnity(VratSuperOdbor());
//  print_r($podrizene_unity);
    while (list($key,$val)=each($podrizene_unity))
    {
      $pracovnici=$user_obj->VratPracovnikyVUnite($key);
      if (count($pracovnici)>0)
        $pracovnici_pode_mnou = array_merge($pracovnici,$pracovnici_pode_mnou);
    }
    $pole = array_flip($pracovnici_pode_mnou);
    while (list($key,$val)=each($pole))
    {
      $users[$key]=$user_obj->GetUserNameByLNAME($key);
    }
    asort($users);//6200126 Klime3
//   print_r($users);
   //$q->query($sql);
  $sql_select=stripslashes($GLOBALS['TABLE_SELECT']);
  if (HasRole('spisovna')||HasRole('spisovna-odbor')||HasRole('spravce') && !$GLOBALS['SKARTACNI_RIZENI_ID'])
  {
    $show="<table width='100%'><td>   <div class=\"form dark-color\"> <div class=\"form-body\"> <div class=\"form-row\">
    <h1>Zapůjčení ze spisovny:</h1>";
    //$show.="<form action='../../../output/pdf/spisovna_zapujcka.php' method='post' target=protokol><input type='hidden' name='sql' value=\"".$sql_select."\">";
    //$show.="<input type='submit' name='' value='Vytisknout zápujční protokol' class='btn'></form>";
    $show.="<form action='../zapujcky/zaloz.php' method='post' onsubmit='insertIds(this);'><input type='hidden' name='sql' value=\"".$sql_select."\"><input type='hidden' name='spisovna_id' value=\"".$GLOBALS['SPISOVNA_ID']."\">";
    $show.="Vyberte komu: <select name='komu'>";
//    $show.="<option value='0'>odebrat ze spisovny</option>";
    while (list($key,$val)=each($users))
    {
      $show.="<option value='".$key."'>".$val."</option>";
    }
    $show.="</select>";
    $show.="<input type='submit' name='' value='Vytvořit zápůjčku' class='btn'></form></div></div></div>";


    $show.="<table width='100%'><td>   <div class=\"form darkest-color\"> <div class=\"form-body\"> <div class=\"form-row\">
    <h1>Předání do jiné spisovny:</h1>";
    //$show.="<form action='../../../output/pdf/spisovna_zapujcka.php' method='post' target=protokol><input type='hidden' name='sql' value=\"".$sql_select."\">";
    //$show.="<input type='submit' name='' value='Vytisknout zápujční protokol' class='btn'></form>";
    $show.="<form action='predat.php' method='post' onsubmit='insertIds(this);'><input type='hidden' name='sql' value=\"".$sql_select."\">";
    $spisovna = getSelectDataEed(new of_select_spisovna(array()));

    $show.="Vyberte spisovnu: <select name='predat_spisovna'>";
//    $show.="<option value='0'>odebrat ze spisovny</option>";
    while (list($key,$val)=each($spisovna))
    {
      $show.="<option value='".$key."'>".$val."</option>";
    }
    $show.="</select>";
    $show.="<input type='submit' name='' value='Předat do spisovny přímo' class='btn'></form>";
    $show .="<p>nebo</p>";
    $show.="<form action='predat_delimitace.php' method='post' onsubmit='insertIds(this);'><input type='hidden' name='sql' value=\"".$sql_select."\">";
    $show.="Vyberte spisovnu pro převod protokolem:<br/><select name='predat_spisovna'>";
//    $show.="<option value='0'>odebrat ze spisovny</option>";
    reset($spisovna);
    $spisovna = getSelectDataEed(new of_select_spisovna(array('add_main'=>true)));

    while (list($key,$val)=each($spisovna))
    {
      $show.="<option value='".$key."'>".$val."</option>";
    }
    $show.="</select><br/>";
    $show.="<input type='submit' formaction='../../../output/pdf/delimitace.php'  formtarget=protokol name='' value='Náhled protokolu' class='btn' onsubmit='insertIds(this);'>
    &nbsp;&nbsp;&nbsp;<input type='submit' formaction='../../../output/pdf/delimitace.php?tisk=1'  formtarget=protokol name='' value='Vytisknout protokol' class='btn' onsubmit='insertIds(this);'>";
    $show .="<br/>&nbsp;a&nbsp;poté&nbsp;<input type='submit' name='' value='Uvolnit dokumenty pro předání' class='btn'>";
    $show.="</form>";

    $show .="</div></div></div>";

    //if ($je_spisovna)
    {
      $show.="</td><td>
         <div class=\"form darkest-color\"> <div class=\"form-body\"> <div class=\"form-row\">
          <h1>Archivace a skartace:</h1>";
      $show.="<form action='rizeni.php' method='post' onsubmit='insertIds(this); '><input type='hidden' name='sql' value=\"".$sql_select."\">";
      $show.="<input type='submit' name='' value='Zahájit skartační řízení' class='btn'></form>nebo";


      $rizeni = getSelectDataEed(new of_select_skartacni_rizeni(array()));
      if (count($rizeni)>0) {
        $show.="<form action='rizeni.php' method='post' onsubmit='insertIds(this); '><input type='hidden' name='sql' value=\"".$sql_select."\"><select name='rizeni_id'>";
        foreach($rizeni as $key => $val) $show.="<option value='$key'>$val</option>";
        $show.="</select><input type='submit' name='' value='Přidat do existujícího řízení' class='btn'></form>";
      }

      $show.="</div></div></div>";
    }
  }
  $show.="</td></table>";
