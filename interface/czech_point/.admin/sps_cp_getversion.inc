<?php
//Login czechpointu do serveru 
Function GetVersion() 
{

    $text='(GetVersion)';
    WriteLog($software_id,$text,$session);
    $return='<ns1:GetVersionResponse xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:GetVersionResult>1.0</ns1:GetVersionResult> 
      </ns1:GetVersionResponse>
    ';
    return $return;
}
?>
