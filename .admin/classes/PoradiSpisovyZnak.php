<?php
class PoradiSpisovyZnak {

  private $abc;
  private $cis;
  
  /*
   * Contructor
   * @author luma
   */
  function PoradiSpisovyZnak() {
    $this->abc = range(A,Z);
    $this->cis = array(
      "M" => 1000, "CM" => 900,
      "D" => 500, "CD" => 400,
      "C" => 100, "XC" => 90,
      "L" => 50, "XL" => 40,
      "X" => 10, "IX" => 9,
      "V" => 5, "IV" => 4,
      "I" => 1
    );
  }
  
  /*
   * @param string $kod - spisovy znak ve formatu Axxx/C, kde A je pismeno abecedy A..Z, xxx je rimske cislo 1-99 a C je cislo 1-9999
   * @return int $poradi
   */
  public function zjistiPoradi($kod) {
    //pismeno bude vzdy
    $poradi = $this->poradiPismenaAbecedy($kod[0]);
    //jedna se o kompletni retezec
    if (strpos($kod, '/') !== false) {
      $expl = explode('/',$kod);
      $rc = substr($expl[0], 1);
      $poradi += $this->rimskeCisloNaPoradove($rc);
      $poradi += $expl[1];
  
    }
    //jedna se o pismeno a rimske cislo
    elseif (strlen($kod)>1) {
      $rc = substr($kod, 1);
      $poradi += $this->rimskeCisloNaPoradove($rc);
    }
    return $poradi;
  }
  
  private function poradiPismenaAbecedy($hledane) {
    $i=10;
    foreach ($this->abc as $pismeno){
      if ($pismeno==$hledane) 
        return $i*10e6;
      $i++;
    }
  }
  
  private function rimskeCisloNaPoradove($r) {
    for ($i=0; $i < strlen($r); $i++) {
      $x = $this->cis[$r[$i]];
      if ($i+1 < strlen($r) && ($dalsi = $this->cis[$r[$i+1]]) > $x) {
        $rc += $dalsi - $x;
        $i++;
      } else {
        $rc += $x;
      }
    }
    $result = ($rc + 100) * 10000;
    return $result;
  } 

}