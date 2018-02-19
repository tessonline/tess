<?php 
namespace posta\transformace;

class Datum {
  
  /*
   * @author luma
   */
  
  
  private function validateDate($date, $format = 'Y-m-d H:i:s')
  {
    $res = false;
    $d = \DateTime::createFromFormat($format, $date);
    if ($d) {
      $dat = $d->format($format);
      $res = ($d->format($format) == $date);
    }
    return $res;
  }
  
   
  public function ifDateToUSformat($date_text) {
    $res = $date_text;

        if (self::validateDate($date_text,"d.m.Y")) {        
          $d = \DateTime::createFromFormat("d.m.Y", $date_text);
          $res = $d->format('Y-m-d');
        }
        elseif (self::validateDate($date_text,"j.n.Y")) {
          $d = \DateTime::createFromFormat("j.n.Y", $date_text);
          $res = $d->format('Y-m-d');
        }
        
        elseif (self::validateDate($date_text,"d.m.Y H:i:s")) {
          $d = \DateTime::createFromFormat("d.m.Y H:i:s", $date_text);
          $res = $d->format('Y-m-d H:i:s');
        }
        elseif (self::validateDate($date_text,"j.n.Y H:i:s")) {
          $d = \DateTime::createFromFormat("j.n.Y H:i:s", $date_text);
          $res = $d->format('Y-m-d H:i:s');
        }
        
    return $res;
  }
  
}
  

?>