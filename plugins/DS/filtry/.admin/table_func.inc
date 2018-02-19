<?php
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

function getSelectData($select) {
  $result = array();
  if (is_object($select)) {
    $options = $select->options;
    if (is_array($options)) {
      foreach ($options as $option) {
        if (trim($option["value"])) {
          $result[$option["value"]] = $option["label"];
        }
      }
    }
  }
  return $result;
}

function selectVita($value) {
  static $select;
  if (!isset($select)) $select = getSelectData(new of_select_vita(array()));
  return ($select[$value]);
}

function getDmItemLabel($value) {
  global $config;
  return $config['POSTA_DS_FILTRY']['DM_ITEMS'][$value]['label'];
}

function ShowDmItem($value) {
  $res = str_replace('|','| ',$value);
  return $res;
}
