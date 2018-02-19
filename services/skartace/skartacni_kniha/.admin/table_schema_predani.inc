<?php
  $TABLE_CONFIG["schema"][]= array( field=>"CISLO_SPISU", "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"], width=>"20%","add"=>"NOWRAP");
  $TABLE_CONFIG["schema"][]= array( field=>"VEC", "label"=>"Věc", width=>"50%");
  
  $TABLE_CONFIG["schema"][] =  array( "field"=>"'<b>'...LISTU...'</b><br/>'...PRILOHY", "label"=>"Listy/Přílohy","add"=>"NOWRAP", "width"=>"10%","is_html"=>true);
  $TABLE_CONFIG["schema"][] =  array( "field"=>"'<b>'...DIGITALNE...'</b>'", "label"=>"Dig.","add"=>"NOWRAP", "width"=>"10%","is_html"=>true);
  $TABLE_CONFIG["schema"][] =  array( "field"=>"ZNAK", "label"=>"Skartační znak","add"=>"NOWRAP align=center", "width"=>"10%");
