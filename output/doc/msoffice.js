function startOffice(OfficeFile,OfficeApp,close)
{
  var message="";
  if (navigator.appName=='Microsoft Internet Explorer')
  { // otestovat, zda jde o IE
    var startApp = new ActiveXObject(OfficeApp+".Application")
    if (startApp != null)
    {
      startApp.Visible = true; // nastavit viditelnost aplikace
      switch(OfficeApp)
      { // vybrat akci pro otevření dokumentu v aplikaci
        case "Word":
          startApp.Documents.Open(OfficeFile);
        break;
        case "Excel":
          startApp.Workbooks.Open(OfficeFile);
        break;
        case "PowerPoint":
          startApp.Presentations.Open(OfficeFile);
        break;
        default:
          startApp.Documents.Open(OfficeFile);
        break;
      }
      if (close==1)
     { // zavřít původní okno
        top.opener="startApp";
        top.window.close();
      }
    }
   else
     message="Aplikaci MS Office nelze spustit, moná není řádně nainstalovaná!";
  }
  else
    message="Prohlíeč není MS Internet Explorer, aplikaci MS Office nelze spustit!";
  if (message!="")
  {
    message = message + "\nSoubor bude nabídnut ke staení.";
    alert(message);
    window.location=OfficeFile;
  }
} 

