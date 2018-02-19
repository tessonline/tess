<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>
<iframe id="ifrm_get_value2" name="ifrm_get_value2" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>
<style>
.ui-autocomplete-loading { background: white url('ui-anim_basic_16x16.gif') right center no-repeat; }
</style>

<script type="text/javascript">
  $(function() {
    $( "#tabs" ).tabs();


  });

  function sendFormAll() {
    var fAll = document.getElementById('frm_all');
    var fArr = document.forms;
    var validResult = true;
    for (var i = 0; i < fArr.length; i++) {
      if (fArr[i].name == 'frm_all') continue;
      if (fArr[i].name == 'frm_edit') {
        fAll.action = fArr[i].action;
      }
      if (typeof fArr[i].onSubmit == 'function') {
        validResult = fArr[i].onSubmit();
        if (validResult === false) return false;
      }
      var frm = $("form[name=" + fArr[i].name + "]");
      frm.find(":input").clone().appendTo("form[name=" + fAll.name + "]");
      frm.find("select option:selected").each(function() { 
        var selNew = $("form[name=" + fAll.name + "]").find("select[name='" + $(this).parent().attr('name') + "']");
        if ($(this).parent().attr('multiple') == 'multiple') {
          selNew.find("option[value='" + $(this).attr('value') + "']").attr('selected', 'selected')
        }
        else {
          selNew.prop("selectedIndex", $(this).parent().prop("selectedIndex"));
        }
      });
      frm.find("textarea").each(function() { 
        var txtNew = $("form[name=" + fAll.name + "]").find("textarea[name='" + $(this).attr('name') + "']");
        txtNew.attr('value', $(this).attr('value'));
      });
    }
    // ADD_REMOVE selecty oznacime
    $("form[name=" + fAll.name + "]").find("select").each(function() { 
      if ($(this).attr('multiple') == 'multiple') {
        if ($("select[name='" + $(this).attr('name').substr(0, $(this).attr('name').indexOf("[]")) + "_AR[]']").length > 0) {
          $(this).find("option").each(function() { 
            $(this).attr('selected', 'selected'); 
          });
        }
      }
    });
    fAll.submit();
  }
</script>
