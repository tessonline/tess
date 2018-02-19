<?php
$TABLE_CONFIG['callback'] = 'ChangeStornovano';

include_once(FileUp2('.admin/table_func.inc'));

$TABLE_CONFIG['schema'][] = array(
  field => "UkazUsera(OWNER_ID)...'<br/>'...POZNAMKA", 
  label => 'Zadal', 
  add => 'align="left"',
  order_by => 'OWNER_ID',
  width => '15%'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "'&nbsp;'...JeNaRade(POSTA_ID, SCHVALUJICI_ID)...''...UkazUsera(SCHVALUJICI_ID)", 
  label => 'Schvalující', 
  add => 'align="left"',
  order_by => 'SCHVALUJICI_ID',
  width => '15%'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'StanoviskoSchvalovani(TYPSCHVALENI, \'ZADOST\')', 
  label => 'Žádost o', 
  add => 'align="left"',
  order_by => 'SCHVALUJICI_ID',
  width => '10%'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'DATUM_ZALOZENI', 
  label => 'Vyžádáno', 
  add => 'align="left"', 
  order_by => 'datum_zalozeni',
  width => '10%'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'DATUM_PODPISU', 
  label => 'Vyřízeno', 
  add => 'align="left"', 
  order_by => 'DATUM_PODPISU',
  width => '10%'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'StanoviskoSchvalovani(SCHVALENO)', 
  label => 'Stanovisko', 
  add => 'align="left"', 
  order_by => 'schvaleno',
  width => '20%'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'ShowPoznamka(POZNAMKA2,STORNOVANO)', 
  label => 'Komentář',
  add => 'align="left"', 
  order_by => 'POZNAMKA',
  width => '30%'
);

?>
