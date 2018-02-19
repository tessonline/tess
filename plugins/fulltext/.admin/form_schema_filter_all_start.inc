<?php

require_once(FileUpUrl('.admin/form_js_global.inc'));
$path = addslashes (FileUpUrl('/plugins/fulltext/verify.php'));

/*$validFullText = "
    var url = '".$path."?&FULLTEXT='+document.forms[0].FULLTEXT_SEARCH.value;
    var ajx = getAjax(url, null, null, false);
    if (ajx.responseText != '0') {
      alert('Výraz pro fulltextové vyhledávání je chybný. Prosím opravte jej.');
      return false;
    }
    return(true);    ";
*/
$validFullText = "
     var ret = false;
    var url = encodeURI('".$path."?&FULLTEXT='+document.forms[0].FULLTEXT_SEARCH.value);
    var ajx = getAjax(url, null, null, false);
    if (ajx.responseText != '0') {
      alert('Výraz pro fulltextové vyhledávání je chybný. Prosím opravte jej.');
      ret = false;
    } else
    ret = true;
 ";


$isEdit = In_Array($form_params['formtype'], array($f_edit));
$isInfo = In_Array($form_params['formtype'], array($f_info));
$isInsert = In_Array($form_params['formtype'], array($f_insert));

$FORM_CONFIG['schema'][] = array(
  'label' => 'Fulltext',
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
          "type" => "text",
          "name" => "FULLTEXT_SEARCH",
          "size" => 70,
          'tooltip' => '<b>Tipy pro vyhledávání:</b>
            <br /> - je možné používat logické operátory AND, OR, XOR a NOT
            <br />  <i>   Příklad výrazu: \'text1 AND text2 AND NOT text3\'</i>
            <br /> - spojování složitějších výrazů se provádí pomocí kulatých závorek ()
            <br />  <i>   Příklad výrazu: \'(text1 AND text2 AND NOT text3) OR text4\'</i>
            <br /> - pro vyhledávání částí řetězce použijte hvězdičku * na konci řetězce
            <br />  <i>   Příklad výrazu: \'text*\'</i>'
        )
        ),
        "label"=>"Výraz:");

/* $FORM_CONFIG["schema"][] = array("elements"=>array(
        array("type"=>"valid_fce","name_fce"=>$validFullText)),
);*/
       