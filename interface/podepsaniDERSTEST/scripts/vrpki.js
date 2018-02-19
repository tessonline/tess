/**
 * VERSO-2658, JHf, implementace pki_signer do VERSO
 */
var g_websocket_url = 'wss://localhost.ders.cz:5559/';
var g_ws_alert_connection_showed = null; // priznak, jestli uz byla zobrazena hlaska, ze se nejde pripojit k websign. Nezapomenout spravne vyNULLovat
var g_podepisuje = '' // ten, kdo podepisuje, info z certifikatu
var g_websign_url = vr_pki_url_jnlp || 'https://ders.cz/pkisigner/launch.jnlp'
var g_ws;

/**
 * Stáhne soubor z VR_FILEMAN pres fname=dload a pošle k podpisu
 * @author JHf hofman@ders.cz
 * @param {Object} p_vr_fileman
 * @param {Int} p_vr_fileman.id VR_FILEMAN.id
 * @param {Int} p_vr_fileman.pouzit_udidfile pokud 1 upravime URL pro stažení souboru na: /fname/dload/udidfile/1234567890, jinak bezne /fname/dload/idfile/1234567890 (default)
 * @param {String} p_vr_fileman.akce 'stahnout', 'ulozit', 'ulozit_stahnout', 'wf_podepsat'. Default: ulozit
 * @param {string} p_vr_fileman.typ 'XML' , 'PDF' - uppercase
 * @param {string} p_vr_fileman.nazev Nazev podepisovaneho/stahovaneho souboru. Nepovinny
 * @param {string|Blob} p_vr_fileman.data Obsah souboru
 * @param {Object} p_vr_fileman.layout Objekt popisujici umisteni podpisu
 * @param {int} p_vr_fileman.layout.x
 * @param {int} p_vr_fileman.layout.y
 * @param {int} p_vr_fileman.layout.p na kolikate strance od konce bude podpis, 0=posledni
 * @param {Boolean} p_vr_fileman.layout.bottomRightCorner
 * @param {string} p_websocket_url URL k WebSocket, kde je aplikace WebSign. Default: ws://127.0.0.1:5558/
 * @param {Object} p_progress_fce Případné callback funkce, které se volají v průběhu podepisování
 * @param {Object} p_batch Informace o tom, kolikátý je to soubor v dávce. (pouze pokud podepisujeme vice souboru najednou)
 * @param {Int} p_batch.index Kolikátý soubor je to v dávce?
 * @param {Int} p_batch.size Celkový počet podepisovaných souborů
*/
function vrpki_podepsat(p_vr_fileman, p_websocket_url, p_progress_fce, p_batch) {
  'use strict';
  p_websocket_url = p_websocket_url || g_websocket_url;

  g_ws.progress_fce = p_progress_fce;
  g_ws.vr_fileman = p_vr_fileman;
  g_ws.batch = p_batch;
  switch (p_vr_fileman.akce) {
    case 'wf_podepsat':
      /* PKI-5, pokud delam wf podpis, potrebuju posilat i data - nemam je ulozene v souboru */
      if (p_vr_fileman.akce === 'wf_podepsat' && !p_vr_fileman.data) {
        console.error("Neplatna operace: Podpis WF aktivity, nemame zdrojova data");
        alert("Neplatna operace: Podpis WF aktivity, nemame zdrojova data");
      }
      alert('NOT YET IMPLEMENTED')
      return false;
      break;
      // ulozit, ulozit_stahnout a null jsou zde pro me stejne operace
    case 'ulozit':
    case 'ulozit_stahnout':
    case 'stahnout':
    case null:
      /* XML - nepotrebuju tahat z VERSO. Obsah mam v p_vr_fileman.data */
      if (p_vr_fileman.data && (p_vr_fileman.typ === 'XML' || p_vr_fileman.typ === 'PDF')) {
        /* Zavolám případnou custom funkci, mam stažený soubor a byl odeslán do WebSign */
        if (p_progress_fce && p_progress_fce.sent)
          p_progress_fce.sent("odeslano k podpisu");
        //vrpki_connect_ws(p_vr_fileman, p_vr_fileman.data, p_websocket_url, p_progress_fce, p_batch);
        vrpki_sendFile(g_ws, p_vr_fileman.data, p_vr_fileman, p_batch, p_progress_fce)
        break;
      }

      /* Budu odesilat soubor do WebSign jako blob. Nejdrive ho ale musime stahnout z VERSO */
      /* polyfill pro IE start */
      if (FileReader.prototype.readAsBinaryString === undefined) {
        console.log("Using polyfill FileReader");
        FileReader.prototype.readAsBinaryString = function(fileData) {
          var binary = "";
          var pt = this;
          var reader = new FileReader();
          reader.onload = function(e) {
            var bytes = new Uint8Array(reader.result);
            var length = bytes.byteLength;
            for (var i = 0; i < length; i++) {
              binary += String.fromCharCode(bytes[i]);
            }
            //pt.result  - readonly so assign content to another property
            pt.content = binary;
            pt.onload();
          }
          reader.readAsArrayBuffer(fileData);
        }
      }
      /* polyfill pro IE konec */

      var x = new XMLHttpRequest(), // Pry nejde pres JQuery (nezkousel jsem: http://stackoverflow.com/questions/17657184/)
        l_response,
        l_url = vr_stript_name + '?fname=vr_pki_dload&idfile=' + p_vr_fileman.id,
        l_reader = new FileReader();

      // Stahnu soubor z VERSO, pripravim si URL
      if (p_vr_fileman.pouzit_udidfile === 1) {
        l_url = vr_stript_name + '?fname=vr_pki_dload&udidfile=' + p_vr_fileman.id
      }
      /* Soubor muze byt lokalni - mam relativni URL -> p_vr_fileman.id='url'
      nebo z VR_FILEMAN - mam jeho ID */
      if (p_vr_fileman.id === 'url'){
        console.log("Budu stahovat lokalni soubor: ", p_vr_fileman.url);
        l_url = p_vr_fileman.url
      }
      x.open("GET", l_url, true);
      x.responseType = 'blob';
      x.onload = function(e) {
        if (x.status !== 200) {
          // napr. verso chyba ze soubor neexistuje nebo nnei pravo
          alert($.i18n.message('core.pki.error.download', x.status, p_vr_fileman.id));
          console.error('Chyba stahovani souboru z VERSO [code=' + x.status + '] [id=' + p_vr_fileman.id + ']');
          return false;
        }
        // z http odpovedi vytvorim JS objekt typu File a prectu ho
        l_response = new Blob([x.response], {
          type: p_vr_fileman.typ
        });

        var file = p_vr_fileman.data;
        var start = 0;
        var step = 65536; // MAX
        var end = step;
        var EOF = l_response.size;

        if (end > EOF) {
          end = EOF;
        }
        /* Zavolám případnou custom funkci, mam stažený soubor a byl odeslán do WebSign */
        if (p_progress_fce && p_progress_fce.sent)
          p_progress_fce.sent("odeslano k podpisu");

        vrpki_sendFile(g_ws, x.response, p_vr_fileman, p_batch, p_progress_fce)
      }
      x.onerror = function(e) {
        alert($.i18n.message('core.pki.error.download', x.status));
        console.error('Chyba stahovani souboru z VERSO [id=' + p_vr_fileman.id + ']');
        return false;
      }
      x.send();

      // co se stane pri nacteni souboru do javascriptove promenne
      // zde to chceme odeslat do pki_signeru, ktery spusti JAvu a proces podepisovani
      // a pockat si az se to vrati podepsane
      l_reader.onload = function(e) {
        console.log('Posilam na websocket [%s]', p_websocket_url)
        vrpki_sendFile(g_ws, x.response, p_vr_fileman, p_batch, p_progress_fce)
      }
      break;
    default:
      alert($.i18n.message('core.pki.error.download', x.status))
  }
}

