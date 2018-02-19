<?php
require("tmapy_config.inc");

require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

Form_(array("showaccess"=>true, "nocaption"=>false));
require(FileUp2("html_footer.inc"));

if ($_SERVER['REMOTE_USER']=='malyo') {
  echo '<iframe id="ifrm" name="ifrm" src="/empty.php" Xstyle="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>';
  
  ?>
  <br />
  <a href="https://devel-tohu.matej3.tmapserver.cz/ost/csx/csx.php" target="_blank">Iframe sample - supported: Firefox</a><br />
  <a href="#" onclick="openWindow();">Javascript sample (by HTML 5) - supported: Chrome, Firefox</a>

  <script type="text/javascript">

  function openWindow() {  
    var popup = window.open('https://devel-tohu.matej3.tmapserver.cz/ost/csx/csx.php', 'anyWebsite', 'height=570,width=790,left=1,top=1,scrollbars,resizable');
    // Bez timeoutu nestihl handler udalosti zachytit
    window.setTimeout(function () { 
      popup.postMessage("hello there!", "https://devel-tohu.matej3.tmapserver.cz");},
      1000
    );
  }

  function receiveMessage(event) {
    if (event.origin !== "https://devel-tohu.matej3.tmapserver.cz")
      window.alert('edit.php');
    
    window.document.frm_edit.NAZEV_SPISU.value = event.data.item;
    // event.source is popup
    // event.data is "hi there yourself!  the secret response is: rheeeeet!"
  }

  window.addEventListener("message", receiveMessage, false);

  </script>

  <?php
}
else
  echo '<iframe id="ifrm" name="ifrm" src="/empty.php" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>';

?>