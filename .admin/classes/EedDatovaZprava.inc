<?php
require_once ('db.inc');
class EedDatovaZprava extends EED_db_object{

  /**
   * Constructor
   * 
   * @author luma
   */
  function EedDatovaZprava(){
    parent::Eed_db_object();
  }

  private function NullInt($num){
    if (strlen($num) == 0)
      return 'NULL';
    else
      return $num;
  }
  

  public function getDZinfo($mId){
  	$sql='select * from posta_datova_zprava where dmid IN (\''.$mId.'\')';
  	$this->_sql_query($sql);
  	$this->db->RecordKeyUpperCase = false;
  	while ($this->db->Next_Record()) {
  		$row = $this->db->Record;
  		$rec = array(
  				'dmOrdinal' => $row['dmordinal'],
  				'dmID' => $row['dmid'],
  				'dbIDSender' => $row['dbidsender'],
  				'dmSender' => $row['dmsender'],
  				'dmSenderAddress' => $row['dmsenderaddress'],
  				'dmSenderType' => $row['dmsendertype'],
  				'dmRecipient' => $row['dmrecipient'],
  				'dmRecipientAddress' => $row['dmrecipientaddress'],
  				'dmSenderOrgUnit' => $row['dmsenderorgunit'],
  				'dmSenderOrgUnitNum' => $row['dmsenderorgunitnum'],
  				'dbIDRecipient' => $row['dbidrecipient'],
  				'dmRecipientOrgUnit' => $row['dmrecipientorgunit'],
  				'dmRecipientOrgUnitNum' => $row['dmrecipientorgunitnum'],
  				'dmToHands' => $row['dmtohands'],
  				'dmAnnotation' => $row['dmannotation'],
  				'dmRecipientRefNumber' => $row['dmrecipientrefnumber'],
  				'dmSenderRefNumber' => $row['dmsenderrefnumber'],
  				'dmRecipientIdent' => $row['dmrecipientident'],
  				'dmSenderIdent' => $row['dmsenderident'],
  				'dmLegalTitleLaw' => $row['dmlegaltitlelaw'],
  				'dmLegalTitleYear' => $row['dmlegaltitleyear'],
  				'dmLegalTitleSect' => $row['dmlegaltitlesect'],
  				'dmLegalTitlePar' => $row['dmlegaltitlepar'],
  				'dmLegalTitlePoint' => $row['dmlegaltitlepoint'],
  				'dmPersonalDelivery' => $row['dmPersonalDelivery'],
  				'dmAllowSubstDelivery' => $row['dmallowsubstdelivery'],
  				'dmMessageStatus' => $row['dmmessagestatus'],
  				'dmAttachmentSize' => $row['dmattachmentsize'],
  				'dmDeliveryTime' => str_replace(' ','T',$row['dmdeliverytime'].':00'),
  				'dmAcceptanceTime' => str_replace(' ','T',$row['dmacceptancetime'].':00')
  		);
  	}
  	return $rec;
  }

  /*
   * Nacte zprávy k zobrazeni
   */
  //public function NactiZpravy($status,$res){
  public function NactiZpravy($status){
	$r['dmRecord'] = array();
  	$sql='select row_number() OVER () as dmOrdinal,* from posta_datova_zprava where dmMessageStatus IN ('.$status.')';
  	$this->_sql_query($sql);
  	$this->db->RecordKeyUpperCase = false;
  	while ($this->db->Next_Record()) {
  		$row = $this->db->Record;
  		$rec = array(
  				'dmOrdinal' => $row['dmordinal'], 
  				'dmID' => $row['dmid'], 
  				'dbIDSender' => $row['dbidsender'], 
  				'dmSender' => $row['dmsender'], 
  				'dmSenderAddress' => $row['dmsenderaddress'], 
  				'dmSenderType' => $row['dmsendertype'], 
  				'dmRecipient' => $row['dmrecipient'], 
  				'dmRecipientAddress' => $row['dmrecipientaddress'], 
  				'dmSenderOrgUnit' => $row['dmsenderorgunit'], 
  				'dmSenderOrgUnitNum' => $row['dmsenderorgunitnum'], 
  				'dbIDRecipient' => $row['dbidrecipient'], 
  				'dmRecipientOrgUnit' => $row['dmrecipientorgunit'],
  				'dmRecipientOrgUnitNum' => $row['dmrecipientorgunitnum'],
  				'dmToHands' => $row['dmtohands'],
  				'dmAnnotation' => $row['dmannotation'],
  				'dmRecipientRefNumber' => $row['dmrecipientrefnumber'],
  				'dmSenderRefNumber' => $row['dmsenderrefnumber'],
  				'dmRecipientIdent' => $row['dmrecipientident'],
  				'dmSenderIdent' => $row['dmsenderident'],
  				'dmLegalTitleLaw' => $row['dmlegaltitlelaw'],
  				'dmLegalTitleYear' => $row['dmlegaltitleyear'],
  				'dmLegalTitleSect' => $row['dmlegaltitlesect'],
  				'dmLegalTitlePar' => $row['dmlegaltitlepar'],
  				'dmLegalTitlePoint' => $row['dmlegaltitlepoint'],
  				'dmPersonalDelivery' => $row['dmPersonalDelivery'],
  				'dmAllowSubstDelivery' => $row['dmallowsubstdelivery'],
  				'dmMessageStatus' => $row['dmmessagestatus'],
  				'dmAttachmentSize' => $row['dmattachmentsize'],
  				'dmDeliveryTime' => str_replace(' ','T',$row['dmdeliverytime'].':00'),
  				'dmAcceptanceTime' => str_replace(' ','T',$row['dmacceptancetime'].':00')
  		);
  		array_push($r['dmRecord'],$rec);
  	}
  	return $r;
  }

