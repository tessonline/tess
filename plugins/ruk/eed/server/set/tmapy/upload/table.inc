<?php
/* HEADER */ if ($TWIST_FILE_INFO) {echo __FILE__.': $Id: table.inc,v 1.27 2010/09/30 15:05:00 figa Exp $'.'$Name:  $';exit;}; /* HEADER */ 

require_once ('main.inc');

class Upload_Obj_Table extends Upload_Obj_Main
{
  var $modul_name = 'table';
  var $upl_table = '';
  var $upl_tab_met = array();
  var $q = array();
  var $q_ag = array();
  var $UPL_RECORD = array();
  var $AGENDA_RECORD = array();
  var $storage_type = 'filesystem';
  var $only_file_types = array();

  function Upload_Obj_Table ($config) {
    
    parent::Upload_Obj_Main($config);

    $this->upl_table = $this->config['TABLE'];
    $GLOBALS['upl_table'] = $this->upl_table;

    //db konektor na tabulku UPLOADU
    $db = $this->config['DB_NAME']?$this->config['DB_NAME']:'DB_DEFAULT';
    $this->q = new $db;

    //db konektor na tabulku AGENDY
    $db = $this->config['AGENDA_PROPERTIES']['DB_NAME']?$this->config['AGENDA_PROPERTIES']['DB_NAME']:'DB_DEFAULT';
    $this->q_ag = new $db;

    $this->upl_tab_met = $this->q->metadata($this->upl_table);
    
    if($GLOBALS['DELETE_ID'] || $GLOBALS['EDIT_ID'] || $GLOBALS['FILE_ID'] || $GLOBALS['FILE_ID_H'] || $GLOBALS['HISTORY_ID'] || $GLOBALS['DELETE_ID_H']){

      $id = $GLOBALS['FILE_ID']?$GLOBALS['FILE_ID']:($GLOBALS['DELETE_ID']?$GLOBALS['DELETE_ID']:($GLOBALS['EDIT_ID']?$GLOBALS['EDIT_ID']:$GLOBALS['HISTORY_ID']));
      $idh = $GLOBALS['FILE_ID_H']?$GLOBALS['FILE_ID_H']:$GLOBALS['DELETE_ID_H'];

      if( ($id && !is_numeric($id)) || ($idh && !is_numeric($idh)) ){
        $this->flushMesg('Error ID');
        return ($this->silent) ? false : die();
      }

      if($idh)
        $this->UPL_RECORD = $this->GetRecordTable($idh, true);
      else
        $this->UPL_RECORD = $this->GetRecordTable($id, false);
        
    }

    $RECORD_ID = $this->UPL_RECORD['RECORD_ID']?$this->UPL_RECORD['RECORD_ID']:$GLOBALS['RECORD_ID'];
    
    if($RECORD_ID)
      $this->AGENDA_RECORD = $this->GetRecordAgenda($RECORD_ID);

    $this->stg_obj->UPL_RECORD = &$this->UPL_RECORD;
    $this->stg_obj->AGENDA_RECORD = &$this->AGENDA_RECORD;   
    $this->stg_obj->AGENDA_RECORD_ID = $RECORD_ID;

    // prevedeni casu pro MSSQL - lumo
//    $this->UPL_RECORD['LAST_DATE'] = $this->q->dbdate2str($this->UPL_RECORD['LAST_DATE']);
//    $this->UPL_RECORD['LAST_DATE'] = $this->q->str2dbdate($this->UPL_RECORD['LAST_DATE']);

    //ziskani z konfigurace pripadne omezeni na typy souboru
    if($this->config['AGENDA_PROPERTIES']['UPLOAD_CONFIG']['MODULES'][$this->modul_name]['ONLY_FILE_TYPES'])
      $this->only_file_types = $this->config['AGENDA_PROPERTIES']['UPLOAD_CONFIG']['MODULES'][$this->modul_name]['ONLY_FILE_TYPES'];
    elseif($this->config['ONLY_FILE_TYPES'])  
      $this->only_file_types = $this->config['ONLY_FILE_TYPES'];
      
  }


    ///kontrola na
    ///1. pokud se jedna o anonyma, tak musi byt nastaveno ze je soubor pristupny pro nej
    ///2. pokud je soubor nastaven jako privatni, tak porovnat id uzivatele
    ///3. pravo k zaznamu
  function hasAccessToUploadRecord($right = false){
    if(($this->config['use_anonym_access'] && $this->config['USER_INFO']['is_anonymous'] && $this->UPL_RECORD['ANONYM']=='n')  || ($this->config['use_private_access'] && $this->UPL_RECORD['PRIVATE']=='y' && $this->config['USER_INFO']['ID']!=$this->UPL_RECORD['OWNER_ID']))
      $acc = false;
    else
      $acc = true;

    if($acc && $right && $this->UPL_RECORD)
      $acc = HasAccessToRecord($right, $this->AGENDA_RECORD);

    return $acc;
  }


  //ziska zaznam z UPLOADU pro konkretni prilohu
  function getRecordTable($id, $history=false){
    
    static $cache = array();
    
    $cache_key = $id.($history ? 'H' : ''); 
    
    if(!$cache[$cache_key]) {
    
      $tname = $history ? $this->upl_table.'_h' : $this->upl_table;
      $tid = $history ? 'id_h' : 'id';

      $this->q->query("SELECT * FROM $tname WHERE $tid = $id");
  
      $this->q->next_record();
      
      $cache[$cache_key] = $this->q->Record;
    }

    return $cache[$cache_key];
  }

  //ziska zaznam z agendy, pro ktery patri konkretni priloha
  function getRecordAgenda($record_id=0){

    if(!$record_id) $record_id = $this->UPL_RECORD['RECORD_ID'];

    if($this->config['AGENDA_PROPERTIES']['UPLOAD_SELECT'])
      $sql = $this->config['AGENDA_PROPERTIES']['UPLOAD_SELECT'];
    else
      $sql = 'SELECT * FROM '.$this->config['AGENDA_PROPERTIES']['AGENDA_TABLE'];    
    
    $this->q_ag->query($sql.' WHERE '.$this->config['AGENDA_PROPERTIES']['AGENDA_ID'].' = '. $record_id);

    $this->q_ag->next_record();

    return $this->q_ag->Record;
  }

