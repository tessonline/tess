<?php
//ini_set("display_errors", 1);
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

//$GLOBALS['Debug']['sql'] = 1;

//apc_clear_cache('opcode');
//apc_clear_cache('user');
$co=StrTok($GLOBALS["QUERY_STRING"], '&');
Form_(array("showaccess"=>true, "nocaption"=>true));

if ($co == 'edit' || $co == 'insert') {
  require(FileUp2(".admin/brow_.inc"));
  unset($GLOBALS['ID']);
  $count=Table(array(
    "agenda" => "POSTA_SPISOVNA_BOXY_VLOZENI",
//    "appendwhere" => "and b.ID IN (select box_id from posta_spisovna_boxy_ids where posta_id=".$DOKUMENT_ID.")",
    "appendwhere" => "and posta_id=".$DOKUMENT_ID."",
    "showdelete" => true,
    'showcount' => false, //protahuje to tabulku
  //    "showedit" => $lze_editovat,
    "showedit" => false,
    "showinfo" => false,
    //"nocaption" => true,
    "showaccess" => true,
    "setvars" => true,
    "unsetvars" => true,
    "emptyoutput" => false,
  ));

echo '<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>';
  echo "<script>

  function UkazSkartacniRezim(skartace) {
    newwindow =   window.open('" . GetAgendaPath('POSTA',false,true). "/services/spisovka/oddeleni/get_value_rezim.php?SKARTACE_ID='+skartace.value+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  }
  ";
  if ($GLOBALS['SKARTACE_ID']>0) {
    echo "UkazSkartacniRezim(document.frm_edit.SKARTACE_ID);";
  }

  echo "</script>";

  $path = GetAgendaPath('POSTA_SPISOVNA_BOXY_VLOZENI');
  $path2 = GetAgendaPath('POSTA_SPISOVNA_BOXY');
  $boxy = getSelectDataEed(new of_select_archivni_box(array('POSTA_ID' => $DOKUMENT_ID)));

  NewWindow(array("fname" => "AgendaBox", "name" => "AgendaBox", "header" => true, "cache" => false, "window" => "AgendaBox"));

  echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';

  echo '<form method"GET" action="" id="myselect" onsubmit="send();return false;">Vložit do boxu:&nbsp;
  <input type="hidden" name="POSTA_ID" value="' . $DOKUMENT_ID. '">
  <select name="BOX_ID">
  ';

  foreach ($boxy as $key => $val) {

    $box = LoadClass('EedArchivacniBox', $key);
    $box->PrepocitatArchivaci($key);

    echo '<option value="' . $key . '">' . $val . '</option>';
  }
  echo '
  </select>
  <input type="submit" class="btn" value="Vložit">&nbsp;
  </form>
  <a class="btn" href="javascript:NewWindowAgendaBox(\'' . $path2 . '/edit.php?insert&cacheid=\')">Vytvořit nový box</a>
  <a class="btn" href="javascript:NewWindowAgendaBox(\'' . $path2 . '/brow.php?insert&cacheid=\')">Upravit stávající boxy</a>
  ';
  echo '</div> </div> </div>';
  echo '<script>
    function send() {
      var a = $( "#myselect option:selected" ).val();
      NewWindowAgendaBox(\'' . $path . '/run.php?POSTA_ID=' . $DOKUMENT_ID . '&BOX_ID=\' + a + \'&cacheid=\');
    }
  </script>
  ';
}
require(FileUp2("html_footer.inc"));