/**
 * Pripojeni k WebSocket pro pki_signer a zavolani podepsani. Predam data+type
 */
function vrpki_connect_ws(p_akce, p_data, p_websocket_url, p_progress_fce, p_batch) {
  'use strict';
  p_websocket_url = p_websocket_url || g_websocket_url;
  console.log('START vrpki_connect_ws: ', p_websocket_url)
  var l_websign_odeslan, l_websign_prijat;

  // Create WS
  var ws = g_ws = new WebSocket(p_websocket_url);
  ws.progress_fce = p_progress_fce
  ws.onopen = function() {
    console.log("WebSign connected");
    if (p_progress_fce && p_progress_fce.connected)
      p_progress_fce.connected();
    // TODO: zde posilat message s version_origin - URL k jnlp. Nejspis g_websign_url
    // cesta k JNLP, kde je posledni verze aplikac e
    ws.send(JSON.stringify(new WebSign(0, 0, "VERSION_ORIGIN", g_websign_url)));

    /* Pomocný ws pro zjištění toho, kdo podepisuje.
    Pouze když toto dopadne dobře, mohu pokračovat dále. */
    ws.send(JSON.stringify(new WebSign(0, 0, "SUBJECT")));
    g_ws_alert_connection_showed = null; // vynuluju globalni priznak
  };

  /* Prijem zprav z WebSign
     - Navazani spojeni
     - Prijem podepsaneho souboru
     */
  ws.onmessage = function(evt) {
    if (evt.data instanceof Blob) {
      /* Pravdepodobne:
       - odesilam nepodepsany soubor
       - dostavam podepsany soubor */
      console.log("Blob size " + evt.data.size);
      console.log("Blob type " + evt.type);
      console.log(evt.data);
      var pdfBlob = new Blob([evt.data], {type: "application/pdf"});

      ws.vr_fileman.data = pdfBlob;
      l_websign_prijat = new WebSign(0, 0, pdfBlob.type, pdfBlob)
      // Prijem souboru z WebSign, idealne podepsany
      vrpki_vysledek(ws.vr_fileman, l_websign_prijat, p_websocket_url, ws.progress_fce)
    } else {
      console.log("WS onmessage WebSign: ", JSON.parse(evt.data), JSON.parse(evt.data).type);
      var l_type = JSON.parse(evt.data).type,
        l_data = JSON.parse(evt.data).data,
        l_evt_data = JSON.parse(evt.data),
        l_nazev = JSON.parse(evt.data).fileName;
      l_websign_prijat = new WebSign(0, 0, l_type, l_data)

      /**********************************************/
      /* WebSign mi vratil odpoved a ja ji zpracuji */
      /**********************************************/
      switch (l_websign_prijat.type) {
        case 'VERSION_ORIGIN':
          // Zjistuji, kdo podepisuje
          console.log('VERSION_ORIGIN', l_data);
          break
        case 'SUBJECT':
          // Zjistuji, kdo podepisuje
          console.log('Subject', l_data);
          if (l_data){ // Mam jmeno z certifikatu
            g_podepisuje = l_data; // Nastavim, kdo podepsal
          }
          if (ws.progress_fce && ws.progress_fce.subject_ok)
            ws.progress_fce.subject_ok(l_data);
          break
        case 'PDF':
          if (l_websign_prijat.data == 'SIGNED'){
            console.log('zacatek prebirani podepsaneho PDF... %s', l_nazev, l_evt_data);
            // nejdriv dostanu info, ze stahnu nejaky soubor, teprve potom prijde filestream
            // proto si zde nastavim jmeno souboru, ktery pak prijde do line 180
            ws.vr_fileman.nazev = l_nazev;
            // nastavim si i poradi souboru v davce
            ws.batch.batchIndex = l_evt_data.batchIndex;
            ws.batch.batchSize = l_evt_data.batchSize;
            if (ws.progress_fce && ws.progress_fce.pdf_signed)
              ws.progress_fce.pdf_signed(l_evt_data);
          }
          break;
        case 'XML':
          if (ws.vr_fileman.akce === 'test_connect'){
            /* Muze se jednat jen o test pripojeni z pki_signer/index.html */
            if (ws.vr_fileman && ws.vr_fileman.akce === 'test_connect'){
              if (ws.progress_fce && ws.progress_fce.xml_signed)
                ws.progress_fce.xml_signed(l_data);
            }
            return true;
          }
          console.log('Jde o XML. Mam ho podepsane. Provedu UPDATE VR_FILEMAN [id=%s]', ws.vr_fileman.id)
          vrpki_vysledek(ws.vr_fileman, l_websign_prijat, p_websocket_url, ws.progress_fce)
          break;
        case 'INFO':
          // obycejna info hlaska, nic nedelam
          break;
        default:
          console.error('Nepodporovany vystup pki_signer:', evt.data);
      }
    }
  };
  ws.onclose = function() {
    console.log("WebSign Disconnected");
    /* Zavolam pripadnout custom funkci */
    if (ws.progress_fce && ws.progress_fce.websign_disconnected)
      ws.progress_fce.websign_disconnected(evt);
  };
  ws.onerror = function(err) {
    console.error("Chyba pri komunikaci s aplikaci pki_signer: ", err);
    if (this.readyState === 3 || this.readyState === 2 || this.readyState === 0){
      if (!g_ws_alert_connection_showed){
        alert($.i18n.message('core.pki.error.connect'));
        g_ws_alert_connection_showed = 1; // ulozim si info, ze jsem zobrazil alert a nabidl stazeni
        /* Spustim stazeni JNLP souboru */
        var elem = window.document.createElement('a');
        elem.href = g_websign_url
        document.body.appendChild(elem);
        elem.click();
        document.body.removeChild(elem);
      }

      /* Zavolam pripadnout custom funkci */
      if (ws.progress_fce && ws.progress_fce.websign_cant_connect)
        ws.progress_fce.websign_cant_connect();
      return false;
    } else {
      /* Jina chyba WebSocketu */
      alert($.i18n.message('core.pki.error.unknown'))
    }
  };
  console.log('KONEC vrpki_connect_ws: ', p_websocket_url)
}

