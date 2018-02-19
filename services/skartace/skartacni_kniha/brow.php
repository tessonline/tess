<?php
require("tmapy_config.inc");
/*require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
include(FileUp2(".admin/brow_func.inc"));
*/
include_once(FileUp2(".admin/db/db_default.inc"));
include_once(FileUp2(".admin/config.inc"));
//include_once(FileUp2(".admin/has_access.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/oth_funkce_2D.inc"));
//security_func vraci odbory atd.
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/el/of_odbory_.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

if ($GLOBALS['PROTOKOL']) {
  $GLOBALS['PREDANI'] = 1;
}

if (!isset($GLOBALS["EXPORT_ALL_step"]) && !$GLOBALS['SKARTACNI_RIZENI_ID']) {
  include(FileUp2(".admin/brow_filter.inc"));

  if (!$GLOBALS['PREDANI']) include(FileUp2(".admin/brow_filter_spisovna.inc"));
  if ($GLOBALS['PREDANI'] == 1) {
    UNSET($GLOBALS['SPISOVNA_ID']);
    if ($_POST['sql']<>'') {
      $q = new DB_POSTA;
      $q->query($_POST['sql']);
      while ($q->Next_Record())
        $GLOBALS['ID'][] = $q->Record['ID'];
    }
  }
}

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
if ($GLOBALS['SELECT_IDdenik']) $GLOBALS['ID'] = $GLOBALS['SELECT_IDdenik'];

if ($GLOBALS["EXPORT_ALL_step"] == 2) {
  //JEDNÁ SE O EXPORT, ZAPISEME DO TRANSAKCNIHO PROTOKOLU
  $text = 'Uživatel  <b>'.$USER_INFO['FNAME'].' '.$USER_INFO['LNAME'].'</b> (' . $USER_INFO['ID'] . ') spustil export dokumentů spisové a skartační knihy do formátu ' . $_POST['export_output'];
  EedTransakce::ZapisLog(0, $text, 'EXPORT', $id_user);

}

//include(FileUp2(".admin/brow_func.inc"));
//include(FileUp2(".admin/brow_access.inc"));


echo "<script>
function insertIds(el) {
       var tablename = '';
       var f_t = document.getElementsByName('frm_'+tablename);
        f_t = f_t[0];
        if (f_t != null) {
          for (var i=f_t.length-1; i>=0; i--) {
            if (unescape(f_t[i].name)=='SELECT_ID'+tablename+'[]' &&
                f_t[i].checked) {
                var input = document.createElement('INPUT');
                input.setAttribute('type', 'hidden');
                input.setAttribute('name', 'SELECT_ID'+tablename+'[]');
                input.setAttribute('value', f_t[i].value);
                el.appendChild(input);
            }
          }
        }
}
</script>
";
//kvuli multieditaci musime nacist javascript
echo '
<link rel="stylesheet" href="jquery-ui.css">

<style>

.ui-helper-hidden-accessible {
    border: 0;
    clip: rect(0 0 0 0);
    height: 1px;
    margin: -1px;
    overflow: hidden;
    padding: 0;
    position: absolute;
    width: 1px;
}
.ui-autocomplete {
     z-index: 9999 !important;
}

</style>
<script>
$(function() {
    $( "#txtAuto" ).autocomplete({
        source: "getLokace.php?spisovna_id='.$GLOBALS['SPISOVNA_ID'].'",
        minLength: 3,
        select: function( event, ui ) {
            if(ui.item) {
                $("#LokaceId").val(ui.item.id);
            }
        },
        change: function(event, ui) {
            if(!ui.item) {
                $("#LokaceId").val(0);
                $(this).val("");
            }
        }
    });
});
</script>
';

include(FileUp2(".admin/table_append_where.inc"));

//echo "onma $where XXX $where2";
$temp = $GLOBALS['ID'];


