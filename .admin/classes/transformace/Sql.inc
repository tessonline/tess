<?php
include_once('Transformace.inc');

/*
 * @author luma
 */

class Sql extends Transformace{
  
  private $replace;
 
  /*
   * Provede nahrazeni vyrazu AND OR XOR NOT v SQL prikazu
   */
  public function transform($sql) {
    $len = mb_strlen($sql, $this->charset);
    //nachazim se mezi apostrofy?
    $in = false;
    ///prochazim cely retezec sql
    for ($i=0; $i<$len; $i++) {
      
      //najdu apostrof, nastavim, ze se nachazim mezi apostrofy, ulozim pozici
      if (mb_substr($sql, $i,1,$this->charset)=="'") {
      //if ($sql[$i]=="'") {
        $in=!$in;
        if ($in) $pos_in = $i; else 
        {
          //mam vyraz v apostrofech, ktery zacina na $pos_in+1 a konci $i-$pos_in-1
          $exp = mb_substr($sql, $pos_in+1, $i-$pos_in-1, $this->charset);
          
          //pokud obsahuje XOR OR AND NOT

          $contains = array("xor","or","and","not");
          if(0 < count(array_intersect(array_map('strtolower', explode(' ', $exp)), $contains)))
          {
            //rozlozim XOR
            $exp = $this->xor_func($exp);
            //zapisu pozici kde se bude nahrazovat a cim do pole
            $this->replace[] = array('begin' => $exp_pos, 'end' => $i, 'exp' => $this->insertExpNameToExp($exp,$exp_name));      
          }
        }
      }
      
      //pokud se nenachazim mezi apostrofy a najdu vyraz p. vim, ze bude nasledovan nazev vyrazu, ktery ulozim do pomenne $exp_name a zacatecni pozici do $exp_pos
      if (!$in && mb_substr($sql, $i,2,$this->charset)=="p.") {
        $next_space = mb_strpos($sql,' ',$i+2,$this->charset);
        $exp_name = mb_substr($sql,$i,$next_space-$i,$this->charset);
        $exp_pos = $i;
      }
    }
    // provede nahrazeni vsech vyrazu v sql
    return $this->replaceSql($sql);
  }
  
  
  /*
   * provede nahrazeni vsech vyrazu v sql
   */
  private function replaceSql($sql) {
    if (is_array($this->replace)===true) {
    //musime zamenovat v retezci odzadu, protoze se meni delka retezce
      foreach (array_reverse($this->replace) as $rep) {
        $len = mb_strlen($sql, $this->charset);
        $sql = mb_substr($sql,0, $rep['begin'],$this->charset).$rep['exp'].mb_substr($sql, $rep['end']+1, $len-$rep['end']-1, $this->charset);  
      }
      $sql = '('.$sql.')';
    }
    return $sql;
  }
  
  private function endsWith( $str, $sub ) {
    return ( substr( $str, strlen( $str ) - strlen( $sub ) ) === $sub );
  }
  
  /*
   * spocita zaviraci zavorky a prehodi je na konec retezce
   */
  private function endBrackets($p) {
    $brackets_count = substr_count($p,")");
    $p = str_replace(")","",$p);
    return $p.str_repeat(")", $brackets_count);    
  }
    
    /*
     * pred kazdy vyraz zapise jmeno_vyrazu=, pokud je pred nim NOT zapise jmeno_vyrazu<>
     */
  private function insertExpNameToExp($exp,$exp_name) {      
      /* vyraz napr. ((X OR Y) AND (NOT X OR NOT Y)) rozseka podle mezer 
         1. pokud vyraz neni AND, OR,  a vyraz nekonci NOT tak 
         pokud predchozi vyraz nekonci not -> pridat pred retezec za posledni zavorku jmeno_vyrazu ILIKE '%%'
         pokud predchozi vyraz konci not -> vymazat not z predchoziho vyrazu a pred retezec pridat jmeno_vyrazu<>
       */ 
       
    $parts = explode(" ",$exp);
    //$parts = mb_split(" ",$exp);
    $prev = '';
    $new_parts = array();
    foreach ($parts as $key => &$p) {
      if ((mb_strtolower($p,$this->charset)!="and")&& (mb_strtolower($p,$this->charset)!="or") && (!$this->endsWith(mb_strtolower($p,$this->charset),"not"))) {
        // osetreni %%% ve vyrazu $p
        $p = str_replace("%","",$p);
        if ($this->endsWith(mb_strtolower($prev,$this->charset),"not")) {
          $new_parts[$key-1] = str_replace(array('not','NOT'),"",$prev);
          $new_parts[$key] = $this->endBrackets($exp_name." NOT ILIKE '%".$p."%'");
        } else {
          $brackets_count = substr_count($p,"(");
          $p = str_replace("(","",$p);
          $new_parts[$key] = $this->endBrackets(str_repeat("(", $brackets_count).$exp_name." ILIKE '%".$p."%'");  //dodelat pridani za posledni zavorku v $p; 
        }
      } else $new_parts[$key] = $p;
      $prev = $p;     
    }
    $ret = implode(" ",$new_parts);
    return $ret;
  }
}