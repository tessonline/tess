<?php 
$GLOBALS['CONFIG']['HROMADNY_IMPORT'] = '';

//musel jsem pridat podminku, aby to delalo jen u uploadu u hromadneho importu.
//pokud tady podminka neni, tak nelze vkladat soubory do normalni spisovky
if ($GLOBALS['PROPERTIES']['AGENDA_IDENT'] == 'POSTA_HROMADNY_IMPORT')
  $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['ONLY_FILE_TYPES'] = array('rtf','csv','docx');