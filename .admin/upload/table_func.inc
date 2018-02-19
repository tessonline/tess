<?php
 

include_once(FileUp2(".admin/upload_fce_.inc"));
include_once(FileUp2(".admin/table_func_posta.inc"));


echo "\n".'<iframe id="ifrm_doc" name="ifrm_doc" src="'.FileUp_Main('empty.php',$PROPERTIES['AGENDA_IDENT']).'" style="position:absolute;z-index:0;left:0;top:0;display:none"></iframe>'."\n";

$upload_modul_first_key = array_pop(array_keys($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']));
$GLOBALS['upload_modul_to_url'] = ($upload_modul_first_key ? $upload_modul_first_key : 'table');

function Url2File($idf,$idf_h,$dir,$name,$typefile){
  global $USER_INFO;
  if (!$GLOBALS['modul_obj']) {
    $temp = Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>false));
    $GLOBALS['modul_obj'] = $temp['table'];
  }
  if($GLOBALS['modul_obj']->IsApplTypeFile($typefile))
    $target = 'ifrm_doc';
  else
    $target = '_blank';

  if(true) { //tady by se melo radeji testovat, zda priloha existuje  
     
     if($idf_h){
     
       $href = '"ug_file.php?upload_modul='.$GLOBALS['upload_modul_to_url'].'&_set_sess_ceche_limit_=1&FILE_ID_H='.$idf_h.'"';
       $onclick = '';
     
     }else{

       ShowJSfce_EditShowAtt();
       
       $href = '#';
       $onclick = "return EditShowAtt(event,$idf,'$target');";
     
     }
     $name = WrapUpload($name);
     $ret = "<a href=$href onclick=\"$onclick\" target=\"$target\" class=\"pages\">$name</a>";

//     ShowJSfce_URLFile2Clip();
//     $ret .= '&nbsp;<a href='.$href.' onclick="URLFile2Clip(event,'.$idf.',false)"><img src="'.FileUpURL('images/clip_copy_small.gif').'" alt="'.$GLOBALS["RESOURCE_STRING"]["tooltip_clip_copy"].'" border="0"></a>';
     $muze_duverne = false;


     $muze_duverne = MuzeDuverne($GLOBALS['RECORD_ID'], $GLOBALS['OWNER_ID']);
     //if (($GLOBALS['PRIVATE'] == 'y') && !$muze_duverne) $ret = WrapUpload($name);


  }else{

     $ret = WrapUpload($name);

  }

  return $ret;
}


function AnoNe_Upload($bool){
  if ($bool=='a' || $bool=='t' || $bool=='y') $res = "ANO";
  else $res = "&nbsp;";
  return $res;
}

function WrapUpload($text, $pocet = 25) {
  $text = wordwrap($text, $pocet, "<br />", true);
  return $text;
}


