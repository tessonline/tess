<?php
//echo "Jsme tam";
//echo $jmeno;


$where=" AND (ODESL_PRIJMENI ILIKE '%".$jmeno."%')";
//$where.=" AND u.ulice_kod = a.ulice_kod";
//$where.=" AND (odesl_adrkod<>'')";
$where.=" AND (frozen!='A' or frozen IS NULL)";

If (HasRole('spravce'))
{ 
Table(array(
 "agenda" => "POSTA_SEZNAMY_FIRMY", 
 "schema_file" =>"ost/posta/services/spisovka/firmy/.admin/table_schema.inc",
 "sql"=>"select * from posta where odesl_prijmeni ilike '%".$jmeno."%' order by id",
 "showselect"=>true, 
 "showedit"=>false, 
 "appendwhere"=>$where,
 "showdelete"=>false, 
 "showguide"=>true, 
 "showinfo"=>false,
 "showhistory"=>false,
 "setvars"=>false,
//"select_id"=>"ID",
 "unsetvars"=>false,
 "nopaging"=>true,
 "action"=>"guide/posta_firmy/page2.inc"
));

}
else
{
//echo $where;
Table(array(
 "agenda" => "POSTA_SEZNAMY_FIRMY", 
 "schema_file" =>"ost/posta/services/spisovka/firmy/.admin/table_schema.inc",
 "showselect"=>true, 
 "showedit"=>false, 
 "appendwhere"=>$where,
 "showdelete"=>false, 
 "showguide"=>true, 
 "showinfo"=>false,
 "showhistory"=>false,
 "setvars"=>false,
//"select_id"=>"ID",
 "unsetvars"=>false,
 "nopaging"=>true,
 "action"=>"guide/posta_firmy/page2.inc"
));

}



?>
