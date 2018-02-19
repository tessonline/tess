<?php

class File {
  
  private $eedId;
  private $name;
  private $description;
  private $size;
  private $bindType;
  private $data;
  private $oneClickId;
  
  public function __construct() {
  }
  
  // Settery
  public function __set($name, $value) {
    $this->$name = $value;
  } 

  // Gettery
  public function __get($name) {
    return $this->$name;
  }
}