function ShowHistory($id){
  global $upload_agenda_path;
  static $img, $q, $upl_table;
  
  if(!$q){
    $q = $GLOBALS['modul_obj']->q;
    $upl_table = $GLOBALS['modul_obj']->upl_table;
  }
  $q->query('SELECT id FROM '.$upl_table.'_h WHERE id='.$id);
  if($q->next_record()){
    if(!$img) $img = InsertImage_Main('images/history',$GLOBALS["RESOURCE_STRING"]["history"],$PROPERTIES["AGENDA_IDENT"]);
    $res = '<a href="javascript:NewWindowHistory_upload(\''.$upload_agenda_path.'/ug_file.php?info&upload_modul='.$GLOBALS['upload_modul_to_url'].'&show_typ=4&HISTORY_ID='.$id.'\')" title="' . $GLOBALS["RESOURCE_STRING"]["history"] . '">'.$img.'</a>';
  }else{
    $res = '&nbsp;';
  }
  return $res;
}
function ShowInfo($id){
  global $upload_agenda_path;
  static $img;
  if(!$img) $img = InsertImage_Main('images/info_i',$GLOBALS["RESOURCE_STRING"]["tooltip_info"],$PROPERTIES["AGENDA_IDENT"]);
  $res = '<a href="javascript:NewWindowInfo_upload(\''.$upload_agenda_path.'/ug_file.php?info&upload_modul='.$GLOBALS['upload_modul_to_url'].'&show_typ=1&EDIT_ID='.$id.'\')">'.$img.'</a>';
  return $res;
}
function ShowEdit($id){
  global $upload_agenda_path;
  static $img;
  if(!$img) $img = InsertImage_Main('images/edit',$GLOBALS["RESOURCE_STRING"]["tooltip_edit"],$PROPERTIES["AGENDA_IDENT"]);
  $res = '<a href="javascript:NewWindowEdit_upload(\''.$upload_agenda_path.'/ug_file.php?edit&upload_modul='.$GLOBALS['upload_modul_to_url'].'&show_typ=1&EDIT_ID='.$id.'\')">'.$img.'</a>';
  return $res;
}
function ShowDelete($id){
  global $upload_agenda_path;
  static $img;
  if(!$img) $img = InsertImage_Main('images/delete',$GLOBALS["RESOURCE_STRING"]["tooltip_delete"],$PROPERTIES["AGENDA_IDENT"]);
  $res = '<a href="javascript:NewWindowDelete_upload(\''.$upload_agenda_path.'/ug_file.php?upload_modul='.$GLOBALS['upload_modul_to_url'].'&show_typ=3&DELETE_ID='.$id.'\')">'.$img.'</a>';
  return $res;
}
function ShowText($id){
  global $upload_agenda_path;
  static $img;
  if(!$img) $img = InsertImage_Main('images/paper_full','Text',$PROPERTIES["AGENDA_IDENT"]);
  $text = Upload_GetText($id);
  if (!$text) {
    $res = '&nbsp;';
  } else {
    $res = '<a href="javascript:NewWindowText_upload(\''.$upload_agenda_path.'/ug_file.php?upload_modul='.$GLOBALS['upload_modul_to_url'].'&show_typ=5&FULLTEXT_UPLOAD='.UrlEncode($GLOBALS['FULLTEXT_UPLOAD']).'&ID='.$id.'\')">'.$img.'</a>';
  }
  return $res;
}
function DatumCasVlozeni($datum,$cas){
  global $q;
  return $q->dbdate2str($datum,1).' '.$cas;
}
function NahralKdo($id){
  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($id,false,false,1);
  $res .= $USER_INFO['TITLE1'].' '.$USER_INFO['LNAME'].' '.$USER_INFO['FNAME'].' '.$USER_INFO['TITLE2'];
  return $res;
}
function FileSize_kB($filesize){
  $ret = number_format(round($filesize/1024),0, '',' ');
  $ret = '<span title="'.number_format($filesize,0,'',' ').' B">'.$ret.'</span>';
  return  $ret;
}

function ShowPreviewFoto($id){
  $ratio_arr = $GLOBALS['modul_obj']->config['AGENDA_PROPERTIES']['UPLOAD_CONFIG']["MODULES"][$GLOBALS['modul_obj']->modul_name]['PREVIEW_SIZE_RATIO']?$GLOBALS['modul_obj']->config['AGENDA_PROPERTIES']['UPLOAD_CONFIG']["MODULES"][$GLOBALS['modul_obj']->modul_name]['PREVIEW_SIZE_RATIO']:$GLOBALS['modul_obj']->config['PREVIEW_SIZE_RATIO'];
  $preview = $ratio_arr[0];
  $img = GetAgendaPath($GLOBALS['PROPERTIES']['AGENDA_IDENT'],0,1).'/ug_file.php?upload_modul='.$GLOBALS['upload_modul_to_url'].'&_set_sess_ceche_limit_=1&FILE_ID='.$id;
  $res = "<a href=\"$img\" target=\"_blank\"><img alt=\"".$GLOBALS['RESOURCE_STRING']['photo']."\" src=\"$img&preview=$preview\" border=\"0\"></a>";
  return $res;
}