  /**
   * Vlozi nove prichozi datove zpravy do databaze
   */
  public function VlozNoveZpravy($zpravy){
    if ($zpravy){
      foreach ($zpravy['dmRecord'] as $zprava){
      	$sql = "insert into posta_datova_zprava (
          dmID,
          dbIDSender,
          dmSender,
          dmSenderAddress,
          dmSenderType,
          dmRecipient,
          dmRecipientAddress,
          dmSenderOrgUnit,
          dmSenderOrgUnitNum,
          dbIDRecipient,
          dmRecipientOrgUnit,
          dmRecipientOrgUnitNum,
          dmToHands,
          dmAnnotation,
          dmRecipientRefNumber,
          dmSenderRefNumber,
          dmRecipientIdent,
          dmSenderIdent,
          dmLegalTitleLaw,
          dmLegalTitleYear,
          dmLegalTitleSect,
          dmLegalTitlePar,
          dmLegalTitlePoint,
          dmPersonalDelivery,
          dmAllowSubstDelivery,
          dmMessageStatus,
          dmAttachmentSize,
          dmDeliveryTime,
          dmAcceptanceTime) SELECT
          '%s','%s','%s','%s',%s,'%s','%s','%s',%s,'%s','%s',%s,'%s','%s',
          '%s','%s','%s','%s','%s',%s,'%s','%s','%s',%s,%s,%s,%s,'%s','%s'
  	WHERE NOT EXISTS (SELECT dmID FROM posta_datova_zprava WHERE dmID='".$zprava['dmID']."')";
        $sql = sprintf($sql, 
            $zprava['dmID'], 
            $zprava['dbIDSender'], 
            $zprava['dmSender'], 
            $this->NullInt($zprava['dmSenderAddress']), 
            $zprava['dmSenderType'], 
            $zprava['dmRecipient'], 
            $zprava['dmRecipientAddress'], 
            $zprava['dmSenderOrgUnit'], 
            $this->NullInt($zprava['dmSenderOrgUnitNum']), 
            $zprava['dbIDRecipient'], 
            $zprava['dmRecipientOrgUnit'], 
            $this->NullInt($zprava['dmRecipientOrgUnitNum']), 
            $zprava['dmToHands'], 
            str_replace("'","",$zprava['dmAnnotation']),
            $zprava['dmRecipientRefNumber'], 
            $zprava['dmSenderRefNumber'], 
            $zprava['dmRecipientIdent'], 
            $zprava['dmSenderIdent'], 
            $zprava['dmLegalTitleLaw'], 
            $this->NullInt($zprava['dmLegalTitleYear']), 
            $zprava['dmLegalTitleSect'], 
            $zprava['dmLegalTitlePar'], 
            $zprava['dmLegalTitlePoint'], 
            ($zprava['dmPersonalDelivery']?"TRUE":"FALSE"),
            ($zprava['dmAllowSubstDelivery']?"TRUE":"FALSE"),
            $this->NullInt($zprava['dmMessageStatus']), 
            $this->NullInt($zprava['dmAttachmentSize']), 
            $zprava['dmDeliveryTime'], 
            $zprava['dmAcceptanceTime']);
        $this->_sql_query($sql);
      }
    }
  }
}