// export dokumentu, musime zapsat do trasakcniho protokolu
// if ($GLOBALS["EXPORT_ALL_step"] == 2) {
//   if ($_POST['SELECT_ID']) $GLOBALS['ID'] = $_POST['SELECT_ID'];
//   elseif ($_POST['SELECT_ID_FILTER']) $GLOBALS['ID'] = $_POST['SELECT_ID_FILTER'];
//
//   $sql = Table(array(
//     'tablename' => '',
//     "appendwhere"=>$where.$where2,
//     'return_sql' => true
//   ));
//   $q->query($sql);
//   while ($q->Next_Record()) {
//     $id = $q->Record['ID'];
//     $text = 'Dokument <b>' . $id . '</b> byl exportován do formátu <b>' . $_POST['export_output'] . '</b>';
//     EedTransakce::ZapisLog($id, $text, 'EXPORT', $id_user);
//   }
// }

if ($GLOBALS['SPISOVNA_ID']) $sid = $GLOBALS['SPISOVNA_ID'];

$skartacni_rizeni = ($GLOBALS['SKARTACNI_RIZENI_ID']>0) ? true : false;

if (!$GLOBALS['PREDANI'] && !$GLOBALS['SPISOVNA_ID'] && !$GLOBALS['SKARTACNI_RIZENI_ID'])
  echo "Vyberte spisovnu pro zobrazení";

else {


  $count=Table(array(
  //  "showaccess" => true,
    "appendwhere"=>$where.$where2,
    "setvars"=>true,
    'agenda' => ($agenda ? $agenda : ''),
    "caption"=>$caption,
  //  "showself"=>true,
    //"select_id"=>ID2,
    "showinfo"=>false,
    'showexportall' => true,
    "showselect"=>$show_select,
    "multipleselect"=>true,
    "multipleselectsupport"=>true,
    "showedit"=>$showedit,
    "showeditall"=>$showedit,
    "showdelete"=>$showedit,
    "showhistory"=>($showedit && !$agenda),
    'formvars'=>array('SPISOVNA_ID'),
    'unsetvars'=>!$skartacni_rizeni,
    //  "return_sql"=>true,
    "page_size"=>"25",
  ));

  $sql_select=stripslashes($GLOBALS['TABLE_SELECT']);
  if (!$skartacni_rizeni && !$GLOBALS['PREDANI']) {

    if ($sid) $GLOBALS['SPISOVNA_ID'] =  $sid;
    $where2 = str_replace('not exists', 'exists', $where2);

    $count2=Table(array(
      "showaccess" => true,
      "appendwhere"=>$where.$where2,
      "setvars"=>true,
      'agenda' => ($agenda ? $agenda : ''),
      "caption"=>$caption2,
      //  "showself"=>true,
      //"select_id"=>ID2,
      "showinfo"=>false,
      'showexportall' => true,
    //  "showselect"=>$show_select,
    //  "multipleselect"=>true,
    //  "multipleselectsupport"=>true,
      "showedit"=>false,
      "showeditall"=>false,
      "showdelete"=>false,
      "showhistory"=>false,
      'formvars'=>array('SPISOVNA_ID'),
      "page_size"=>"25",
    ));

  }
}

  $GLOBALS['TABLE_SELECT'] = $sql_select; //abzchom nebrali select s skartace



  if ($GLOBALS['PREDANI'] == 1) {
    UNSET($GLOBALS['SPISOVNA_ID']);
  }

If ($count>0  && !$GLOBALS["SPISOVNA_ID"])  {
  include('.admin/brow_predani.inc');
  echo $show;
}

If ($count>0  && $GLOBALS["SPISOVNA_ID"] && !$GLOBALS['SKARTACNI_RIZENI_ID'])  {
  include('.admin/brow_spisovna.inc');

  echo $show;

}


If ($count>0  && $GLOBALS['SKARTACNI_RIZENI_ID'])  {
  include('.admin/brow_skartacni_rizeni.inc');
  echo $show;
}


require(FileUp2("html_footer.inc"));
?>
