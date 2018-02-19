<?php

class Transformace {
  
  public $charset;

  /*
   * Contructor
   * @author luma
   */
  function __construct($charset) {
      $this->charset = $charset;
  }

  /*
   * Prevadi nalezene vyrazy X XOR Y v retezci na ((X OR Y) AND (NOT X OR NOT Y))
   */
  public function xor_func($text_fulltext) {
    //EXCLUSIVE OR
    $xor = true;
    while ($xor==true) {
      $xor_array = preg_split('[() ]',$text_fulltext);
      $xor_pos = array_search('XOR', $xor_array);
      if ($xor_pos===false) $xor_pos = array_search('xor', $xor_array);
      if ($xor_pos===false) $xor = false; else
      {
        //((Markvart* XOR Luboš) OR (Ondřej XOR Mal*)) AND CDMS
        $fulltext_len = mb_strlen($text_fulltext,$this->charset);

        foreach ($xor_array as &$xor_item) {
          $xor_item = str_replace(array('(',')'),'',$xor_item);
        }

        $before_xor_pos = mb_strpos(mb_strtolower($text_fulltext,$this->charset),'xor',0,$this->charset)-mb_strlen($xor_array[$xor_pos-1],$this->charset)-1;
        $before_xor = mb_substr($text_fulltext, 0,$before_xor_pos,$this->charset);

        $p1 = mb_strpos(mb_strtolower($text_fulltext,$this->charset),'xor',0,$this->charset);
        $p2 = mb_strlen($xor_array[$xor_pos+1],$this->charset);
        $behind_xor_pos = $p1+$p2+4;
        $behind_xor = mb_substr($text_fulltext, $behind_xor_pos,$fulltext_len-$behind_xor_pos,$this->charset);

        $xor_fulltext = '(('.$xor_array[$xor_pos-1].' OR '.$xor_array[$xor_pos+1].') AND (NOT '.$xor_array[$xor_pos-1].' OR NOT '.$xor_array[$xor_pos+1].'))';
        $text_fulltext = $before_xor.$xor_fulltext.$behind_xor;
      }
    }
    return $text_fulltext;
  }

}