/* Vola se po odpovedi z pki_signeru. Pokud vse dopadlo ok, dostanu z nej: soubor, zpravu (stav)
   Volana z funkce: vrpki_connect_ws
   Parametry:
    ws.vr_fileman - informace o VERSO souboru
    p_websign_prijat - soubor, ktery vratila aplikace WebSign
    p_websocket_url - URL k aplikaci WebSign
    p_progress_fce - Zatim nevyuzito, custom progress bar, modalni okna apod
*/
function vrpki_vysledek(p_vr_fileman, p_websign_prijat, p_websocket_url, p_progress_fce) {
  'use strict';
  function stahnout(){
    var elem = window.document.createElement('a');
    var binaryData = [];
    binaryData.push(p_websign_prijat.data);

    if (p_websign_prijat.data.size === 0){
      console.error("Soubor ma nulovou velikost!");
      alert("Chyba: Soubor ma nulovou velikost! Stažení bylo přerušeno");
      return false;
    }

    elem.href = window.URL.createObjectURL(new Blob(binaryData));
    elem.download = p_vr_fileman.nazev;
    document.body.appendChild(elem);
    if (navigator.msSaveOrOpenBlob) { // for IE and Edge, thx: https://stackoverflow.com/a/43273212/2542096
      navigator.msSaveBlob(new Blob(binaryData), elem.download);
    } else {
      elem.click();
    }
    document.body.removeChild(elem);
  }

  if (p_vr_fileman.akce === 'stahnout') {
    /* Podepiseme soubor pres WebSign a rovnou stahneme uzivateli */
    stahnout();
    if (p_progress_fce && p_progress_fce.success)
      p_progress_fce.success(p_websign_prijat);
  } else if (p_vr_fileman.akce === null || p_vr_fileman.akce === 'ulozit' || p_vr_fileman.akce === 'ulozit_stahnout') {
    /* Podepsany soubor vlozime zpet do VERSO */
    if (p_vr_fileman.data instanceof Blob) {
      console.log("Prijimam podepsane PDF ...")
    } else {
      console.error("Soubor Pravdepodobne neni v poradku: ", p_vr_fileman);
    }
    var binaryData = [];
    binaryData.push(p_websign_prijat.data);

    var reader = new FileReader();
    reader.onload = function(event) {
      var fd = new FormData();
      // obsah souboru predavam v base64, jinak verso nedostalo cely obsah
      // ve verso pak ekoduji z base64
      fd.append('data', btoa(event.target.result) || "NEMAM RESULT");
      fd.append('fname', 'vr_pki_update_fileman');
      fd.append('id', p_vr_fileman.id);
      /* Odeslani do VERSO */
      $.ajax({
        url: vr_stript_name,
        type: 'POST',
        processData: false,
        contentType: false,
        data: fd
      }).fail(function(e) {
        console.error('Chyba pri uploadu souboru do VERSO', e)
        alert($.i18n.message('core.pki.error.upload'))
        if (p_progress_fce && p_progress_fce.fail)
          p_progress_fce.fail();
      }).success(function() {
        console.log('Upload souboru do VERSO se zdaril')
        if (p_progress_fce && p_progress_fce.success)
          p_progress_fce.success(p_websign_prijat, g_podepisuje);
      });
    };
    reader.readAsBinaryString(p_vr_fileman.data);

    if (p_vr_fileman.akce === 'ulozit_stahnout'){
      stahnout();
    }
  } else if (p_vr_fileman.akce === 'test_connect') {
    console.log("TEST, chci pouze zobrazit vysledek: ", p_websign_prijat);
  } else {
    console.error("neznama operace pro praci s podepsanym souborem: %s", p_vr_fileman.akce);
  }
  console.log('STOP vrpki_vysledek: ', p_vr_fileman, p_websign_prijat, p_progress_fce)
} // konec vrpki_vysledek

