<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <meta http- equiv="content-type" content="text/html; charset=iso-8859-2">
  </head>

  <body onload="FillForm()">
    <p>readdata.php</p>
  </body>

  <script type="text/javascript">
    function FillForm() {      
      window.parent.document.frm_edit.NAZEV_SPISU.value='<?php echo $data; ?>';
      window.parent.document.frm_edit.EXT_ID.value='<?php echo $EXT_ID; ?>';
      window.parent.document.frm_edit.KATASTR.value='<?php echo $KATASTR; ?>';      
    }
  </script>

</html>
