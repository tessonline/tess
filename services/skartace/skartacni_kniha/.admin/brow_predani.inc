<?php
NewWindow(array("fname"=>"Spisovna", "name"=>"spis_pridat", "header"=>true, "cache"=>false, "window"=>"edit"));


//  $GLOBALS['SUPERODBOR']=VratSuperOdbor();
/*
$sql='select * from posta_cis_spisovna order by id';
if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $sql='select * from posta_cis_spisovna where superodbor='.EedTools::VratSuperOdbor().' order by id';
If (HasRole('spisovna-odbor') && !HasRole('spisovna')) {
    $EedUser = LoadClass('EedUser',0);

    //if (HasRole('zpracovat-odbor'))
    {
      $id = GetParentGroup($EedUser->VratOdborZSpisUzlu($odbor));
      if ($id>0) {
        $odbor = $EedUser->VratSpisUzelZOdboru($id);
        $odbor =  $odbor['ID'];
      }
    }


  $sql='select * from posta_cis_spisovna where odbor='.$odbor.' order by id';
//    echo $sql;
}
$q->query($sql);
*/
$show="<table width='100%'><td><h1>Předání do spisovny:</h1>";
$spisovny = getSelectDataEed(new of_select_spisovna(array()));

$pocet = count($spisovny);

if (HasRole('spisovna')||HasRole('spisovna-odbor')||HasRole('spravce')) {

  if ($pocet == 0) {
    $show .= '<p><div class="alert alert-msg darkest-color"> <img class="alert-img" src="'.FileUpImage('images/info').'"> <h4 class="alert-title">POZOR:</h4> <p class="info-msg">
    Máte právo pro předání do spisovny, ale v systému nemáte nadefinovanou spisovnu. Požádejte správce o nápravu.</p> </div> </p>';
  }
  else {
    $show.="<form action='spisovna.php?insert' method='post' onsubmit='insertIds(this); '>
    <div class=\"form darkest-color\"> <div class=\"form-body\"> <div class=\"form-row\">
    <input type='hidden' name='sql' value=\"".$sql_select."\">
    <input type='hidden' name='rucne_vlozene' value=\"".implode(',',$GLOBALS['RUCNE_VLOZENE'])."\">
    Vyberte spisovnu: <select name='spisovna'>";
    //    $show.="<option value='0'>odebrat ze spisovny</option>";
    //   while ($q->Next_Record())
    //     $show.="<option value='".$q->Record['ID']."'>".$q->Record['SPISOVNA']."</option>";
     foreach($spisovny as $id_spisovny => $nazev_spisovny)
       $show.="<option value='".$id_spisovny."'>".$nazev_spisovny."</option>";
    $show.="</select>";
    $show.="<input type='hidden' name='protokol_id' value='".$GLOBALS['ID']."'>";
    $show.="<input type='hidden' name='box' value='".$GLOBALS['SHOW_BOX']."'>";
    //    $show.="<br/>Přičíst počet listů:&nbsp;<input type='text' name='pricist_listy' value='0' size='2'><br/><input type='submit' name='' value='Předat do spisovny' class='btn'></p><p><input type='submit' name='protokol' value='Předat do spisovny na základě protokolu' class='btn'></p></form></td>";
    $show.="
    </div></div></div>
       <div class=\"form dark-color\"> <div class=\"form-body\"> <div class=\"form-row\">
    <input type='submit' name='' value='Předat do spisovny' class='btn'>
    </p></form></td>";
  }
}

// $show.="<form action='../../../output/pdf/spisovna.php' method='post' target=protokol onsubmit='insertIds(this);'>
// <input type='hidden' name='box' value='".$GLOBALS['SHOW_BOX']."'>
// <input type='hidden' name='sql' value=\"".$sql_select."\">";
// $show.="<input type='submit' name='nahled' value='   Náhled protokolu  ' class='btn'>&nbsp;&nbsp;&nbsp;<input type='submit' name='tisk' value='   Vytisknout protokol  ' class='btn'>
// </form></td>";
//
