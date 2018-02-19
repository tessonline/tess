<?php
//require_once($GLOBALS['TMAPY_DIR'] . '/.admin/adapter/Prime/TW_FormAdapter.inc');
//require_once($GLOBALS['TMAPY_DIR'] . '/.admin/adapter/Theme/TW_ThemeTemplate.inc');


$is_multiedit = In_Array($form_params["formtype"], array($f_editall));


reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/plugins/schvalovani/.admin/form_schema_start.inc');
		if (File_Exists($file)) include($file);
  }
}


//require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedSchvalovani.inc');
$USER_INFO = $GLOBALS['POSTA_SECURITY']->GetUserInfo(); 

$postup_tooltip = '<br/><p>Pokud je toto pole zaškrtnuto, mohou se k dané věci vyjadřovat všichni najednou. <p/><p>Pokud pole není zaškrnuto, probíhá schvalovací proces po jednotlivých lidech tak, jak jsou zadáni.</p>';
$postup = array('&nbsp;&nbsp;po sobě' => '1', '&nbsp;&nbsp;všichni najednou' => '2');

if (!$FORM_CONFIG)
$FORM_CONFIG = array(
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'columns' => true
      ),
    )
  )
);


If ((JeVeSchvaleni($GLOBALS[POSTA_ID],$USER_INFO['ID']) || JeKPodpisu($GLOBALS[POSTA_ID],$USER_INFO['ID'])) && _JsemNaRade($GLOBALS['POSTA_ID'], $USER_INFO['ID']))  {
  

  if (JeVeSchvaleni($GLOBALS[POSTA_ID],$USER_INFO['ID'])) {
    foreach($GLOBALS['CONFIG']['SCHVALOVANI'] as $key => $val) {
      if ($val['VALUE']>0 && $val['VALUE']<10) $options[$val['ODPOVED']] = $val['VALUE'];
    }
  }
  
  if (JeKPodpisu($GLOBALS[POSTA_ID],$USER_INFO['ID'])) {
    foreach($GLOBALS['CONFIG']['SCHVALOVANI'] as $key => $val) {
      if ($val['VALUE']>10 && $val['VALUE']<20) $options[$val['ODPOVED']] = $val['VALUE'];
    }
  }
  
  foreach($GLOBALS['CONFIG']['SCHVALOVANI'] as $key => $val) {
    if ($val['VALUE']==0) $options[$val['ODPOVED']] = $val['VALUE'];
  }

  $GLOBALS['SCHVALENO'] = '0';
  
  $FORM_CONFIG['schema'][] = array(   
            'label'=>'<span class="caption">Moje stanovisko:</span>');		


  $FORM_CONFIG['schema'][] = array(
    'elements'=>array(
      array( 
        'type'=>'select_odpoved_schvaleni',
        'options' => $options,
        'insertnull' => true,
        'name'=>'SCHVALENO', 
      )
    ),
    'label'=>'Dokument:'
  );	

  $FORM_CONFIG['schema'][] = array(
    'elements'=>array(
      array( 
        'type'=>'text', 
        'name'=>'POZNAMKA2',
        'size'=>50
      ),
    ),
    'label'=>'Komentář:'
  );
  



  UNSET($GLOBALS['SCHVALENO']);
  UNSET($GLOBALS['SCHVALUJICI_ID']);
}



$FORM_CONFIG['schema'][] = array(
  'label' => 'Přidání dalšího schvalovatele:',
  'visible' => !$is_multiedit,
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'column' => 1,
      )
    )
  )
);


//$schval_obj = new Eed_schvalovani_object;
$schval_obj = LoadClass('EedSchvalovani');
$schvalujici_prednastaveno = '';


$GLOBALS['POSTUP'] = $schval_obj->getPostupSchvalovani($GLOBALS['POSTA_ID']);
if ($GLOBALS['POSTUP'] == 2) $GLOBALS['POSTUP_ANO'] = 1;

$GLOBALS['ODBOR']=VratOdbor();

$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    
array( 'type'=>'hidden', 'name'=>'DATUM_ZALOZENI', 'value'=>Date('d.m.Y H:i:s')),

