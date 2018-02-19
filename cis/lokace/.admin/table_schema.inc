<?php
if(!function_exists("ChangeClassBarva")) {
  Function ChangeClassBarva($t) {
  //staci pustit to zaremovany a barvi se cely radek....
    If (!$GLOBALS["AKTIVNI"]==1) $t->classname="gray_line";
    else 
    {
     static $i=1;
      if ($i):
        $t->classname = "brow".$color;
        $i = 0;
      else:
        $t->classname = "browdark".$color;
        $i = 1;
      endif;
    
    }
        
    
  }
}
$TABLE_CONFIG["callback"]="ChangeClassBarva";

$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Název", 'width' => '20%');
$TABLE_CONFIG["schema"][] =  array( "field"=>"PLNA_CESTA", "label"=>"Cesta", 'width' => '80%');