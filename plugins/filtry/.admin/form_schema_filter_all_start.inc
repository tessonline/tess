<?php


$FORM_CONFIG['schema'][] = array(
  'label' => 'Uživatelské filtry',
  'visible' => true,
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'column' => 1,
      )
    )
  )
);


$FORM_CONFIG["schema"][] = array("elements"=>array(
        array(
          "type"=>"select_filtry",
          "name"=>"SELECT_FILTR",
          "insertnull"=>true,
          'add' => 'onChange=\'getFiltr(this.value);\' style="width:530px"  '
        )
        ),
        "label"=>"Filtr:");

echo '<script language="JavaScript" type="text/javascript">
<!--

  function getFiltr(id) {
    document.location.href=\'edit.php?filter&SELECT_FILTR=\' + id;
  }

//-->
</script>
';

if ($GLOBALS['SELECT_FILTR']>0) {
  $sql = 'select * from posta_user_filtry where id = ' . $GLOBALS['SELECT_FILTR'];
  $q = new DB_POSTA;
  $q->query($sql);
  while ($q->Next_Record()) {
    $temp = explode('|', $q->Record['NASTAVENI']);
    foreach($temp as $tempX) {
      list($key, $val) = explode('=', $tempX);

      if (strpos($val, ',') !== false) {
        $val = explode(',',$val);
        foreach ($val as $v)
           if ($v!="") $GLOBALS[$key][] = $v;
      } else
        $GLOBALS[$key] = $val;
    }
  }
}