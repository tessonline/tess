<script type="text/javascript">
<!--

function createNewFrom(id) {
  script = '<?php echo GetAgendaPath('POSTA_OBALKY', TRUE, FALSE); ?>/edit.php?insertfrom&create_objects=1&EDIT_ID=' + id;
  NewWindowEditOBALKA(script);
}

function changeObjectsPosition(id) {
  script = '<?php echo GetAgendaPath('POSTA_OBALKY', TRUE, FALSE); ?>/change_objects_position.php?edit&EDIT_ID=' + id;
  NewWindowEditOBALKA(script);
}

function copyEnvelope(id) {
	  script = '<?php echo GetAgendaPath('POSTA_OBALKY', TRUE, FALSE); ?>/edit.php?insertfrom&create_objects=1&EDIT_ID=' + id+'&envelope_id='+id;
	  NewWindowEditOBALKA(script);
	}

-->
</script>

<?php

include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require_once(FileUp2('.admin/oth_funkce_2D.inc'));

$GLOBALS['objekty'] = getSelectDataEed(new of_select_objekt(array()));

function ShowObjekt($objekt_id) {
  $ret = $GLOBALS['objekty'][$objekt_id];
  if (!$ret) $ret = $objekt_id;
  return $ret;
}


Function Ukaz($id)
{
  $res="<a href='../../../output/pdf/obalka.php?obalka=".$id."&test=1' target='_blank'>test</a>";
  return $res;
}

function createNewFrom($id) {
  static $img = '';

  if (!$img) {
    $img = FileUpImage('images/whatever-add');
  }

  return "<a href=\"javascript:createNewFrom($id)\">
            <img src=\"$img\" title=\"Vytvořit nový obejkt ze stávajícího\" border=0>
          </a>";
}

function changeObjectsPosition($id) {
  static $img = '';

  if (!$img) {
    $img = FileUp2('images/resize.png');
  }

  return "<a href=\"javascript:changeObjectsPosition($id)\">
            <img src=\"$img\"
                 alt=\"Posunout souřadnice objektů\"
                 title=\"Posunout souřadnice objektů\"
                 border=0>
          </a>";
}

function copyEnvelope($id) {
  static $img = '';

  if (!$img) {
    $img = FileUp2('images/copy.png');
  }

  return "<a href=\"javascript:copyEnvelope($id)\">
  <img src=\"$img\"
  alt=\"Vytvořit kopii obálky\"
  title=\"Vytvořit kopii obálky\"
  border=0>
  </a>";
}
