<?php

$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom));
$is_multiedit = In_Array($form_params["formtype"], array($f_editall));

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"NAZEV"),
                   ),
                   "label"=>"Název:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"ZKRATKA"),
                   ),
                   "label"=>"Zkratka:");

$FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true),
          ),
          "label"=>$GLOBALS["CONFIG"]["NAZEV_ODBOR"]);

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"VEC"),
                   ),
                   "label"=>"Věc:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vita", "name"=>"STAV","insertnull"=>true)
              ),
              "label"=>"Kde se vyřizuje:");


$FORM_CONFIG["schema"][] = array("elements"=>array(
          array(
            "type"=>"select_typ_posty",
            "name"=>"TYP_POSTY",
            "insertnull"=>true,
            "label"=>"Druh dokumentu",
          ),
        )
  );


 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"LHUTA","size"=>"5","frozen"=>$frozen_ref,"label"=>"Lhůta"),
            ),
            "label"=>"Lhůta k vyřízení:",
            // zruseni format pro tema square
    );
   $FORM_CONFIG["schema"][] = array(
     "elements"=>array(array(
       "type"=>"select_vyrizeno",
       "name"=>"VYRIZENO",
       "insertnull"=>true,
//       "frozen"=>!(HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')||HasRole('zpracovatel')),
       "disabled_onoff"=>$is_multiedit,
       'size' => 20,
//       'maxlength' => 100
     )),
     "visible"=>$is_edit or $is_info or $is_insert or $is_multiedit,
     "label"=>"Způsob vyřízení:"
   );

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"DATUM_VYRIZENI"),
                   ),
                   "label"=>"Zapsat datum vyřízení:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"SPIS_VYRIZEN"),
                   ),
                   "label"=>"Uzavřít záznam:");


$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_skartace", "name"=>"SKARTACE","insertnull"=>true),
                   ),
                   "label"=>"Spisový znak:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"AKTIVNI"),
                   ),
                   "label"=>"Aktivní:");

  $FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"hidden", "name"=>"NOVAHODNOTA", "value"=>1),

                   ),
                   "visible" => $is_insert,
                   "label"=>"");

if ($is_edit) {
  $sql="select * from posta_deniky_".$GLOBALS['EDIT_ID']."_seq";
  $q->query($sql); $q->Next_Record(); $aktualni=$q->Record[LAST_VALUE];
  if ($aktualni==1) $GLOBALS['AKTUALNI'] = 1; else $GLOBALS['AKTUALNI'] = $aktualni;


  $FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"AKTUALNI", "frozen"=>true),
                   ),
                   "label"=>"Aktuální hodnota, kterou dostane další záznam:");

  $FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"NOVAHODNOTA"),
                   ),
                   "label"=>"Nová hodnota (pokud chcete nastavit jinou):");
}

/*
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_odbor", "name"=>"ODBOR")),
                   "label"=>"Odbor:");

*/
?>
