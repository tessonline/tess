<?php

if ($GLOBALS['ODES_TYP'] == 'C') {
  $GLOBALS['ODES_TYP'] = 'O';
  if (!$GLOBALS['WHOIS_NUMBER']) $where .= " and whois_number > 0";
  if (!$GLOBALS['WHOIS_IDSTUDIA']) $where .= " and whois_idstudia > 0";
}

NewWindow(array("fname" => "Stitek", "name" => "Stitek", "header" => true, "cache" => false, "window" => "edit"));