array( 'type'=>'hidden', 'name'=>'POSTA_ID'),
array( 'type'=>'hidden', 'name'=>'MOJE_ID', 'value'=>$USER_INFO['ID']),
array( 'type'=>'hidden', 'name'=>'MULTIEDIT', 'value'=>$is_multiedit)
    ));

$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array( 'type'=>'hidden', 'name'=>'POSTA_IDS', 'value'=> implode(',' , $GLOBALS['POSTA_ID'])),
  ),
  'visible' => $is_multiedit,
);


    $FORM_CONFIG['schema'][] = array('elements'=>array(
              array( 'type'=>'select_referent', 'name'=>'SCHVALUJICI_ID','insertnull'=>true,'select_full'=>$pracovnici,'label'=>'Předvybraní:'),
//              array( "type"=>"text", "name"=>"SCHVALUJICI_TEXT", 'size'=>50, 'add'=>'id="txtAuto"','label'=>'Vyhledání jménem'),
              array( 'type' => 'button', 'name' => 'Adresar', 'value' => 'Nade mnou', 'onclick' => 'ZmenReferenty(1);', 'label' => 'Nade mnou', 'tooltip' => 'test'),
              array( 'type' => 'button', 'name' => 'Adresar2', 'value' => 'Všichni', 'onclick' => 'ZmenReferenty(2);', 'label' => 'Všichni', 'tooltip' => 'test'),
              ),
//              "format"=>"'<td class=\"inputblock\">Výběr schvalovatele:<br/><div id=\"schvalovatel\">'...SCHVALUJICI_ID...'</div><input type=\"button\" onclick=\"ZmenReferenty(1);\" value=\"Zobrazit všechny nade mnou\" class=\"button\">&nbsp;<input type=\"button\" onclick=\"ZmenReferenty(2);\" value=\"Zobrazit všechny \" class=\"button\"></td><td>$schvalujici_prednastaveno</td></table>'",
//              "format"=>"'Výběr schvalovatele:<br/><table width=\"10\" border=0><tr><td><div id=\"schvalovatel\">'...SCHVALUJICI_ID...'</div></td><td>nebo&nbsp;vyhledat:&nbsp;'...SCHVALUJICI_TEXT...'</td></tr><tr><td colspan=2></table></td><td>$schvalujici_prednastaveno'",
  //            "visible"=>$is_edit or $is_info or $is_insert ,
              "label"=>"Schvalující:",
              'visible' => !$is_multiedit,
      
    );


    $FORM_CONFIG['schema'][] = array('elements'=>array(
//              array( 'type'=>'select_referent', 'name'=>'SCHVALUJICI_ID','insertnull'=>true,'select_full'=>$pracovnici,'label'=>'Předvybraní:'),
              array( "type"=>"text", "name"=>"SCHVALUJICI_TEXT", 'size'=>50, 'add'=>'id="txtAuto"','label'=>'Vyhledání jménem'),
//              array( 'type'=>'hidden', 'name'=>'DATUM_ZALOZENI', 'value'=>Date('d.m.Y H:i:s')),
//              array( 'type'=>'hidden', 'name'=>'POSTA_ID'),
//              array( 'type'=>'hidden', 'name'=>'MOJE_ID', 'value'=>$USER_INFO['ID']),
              ),
//              "format"=>"'<td class=\"inputblock\">Výběr schvalovatele:<br/><div id=\"schvalovatel\">'...SCHVALUJICI_ID...'</div><input type=\"button\" onclick=\"ZmenReferenty(1);\" value=\"Zobrazit všechny nade mnou\" class=\"button\">&nbsp;<input type=\"button\" onclick=\"ZmenReferenty(2);\" value=\"Zobrazit všechny \" class=\"button\"></td><td>$schvalujici_prednastaveno</td></table>'",
//              "format"=>"'Výběr schvalovatele:<br/><table width=\"10\" border=0><tr><td><div id=\"schvalovatel\">'...SCHVALUJICI_ID...'</div></td><td>nebo&nbsp;vyhledat:&nbsp;'...SCHVALUJICI_TEXT...'</td></tr><tr><td colspan=2></table></td><td>$schvalujici_prednastaveno'",
  //            "visible"=>$is_edit or $is_info or $is_insert ,
              "label"=>"Schvalující:",
              'visible' => !$is_multiedit,
      
    );


    $FORM_CONFIG['schema'][] = array('elements'=>array(
              array( 'type'=>'text', 'name'=>'POZNAMKA','size'=>50),
              ),
  //            'visible'=>$is_edit or $is_info or $is_insert ,
              'label'=>'Poznámka:',
              'visible' => !$is_multiedit,
      );

    $options_typ = array();
    foreach($GLOBALS['CONFIG']['SCHVALOVANI'] as $key => $val) {
      if ($val['ZADOST']<>'') $options_typ[$val['ZADOST']] = $val['VALUE'];
    }
    $FORM_CONFIG['schema'][] = array('elements'=>array(
             array( 
                  'type'=>'select_zadost_schvaleni',
                  'name'=>'TYPSCHVALENI', 
            ),
          ),
          'label'=>'Žádám o:',
          'visible' => !$is_multiedit,
             );	

              
    $FORM_CONFIG['schema'][] = array('elements'=>array(
              array( 'type'=>'checkbox', 'name'=>'KOPIE'),
              ),
              'visible'=>!JeVeSchvaleni($GLOBALS[POSTA_ID]) && $GLOBALS['CONFIG']['SCHVALOVANI_TAKE_JA'] &&!$is_multiedit,								 
              'label'=>'Jsem také schvalující:');			
              

    $FORM_CONFIG['schema'][] = array('elements'=>array(
             array( 
                  'type'=>'checkbox', 
                  'name'=>'POSTUP_ANO', 
                  'tooltip'=>$postup_tooltip
            ),
          ),
          'label'=>'Předložit všem najednou:',
          'visible' => !$is_multiedit,
             );	
             							   
  $reditel = $schval_obj->NajdiRediteleVPracovisti(EedTools::VratSuperOdbor());
  $schvalujici = $schval_obj->VraSeznamKdoMaSchvalit($USER_INFO['ID']);

  if ($reditel>0) $schvalujici[] = $reditel;

  if (count($schvalujici)>0&&!$is_multiedit) {


    $FORM_CONFIG['schema'][] = array(
      'label' => 'Předvybraní:',
    );


//    $schvalujici_prednastaveno='<span class=\'caption\'>Předvybraní schvalovatelé:</span>';
    $schvalujici_prednastaveno = '<span class="caption">Předvybraní:</span>';
    while (list($key,$val)=each($schvalujici))
      if ($val<>$USER_INFO['ID']) {
        $checkbox = "PREDVYBRANY_ID_$val";
    $FORM_CONFIG['schema'][] = array('elements'=>array(
              array( "type"=>"checkbox", "name"=>$checkbox, 'size'=>30, 'label'=>$schval_obj->GetUserName($val))),
              "label"=>$schval_obj->GetUserName($val),
          );


      }
  }
  
  $FORM_CONFIG['schema'][] = '&nbsp;';
  
  
  $FORM_CONFIG['schema'][] = array(
    'sysident' => 'buttons',
    'elements'=>array(
            array( 'type' => 'button', 'name' => '____', 'value' => 'Uložit', 'onclick' => 'submitForm();'),
            array( 'type' => 'button', 'name' => '__', 'value' => 'Uložit a zavřít', 'onclick' => 'closeForm();'),
    ),
    'visible' => !$is_multiedit,
    'label' => '&nbsp;',
    'format' => "____...'&nbsp;&nbsp;'...__",
    'span' => true,
    'class' => array(
      'right',
      'right',
    ),
    
  );
  
  
  
if ($is_multiedit) 
  require_once (FileUp2("interface/podepsani602/.admin/form_schema_hromadny_podpis.inc"));  

echo '
<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>
<script language="JavaScript" type="text/javascript">
<!--

function submitForm() {
  $("form[name=\'frm_edit\']").submit();
}
    
function closeForm() {
  var input = $("<input>")
               .attr("type", "hidden")
               .attr("name", "CLOSE_ON_SUBMIT").val("true");
  $("form[name=\'frm_edit\']").append($(input));
  $("form[name=\'frm_edit\']").submit();
}

function ZmenReferenty(co)
{
  newwindow = window.open(\'zmen.php?co=\'+co, \'ifrm_get_value\',\'\');
}

//-->
</script>

';

?>
