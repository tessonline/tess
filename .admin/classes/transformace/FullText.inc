<?php

include_once('Transformace.inc');

class FullText extends Transformace{

  private $replace;

  /*
   * Contructor
   * @author luma
   */
  
  private function init() {
    $this->replace = array (
      "  " => " ",
      ")A" => ") A",
      ")O" => ") O",
      "D(" => "D (",
      "R(" => "R (",
      "T(" => "T (",
      " AND NOT " => "&!",
      " OR NOT " => "|!",
      " AND " => "&",
      " OR " => "|",
      " NOT " => "!",
      "NOT " => "!",
      " " => "&",
      "(" => "(",
      ")" => ")",
      "*" => ":*",
    );
    
  }
  
  /*
   * Transformuje výraz fulltextu obsahující logické výrazy na syntaxe výrazu fulltextu v Postgressu
   * @param string $text_fulltext - výraz fulltextu obsahující logické výrazy (AND, OR, XOR, NOT, *)
   * @return string syntaxe výrazu fulltextu v Postgressu
   */
  public function transform($text_fulltext) {
    $this->init();
    $text_fulltext = str_replace('  ',' ',$text_fulltext);
    $text_fulltext = $this->xor_func($text_fulltext);
    foreach ($this->replace as $key => $value) {
      $text_fulltext = str_ireplace($key,$value,$text_fulltext);
    }
    return $text_fulltext;
  }
  
}