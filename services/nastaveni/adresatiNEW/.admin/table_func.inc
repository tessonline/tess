<?php

	function Adresa($odesl_ulice,$odesl_cp,$odesl_cor) {
		if (isset($odesl_ulice) && trim($odesl_ulice) != '') {
			$adr =	$odesl_ulice;
		}
		if (isset($odesl_cp) && trim($odesl_cp) != '') {
			$adr .=	' '.$odesl_cp;
		}
		if (isset($odesl_cor) && trim($odesl_cor) != '') {
			$adr .=	'/'.$odesl_cor;
		}
		return $adr;
	}
	
	function Frozen($id, $state) {
		$img_ok = FileUpUrl('images/ok_check.gif');
		$img_ko = FileUpUrl('images/ko_check.gif');
		if (isset($state)) {
			if ($state == 'N') {
				$adr = '<div id="'.$id.'" class="active '.$state.'" style="cursor: Pointer"><img id="'.$id.'" src="'.$img_ok.'" title="Platná adresa"/></div>';
				
			} else {
				$adr = '<div id="'.$id.'" class="active '.$state.'" style="cursor: Pointer"><img id="'.$id.'" src="'.$img_ko.'" title="Neplatná adresa"/></div>';
			}
		}
		return $adr;
	}
