<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

Run_(array("showaccess"=>true,"outputtype"=>1));

echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
//  window.close();
</script>
';

require_once(Fileup2("html_footer.inc"));  