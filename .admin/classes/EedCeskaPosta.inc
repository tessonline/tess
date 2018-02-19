<?php

include_once('db.inc');
class EedCeskaPosta extends eed_db_object {
  


   /** vrati carovy kod posty, pokud existuje
   */  
  function VratCK($id=0) {
    if (!$GLOBALS['CONFIG_POSTA_CESKAPOSTA']['USE_R_KODY']) return false;

    $db_posta = new DB_POSTA;
    $sql='select * from posta_cis_ceskaposta_ck where posta_id in ('.$id.')';
    $db_posta->query($sql);
    if ($db_posta->Num_Rows()>0) {
      $db_posta->Next_Record();
      return $db_posta->Record['CK'];
    }
    else
      return false;

  }

  /** vrati modulo 11
  */
  function GenMOD11( $base_val ) {
  //stazeno z http://www.eclectica.ca/howto/modulus-11-self-check.php
     $result = "";
     $weight = array( 2, 3, 4, 5, 6, 7,
                      2, 3, 4, 5, 6, 7,
                      2, 3, 4, 5, 6, 7,
                      2, 3, 4, 5, 6, 7 );

     $weight = array( 1,8,6,4,2,3,5,9,7 );

     /* For convenience, reverse the string and work left to right. */
     $reversed_base_val = strrev( $base_val );
//     $reversed_base_val = strrev( $base_val );
//     $reversed_base_val = strrev( $base_val );
     for ( $i = 0, $sum = 0; $i < strlen( $base_val ); $i++ ) {
        /* Calculate product and accumulate. */
        $sum += substr( $base_val, $i, 1 ) * $weight[ $i ];
     }

     /* Determine check digit, and concatenate to base value. */
     $remainder = $sum % 11;
     switch ( $remainder ) {
     case 0:
        $result = $base_val . 0;
        break;
     case 1:
        $result = "n/a";
        $result = $base_val . 0;
        break;
     default:
        $check_digit = 11 - $remainder;
        $result = $base_val . $check_digit;
        break;
     }
     return $result;
  }

  /** zkontroluje, jestli neni dokument vypraven a neni nahodou ceskou postou.
   *Pokud ano, vytvori CK. Pokud ne, zkontroluje, estli uz nahodou carovy kod neni a pripadne
   *ho stornuje (protoze nejde ceskou postou)
   */
  function NastavCK($id = 0)  {
    if (!$GLOBALS['CONFIG_POSTA_CESKAPOSTA']['USE_R_KODY']) return false;

    $a = new DB_POSTA;
    $db_posta = new DB_POSTA;
    $sql = 'select * from posta_cis_ceskaposta_ck where posta_id in ('.$id.')';
    $db_posta->query($sql);
    if ($db_posta->Num_Rows()>0) $uz_existuje = true; else $uz_existuje = false;

    $sql = "SELECT * FROM posta WHERE ID IN (".$id.")";
    $db_posta->query($sql);
    $db_posta->Next_Record();
    $doporucene = $db_posta->Record['DOPORUCENE'];
    $rok = $db_posta->Record['ROK'];
    if ($db_posta->Record["VLASTNICH_RUKOU"] == 1 && $db_posta->Record["DOPORUCENE"]<>1) {
      if (strlen($db_posta->Record["DATUM_VYPRAVENI"])<2 && !$uz_existuje) {
        $kod = '';
        reset($GLOBALS["CONFIG"]["TYP_ODESLANI"]);
        while (list($key,$val) = each($GLOBALS["CONFIG"]["TYP_ODESLANI"])) {
          If ($val['VALUE'] == $db_posta->Record['DOPORUCENE']) $kod = $val['KOD'];
        }
        if (!$kod) $kod = 'RR';
        $kod = 'RR'; // pozadavek decina, pry se vsecno eviduje jako RR
//        $sqla = "select max(podaci_id) as MAX_PODACI from posta_cis_ceskaposta_ck where rok = ".$rok." and kod = '".$kod."'";
        $sqla = "select max(podaci_id) as MAX_PODACI from posta_cis_ceskaposta_ck where kod = '".$kod."'";
        $a->query($sqla);
        $a->Next_Record();
        $posledni_id = $a->Record['MAX_PODACI'];
        if (!$posledni_id) $posledni_id = 0;
        $dalsi_id = $posledni_id+1;
        $cpost = $GLOBALS['CONFIG_POSTA']['HLAVNI']['POSTA_CISLO_POSTY'];
        $ident = $GLOBALS['CONFIG_POSTA']['HLAVNI']['POSTA_IDENTIFIKACE'];
        $podavatel = $GLOBALS['CONFIG_POSTA']['HLAVNI']['POSTA_PODAVATEL'];

        if ($ident == 'U') $delka = 6;
        if ($ident == 'C') $delka = 5;
        if ($ident == 'M') $delka = 4;

        $dalsi_id_text = str_pad($dalsi_id, $delka, "0", STR_PAD_LEFT);

        $cislo_kontrola = $cpost.$podavatel.$dalsi_id_text;
        //cislo pro kontrolu, spocitame modulo 11
        $cele_cislo_vcetne_kontroly = EedCeskaPosta::GenMOD11($cislo_kontrola);

        $ck = $kod.$cele_cislo_vcetne_kontroly.$ident;
//Die('CK je ' . $ck);
        $sql = "insert into posta_cis_ceskaposta_ck (posta_id,rok,kod,podaci_id,ck,stav) VALUES
         ($id,$rok,'".$kod."',$dalsi_id,'$ck',1)";
  //    Die('onma'.$sql);
         $a->query($sql);
      }
    }
    else {
      //nejde to ceskou postou, tak koukneme, jestli uz tam neni ID - pokud ano, nastavime storno na 0
      //provedeme storno dokumentu
      while ($db_posta->Next_Record()) {
        $sqla = 'update posta_cis_ceskaposta_ck set stav = 0 where id = '.$db_posta->Record['ID'];
        $b->query($sqla);
      }
    }
  }
}