function ShowJSfce_EditShowAtt($show_iframe=false){

  if(!$GLOBALS['fce_EditShowAtt_inserted']){
    $GLOBALS['fce_EditShowAtt_inserted']=true;
    $script = GetAgendaPath($GLOBALS['PROPERTIES']['AGENDA_IDENT'],0,1).'/ug_file.php?upload_modul=table&_set_sess_cache_limit_=1';
    if($show_iframe) echo '<iframe id="ifrm_doc" name="ifrm_doc" src="'.FileUp_Main('empty.php',$GLOBALS['PROPERTIES_MAIN']['AGENDA_IDENT']).'" style="position:absolute;z-index:0;left:0;top:0;display:none"></iframe>';
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
      function EditShowAtt(e,id,target){
        var script = '<?php echo $script?>';
        if (e.ctrlKey){
          script = script + '&edit&show_typ=1&EDIT_ID='+id;
          var param = 'height=430,width=580,'
          target = 'FileAtt';
        }else{
          script = script + '&FILE_ID='+id;
          var param = 'menubar,status,titlebar,toolbar,';
        }
        var d = new Date();
        newwindow = window.open(script+'&cacheid='+d.getTime(),target,param+'left=100,top=50,scrollbars,resizable');
        newwindow.focus();
        e.cancelBubble=true;
        return false;
      }
    //-->
    </script>
    <?php
  }

}


function ShowJSfce_URLFile2Clip(){

  if(!$GLOBALS['fce_URLFile2Clip_inserted']){
    $GLOBALS['fce_URLFile2Clip_inserted']=true;
    $script = GetAgendaPath($GLOBALS['PROPERTIES']['AGENDA_IDENT'],0,1).'/ug_file.php?upload_modul=table&_set_sess_cache_limit_=1&';
    $script = 'http'.($GLOBALS['HTTPS']?'s':'').'://'.$GLOBALS['HTTP_HOST'].$script;
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
      function copy_clip_rel(meintext){
        if(window.confirm('<?php echo $GLOBALS['RESOURCE_STRING']['copy_clip_01']?> \n\n'+meintext)){ 
          if (window.clipboardData){
           window.clipboardData.setData("Text", meintext);
          }else if (window.netscape){ 
           try {
             netscape.security.PrivilegeManager.enablePrivilege('UniversalXPConnect');
           } catch (err) {
             alert('<?php echo $GLOBALS['RESOURCE_STRING']['copy_clip_02']?>');
             return false;
           }  
           var clip = Components.classes['@mozilla.org/widget/clipboard;1'].createInstance(Components.interfaces.nsIClipboard);
           if (!clip) return;
           var trans = Components.classes['@mozilla.org/widget/transferable;1'].createInstance(Components.interfaces.nsITransferable);
           if (!trans) return;
           trans.addDataFlavor('text/unicode');
           var str = new Object();
           var len = new Object();
           var str = Components.classes["@mozilla.org/supports-string;1"].createInstance(Components.interfaces.nsISupportsString);
           var copytext=meintext;
           str.data=copytext;
           trans.setTransferData("text/unicode",str,copytext.length*2);
           var clipid=Components.interfaces.nsIClipboard;
           if (!clip) return false;
           clip.setData(trans,null,clipid.kGlobalClipboard);
          }
        } 
        return true;
      }
            
      function URLFile2Clip(e,id,hist){
        var script = '<?php echo $script?>';
        if(hist) script=script+'FILE_ID_H='+id;
        else script=script+'FILE_ID='+id;
        copy_clip_rel(script);
        e.cancelBubble=true;
        return false;
      }
    //-->
    </script>
    <?php
  }

}

?>
