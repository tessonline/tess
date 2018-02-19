<?php
require("tmapy_config.inc");
require(FileUp2(".admin/isds_.inc"));
require(FileUp2(".admin/config.inc"));

$podaci_cislo = 'UKRUK123456789';
//header("Content-type: image/png");
//header("Content-type: image/png");
        require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf_barcodes_1d.php');
         $barcodeobj = new TCPDFBarcode($podaci_cislo, 'C128');
         $image = $barcodeobj->getBarcodePngData(5,4);

echo '<html>
    <body>
        <img src="data:image/png;base64,'.base64_encode($image).'" alt="" height=50 width=800/>
    </body>
</html>';
