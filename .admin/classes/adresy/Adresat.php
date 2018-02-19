<?php

class Adresat {
  
  private $typ;
  private $kodAdresy;
  private $titul;
  private $oddeleni;
  private $prijmeni;
  private $jmeno;
  private $osoba;
  private $rc; // rodne cislo
  private $ulice;
  private $cp; // cislo popisne
  private $cor; // cislo orientacni
  private $psc;
  private $ico;
  private $posta;
  private $email;
  private $datovaSchranka;
  private $datumNarozeni;
  
  public function __construct($typ, $kodAdresy, $titul, $prijmeni, $jmeno, $oddeleni, $osoba, $ulice,
                         $cp, $cor, $psc, $ico, $posta, $rc, $email, $datovaSchranka, $datumNarozeni) {   
  
    $this->typ            = $typ;
    $this->kodAdresy      = $kodAdresy;
    $this->titul          = $titul;     
    $this->oddeleni       = $oddeleni;  
    $this->prijmeni       = $prijmeni;
    $this->jmeno          = $jmeno;
    $this->osoba          = $osoba;
    $this->ulice          = $ulice;
    $this->cp             = $cp;
    $this->cor            = $cor;
    $this->psc            = $psc;
    $this->ico            = $ico;
    $this->posta          = $posta;
    $this->rc             = $rc;
    $this->email          = $email;
    $this->datovaSchranka = $datovaSchranka;
    $this->datumNarozeni  = $datumNarozeni;
  }
  
  public function save($dbConnector) {
    
    $id = $this->getId($dbConnector);
    
    if (!$id) {
    
      $sql = 'INSERT INTO posta_adresati (odes_typ, odesl_adrkod, odesl_titul, odesl_odd,
                                          odesl_prijmeni, odesl_jmeno, odesl_osoba, odesl_rc,
                                          odesl_ulice, odesl_cp, odesl_cor, odesl_psc, odesl_ico,
                                          odesl_posta, odesl_email, odesl_datschranka, odesl_datnar)
                VALUES ('
           . "'" . trim($this->typ)                                     . "', "
           .       trim($this->kodAdresy)                               . ", "
           . "'" . str_replace("'", "''", trim($this->titul))           . "', "
           . "'" . str_replace("'", "''", trim($this->oddeleni))        . "', "
           . "'" . str_replace("'", "''", trim($this->prijmeni))        . "', "
           . "'" . str_replace("'", "''", trim($this->jmeno))           . "', "
           . "'" . str_replace("'", "''", trim($this->osoba))           . "', "
           . "'" . str_replace("'", "''", trim($this->rc))              . "', "
           . "'" . str_replace("'", "''", trim($this->ulice))           . "', "
           . "'" . str_replace("'", "''", trim($this->cp))              . "', "
           . "'" . str_replace("'", "''", trim($this->cor))             . "', "
           . "'" . str_replace("'", "''", trim($this->psc))             . "', "
           . "'" . str_replace("'", "''", trim($this->ico))             . "', "
           . "'" . str_replace("'", "''", trim($this->posta))           . "', "
           . "'" . str_replace("'", "''", trim($this->email))           . "', "
           . "'" . str_replace("'", "''", trim($this->datovaSchranka))  . "', "
           . ($this->datumNarozeni ? "'" . trim($this->datumNarozeni)   . "'" : 'NULL' ) . ')';

      $dbConnector->query($sql);
      $id = $dbConnector->getlastid('posta_adresati', 'ID');      
    }
    
    return $id;
  }
  
  public function getId($dbConnector) {
    
    $sql = 'SELECT * FROM posta_adresati WHERE '
         . "odes_typ = '"       . trim($this->typ)                              . "' AND "
         . "odesl_prijmeni = '" . str_replace("'", "''", trim($this->prijmeni)) . "' AND "
         . "odesl_jmeno = '"    . str_replace("'", "''", trim($this->jmeno))    . "' AND "
         . "odesl_ulice = '"    . str_replace("'", "''", trim($this->ulice))    . "' AND "
         . "odesl_cp = '"       . str_replace("'", "''", trim($this->cp))       . "' AND "
         . "odesl_cor = '"      . str_replace("'", "''", trim($this->cor))      . "' AND "
         . "odesl_ico = '"      . str_replace("'", "''", trim($this->ico))      . "' AND "
         . "odesl_psc = '"      . str_replace("'", "''", trim($this->psc))      . "' AND "
         . "odesl_posta = '"    . str_replace("'", "''", trim($this->posta))    . "' AND "
         . "odesl_datnar " . ($this->datumNarozeni
                              ? "= '" . trim($this->datumNarozeni) . "'"
                              : 'IS NULL');
  
    $dbConnector->query($sql);
    $dbConnector->next_record();
    
    return $dbConnector->Record['ID'];
  }
}