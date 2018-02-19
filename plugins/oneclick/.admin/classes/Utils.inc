<?php

/**
 * Staticka trida. Zapouzdruje pouze vseobecnou funkcionalitu aplikace.
 */
class Utils {
  
  private function __construct() {
  }
  
  /**
   * Funkce vrati identifikator uzivatele sluzby 1click na zaklade id z T-WISTu.
   * @param array $oneClickUsers - Seznam uzivatelu sluzby 1click.
   * @param string $twistLogin - Login uzivatele T-WISTU.
   * @return string Pokud existuje pak: 1Click user id, jinak: prazdny retezec.
   */
  public static function getOneClickId($oneClickUsers, $twistLogin) {
    $oneClickId = '';
    foreach ($oneClickUsers as $user) {
      if (!strcmp($twistLogin, $user->login)) {
        $oneClickId = $user->id;
        break;
      }
    }
    return $oneClickId;
  }
  
  /**
  * Konvertuje kodovani polozek pole. 
  * @param string $inCharset - Vstupni kodovani (UTF-8 | ISO-8859-2 | ...,
  * viz dokumentace PHP funkce iconv()) 
  * @param string $outCharset - Vystupni kodovani. 
  * @param array $array - Pole, kteremu bude zmeneno kodovani.
  * @return array - Prekodovane pole.
  */
  public static function convertEncoding($inCharset, $outCharset, $array) {
    foreach ($array as $key => $value) {
      $array[$key] = iconv($inCharset, $outCharset, $value);
    }
    return $array;
  }
  
  /**
   * Funkce vraci login uzivatel TWISTu na zaklade jeho id.
   * @param integer $twistId - Id uzivatele TWISTu.
   * @return string - Login uzivatele TWISTu.
   */
  public static function getTwistLogin($twistId) {
    $user = $GLOBALS['TMAPY_SECURITY']->GetUserInfo($twistId, false, true, 1);
    return $user['LOGIN'];
  }
}
