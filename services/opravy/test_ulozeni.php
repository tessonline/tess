<?php
require('tmapy_config.inc');
include(FileUp2('.admin/brow_.inc'));
include(FileUp2('.admin/security_obj.inc'));
include(FileUp2('.admin/uzavreni_cj.inc'));
include(FileUp2('html_header_full.inc'));
set_time_limit(0);
$USER_INFO = $GLOBALS['POSTA_SECURITY']->GetUserInfo();
$id_user = $USER_INFO['ID'];
$jmeno = $USER_INFO['FNAME'] . ' ' . $USER_INFO['LNAME'];
$LAST_USER_ID = $id_user;
$OWNER_ID = $id_user;
$LAST_TIME = Date('H:m:i');
$LAST_DATE = Date('Y-m-d');
$dnes = Date('d.m.Y');
$q = new DB_POSTA;
$a = new DB_POSTA;

$pracoviste = array();

$statusy = array(
  '1' => 'uzavřeno, nezaloženo',
  '-3' => 've spisovně', 
);
$sqla = 'SELECT DISTINCT g.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=0 or g.parent_group_id is null and g.id is not null ORDER BY g.id';
$q->query($sqla);
while ($q->Next_Record()) $pracoviste[$q->Record['ID']] = $q->Record['NAME'];
$pracoviste = array('2' => 'Generální ředitelství' );
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.count($pracoviste).'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();

foreach($pracoviste as $prac_id => $prac_name) {
  echo '<h1>' . $prac_name . '</h1>';
  foreach($statusy as $status_id => $status_name) {
    echo '<h2>' . $status_name . '</h2><table border=1>';
    
    $sql = 'select id from posta_view_spisy where superodbor in (' . $prac_id. ') and status=' . $status_id.' and rok in (2012,2013)';
    $q->query($sql); 
    while($q->Next_Record()) {
      $id = $q->Record['ID'];
      $kontroly = array();
      $kontroly = LzeUzavritCj($id);
      $chyba_text = array();
      if (count($kontroly)>0) {
        while (list($key,$val)=each($kontroly)) $chyba_text[]="<b>Chyba:</b> ".$GLOBALS['chyby'][$val]."<br/>";
        echo '<tr><td>'.$id.'</td><td>'.implode('<br/>', $chyba_text).'</td></tr>';
        
      }
      
      
    }
    echo '</table>';
  }
}
