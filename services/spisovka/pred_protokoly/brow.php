<?php
session_start();
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/upload_.inc"));
require(FileUp2(".admin/has_access.inc"));
include_once(FileUp2(".admin/security_.inc"));
include_once(FileUp2(".admin/security_name.inc"));
require(FileUp2("html_header_full.inc"));

$uplobj=Upload(array('create_only_objects'=>true,'noshowheader'=>true));


$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

$GLOBALS['TYP_POSTY']=$GLOBALS['CONFIG']['REZERVACE_TYP_POSTY'];

//if (HasRole('podatelna'))
//  $GLOBALS['SUPERODBOR']=VratSuperOdbor();
//else
  $GLOBALS['REFERENT']=$rezervace_id;

$GLOBALS["ODESLANA_POSTA"]='t';
$count = Table(array(
         "appendwhere"=>$where,
         "showdelete"=>true, 
         "showedit"=>true,
         "showinfo"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
         "showexportall"=>true,
  	     "setvars"=>true,
));

require(FileUp2("html_footer.inc"));