  //ziska pole zaznamu z UPLOADU dle agenda_ident a record_id
  function getRecordsUploadForAgenda($record_id=0, $agenda_ident = null){

    $ret = array();

    if(!$record_id) $record_id = $this->UPL_RECORD['RECORD_ID'];

    $this->q->query('SELECT * FROM '.$this->upl_table.' WHERE record_id = '. 
                    $record_id.' AND agenda_ident = \''.
                    ($agenda_ident ? $agenda_ident : $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']).
                    '\' ORDER BY id');

    while($this->q->next_record()){
      $ret[] = $this->q->Record;
    }

    return $ret;
  }

  //zobrazi vlastni prilohu
  function showUploadFiles(){


    if(!$this->UPL_RECORD) return false;

    if(!$this->stg_obj->uplFileExists()){
      $error_f = FileUp2('images/foto/error.gif');
      $this->sendHTTPHeaderForFile($error_f, 'image/gif', 'inline', filesize($error_f));
      readfile($error_f);
      die();
    }

    $preview = $GLOBALS['preview']?$GLOBALS['preview']:0;
    
    $info = $this->stg_obj->getInfoAboutFile();
    //jestlize je pozadovany nahled
    if($preview && $info['imagefile']){

       $img = $this->CreatePreview('', $info['imagefile'], array($preview), false, false);

       $this->sendHTTPHeaderForFile($this->UPL_RECORD['NAME'], $this->UPL_RECORD['TYPEFILE'], 'inline');
       
       $this->stg_obj->sendReadFilePreview($img[$preview], $preview);

    }else{
      if($this->isApplTypeFile($this->UPL_RECORD['TYPEFILE']))
        $content_disposition = 'attachment';
      else
        $content_disposition = 'inline';
      if($this->UPL_RECORD['TYPEFILE'] == 'text/plain')
        $this->UPL_RECORD['TYPEFILE'] .= '; charset=windows-1250';

     $this->sendHTTPHeaderForFile($info['filename'], $this->UPL_RECORD['TYPEFILE'], $content_disposition, $info['filesize']);

      if($this->stg_obj->sendReadFile()){
        if($GLOBALS['FILE_ID']){
          $sql = 'UPDATE '.$this->upl_table.' SET counter = '.($this->UPL_RECORD['COUNTER']+1).', last_date_show=\''.$this->q->date2dbdate().'\' WHERE id = '.$GLOBALS['FILE_ID'];
          $this->q->query($sql);
        }
      }else{
        $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_not_found']);
      }
      
    }
  }
  /**
   *onma, 13.9.2009 funkce vrati obsah souboru
   **/     
  function GetUploadFiles($val){
  $this->UPL_RECORD=$val;

    if(!$this->stg_obj->uplFileExists()){
      return '';
    }

    return $this->stg_obj->sendReadFile('',1);
  }

  /**
  Zobrazuje Table uploadu
  **/
  function showUploadTable($agenda_ident = null){

    $schema_file = FileUp_Main('.admin/upload/table_schema.inc', $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']);
    $add_where='';
    if($this->config['USER_INFO']['is_anonymous'] && $this->config['use_anonym_access']) $add_where.=" AND anonym='y'";

    ///podminka pro "duverne" dokumenty
    if($this->config['use_private_access']) $add_where.=" AND (private<>'y' OR owner_id=".$this->config['USER_INFO']['ID'].')';

    $sql_arr = array();

    if($GLOBALS['DELETE_ID']){
      $nocapt = true;
      $nopaging = true;
      $sql_arr[1]="SELECT * FROM $this->upl_table WHERE id=$GLOBALS[DELETE_ID] $add_where";
    }else{
      $nocapt = false;
      $sql_arr['image']   = "SELECT * FROM $this->upl_table WHERE agenda_ident='".
                            ($agenda_ident ? $agenda_ident : $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']).
                            "' AND record_id=".
                            ($GLOBALS['RECORD_ID']?$GLOBALS['RECORD_ID']:'0').
                            " $add_where AND isimage = 'y'";
      $sql_arr['noimage'] = "SELECT * FROM $this->upl_table WHERE agenda_ident='".
                            ($agenda_ident ? $agenda_ident : $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']).
                            "' AND record_id=".
                            ($GLOBALS['RECORD_ID']?$GLOBALS['RECORD_ID']:'0').
                            " $add_where AND (isimage = 'n' OR isimage IS NULL)";
    }

    $properties = $this->config['AGENDA_PROPERTIES'];
    $properties['DB_NAME'] = $this->config['DB_NAME']?$this->config['DB_NAME']:'DB_DEFAULT';
    $properties['AGENDA_ID'] = 'ID';
    $properties['AGENDA_TABLE'] = $this->upl_table;

    foreach($sql_arr as $typ => $sql){

      $GLOBALS['ORDER_BYupload_files'] = $GLOBALS['ORDER_BYupload_files']?$GLOBALS['ORDER_BYupload_files']:'id';
      $sql.= ' ORDER BY '.$GLOBALS['ORDER_BYupload_files'];

      if($typ == 'image'){
        $capt = 'Přílohy - obrázky';
        $no_top_menu = false;
        $GLOBALS['IMAGE_PREVIEW'] = true;
      }elseif($typ == 'noimage'){
        $capt = 'Přílohy - ostatní';
        $no_top_menu = true;
        $GLOBALS['IMAGE_PREVIEW'] = false;
      }
      Table(array(
          'properties'=>$properties, //tento parametr MUSI byt podporovan, pokud db tabulky pro UPLOAD, jsou jinde nez agenda
          'caption'=>$capt,
          'nocaption'=>$nocapt,
          'nopaging'=>$nopaging,
          'tablename'=>$this->upl_table,
          'sql'=>$sql,
          'schema_file'=>$schema_file,
          'showhistory'=>false,
          'setvars'=>true,
          'noprint'=>true,
          'noexport'=>true,
          'showaccess'=>true,
          'showinfo'=>false,
          'showedit'=>false,
          'showdelete'=>false,
          'noshowrelation'=>true,
          'noshowinsert2clip'=>true,
          'no_top_menu'=>$no_top_menu,
        ));

    }

    $text = $GLOBALS['RESOURCE_STRING']['upload_nova_verze'];
    // uz ej v resource string
    //if(strcasecmp($this->config['AGENDA_PROPERTIES']['DEFAULT_LANG'],'cz_utf-8')==0) $text = iconv('windows-1250','ISO-8859-2',$text);

    $this->flushMesg($text);

  }




  function showUploadForm(){

    $schema_file = FileUp_Main('.admin/upload/form_schema.inc', $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']);

    if($GLOBALS['EDIT_ID']) $sql = "SELECT * FROM $this->upl_table WHERE id = $GLOBALS[EDIT_ID]";
    else $sql=false;

    /// toto je vyuziti tohoto globalniho parametru, ktery se pouziva ve fci HasAccessToRecord,
    /// ktera se vola ve Form_(), abych se vyhnul kontrole, protoze nemuze spravne zafungovat,
    /// protoze ma PROPERTIES z jine agendy a EDIT_ID z UPLOADU
    $GLOBALS['PROPERTIES']['NO_TABLE'] = HasAccessToRecord('update', $this->UPL_RECORD['RECORD_ID']);

    $properties = $this->config['AGENDA_PROPERTIES'];
    $properties['DB_NAME'] = $this->config['DB_NAME']?$this->config['DB_NAME']:'DB_DEFAULT';
    $properties['AGENDA_ID'] = 'ID';
    $properties['AGENDA_TABLE'] = $this->upl_table;

    Form_(array(
        'properties'=>$properties, //tento parametr MUSI byt podporovan, pokud db tabulky pro UPLOAD, jsou jinde nez agenda
        'caption'=>'Příloha',
        'action'=>'ug_file.php',
        'myform_schema'=>$schema_file,
        'myform_sql_all'=>$sql,
        'formvars'=>array('show_typ'=>2),
        'method'=>'post',
        'showaccess'=>true
    ));

  }



  /**
  Historie
  **/
  function showUploadHistory(){
    global $PROPERTIES, $USER_INFO;

    if(HasSubRole('update') && $this->hasAccessToUploadRecord('update')){

      $capt = 'Přílohy';

      if($this->config['use_private_access']) $private = " AND (private<>'y' OR owner_id=".$this->config['USER_INFO']['ID'].')';

      $sql = "SELECT * FROM $this->upl_table WHERE agenda_ident='".$this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']."' AND id=".($GLOBALS['HISTORY_ID']?$GLOBALS['HISTORY_ID']:'0').$private;

      $table_schema_file=FileUp_Main('.admin/upload/table_schema.inc', $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']);
      $form_schema_file=FileUp_Main('.admin/upload/form_schema.inc', $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']);

      ///zde se podstrci fci History() jine hodnoty
      $GLOBALS['PROPERTIES']['AGENDA_TABLE'] = $this->upl_table;
      $GLOBALS['PROPERTIES']['AGENDA_ID'] = 'ID';
      $GLOBALS['PROPERTIES']['DB_NAME'] = $this->config['DB_NAME']?$this->config['DB_NAME']:'DB_DEFAULT';

      include(FileUp2('.admin/history_.inc'));

      History(array(
          'table_name'=>$this->upl_table,
          'table_sql'=>$sql,
          'table_caption'=>$capt,
          'agenda_id'=>'ID',
          'caption'=>'Historie',
          'table_schema_file'=>$table_schema_file,
          'table_showinfo'=>false,
          'form_schema_file'=>$form_schema_file,
          'noundo'=>true,
          'noacceptfields'=>array('COUNTER','FILESIZE','DIRECTORY','TYPEFILE','WIDTH','HEIGHT'),
      ));

    }else{
      include_once(FileUp2('html_error.inc'));
    }
  }


  /**
  Uklada do Uploadu
  **/
  function actionRun() {

    include_once(FileUp2('.admin/upload_fce_.inc'));

    $button_back = "<input type=\"button\" value=\"".$GLOBALS["RESOURCE_STRING"]["button_back"]."\" onClick=\"javascript:window.history.go(-1)\" class=\"button\">\n";

    /// toto je vyuziti tohoto globalniho parametru, ktery se pouziva ve fci HasAccessToRecord,
    /// ktera se vola ve Form_(), abych se vyhnul kontrole, protoze nemuze spravne zafungovat,
    /// protoze ma PROPERTIES z jine agendy a EDIT_ID/DELETE_ID z UPLOADU
    if($GLOBALS['EDIT_ID']) $role = 'update';
    elseif($GLOBALS['DELETE_ID'] || $GLOBALS['DELETE_ID_H']) $role = 'delete';
    if($role) $GLOBALS['PROPERTIES']['NO_TABLE'] = $this->hasAccessToUploadRecord($role);

    if(!$GLOBALS['DELETE_ID']){ ///nejedna se o mazani

      if($GLOBALS['UPLOAD_FILE']){
        $maxfilesize = $this->getMaxFileSizeUpload();
        if($maxfilesize && $maxfilesize < $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['size']){
          $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_too_big'].' '.
                           number_format(round($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['size']/1024),'','',' ').
                           'kB (max. '.number_format(round($maxfilesize/1024),'','',' ').
                           'kB)<br>&nbsp;<br>&nbsp;');
          return ($this->silent) ? false : die($button_back);
        }
      }
      
      if (!$GLOBALS['EDIT_ID'] && (!$GLOBALS['UPLOAD_FILE'] || $GLOBALS['UPLOAD_FILE']=='none') && !($GLOBALS['UPL_FILE'] && $GLOBALS['UPL_DIR'])){ ///jedna se o nepovedeny UPLOAD
        $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_no_or_big'].
                         '  !!!<br>&nbsp;<br>&nbsp;');
        return ($this->silent) ? false : die($button_back);
      }


      $ftype = '';
      if($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE'] && !$this->isAllowedFileType(&$ftype)){
        $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_not_allowed_format'].
                         ' ('.$ftype.')!!!<br>&nbsp;<br>&nbsp;');
        return ($this->silent) ? false : die($button_back);
      }
      

      $tmp_file = '';
      $archiv_file = '';

      if($GLOBALS['UPL_FILE'] && $GLOBALS['UPL_DIR']){
         $tmp_file =  $this->tmp_dir.'/'.$GLOBALS['UPL_DIR'].'/'.$GLOBALS['UPL_FILE'];
         if(file_exists(FileSystemConvertFNToFS($tmp_file))){
           $GLOBALS['RENAME_NEW'] = strtr(trim($GLOBALS['RENAME_NEW']),'\/:*?"<>|&','__________');
           $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'] = $tmp_file;
           $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name'] = $GLOBALS['RENAME_NEW']?$GLOBALS['RENAME_NEW']:$GLOBALS['UPL_FILE'];
           $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['type'] = $GLOBALS['UPL_TYPE'];
           $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['size'] = $GLOBALS['UPL_SIZE'];
         }else{
           $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_not_tmp'].
                            ' !!!<br>(<i>'.$tmp_file.'</i>)<br>&nbsp;<br>&nbsp;');
           return ($this->silent) ? false : die($button_back);
         }
      }

      ///pokud je zaroven v editu upload a rename
      $GLOBALS['RENAME'] = strtr(trim($GLOBALS['RENAME']),'\/:*?"<>|&','__________');
      if($GLOBALS['RENAME'] && $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name']){
        $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name'] = $GLOBALS['RENAME'];
        unset($GLOBALS['RENAME']);
      }

      if($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name']){

        $file_name = $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name'];

        ///jedna se o ZIP
        $file_is_zip = $this->isZipTypeFile($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['type']);

        ///kontrola na existenci stejne prilohy pro dany zaznam a agendu
        $file_is_exists = $this->stg_obj->uplFileExists($file_name);

        ///jedna se o EDIT a jmeno souboru je jine, nez puvodni
        $upl_file_have_new_name = ($GLOBALS['EDIT_ID'] && strcasecmp($this->UPL_RECORD['NAME'],$file_name));

        ///pekne zkurvena podminka, ale vypada to, ze maka jak ma
        ///podminka se snazi vystihnou stav kdy nazev nebo novy nazev je shodny s jinym existujicim souborem, nebo se pta pouze na archivaci
        if(
            (($file_is_exists &&
              (substr($GLOBALS['COSTIM'],0,6)!='archiv' ||
                (substr($GLOBALS['COSTIM'],0,6)=='archiv' && $GLOBALS['RENAME_NEW'] && strcasecmp($this->UPL_RECORD['NAME'],$file_name))
               )) ||
             ($GLOBALS['EDIT_ID'] && substr($GLOBALS['COSTIM'],0,6)!='archiv') ||
             ($file_is_zip && !$GLOBALS['EDIT_ID'] && !$GLOBALS['COSTIM'] && !$GLOBALS['RENAME_NEW'])
            )
          ){
          $frm_rename = false;
          $frm_archiv = false;
          $frm_zip    = false;

          $uniqid_dir = $GLOBALS['UPL_DIR'] ? $GLOBALS['UPL_DIR'] : uniqid('');
          $tmp_dir = $this->tmp_dir.'/'.$uniqid_dir.'/';
          
          ///tady se musi soubor zazalohovat, aby se mohl v dalsim kroku pouzit
          if(!$GLOBALS['UPL_DIR']) {
            
            CreateDirAll($tmp_dir, true, 0777);
            if(!@move_uploaded_file(FileSystemConvertFNToFS($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name']), FileSystemConvertFNToFS($tmp_dir.$file_name))){
              $this->flushMesg($GLOBALS['RESOURCE_STRING']['file'].
                               ' <i>'.$file_name.'</i> '.
                               $GLOBALS['RESOURCE_STRING']['file_cant_load_tmp'].
                               '!!!<br>&nbsp;<br>&nbsp;');
              return ($this->silent) ? false : die($button_back);
            }
          }  
          include_once($GLOBALS['TMAPY_LIB'].'/oohformsex.inc');

          $f = new formex;
          $GLOBALS['show_typ']=2;
          if($GLOBALS['EDIT_ID']) $f->ae(array( type=>'hidden', name=>'EDIT_ID'));
          $f->ae(array( type=>'hidden', name=>'show_typ'));
          $f->ae(array( type=>'hidden', name=>'UPL_FILE', 'value'=>$file_name));///POZOR: param 'value' zafunguje pouze v pripade ze neexistuje globalni promenna
          $f->ae(array( type=>'hidden', name=>'UPL_DIR', 'value'=>$uniqid_dir));
          $f->ae(array( type=>'hidden', name=>'UPL_TYPE', 'value'=>$GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['type']));
          $f->ae(array( type=>'hidden', name=>'UPL_SIZE', 'value'=>$GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['size']));
          $f->ae(array( type=>'submit', name=>'__', value=>'Pokračovat'));
          $f->ae(array( type=>'button_close', name=>'___', value=>'Konec'));

          if(!$GLOBALS['EDIT_ID'] && $file_is_exists){  ///INSERT se stejnym nazvem
            $frm_caption = "<div class=\"caption\">POZOR: $file_name existuje !</div>\n";
            $f->ae(array( type=>"text", name=>'RENAME_NEW', size=>20, required=>true, label=>'Nový přejmenovat na', 'add'=>'class="required"'));
            $frm_rename = true;
          }
          elseif($GLOBALS['EDIT_ID'] && !$file_is_exists){  ///EDIT pod jinym nazvem
            $frm_caption = "<div class=\"caption\">Archivovat původní soubor ?</div>\n";
            $frm_archiv = true;
          }
          elseif($GLOBALS['EDIT_ID'] && $file_is_exists){  ///EDIT pod stejnym nazvem (jeste se musi rozlisit, zda je shoda se stejnym zaznamem, nebo s jinym)
            if($upl_file_have_new_name){ ///nazev souboru je neni shodny s nazvem prave editovaneho zaznamu
              $frm_caption = "<div class=\"caption\">POZOR: $file_name má shodný název s jinou přílohou!</div>\n";
              $f->ae(array( type=>'text', name=>'RENAME_NEW', size=>20, required=>true, label=>'Nový přejmenovat na', 'add'=>'class="required"'));
              $frm_rename = true;
            }else{
              $frm_caption = "<div class=\"caption\">Archivovat původní soubor ?</div>\n";
            }
            $frm_archiv = true;
          }
          elseif(!$GLOBALS['EDIT_ID'] && $file_is_zip){ //INSERT ZIP souboru
            $frm_caption = "<div class=\"caption\">Vkládáte ZIP soubor</div>\n";
            $frm_zip = true;
          }

          ///vytvori vlastni form
          $f->start('frm','GET','ug_file.php','','frm');
          echo $frm_caption;
          ?>
          <table width="100%">
          <tr><td align="left">
          <br>
          <?php
          if($frm_rename){
            echo '<span class="text">Nový přejmenovat na</span>&nbsp;';
            echo $f->se('RENAME_NEW');
            echo "<br>\n";
          }
          if($frm_archiv){
            echo '<input type="radio" name="COSTIM" value="archiv_a" class="radio" checked="checked"><span class="text">původní archivovat ANO</span><br>';
            echo '<input type="radio" name="COSTIM" value="archiv_n" class="radio"><span class="text">původní archivovat NE</span>';
          }
          if($frm_zip){
            echo '<input type="radio" name="COSTIM" value="unzip_n" class="radio" checked="checked"><span class="text">NEROZBALOVAT a ponechat jako ZIP</span><br>';
            echo '<input type="radio" name="COSTIM" value="unzip_a" class="radio"><span class="text">rozbalit a uložit jednotlivé soubory z archivu zvlášť</span>';
          }
          ?>
          <tr><td><hr></td></tr>
          <tr><td align="right"><?php echo $f->se("__")?>&nbsp;&nbsp;&nbsp;<?php echo $f->se("___")?>
          </table>
          <?php

          $fields = array();
          foreach($this->upl_tab_met as $arr) $fields[]=$arr[name];

          CreateHiddenForVars(true,'',$fields);

          $f->finish();
          ///konec mezikroku pri shode jmen, nebo dotazu na archivaci pri editu
          return true;
        }
        
        if($tmp_file && !$tmp_dir) $tmp_dir = dirname($tmp_file);

        ///archivace puvodniho souboru
        if($GLOBALS['COSTIM']=='archiv_a' && $GLOBALS['EDIT_ID']){

          //onma, aby se predal nazev souboru
          if ($GLOBALS['archiv_file_system']) $this->UPL_RECORD['NAME']=$GLOBALS['UPL_FILE'];
          
          $archiv_file = $this->stg_obj->archiveFile();
        }
                 
        $zip_files_arr = array();

        //pri INSERTU se vlozil ZIP soubor a chce jej rozbalit a ulozit jednotlive soubory
        if($GLOBALS['COSTIM']=='unzip_a' && !$GLOBALS['EDIT_ID']){

          $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_from_archive'].' ...');

          //rozbaleni archivu a smazani ZIP souboru
          $output = array();
        
          exec("unzip -j -o $tmp_file -d $tmp_dir", $output);
          //print_r($output);
          unlink(FileSystemConvertFNToFS($tmp_file));
          //tyto prikazy by mohli pomoct pri prekodovani ceskych nazvu souboru v zip archivu, ale stejnak to nefunguje 100%
          //exec("/tmp/convmv-1.07/convmv --notest -f iso-8859-1 -t utf-8 $zip_dir/*");
          //exec("/tmp/convmv-1.07/convmv --notest -f cp850 -t utf-8 $zip_dir/*");
          $this->flushMesg('<hr>');

          $no_exist_some_zipfile = true;

          //vypis souboru z archivu
          $d = dir($tmp_dir);

          while($entry=$d->read()) {

            if($entry[0]!='.'){

              $entry = FileSystemConvertFNFromFS($entry);

              if($this->stg_obj->uplFileExists($entry)) {  
                $no_exist_some_zipfile = false;
                $this->flushMesg($entry.'&nbsp;<i><b>'.$GLOBALS['RESOURCE_STRING']['file_exists'].'</b></i>');
              }elseif(!file_exists(FileSystemConvertFNToFS($tmp_dir.'/'.$entry))){
                $this->flushMesg($entry.'&nbsp;<i><b>'.$GLOBALS['RESOURCE_STRING']['file_this_not_found'].'</b></i>');
              }else{
                $this->flushMesg($entry);
                $zip_files_arr[] = $entry;
              }

            }
          }
          $d->close();

          $tmp_file = '';

        }
        
        $files_arr = array();

        ///dle typu vkladani souboru pripravy pole $files_arr
        if($tmp_file){

          $files_arr[] = array($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'], $file_name, true);

        }elseif($zip_files_arr && $no_exist_some_zipfile){ //jedna se o rozbaleny ZIP archiv a nema zadne existujici soubory jiz uploadovane

          foreach($zip_files_arr as $zip_file)
            $files_arr[] = array($tmp_dir.'/'.$zip_file, $zip_file, true);

        }else{//klasicky uploadovany soubor
          $files_arr[] = array($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'], $file_name, 1);
        }

        
        ///ulozi soubor(y), zjisti informace o nem a vytvori nahledy
        if($files_arr){

          $for_RUN_GLOBALS = array();

          foreach($files_arr as $file_arr){
            
            $file_name = $file_arr[1];
            
            $this->stg_obj->saveFile($file_arr[0], $file_name, $file_arr[2]);

            $info = $this->stg_obj->getInfoAboutFile($file_name);

            //$for_RUN_GLOBALS[$file_name]['TYPEFILE'] = $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['type'];
            $for_RUN_GLOBALS[$file_name]['TYPEFILE'] = $info['typefile'];
            $for_RUN_GLOBALS[$file_name]['FILESIZE'] = $info['filesize'];
            $for_RUN_GLOBALS[$file_name]['NAME'] = $file_name;
            $for_RUN_GLOBALS[$file_name]['DIRECTORY']  = $info['directory'];

            //navic, pokud se jedna o obrazek
            if($info['imagefile']){ ///jedna se o obrazek
              $for_RUN_GLOBALS[$file_name]['ISIMAGE'] = 'y';
              $for_RUN_GLOBALS[$file_name]['WIDTH'] = $info['imagefile'][0];
              $for_RUN_GLOBALS[$file_name]['HEIGHT'] = $info['imagefile'][1];
              $for_RUN_GLOBALS[$file_name]['TYPEFILE'] = $info['imagefile']['mime'];
              $this->CreatePreview($file_name, $info['imagefile'], false, false, true);

            }else{
              $for_RUN_GLOBALS[$file_name]['ISIMAGE'] = 'n';
              $for_RUN_GLOBALS[$file_name]['WIDTH'] = false;
              $for_RUN_GLOBALS[$file_name]['HEIGHT'] = false;
            }
          }

        }else{

          $this->flushMesg('<br>'.$GLOBALS['RESOURCE_STRING']['file'].' <i>'.$file_name.'</i> '.$GLOBALS['RESOURCE_STRING']['file_cant_load'].' !!!<br>&nbsp;<br>&nbsp;');
          return ($this->silent) ? false : die($button_back);

        }


      }

      if ($GLOBALS['EDIT_ID'] && trim($GLOBALS['RENAME'])){

        $frename = strtr(trim($GLOBALS['RENAME']),'\/:*?"<>|&','__________');

        if($this->stg_obj->uplFileExists($frename)) {
          $this->flushMesg('<div class="text">'.$GLOBALS['RESOURCE_STRING']['file_name_exists'].'</div><br><br>');
          return ($this->silent) ? false : die($button_back);
        }

        if (!$this->stg_obj->renameFile($frename)){
          $this->flushMesg('<div class="text">'.$GLOBALS['RESOURCE_STRING']['file_cant_rename'].'</div><br><br>');
          return ($this->silent) ? false : die($button_back);
        }
        $GLOBALS['NAME'] = $frename;
      }

    }//konec if(!$GLOBALS['DELETE_ID'])
    

    ///zde se podstrci fci Run() jine hodnoty
    $GLOBALS['PROPERTIES']['AGENDA_TABLE'] = $this->upl_table;
    $GLOBALS['PROPERTIES']['AGENDA_ID'] = 'ID';
    $GLOBALS['PROPERTIES']['DB_NAME'] = $this->config['DB_NAME']?$this->config['DB_NAME']:'DB_DEFAULT';
    $GLOBALS['PROPERTIES']['FIELD_OWNER_ID'] = 'OWNER_ID';
    $GLOBALS['PROPERTIES']['FIELD_UPDATE_DATE'] = 'LAST_DATE';
    $GLOBALS['PROPERTIES']['FIELD_UPDATE_TIME'] = 'LAST_TIME';
    $GLOBALS['PROPERTIES']['FIELD_UPDATE_ID'] = $GLOBALS['LAST_USER_ID'];

    ///no a zde dochazi k vlastnimu uprave zaznamu !!!
    if($for_RUN_GLOBALS){
      foreach($for_RUN_GLOBALS as $file_name_arr){
        foreach($file_name_arr as $name => $value) $GLOBALS[$name] = $value;
        unset($GLOBALS['ID']);
        $GLOBALS['NEW_ID_UPLOAD'] = Run_(array('outputtype'=>1,'no_unsetvars'=>true));
      }
    }else{
      $GLOBALS['NEW_ID_UPLOAD'] = Run_(array('outputtype'=>1, 'no_unsetvars'=>true));
    }

    //FullText - begin - TOKR
    if ($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']) {
      if ($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_FILE'])
        include_once(FileUp2('.admin/db/'.$GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_FILE']));
      if ($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_NAME'])
        $qft = new $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_NAME'];
    }
    //end

    //FullText - begin - TOKR
    if ($qft && $GLOBALS['NEW_ID_UPLOAD']) {
      InsertIntoFullText(&$qft, $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['TABLE'], $GLOBALS['NEW_ID_UPLOAD'], $this->main_dir.$GLOBALS['DIRECTORY'].$GLOBALS['NAME']);
    }

    $table_h = $GLOBALS['upl_table'].'_h';

    if($GLOBALS['EDIT_ID']){ ///puvodni zapise do historie

      $meth = $this->q->metadata($table_h);
      foreach($this->UPL_RECORD as $key => $val) $GLOBALS[$key]=$val;

      if($archiv_file){ ///byl archivovan i soubor
        $GLOBALS['NAME']=$archiv_file;
        $GLOBALS['DIRECTORY'] .= $this->stg_obj->dir_for_archive;
        ///aby se pripadne nazvy v historii prejmenovali podle nazvu archivniho souboru
        $sql = "UPDATE $table_h SET name='$GLOBALS[NAME]', directory='$GLOBALS[DIRECTORY]' WHERE id=$GLOBALS[EDIT_ID] AND name='$this->UPL_RECORD[NAME]'";
        $this->q->query($sql);
      }

      $seth = "INSERT INTO $table_h ";

      //onma, nepredavalo se mi ID zaznamu, resp. se mi nekde ztratilo cestou.
      if ($GLOBALS['archiv_file_system']) $GLOBALS['ID']=$GLOBALS['FILE_ID'];

      $seth .= CreateValuesSQLFromVar($meth);

      $this->q->query($seth);

      //FullText - begin - TOKR
      if ($qft) {
        InsertIntoFullText(&$qft, $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['TABLE'].'_h', $GLOBALS['NEW_ID_UPLOAD'], $this->main_dir.$GLOBALS['DIRECTORY'].$GLOBALS['NAME'], $q->getlastid($table_h, ID_H));
      }

    }
    elseif($GLOBALS['DELETE_ID']){ ///jedna se o mazani

      ///smaze vlastni soubor z disku
      if (!$this->stg_obj->deleteFile()){
          $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_cant_remove'].'<br>&nbsp;<br>&nbsp;');
          return ($this->silent) ? false : die($button_back);

      }
      
      ///smaze soubory z archivu

      ///smaze db zaznamy z histori
      $sql = 'DELETE FROM '.$table_h.' WHERE id='.$GLOBALS['DELETE_ID'];
      $this->q->query($sql);

      //FullText - begin - TOKR
      if ($qft) {
        $qft->query('DELETE FROM '.$GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['TABLE'].' WHERE id='.$GLOBALS['DELETE_ID']);
        $qft->query('DELETE FROM '.$GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['TABLE'].'_h WHERE id='.$GLOBALS['DELETE_ID']);
      }

    }
    
    ///vycisti po sobe TMP
    if(file_exists($tmp_dir)) { 
      foreach (glob($tmp_dir.'/*.*') as $filename) {
        unlink(FileSystemConvertFNToFS($filename));
      }
      rmdir(FileSystemConvertFNToFS($tmp_dir));
    }

    // onma, konverze souboru
    if ($GLOBALS[CONVERT]=='y')
    {
      $GLOBALS[CONVERT]='n'; //musime to vypnout
      set_time_limit(0);
      include_once($GLOBALS['TMAPY_LIB'].'/upload/functions/SOAP_602_print2pdf.php');

      //pod stejnzm souborem ulozi 
      $a=new SOAP_602_print2pdf($SERVER_CONFIG["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]);
      list($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'],$file_name_pdf)=$a->ConvertFile($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'],$file_name);

      $record_id = $_POST['RECORD_ID'];
      $GLOBALS['EDIT_ID'] = $GLOBALS['NEW_ID_UPLOAD'];
      $GLOBALS['FILE_ID'] = $GLOBALS['NEW_ID_UPLOAD'];
      $GLOBALS['RECORD_ID'] = $record_id ;
      $GLOBALS['AGENDA_IDENT'] = $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT'];
      $GLOBALS['UPLOAD_FILE'] = $file_name;
      $GLOBALS["UPL_FILE"] = $file_name;    
      $GLOBALS['COSTIM']='archiv_a'; //preved puvodni do archivu
      $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name'] = basename($file_name_pdf);
      $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'] = $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'];

      $GLOBALS['archiv_file_system'] = true;
      $GLOBALS['RENAME_NEW'] = $file_name_pdf;

      $this->AGENDA_RECORD = $this->GetRecordAgenda($record_id);
      
      $ret = $this->actionRun();

    }



    if(!$this->no_close_after_delete){
      echo "<script language=\"JavaScript\" type=\"text/javascript\">\n";
      echo "  if (window.opener.parent.frames[1]!=null) {\n";
      echo "    window.opener.parent.frames[1].location.reload(1);\n";
      echo "  }else if(window.opener!=null) {\n";
      echo "    window.opener.location.reload(1);\n";
      echo "    if(window.opener.opener.parent.frames[1]!=null) \n";
      echo "       window.opener.opener.parent.frames[1].location.reload(1);\n";
      echo "  }\n";
      echo "  window.close();\n";
      echo "</script>\n";
    }

  }


  /**
   Delete
  **/
  function showUploadDelete() {

    include_once($GLOBALS['TMAPY_LIB'].'/oohformsex.inc');
    include_once(Fileup2('.admin/access_.inc'));

    if ((!Access())||(!HasSubRole('delete'))||(!$this->hasAccessToUploadRecord('delete'))):

      include_once(FileUp2('html_error.inc'));

      $f = new formex;
      $f->ae(array( type=>'button_close', name=>'__'));
      $f->start('','','','','');
      $f->se('__');
      $f->finish();

    elseif($GLOBALS['actiondelh']):  //maze z historie

      if(!$this->stg_obj->deleteFile('', true)) {
        $this->flushMesg($GLOBALS['RESOURCE_STRING']['file_cant_remove'].'<br>&nbsp;<br>&nbsp;');
        return ($this->silent) ? false : die($button_back);
      }

      echo "<script language=\"JavaScript\" type=\"text/javascript\">\n";
      echo "  if (window.opener.parent.frames[1]!=null) {\n";
      echo "    window.opener.parent.frames[1].location.reload(1);\n";
      echo "  }else if(window.opener!=null) {\n";
      echo "    window.opener.location.reload(1);\n";
      echo "    if(window.opener.opener.parent.frames[1]!=null) \n";
      echo "       window.opener.opener.parent.frames[1].location.reload(1);\n";
      echo "  }\n";
      echo "  window.close();\n";
      echo "</script>\n";

    else:

      $f = new formex;

      if($GLOBALS['DELETE_ID_H']): ///mazani souboru z historie

        echo "<span class=\"caption\">".$GLOBALS['RESOURCE_STRING']['file_from_history']." - ".$GLOBALS["RESOURCE_STRING"]["delete"]."</span>\n";
        echo "<h4 class=filterblock>".$GLOBALS['RESOURCE_STRING']['really_delete_history']."</h4><br>\n";
        echo "<div class=text>".$this->UPL_RECORD['DIRECTORY']."<b>".$this->UPL_RECORD['NAME']."</b></div>\n";

        $GLOBALS['show_typ']=3;
        $f->ae(array( type=>'hidden', name=>'DELETE_ID_H'));
        $f->ae(array( type=>'hidden', name=>'actiondelh', value=>'1'));

      else:

        echo "<span class=\"caption\">".$GLOBALS['RESOURCE_STRING']['tooltip_upload']." - ".$GLOBALS["RESOURCE_STRING"]["delete"]."</span>\n";
        echo "<h3 class=filterblock>".$GLOBALS["RESOURCE_STRING"]["record_delete_confirm"]."</h3>\n";

        $this->ShowUploadTable();

        $GLOBALS['show_typ']=2;
        $f->ae(array( type=>'hidden', name=>'DELETE_ID'));

      endif;

      $frm_str="\n";
      $f->ae(array( type=>'hidden', name=>'show_typ'));
      $f->ae(array( type=>'hidden', name=>'upload_modul'));
      $f->ae(array( type=>'submit', name=>'__', value=>$GLOBALS['RESOURCE_STRING']['button_yes']));
      $f->ae(array( type=>'button_close', name=>'___', value=>$GLOBALS['RESOURCE_STRING']['button_no']));

      $f->start('frm_delete','GET','ug_file.php','','');
      echo $frm_str;
      echo "<table width='100%'>";
      echo "<tr><td align='right'>\n";
      $f->se('__');
      echo '&nbsp;&nbsp;&nbsp;';
      $f->se('___');
      echo "</table>\n";
      $f->finish();

    endif;
  }



  /**
  FullText - tokr
  **/
  function showUploadText() {

    include_once(FileUp2('.admin/upload_fce_.inc'));

    if ($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_FILE'])
      include_once(FileUp2('.admin/db/'.$GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_FILE']));

    if ($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_NAME']) {
      $qft = new $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['DB_NAME'];
      $qft->query('SELECT text FROM '.$GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']['TABLE'].' WHERE id = '.Round($GLOBALS['ID']));
      if ($qft->next_record()) $text = $qft->Record['TEXT'];
      $text = preg_replace('/(.{100})/', '\\1'."\n", $text);
      $text = preg_replace('/\.{3,}/', '...', $text);
      if ($GLOBALS['FULLTEXT_UPLOAD']) {
        $ft = Upload_GetFulltextRegularExp($GLOBALS['FULLTEXT_UPLOAD'],true);
        $colors = array('red','green','blue','magenta','darkgray','black','darkblue');
        $i=0;
        foreach($ft as $val) {
          if ($val)
            $text = preg_replace('/'.$val.'/', ' <span style="color:white;background-color:'.$colors[$i++].'">\\1</span> ', $text);
          if ($i > Count($colors)-1) $i=0;
        }
      }

      echo '<pre>'.$text.'</pre><script type="text/javascript">var els=document.getElementsByTagName("SPAN");'."\n".'if (els && els[0]) window.scrollBy(0,els[0].offsetTop-50);</script>';
    }

  }


  function createPreview($file, $info, $size_arr=array(), $no_exec=false, $force=false){

    $ret = array();

    if(!$size_arr) $size_arr = $this->config['AGENDA_PROPERTIES']['UPLOAD_CONFIG']['MODULES'][$this->modul_name]['PREVIEW_SIZE_RATIO']?$this->config['AGENDA_PROPERTIES']['UPLOAD_CONFIG']['MODULES'][$this->modul_name]['PREVIEW_SIZE_RATIO']:$this->config['PREVIEW_SIZE_RATIO'];
    if(!$size_arr) $size_arr = array(80);

    $WIDTH  = $info[0];
    $HEIGHT = $info[1];

    if(!$WIDTH || !$HEIGHT) return false;
    
    foreach($size_arr as $size){

      // nastaveni procentualni zmeny velikost obrazku podle vetsi strany
      if($WIDTH>$HEIGHT)
        $ratio = $WIDTH / $size;
      else
        $ratio = $HEIGHT / $size;

      //a ted priprav velikostne odpovidajici vysledek
      $new_w = round($WIDTH / $ratio);
      $new_h = round($HEIGHT / $ratio);

      $ret[$size] = $this->stg_obj->createPreview($file, $size, $new_w, $new_h, $no_exec, $force);
      
    }

    return $ret;
  }
  
  
  function isAllowedFileType(&$ftype){
     
    $ret = false;

    $mime_type = $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['type'];
    
    if($this->only_file_types) { 
    
      if(!$mime_type) $mime_type = getMimeContentType($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name']);
      $file_type = end(explode('.', $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name']));

      foreach($this->only_file_types as $type){
        
        if(stristr($mime_type, $type) || stristr($file_type, $type)) $ret = true;
        
        if($ret) break;  
      }
    
    }else {
      
      $ret = true;
    }
    
    $ftype = $mime_type;     
    return $ret;
  }
  

  function isApplTypeFile($mime_type){

    $ret = false;

    switch($mime_type):
      case 'application/msword' :
      case 'application/vnd.ms-excel' :
      case 'application/pdf' :
      case 'message/rfc822' :
      case 'text/rtf' :
      case 'application/octet-stream':
      case 'application/vnd.ms-project' :
      case 'application/vnd.ms-powerpoint' : $ret = true; break;
    endswitch;

    if(!$ret && strstr($mime_type,'application')) $ret = true;

    return $ret;
  }



  function isZipTypeFile($mime_type){

    $ret = false;

    switch($mime_type):
      case 'application/zip' :
      case 'application/zip-compressed' :
      case 'application/x-zip-compressed' : $ret = true; break;
    endswitch;

    return $ret;
  }

  
  
  function isFileExistsByID ($id, $history=false) {

    $this->UPL_RECORD = $this->GetRecordTable($id, $history);
    
    $ret = $this->stg_obj->uplFileExists();
    
    return $ret;
  }
  
  
  //pro kompatibilitu se starsi verzi
  function deleteAllUploadForAgenda($record_id){
    $this->deleteAllUploadForAgendaRecord($record_id);
  }

  ///smaze vsechny uploady, ktere patri konkretni agende a zaznamu
  function deleteAllUploadForAgendaRecord($record_id, $delete_id_arr=array()){

    if(!$record_id) return false;

    $AGENDA_DELETE_ID = $GLOBALS['DELETE_ID'];

    if(!$this->hasAccessToUploadRecord('delete')){
      include_once(FileUp2('html_error.inc'));
      return ($this->silent) ? false : die($button_back);
    }

    $q = $this->q;
    
    //podpora pro smazani pouze urcitych ID -> $delete_id_arr   FIGA
    if (count($delete_id_arr)>0) $where_add = ' AND id in ('.implode(',', $delete_id_arr).')';

    $q->query('SELECT * FROM '.$this->upl_table.' WHERE record_id = '.$record_id.' AND agenda_ident=\''.$this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']."'".$where_add);

    while($q->next_record()){

       $this->UPL_RECORD = $q->Record;

       $GLOBALS['DELETE_ID'] = $this->UPL_RECORD['ID'];

       $this->no_close_after_delete = true;
       $this->actionRun();
    }

    $this->no_close_after_delete = false;
    $GLOBALS['DELETE_ID'] = $AGENDA_DELETE_ID;

  }

  //smaze jeden soubor z uploadu, onma 2009-10-16
  function deleteRecordUploadForAgendaRecord($record_id,$file_id){

    if(!$record_id) return false;

    if(!$file_id) return false;

    $AGENDA_DELETE_ID = $GLOBALS['DELETE_ID'];

    if(!$this->hasAccessToUploadRecord('delete')){
      include_once(FileUp2('html_error.inc'));
      return ($this->silent) ? false : die($button_back);
    }

    $q = $this->q;

    $q->query('SELECT * FROM '.$this->upl_table.' WHERE record_id = '.$record_id.' and id = '.$file_id.' AND agenda_ident=\''.$this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']."'");

    while($q->next_record()){

       $this->UPL_RECORD = $q->Record;

       $GLOBALS['DELETE_ID'] = $this->UPL_RECORD['ID'];

       $this->no_close_after_delete = true;
       $this->actionRun();
    }

    $this->no_close_after_delete = false;
    $GLOBALS['DELETE_ID'] = $AGENDA_DELETE_ID;

  }

  

  function isAnyUploadForRecord($record_id, $agenda_ident = null){

    $this->AGENDA_RECORD = $this->GetRecordAgenda($record_id);

    $q = $this->q;

    $add_where='';
    if($this->config['USER_INFO']['is_anonymous'] && $this->config['use_anonym_access']) $add_where.=" AND anonym='y'";

    $q->query('SELECT count(*) as pocet FROM '.$this->upl_table.
              ' WHERE agenda_ident=\''.
              ($agenda_ident ? $agenda_ident : $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT']).
              '\' AND record_id = '.
              $this->AGENDA_RECORD[$this->config['AGENDA_PROPERTIES']['AGENDA_ID']].
              $add_where);

    $q->next_record();

    return $q->Record['POCET'];
  }


  function saveFileToAgendaRecord($file, $record_id){
    
    //require_once(FileUp2('.admin/run2_.inc')); //tady vlozit nejde, delaji tam neplechu header() v nocahce.inc
    $ret = array();

    if(file_exists(FileSystemConvertFNToFS($file))){
    
      $GLOBALS['RECORD_ID'] = $record_id;
      $GLOBALS['AGENDA_IDENT'] = $this->config['AGENDA_PROPERTIES']['AGENDA_IDENT'];
      
      $GLOBALS['UPLOAD_FILE'] = $file;
      $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['name'] = basename($file);
      $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'] = $file;
      
      $this->AGENDA_RECORD = $this->GetRecordAgenda($record_id);
      
      $this->no_close_after_delete = true;
      $this->silent = true;
      

      $ret = $this->actionRun();
      
      if(!$ret) {
        $ret['err_msg'] = $this->message_cache[0];
        $ret['err_no'] = 1;
        //onma, 2009-10-13, vraci se navic ID ulozeneho souboru
        $ret['file_id'] = $GLOBALS['NEW_ID_UPLOAD'];
      }
      
    }else{
      $ret['err_msg'] = $file.' not exist';
      $ret['err_no'] = 1;
    }
    
    return $ret;
  }

}
