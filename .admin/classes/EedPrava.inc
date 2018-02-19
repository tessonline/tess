<?php
require_once('db.inc');
/**
* trida EED_doc, pro praci s jednotlivymi dokumenty
*@author onma  
*/
class EedPrava extends Eed_db_object {
  /**
  * Constructor
  * @author onma  
  * @param int $id - id dokumentu   
  */
  
  function EedPrava() {
  }

 
  function getSQLWhere($prac, $odbor) {
    $text = ' OR ID IN (SELECT posta_id from posta_prava WHERE 1=1 ';
    if ($prac>0) $text .= ' OR referent=' . $prac;
    if ($odbor>0) $text .= ' OR odbor=' . $odbor;

    return $text;
  }

  function getRight($id, $prac) {
  }

}
