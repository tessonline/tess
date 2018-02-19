<?php
include_once(FileUp2("$path_posta/.admin/javascript.inc"));
if ($GLOBALS['LOKACE_ID'] > 0) $GLOBALS['LOKACE_TEXT'] = EedTools::GetLokace($GLOBALS['LOKACE_ID']);

$FORM_CONFIG['schema'][] = array('elements'=>array(
	array( "type"=>"text", "name"=>"LOKACE_TEXT", 'size'=>80, 'add'=>'id="txtAuto"','label'=>'Fyzická lokace'),
    array( "type"=>"hidden", "name"=>"LOKACE_ID", 'add'=>'id="LokaceId"')
),

"label"=>"Lokace ve spisovně:");

   $FORM_CONFIG['schema'][] = array('elements'=>array(
     array( 
       "type"=>"select_lokace", 
       "name"=>"LOKACE_SELECT", 
       'add'=>'onChange="zmenaLokace(this);"',
       'label'=>'Výběr lokace ve spisovně:',
       'spisovna_id' => !$is_multiedit ? $GLOBALS['spisovna'] : 0,
       "insertnull"=>true,
      ),
     ),
     "label"=>"Výběr lokace ve spisovně:");
                    