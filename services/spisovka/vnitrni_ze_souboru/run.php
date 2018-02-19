<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
require_once(FileUp2(".admin/classes/dokument/Txt.php"));
include_once(FileUp2('.admin/upload_.inc'));

$temp_dir_name = uniqid();
$dir = $GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar'].$temp_dir_name;

mkdir($dir);
$path = $dir."/".$GLOBALS['ZE_SOUBORU_name'];

copy( $GLOBALS['ZE_SOUBORU'], $path);

$ext = pathinfo($GLOBALS['ZE_SOUBORU_name'], PATHINFO_EXTENSION);
$doc = new Txt();

$load_content = true;

switch ($ext) {
  case "txt":
    $load_content = true;
    break;
  case "pdf":
    $load_content = false;
    break;
  case "msg":
    $load_content = false;
    break;
  case "eml":
    $load_content = false;
    break;
}

$url = "/".GetAgendaPath('POSTA')."/";

$prop_path = "";
if (!$load_content) $prop_path="./../../../";

?>
<script>

function documentWidth() {
    return Math.max(
            window.innerWidth,
            parent.document.body.offsetWidth,
            parent.document.documentElement.clientWidth
        );
    	}
  

  var width = documentWidth();

  var window_width = width-110;
 // alert('<?php echo $load_content; ?>');
  if ('<?php echo $load_content; ?>'=="1") {
	  var unit = (width-110) /10;
	  Math.round(unit);
	  if (unit>152) unit = 152;
	  window_width = 10*unit+80;
  } 
  else {
	  if (window_width>820) window_width = 820;
  }

  </script>
  <?php
  
  echo "
 <script> 
function NewWindowFromFile(script) { 
  $.fancybox({
    'type':        'iframe',
    'href':        script,
    'openEffect':  'elastic',
    'closeEffect': 'elastic',
    'helpers': {
      'overlay':{'closeClick': false}
    },
    'autoSize':    true,
    'width': window_width,
    'minHeight':  window.innerHeight-50,
    'tpl': {
      iframe: '<iframe id=\"fancybox-frame{rnd}\" name=\"FromFile\" class=\"fancybox-iframe\" frameborder=\"0\" vspace=\"0\" hspace=\"0\"></iframe>',
      closeBtn: '<a class=\"fancybox-item fancybox-close btn\" title=\"Zavřít\"></a>',
      minMaxBtn: '<a class=\"fancybox-item fancybox-minimize btn darkest-color\" title=\"Minimalizovat/Maximalizovat\"></a>'
    },
    'afterShow': function () {
      for(var ii = 0; ii < frames.length; ii++) {
        if(frames[ii].$) {
          (function(idx) {
            setTimeout(function(){
               frames[idx].$('#fixedsticky').fixedsticky();
            }, 200);
          })(ii);
        }
      }
      $(this.tpl.minMaxBtn).appendTo(this.skin).bind('click.fb', function(e) {
        e.preventDefault();
        $('html').toggleClass('fancybox-minimized');
        $.fancybox.update();
      });      
    },
    'afterClose': function() {
      $('html').removeClass('fancybox-minimized');
      $.ajax({url: \"".GetAgendaPath('VNITRNI_ZE_SOUBORU',false,true)."/delfile.php?del_path=".urlencode($path)."\", success: function(result){
      }});     
      parent.document.location.href = parent.document.location;
    }
  });  
}
 
NewWindowFromFile('".$url."fromfile.php?insert&cacheid=&load_content=".$load_content."&path_content=".urlencode($path)."&type_content=".$ext."&width='+width);

</script>
";
require_once(Fileup2("html_footer.inc"));  

