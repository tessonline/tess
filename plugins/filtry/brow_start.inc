<?php

if (!$show_filter && !$GLOBALS["EXPORT_ALL_step"]) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $sql = 'select * from posta_user_filtry where owner_id=' . $USER_INFO['ID'];

  $q = new DB_POSTA;
  $q->query($sql);
  if ($q->Num_Rows()>0) {
    echo '<div class="form dark-color"><div class="form-body"><div class="form-row">';
    echo 'Vlastní&nbsp;filtry:&nbsp;&nbsp;&nbsp;';
    while ($q->Next_Record()) {
    //  $this->options[] = array('value' => $q->Record['ID'], 'label' => $q->Record[NAZEV]);
      $a = array();
      $temp = explode('|', $q->Record['NASTAVENI']);
      foreach($temp as $tempX) {
        list($key, $val) = explode('=', $tempX);

        //nova cast
        if (strpos($val, ',') !== false) {
          $val = explode(',',$val);
          foreach ($val as $v)
            if ($v!="") $a[] = $key."=".$v;
        } else
        //konec nova cast
          $a[] = $key."=".$val;

      }
      $href='document.location.href=\'brow.php?' . implode('&', $a) .'&MYFILTR=1\'';
      echo '<input type="button" onclick="'.$href.'" value="'.$q->Record['NAZEV'].'" class="btn">&nbsp;';
    }
    echo '';
    echo '</div></div></div>';
  }
}