/**
 * Objekt určující umístění podpisu v PDF
 * @param {Number} x Horizontální souřadnice zleva
 * @param {Number} y Vertikální souřadnice zhora
 * @param {Number} pageFromEnd Stránka od konce. 0=poslední stránka
 * @param {Boolean} bottomRightCorner Pokud true, bude podpis vždy vpravo dole na stránce
 */
function SignPosition(x, y, pageFromEnd, bottomRightCorner) {
  'use strict';
  this.x = x;
  this.y = y;
  this.page = pageFromEnd;
  this.bottomRightCorner = bottomRightCorner;
  console.log("Pozice signatury: x=" + this.x + " y=" + this.y + " page=" + this.page + ', vpravo dole:' + this.bottomRightCorner);
}

/**
 * Pomocny objekt, ktery drzi informace o podepisovanem/podpsanem souboru
 */
function WebSign(batchIndex, batchSize, type, data, fileName) {
  'use strict';
  this.batchIndex = batchIndex;
  this.batchSize = batchSize;
  this.type = type;
  this.data = data;
  this.fileName = fileName;
}

/* Odeslani PDF souboru po kouskach. Odesilame z klienta do aplikace WebSign. */
function vrpki_sendFile(ws, p_blob, p_vr_fileman, p_batch, p_progress_fce) {
  'use strict';
  console.log("Sending file");
  ws = ws || g_ws;
  var l_batch_index = 0, l_batch_size = 0;
  if (p_batch){
    l_batch_index = p_batch.index || 0;
    l_batch_size = p_batch.size || 0;
  }

  /* Zjistuji jeslti jde o XML nebo PDF */
  if (p_vr_fileman.typ === 'XML'){
    /* ****** XML ***************/
    var xml = p_vr_fileman.data.replace(/\s+/g, ' ').trim();
    var l_data = JSON.stringify(new WebSign(l_batch_index, l_batch_size, "XML", xml, p_vr_fileman.nazev));
    ws.send(l_data)
  } else {
    /* ****** PDF ***************/
    ws.send(JSON.stringify(new WebSign(l_batch_index, l_batch_size, "PDF", "START")));
    p_blob = new Blob([p_blob], {type: 'application/pdf'});
    var start = 0;
    var step = 65536; // MAX
    var end = step;
    var EOF = p_blob.size;

    if (end > EOF) {
      end = EOF;
    }

    var reader = new FileReader();
    reader.onload = function(e) {
      var rawData = e.target.result;
      ws.send(rawData);
      console.log("Sending file (" + end + "/" + EOF + ")");

      if (end < EOF) {
        start = end;
        end = start + step;

        if (end > EOF) {
          end = EOF;
        }

        reader.readAsArrayBuffer(p_blob.slice(start, end));
      } else {
        console.log("File sent");
        var endMsg = new WebSign(l_batch_index, l_batch_size, "PDF", "END");

        // pouzijeme zobrazeni podpisu?
        if (p_vr_fileman.layout) {
          var x = p_vr_fileman.layout.x || 0;
          var y = p_vr_fileman.layout.y || 0;
          var pageFromEnd = p_vr_fileman.layout.page || 0;
          var bottomRightCorner = p_vr_fileman.layout.bottomRightCorner || false;
          endMsg.signPosition = new SignPosition(x, y, pageFromEnd, bottomRightCorner);
          endMsg.fileName = p_vr_fileman.nazev
        }
        ws.send(JSON.stringify(endMsg));
      }
    };

    reader.readAsArrayBuffer(p_blob.slice(start, end));
  }
}
