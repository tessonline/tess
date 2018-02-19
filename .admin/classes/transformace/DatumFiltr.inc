<?php

class DatumFiltr {

  /*
   * @author luma
   */

  private $day;
  private $month;
  private $year;
  
  function __construct() {
    $time = time();
    $this->day = date('d',$time);
    $this->month = date ('m',$time);
    $this->year = date('Y',$time);
  }
  
  private function createTimeFromDateText($date_text) {
    try {
      $d_arr = split('[/.-]',$date_text);
      $new_date_text = $d_arr[1]."/".$d_arr[0]."/".$d_arr[2];
      $time = strtotime($new_date_text);
      return $time;
    }
    catch (Exception $e){
      return false;
    }
  }

  /*
   * Je-li vstupem datum, vrací nezměněné datum, je-li vstupem text +-NY, vrací datum s odečteným/přičteným počtem N dnů (Y=D) nebo N měsíců (Y=M) nebo N roku (Y=Y)
   */
  public function transform($date_text,$curr_time=false){
    if ($date_text=='') return '';
    $date_text = str_replace("*","",$date_text);
    $match = preg_match("/^[\+\-]*[0-9]+[dmyrDMYR]/", $date_text);
    //if ((DateTime::createFromFormat('d.m.Y', $date_text) === FALSE)&&($match==1)){
    if (($this->createTimeFromDateText($date_text) === FALSE)&&($match==1)){
      $dmy = strtolower($date_text[strlen($date_text) - 1]);
      $add = substr($date_text, 0,strlen($date_text) - 1);
      $add_day = 0;
      $add_month = 0;
      $add_year = 0;
      switch ($dmy) {
        case 'd':
          $add_day = $add;
          break;
        case 'm':
          $add_month = $add;
          break;
        case 'y' or 'r':
          $add_year = $add;
          break;
      }
      $timestamp = mktime(0, 0, 0, $this->month+$add_month, $this->day+$add_day, $this->year+$add_year);
      $time_text = "";
      if ($curr_time) $time_text = " ".date('G:i:s');
      return date('d.m.Y',$timestamp).$time_text;
    } 
    else
      return $date_text;
  }

}