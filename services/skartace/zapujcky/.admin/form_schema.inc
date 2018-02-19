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

//nadefinujeme potrebne promenne...
if ($is_filter) {
//  include_once(FileUp2(".admin/table_funkce.inc"));
  include('form_schema_filter.inc');
}
else {
  include('form_schema_edit.inc');
}
