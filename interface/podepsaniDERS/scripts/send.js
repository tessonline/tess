    function sendCustomFile(event) {
      /* Duplicitni kod k vrpki.js ws onload */
      /* kontrola jestli jsem pripojenej */
      if (g_ws && g_ws.readyState === 1){
        g_ws.batch = {  // vzdy musim mit oznacene poradi
              'index': 0,
              'size': 0
            };
        vrpki_test_pdfcustom_sent()
        g_ws.progress_fce.success = vrpki_test_pdf_custom_signed
      } else {
        $('span#result_podepsat_pdf_custom').html('Pripojte se k WebSign!').addClass('alert-danger').removeClass('alert-success alert-warning');;
        return false;
      }

        var file = event.target.files[0];

        var msgPdfStart = new WebSign(0, 0, "PDF", "START");
        msgPdfStart.fileName = file.name;
        g_ws.send(JSON.stringify(msgPdfStart));


        var l_layout = {x: $('#x').val()||0, y: $('#y').val()||0, p: 0, bottomRightCorner: $('#c').prop('checked')};
        g_ws.vr_fileman = {id:'url', akce: 'stahnout', typ: 'PDF', layout: l_layout, nazev: 'pdfcustom_signed.pdf'};

        var start = 0;
        var step = 65500; // MAX
        var end = step;
        var EOF = file.size;

        if (end > EOF) {
            end = EOF;
        }

        var reader = new FileReader();
        reader.onload = function (e) {
            rawData = e.target.result;
            g_ws.send(rawData);
            console.log("Sending file (" + end + "/" + EOF + ")");

            if (end < EOF) {
                start = end;
                end = start + step;

                if (end > EOF) {
                    end = EOF;
                }

                reader.readAsArrayBuffer(file.slice(start, end));
            } else {
                console.log("File sent");
                var endMsg = new WebSign(0, 0, "PDF", "END");
                endMsg.fileName = file.name;
                var x = $('#x').val()||0
                var y = $('#y').val()||0
                var pageFromEnd = 0;
                var usePosition = $('#v').prop('checked');
                if (usePosition != true) {
                  var bottomRightCorner = $('#c').prop('checked');
                  endMsg.signPosition = new SignPosition(x, y, pageFromEnd, bottomRightCorner);
                }
                g_ws.send(JSON.stringify(endMsg));
            }
        };

        reader.readAsArrayBuffer(file.slice(start, end));
    }
