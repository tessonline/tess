<?php
/* HEADER */ if ($TWIST_FILE_INFO) {echo __FILE__.': $Id: delete_.inc 129 2014-01-14 13:13:04Z tohu $'.'$Name:  $';exit;}; /* HEADER */

if (!isset($GLOBALS['DELETE_ALL_rec'])) {
  include_once(FileUp2('.admin/nocache.inc'));
  include_once(FileUp2('.admin/agenda_func.inc'));

  $PROPERTIES = loadProperties();;
  $RESOURCE_STRING = $GLOBALS['RESOURCE_STRING']; 
  $captionView = $GLOBALS['RESOURCE_STRING']['delete'];
  $desc = $GLOBALS['RESOURCE_STRING']['record_delete_confirm'];
  $showcount = false;
}
else {
  unset($GLOBALS['DELETE_ALL_rec']);
  $captionView = $GLOBALS['RESOURCE_STRING']['delete_all'];
  $desc = $GLOBALS['RESOURCE_STRING']['record_delete_confirm_all'];
  $showcount = true;
}
  
$captionApp = $PROPERTIES['AGENDA_NAME']; 

if (isset($PROPERTIES['CAPTION_DELETE'])) $captionView = $PROPERTIES['CAPTION_DELETE'];
if (isset($PROPERTIES['MESSAGE_DELETE'])) $desc = $PROPERTIES['MESSAGE_DELETE'];

include_once($GLOBALS['TMAPY_LIB'] . '/oohformsex.inc');
include_once(FileUp2('.admin/brow_.inc'));
//support for WPS
if (!$GLOBALS['PROPERTIES']['NO_DELETE_HEADER']) include_once(FileUp2('html_header.inc'));
include_once(Fileup2('.admin/access_.inc'));

echo '<title>' . $captionView . ' - ' . $captionApp. "</title>\n";
echo "</head>\n";
echo '<body class="delete">' . "\n";

if(is_array($DELETE_ID)) $delete_id = $DELETE_ID;
else $delete_id = array($DELETE_ID); 

if ((!Access())||(!HasSubRole('delete'))||(!HasAccessToRecord('delete', $delete_id[0]))) {

  include_once(FileUp2('html_error.inc'));

  $f = new formex;
  $f->ae(array( type => 'button_close', name => '__'));
  $f->start('', '', '', '', '');
  $f->se('__');
  $f->finish();
}       
else {

  $themeObj = loadThemeConfig(array('lang' => $PROPERTIES['DEFAULT_LANG']));
  $dAdapter = TW_AdapterFactory::getAdapter('Delete', $themeObj);
  
  if($captionView || $captionApp) {
    echo $dAdapter->getCaption($captionView, $captionApp);
  }
  
  if (isset($DELETE_ID)) {
    
    if($desc) echo $dAdapter->getDescription($desc);
    
    $GLOBALS[$PROPERTIES['AGENDA_ID']] = $DELETE_ID;
    
    if ($image_dir) {
      Table(array(
        'setvars' => true, 
        'nocaption' => true, 
        'nopaging' => true, 
        'showcount' => $showcount, 
        'showedit' => false, 
        'showdelete' => false, 
        'noprint' => true, 
        'noexport' => true, 
        'noaccesscondition' => true, 
        'showaccess' => true, 
        'image_dir' => $image_dir, 
        'script_extension' => $script_extension, 
        'noshowrelation' => true, 
        'noshowinsert2clip' => true, 
        'noshowrelationbreak' => true
      ));
    }
    else {
      Table(array(
        'setvars' => true, 
        'nocaption' => true, 
        'nopaging' => true, 
        'showcount' => $showcount, 
        'showinfo' => false,
        'showedit' => false,
        'showdelete' => false,
        'noprint' => true, 
        'noexport' => true, 
        'noaccesscondition' => true, 
        'showaccess' => true, 
        'noshowrelation' => true, 
        'noshowinsert2clip' => true, 
        'noshowrelationbreak' => true
      ));
    }
  } 
  else {
    echo '<h3 class=filterblock>' . $GLOBALS['RESOURCE_STRING']['record_delete_empty'] . "</h3><br>\n";
  }
  
  $f = new formex;
  
  $frm_str = "\n";
  
  if(is_array($DELETE_ID)) {
    foreach($DELETE_ID as $id)
      $frm_str .= '<input type="hidden" name="DELETE_ID[]" value="' . htmlspecialchars($id) . "\">\n";
  } else {
    $f->ae(array( type => 'hidden', name => 'DELETE_ID', value => $DELETE_ID));
  }
  
  if (is_array($formvars)) {
    foreach($formvars as $key => $val) {
      if (is_integer($key)) {
        $key = $val;
        $val = $GLOBALS[$val];
      }
      $f->ae(array( 'type' => 'hidden', 'name' => $key, 'value' => $val));
    }
  }
  
  $f->ae(array(type => 'submit', name => '__', value => $GLOBALS['RESOURCE_STRING']['delete']));
  
  if ($BUTTON_BACK_AS_NO) {
    $f->ae(array(type => 'button_back', name => '___', value => $GLOBALS['RESOURCE_STRING']['button_close']));
  } else {
    $f->ae(array(type => 'button_close', name => '___', value => $GLOBALS['RESOURCE_STRING']['button_close']));
  }
  
  $f->start('frm_delete', 'GET', 'run.' . ($script_extension ? $script_extension : 'php'), '', '');
  $f->start('frm_delete', 'GET', 'run.' . ($script_extension ? $script_extension : 'php'), '', '');
  
  // Moznost vlozeni vlastnich formularovych poli do formulare 'Smazat zaznam'
  // Napr.: 'Duvod mazani/stornovani'
  if ($PROPERTIES['USE_DELETE_FORM']) {    
    
    $file_sch = FileUp2('.admin/delete_schema.inc');
    if (is_File($file_sch)) {
      include($file_sch);
    }
    
    $f->schema = array_merge((array) $f->schema, (array) $FORM_CONFIG['schema']);
    
    $f->classrequired = 'required';
    $f->classfrozen = 'frozen';
    $f->classblock = 'inputblock';
    
    $f->show_in_table();
  }
  
  
  echo $frm_str;
  echo $dAdapter->getButtons($f->ge('__'), $f->ge('___'));

  if(is_array($DELETE_ID) && count($DELETE_ID) && $GLOBALS['_count_delete_all_noaccc_']){
  ?>
  <script language="JavaScript" type="text/javascript">
  <!--
  if(!confirm('Nemáte právo mazat <?php echo $GLOBALS['_count_delete_all_noaccc_']?> záznam(ů).\n\nChcete mazat ostatní ?'))
    window.close();
  //-->
  </script>
  <?php 
  }

  $f->finish();     
}

if(!$NO_HTML_FOOTER) include_once(FileUp2('html_footer.inc'));
