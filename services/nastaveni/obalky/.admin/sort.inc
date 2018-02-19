<?php
if (isset($GLOBALS['save'])) {
  $pole = explode(',',$_POST['order']);

  $db_name = $PROPERTIES['DB_NAME'] ? $PROPERTIES['DB_NAME'] : 'DB_DEFAULT';
  $q = new $db_name;

  foreach($pole as $poradi => $id) {
    $sql = 'update ' . $PROPERTIES['AGENDA_TABLE'] . ' set poradi=' . $poradi . ' where '.$PROPERTIES['AGENDA_ID'].'='.$id;
    $q->query($sql);
  }
}

require(FileUp2("html_header_full.inc"));
echo ' <script src="//code.jquery.com/ui/1.11.2/jquery-ui.js"></script>
';
echo '<div class="table-title">Třídění - ' . $PROPERTIES['AGENDA_NAME'] . '</div>';
$where = '';
if (isset($GLOBALS['SELECTOR'])) $where = ' WHERE '.$GLOBALS['SELECTOR'].'='.$GLOBALS['SELECTOR_ID'];

$sql = 'select * from ' . $PROPERTIES['AGENDA_TABLE'] . $where.' order by poradi ,'.$PROPERTIES['AGENDA_ID'].' asc';

if (isset($_GET['sql'])) $sql = $_GET['sql'];
$db_name = $PROPERTIES['DB_NAME'] ? $PROPERTIES['DB_NAME'] : 'DB_DEFAULT';
$q = new $db_name;

$q->query($sql);

echo '
<br /><br /><ul id="sortable">';
$a = 0;
while ($q->Next_Record()) {
  $a++;
  echo '<li class="table-col-sortable up-down" id="'.$q->Record['ID'].'">'.$a.' - '.$q->Record['NAZEV'].'</li>';
}
echo '
</ul>
<script>

$( "#sortable" ).sortable({
    stop: function(event, ui) {
         var productOrder = $(this).sortable(\'toArray\').toString();

        var jqxhr = $.ajax({
          type: "POST",
          url: "sort.php?save",
          data: {order:productOrder}
          })
        .done(function() {
        })
        .fail(function() {
        alert( "Došlo k chybě při uložení" );
        });
   },

});
</script>
';


require(FileUp2("html_footer.inc"));

