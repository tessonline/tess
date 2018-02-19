<?php
  include_once(FileUp2(".admin/security_name.inc"));
  include_once(FileUp2(".admin/config.inc"));
	$zkratka=UkazOdbor($ODBOR,true);
?>
<script language="JavaScript" type="text/javascript">
function frm_edit_Validator(f) {
if (f.CISLO_JEDNACI1.value.length < 1) {
  alert("Nezadal(a) jste číslo jednací!");
  f.CISLO_JEDNACI1.focus();
//  return(false);
}
//else
//  return(false)
}
function VratSpis() {

  window.opener.document.getElementById('OBJEKT_KOD_SPAN').innerHTML = '<?php echo $CISLO_JEDNACI1."/".$CISLO_JEDNACI2;?>';
  window.opener.document.frm_edit.CISLO_SPISU1.value = '<?php echo $CISLO_JEDNACI1;?>';
  window.opener.document.frm_edit.CISLO_SPISU2.value = '<?php echo $CISLO_JEDNACI2;?>';
  window.opener.document.frm_edit.ODBOR_SPISU.value = '<?php echo $zkratka;?>';
  window.opener.document.frm_edit.PODCISLO_SPISU.value = -1;
  window.close();
}
</script>
<?php
  echo "<span class='caption'>Vyberte si:</span>";
  echo "<p></p>";
//  echo "<input type='button' onclick='javascript:VratSpis();' value='Vytvořit ".$GLOBALS["CONFIG"]["CISLO_SPISU"]." ".$CISLO_JEDNACI1."/".$CISLO_JEDNACI2."' class='button btn'>";
  echo "<span class='caption'>Nový spis</span>";
  echo '<form name="frm_edit" action="javascript:GuideSubmit(1)" method="GET" target="_self" onsubmit="return frm_edit_Validator(this)">';
  echo "<span class='text'>Vytvořit ".$GLOBALS["CONFIG"]["CISLO_SPISU_1P"]."<b> ".$CISLO_JEDNACI1."/".$CISLO_JEDNACI2."";
  echo "<input type='hidden' name='CISLO_JEDNACI1' value='$CISLO_JEDNACI1'>";
  echo "<input type='hidden' name='CISLO_JEDNACI2' value='$CISLO_JEDNACI2'>";
  echo " - <input type='text' name='NAZEV_SPISU' size='20'></b>";
  echo "<p>&nbsp;</p>";
  echo "<span class='caption'>Historický spis</span><br/>";
  echo "<span class='text'>nebo vytvořit starší ".$GLOBALS["CONFIG"]["CISLO_SPISU_1P"].":</span>\n";
  echo "<input type='hidden' name='ODBOR' value='".$ODBOR."'>";
  echo "<input type='text' name='CISLO_JEDNACI3' size='6'> /";
  echo "<select name='CISLO_JEDNACI4'>\n";
  echo "<option value='2007'>2007</option>";
  echo "<option value='2006'>2006</option>";
  echo "<option value='2005'>2005</option>";
  echo "<option value='2004'>2004</option>";
  echo "<option value='2003'>2003</option>";
  echo "<option value='2002'>2002</option>";
  echo "<option value='2001'>2001</option>";
  echo "<option value='2000'>2000</option>";
  echo "<option value='1999'>1999</option>";
  echo "<option value='1998'>1998</option>";
  echo "<option value='1997'>1997</option>";
  echo "<option value='1996'>1996</option>";
  echo "<option value='1995'>1995</option>";
  echo "<option value='1994'>1994</option>";
  echo "<option value='1993'>1993</option>";
  echo "<option value='1992'>1992</option>";
  echo "<option value='1991'>1991</option>";
  echo "<option value='1990'>1990</option>";
  echo "<option value='1989'>1989</option>";
  echo "<option value='1988'>1988</option>";
  echo "<option value='1987'>1987</option>";
  echo "<option value='1986'>1986</option>";
  echo "<option value='1985'>1985</option>";
  echo "<option value='1984'>1984</option>";
  echo "<option value='1983'>1983</option>";
  echo "<option value='1982'>1982</option>";
  echo "<option value='1981'>1981</option>";
  echo "<option value='1980'>1980</option>";
  echo "<option value='1979'>1979</option>";
  echo "<option value='1978'>1978</option>";
  echo "<option value='1977'>1977</option>";
  echo "<option value='1976'>1976</option>";
  echo "<option value='1975'>1975</option>";
  echo "<option value='1974'>1974</option>";
  echo "<option value='1973'>1973</option>";
  echo "<option value='1972'>1972</option>";
  echo "<option value='1971'>1971</option>";
  echo "<option value='1970'>1970</option>";
	echo "</select>";
  echo " - <input type='text' name='NAZEV_SPISU2' size='20'>";
	
?> 
