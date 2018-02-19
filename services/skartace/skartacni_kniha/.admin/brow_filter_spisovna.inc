<?php
include_once(FileUp2(".admin/oth_funkce_2D.inc"));

if ((!$GLOBALS['SET_SPISOVNA_ID'])&&($GLOBALS['omez_zarizeni'])) {
  unset($_SESSION['SESSION_SPISOVNA_ID']);
}

if ($GLOBALS['SPISOVNA_ID']&&!$GLOBALS['omez_zarizeni']) {
  $_SESSION['SESSION_SPISOVNA_ID'] = $GLOBALS['SPISOVNA_ID'];
  $q = new DB_POSTA;
  $sql = "SELECT superodbor FROM posta_cis_spisovna where id=".$GLOBALS['SPISOVNA_ID'];
  $q->query($sql);
  $q->next_record();
  $GLOBALS['omez_zarizeni'] = $q->Record['SUPERODBOR'];
}



if (HasRole('access_all')) {
  $spisovny = getSelectDataEed(new of_select_spisovna(array("superodbor"=>"null")));   
  include_once(FileUp2('.admin/brow_superodbor.inc'));
  //include_once(FileUp2('.admin/brow_superodbor.inc'));
    
  if ($GLOBALS['omez_zarizeni']) {
    $spisovny = getSelectDataEed(new of_select_spisovna(array("superodbor"=>$GLOBALS['omez_zarizeni'])));
  }
} else {
  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();  
  $spisovny = getSelectDataEed(new of_select_spisovna(array("superodbor"=>$USER_INFO["PRACOVISTE"])));
}
//$spisovny = getSelectDataEed(new of_select_spisovna(array()));

if ($GLOBALS['SET_SPISOVNA_ID']) {
  $_SESSION['SESSION_SPISOVNA_ID'] = $GLOBALS['SET_SPISOVNA_ID'];
}

if ($GLOBALS['VYHLEDAVANI'] == 1) UNSET($_SESSION['SET_SPISOVNA_ID']);
if ($GLOBALS['PREDANI'] == 1) UNSET($_SESSION['SESSION_SPISOVNA_ID']);

$GLOBALS['SPISOVNA_ID'] = $_SESSION['SESSION_SPISOVNA_ID'];
if (count($spisovny)>1) {

  if (HasRole('spisovna') && !$GLOBALS['SPISOVNA_ID']) $GLOBALS['SPISOVNA_ID'] = key($spisovny);
  echo '<div class="form dark-color"> <div class="form-body"> <div class="form-row">';

  foreach ($spisovny as $spisovna_id => $spisovna) {
  //    echo '<div><input type="button" value="' . $spisovna . '" onclick="document.location.href=\'brow.php?SET_SPISOVNA_ID=' . $spisovna_id . '\'" class="btn">&nbsp;';
      echo '<a href="brow.php?SET_SPISOVNA_ID=' . $spisovna_id . '&omez_zarizeni='.$GLOBALS['omez_zarizeni'].'" class="'.($GLOBALS["SPISOVNA_ID"]==$spisovna_id?'':'btn').'">' . $spisovna . '</a>&nbsp;';
  }
}
else {
  foreach ($spisovny as $spisovna_id => $spisovna) {
  }
}

if (HasRole('spisovna-odbor')) $GLOBALS['SPISOVNA_ID'] = $spisovna_id;

echo '</div> </div> </div>';


echo "</form></p>";



