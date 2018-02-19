<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

if ($GLOBALS['kniha'] == 1) {
  Form_(array("showaccess"=>true, "caption"=>"Generování podacího deníku","showbuttons"=>false));
  echo '<table border=0 align=center><tr><td align=center>';
  echo '<div id = "upl_wait_message2" class = "text" style = "display:none"><img src = "'.FileUpUrl('images/progress.gif').'" title = "pracuji ..." alt = "pracuji ..."></div>';
  echo '<div id="TIMER"></div><br/>';
  echo '<div id="INFORMACE"></div>';
  echo '</td></tr></table>';
  echo '<script>
  function ShowTime(a) {
    $(function() {
          var b = document.frm_edit;
          $( "#INFORMACE" ).load("info.php?ROK="+b.ROK.value+"&MESIC="+b.MESIC.value),
           function() {
          }
      }
    );
  }
  function Start(rok,mesic,sekund) {
    $( "input[name=\'StartGeneruj\']" ).css( "display", "none" );
    document.getElementById(\'upl_wait_message2\').style.display = \'block\';
    document.getElementById(\'INFORMACE\').innerHTML = \'Pracuji\';
    $(function() {
          timer(
              sekund, // milliseconds
              function(timeleft) { // called every step to update the visible countdown
                  document.getElementById(\'TIMER\').innerHTML = "zbývá cca " + timeleft+" sekund";
              },
              function() { // what to do after
                  document.getElementById(\'TIMER\').style.display = "none";
              }
          );
          $( "#INFORMACE" ).load("'.GetAgendaPath('POSTA', false, true).'/output/pdf/knihaposty.php?ROK="+rok+"&MESIC="+mesic),
           function() {
          }
      }
    );
  }
  function timer(time,update,complete) {
      var start = new Date().getTime();
      var interval = setInterval(function() {
          var now = time-(new Date().getTime()-start);
          if( now <= 0) {
              clearInterval(interval);
              complete();
          }
          else update(Math.floor(now/1000));
      },100); // the smaller this number, the more accurate the timer will be
  }
  function HiddenTime() {
     document.getElementById(\'TIMER\').style.display = "none";
  }

  </script>';
}
else
  Form_(array("showaccess"=>true, "caption"=>"Předávací protokoly","noshowclose"=>true));
require(FileUp2("html_footer.inc"));
?>
