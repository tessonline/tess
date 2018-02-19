<?php
require("tmapy_config.inc");
include_once(Fileup2(".admin/agenda_func.inc"));
//include(Fileup2(".admin/table_func_mmhk.inc"));
//include(Fileup2(".admin/access_.inc"));
//include(Fileup2(".admin/functions.inc"));
$typ=$GLOBALS["SMER"];

include_once(Fileup2(".admin/db/db_posta.inc"));

//print_R($GLOBALS);
  
If ($GLOBALS["KNIHA"]==1)
{
//  dIE('Jsme tam');
//  include(GetAgendaPath('POSTA',true,false).'/output/pdf/knihaposty.php');
  include(GetAgendaPath('POSTA',false,false).'/output/pdf/knihaposty.php');
}
else
{
  If ($typ=='odchozi')
  {
    include(GetAgendaPath('POSTA',false,false).'/output/pdf/odchozipdf.php');
  }
  If ($typ=='prichozi')
  {
    include(GetAgendaPath('POSTA',false,false).'/output/pdf/prichozipdf.php');
  }
  If ($typ=='dorucovatel')
  {
    include(GetAgendaPath('POSTA',false,false).'/output/pdf/dorucovatelpdf.php');
  }
}
/*
if (Access()):
//  include(Fileup2("vzor_dok/dokument_dbhead.inc"));
  include(Fileup2("vzor_dok/dokument_head.inc"));
  include(Fileup2("vzor_dok/dokument_body_".$typ.".inc"));
  include(Fileup2("vzor_dok/dokument_foot.inc"));
else:
  include(FileUp2(".admin/properties.inc"));
  include(FileUp2("html_error.inc"));
endif;

*/

//echo "hotovo";
?>
