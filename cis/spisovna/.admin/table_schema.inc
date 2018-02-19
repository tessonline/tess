<?php
function ShowSkartace($skartace_id)
{
  if ($skartace_id>0)
  {
    $q=new DB_POSTA;
    $sql='select text from cis_posta_skartace where id='.$skartace_id;
    $q->query($sql);
    $q->Next_Record();
    return $q->Record[TEXT];
  }
  else 
    return '&nbsp;';
}

$TABLE_CONFIG["schema"][] =  array( "field"=>"ID", "label"=>"ID");
$TABLE_CONFIG["schema"][] =  array( "field"=>"SPISOVNA", "label"=>"Spisovna");
$TABLE_CONFIG["schema"][] =  array( "field"=>"UkazOdbor(ODBOR)", "label"=>"Spis. uzel");

