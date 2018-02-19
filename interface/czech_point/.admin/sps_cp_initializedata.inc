<?php
//Login czechpointu do serveru 
Function InitializeData()  {

    $text='(InitializeData)';
    WriteLog($software_id,$text,$session);
    $return='<ns1:InitializeDataResponse xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:Exception>Not implemented</ns1:Exception> 
      </ns1:InitializeDataResponse>
    ';
    return $return;
}
?>
