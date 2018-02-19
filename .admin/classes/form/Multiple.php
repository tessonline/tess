<?php

/*
 * @author luma
 * trida ukladajici vazbu z multiple formulare vytvoreneho javascriptem multiple_items.js
 */
class Multiple {

  private $db; 
  private $table;
  
  private $column1_name;
  private $columnN_name;
    
  /*
   * Contructor
   * @author luma
   * @param $db db konektor
   * @param $table jmeno vazebni tabulky
   * @param column1_name jmeno slupce pro stranu 1 vazby 
   * @param columnN_name jmeno sloupce pro stranu N vazby
   */
  function __construct($db,$table,$column1_name = "",$columnN_name = "") {
    $this->db = $db;
    $this->table = $table;
    $this->column1_name = $column1_name;
    $this->columnN_name = $columnN_name;
    
  }

  /*
   * Vklada vazbu 1:N do vazebni tabulky specifikovane db konektorem a jmenem tabulky v konstruktoru
   */
  public function insert($var1_value,$globalN_name) {
      $pos = 0;
      $next_value_exists = true;
      while ($next_value_exists) {
        $pos++;
        $name = $globalN_name."-".$pos."-NEW";
        if (isset($_REQUEST[$name])) {
          $this->insertToDb($var1_value,$_REQUEST[$name]);             
        } else {
          if ($pos>2)
          $next_value_exists = false;
        }
      }
  }
  
  private function insertToDb($var1_value,$varN_value) { 
    if ($varN_value!="") {
      $sql = 'INSERT INTO '.$this->table.' ('.$this->column1_name.','.$this->columnN_name.') VALUES ('.$var1_value.','.$varN_value.')';
      $this->db->query($sql);
    }
  }
  
/*  
 * Příprava pro pole hodnot
 * 
 * public function insert($var1_value,$globalN_names) {
    $pos = 0;
    $next_value_exists = true;
    while ($next_value_exists) {
      $pos++;
      $names = array();
  
      $p = 0;
      foreach ($globalN_names as $globalN_name) {
        $names[$p] = $globalN_name."-".$pos."-NEW";
        $p++;
      }
      if (isset($_REQUEST[$name[0]])) {
        $this->insertToDb($var1_value,$names);
      } else {
        //if ($pos>2)
        $next_value_exists = false;
      }
    }
  }
  
  private function insertToDb($var1_value,$names) {
    $add = "";
    foreach ($names as $name) {
      $add .= ",".$_REQUEST[$name];
    }
    $sql = 'INSERT INTO '.$this->table.' VALUES ('.$var1_value.$add.')';
    $this->db->query($sql);
  }*/
  
  
  public function edit($var1_value) {   
    $editItems = explode("," , $GLOBALS['EDIT_ITEMS']);      
    $this->delete($var1_value);
    foreach ($editItems as $id) {
      if (strlen($id)>0) {
        $this->insertToDb($var1_value,$_REQUEST[$id]);
      }
    }
  }
  
  public function delete($var1_value) {
    $sql = 'DELETE FROM '.$this->table.' WHERE '.$this->column1_name.'='.$var1_value;
    $this->db->query($sql);
  }
  
  /*
   * Nacte data pro multiple edit formular
   * @param $id - promenna pro stranu 1 vazby
   * @param $table_name - jemno tabulky obsahujici data
   * @param $column_names - pole sloupecku ktere nas zajimaji
   * @param $join - pokud chceme data jeste z jine tabulky
   * @return pole obsahujici data pro multiple items
   */
  public function loadFormValues($id,$table_name,$column_names,$join = "") {
    //pukud neni prirazen prefix, je prirazen defaultni aa
    foreach ($column_names as &$column) {
      if (strpos($column, '.') === false) 
      $column = "aa.".$column;
    }
    $column_names_sql = implode(",",$column_names);
    
    //select a.id, a.nazev from cis_posta_typ a left join posta_typovy_spis_typ_posty b on a.id = b.id_typ_posty where id_typovy_spis=42;
    //select a.id, a.nazev, c.agenda from cis_posta_typ a left join cis_posta_agenda c on c.id=a.id_agendy left join posta_typovy_spis_typ_posty b on a.id = b.id_typ_posty where id_typovy_spis=42;
    
    $sql = 'SELECT '.$column_names_sql.' FROM '.$table_name.' aa '.$join.' left join '.$this->table.' bb on aa.id=bb.'.$this->columnN_name.' WHERE '.$this->column1_name.' = ' . $id. 'ORDER BY bb.id ASC';
    $this->db->query($sql);
    $result = array();
    
    while ($this->db->next_record()) {
      $value = array();
      foreach ($column_names as $c) {
        $col = substr($c,strpos($c, '.')+1,strlen($c)-1);
        $col_name = strtoupper($col);
        $value[$col_name] = $this->db->Record[$col_name];
      }
    
      $result[] = $value;
    }
    
    return $result;
    }
  
  
}
