<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170102102418 extends AbstractMigration 
{
    /**
     * @param Schema $schema
     */
  public function up(Schema $schema)
    {
      // this up() migration is auto-generated, please modify it to your needs
      
      $not_null = array('notnull' => true);
      $null = array('notnull' => false);

      //ciselniky
      $table = $schema->createTable('cis_posta_agenda');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_agenda');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 50));
      $table->addColumn('id_superodbor', 'integer', $null );
//      $table->addColumn('poradi', 'integer', array( 'notnull' => true, 'default' => 1 ));
      $table->addIndex(array('id_superodbor'), 'idx_id_superodbor_cis_posta_agenda');

      $table = $schema->createTable('cis_posta_jine');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_jine');
      $table->addColumn('odbor', 'integer', $not_null );
      $table->addColumn('jine', 'string', array('notnull' => false, 'length' => 50));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array('notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );

      $table = $schema->createTable('cis_posta_odbory');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_odbory');
      $table->addColumn('id_odbor', 'integer', $not_null );
      $table->addColumn('prava', 'string', array('notnull' => false, 'length' => 1024 ));
      $table->addColumn('altnazev', 'string', array('notnull' => false, 'length' => 100 ));
      $table->addColumn('zkratka', 'string', array('notnull' => false, 'length' => 20 ));
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('poradi', 'integer', array( 'notnull' => true, 'default' => 1 ));

      $table = $schema->createTable('cis_posta_predani');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_predani');
      $table->addColumn('old_referent', 'integer', $null );
      $table->addColumn('old_odbor', 'integer', $null );
      $table->addColumn('referent', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('datum', 'string', array('notnull' => false, 'length' => 20 ));
      $table->addColumn('poznamka', 'string', array('notnull' => false, 'length' => 1024 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array('notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addColumn('cislo_spisu1', 'integer', $null );
      $table->addColumn('cislo_spisu2', 'integer', $null );
      $table->addColumn('spis_id', 'integer', $null );

      $table = $schema->createTable('cis_posta_prijemci');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_prijemci');
      $table->addColumn('odesl_adrkod', 'integer', $null );
      $table->addColumn('odesl_jmeno', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('odesl_titul', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('odesl_ulice', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_cp', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_psc', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_posta', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_prijmeni', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('odes_typ', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_odd', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('odesl_osoba', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_ico', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('odesl_cor', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_adresat', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_datschranka', 'string', array( 'notnull' => false, 'length' => 20 ));

      $table = $schema->createTable('cis_posta_skartace');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_skartace');
      $table->addColumn('kod', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('text', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('skar_znak', 'string', array( 'notnull' => false, 'length' => 5 ));
      $table->addColumn('aktivni', 'integer', $null );
      $table->addColumn('doba', 'integer', $null );
      $table->addColumn('main_id', 'integer', $null );
      $table->addColumn('vyber', 'integer', $null );
      $table->addColumn('nadrazene_id', 'integer', $null );
      $table->addColumn('typ', 'integer', $null );
      $table->addColumn('show_vs', 'integer', $null );
      $table->addColumn('priorita', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('main_id'), 'idx_main_id_cis_posta_skartace');

      $table = $schema->createTable('cis_posta_skartace_h');
      $table->addColumn('id_h', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id_h'), 'pk_cis_posta_skartace_h');
      $table->addColumn('id', 'integer', $not_null);
      $table->addColumn('kod', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('text', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('skar_znak', 'string', array( 'notnull' => false, 'length' => 5 ));
      $table->addColumn('aktivni', 'integer', $null );
      $table->addColumn('doba', 'integer', $null );
      $table->addColumn('main_id', 'integer', $null );
      $table->addColumn('vyber', 'integer', $null );
      $table->addColumn('nadrazene_id', 'integer', $null );
      $table->addColumn('typ', 'integer', $null );
      $table->addColumn('show_vs', 'integer', $null );
      $table->addColumn('priorita', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('id'), 'idx_id_cis_posta_skartace_h');

      $table = $schema->createTable('cis_posta_spisy');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_spisy');
      $table->addColumn('puvodni_spis', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('novy_spis', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('spis_id', 'integer', $not_null );
      $table->addColumn('dalsi_spis_id', 'integer', $not_null );
      $table->addColumn('nazev_spisu', 'string', array( 'notnull' => false, 'length' => 80 ));
      $table->addColumn('arch', 'integer', array( 'notnull' => true, 'default' => 0 ));
      $table->addColumn('typovy_spis', 'integer', array( 'notnull' => true, 'default' => 0 ));
      $table->addColumn('soucast', 'integer', array( 'notnull' => true, 'default' => 0 ));
      $table->addColumn('dil', 'integer', $null );
      $table->addColumn('typovy_spis_id', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('spis_id'), 'idx_spis_id_cis_posta_spisy');
      $table->addIndex(array('dalsi_spis_id'), 'idx_dalsi_spis_id_cis_posta_spisy');
      $table->addIndex(array('arch'), 'idx_arch_cis_posta_spisy');
      $table->addIndex(array('typovy_spis'), 'idx_typovy_spis_cis_posta_spisy');
      $table->addIndex(array('soucast'), 'idx_soucast_cis_posta_spisy');
      $table->addIndex(array('dil'), 'idx_dil_cis_posta_spisy');
      $table->addIndex(array('typovy_spis_id'), 'idx_typovy_spis_id_cis_posta_spisy');

      $table = $schema->createTable('cis_posta_typ');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_typ');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 100 ));
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('skartace_id', 'integer', $null );
      $table->addColumn('lhuta', 'integer', $null );
      $table->addColumn('kpam', 'integer', $null );
      $table->addColumn('faze', 'integer', $null );
      $table->addColumn('poradi', 'integer', $null );
      $table->addColumn('id_agendy', 'integer', $null );
      $table->addColumn('popis', 'string', array( 'notnull' => false, 'length' => 1024 ));

      $table = $schema->createTable('cis_posta_ulozeno');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_ulozeno');
      $table->addColumn('odbor', 'integer', $not_null );
      $table->addColumn('ulozeno', 'string', array( 'notnull' => true, 'length' => 50 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );

      $table = $schema->createTable('posta_cis_adresati');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_adresati');
      $table->addColumn('kod', 'string', array( 'notnull' => false, 'length' => 3 ));
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('aktivni', 'integer', array( 'notnull' => true, 'default' => 0 ));
      $table->addColumn('poradi', 'integer', array( 'notnull' => true, 'default' => 10 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );

      $table = $schema->createTable('posta_cis_ceskaposta');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_ceskaposta');
      $table->addColumn('datum_od', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('datum_do', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('protokol', 'integer', $null );
      $table->addColumn('datum_vytisteni', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('datum_vraceni', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('cislo_od', 'integer', $null );
      $table->addColumn('cislo_do', 'integer', $null );
      $table->addColumn('cislo2_od', 'integer', $null );
      $table->addColumn('obyc1', 'integer', $null );
      $table->addColumn('obyc2', 'integer', $null );
      $table->addColumn('obyc3', 'integer', $null );
      $table->addColumn('obyc4', 'integer', $null );
      $table->addColumn('rok', 'integer', $null );
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('poradi', 'integer', array( 'notnull' => false, 'default' => 1 ));
      $table->addIndex(array('protokol'), 'idx_protokol_posta_cis_ceskaposta');

      $table = $schema->createTable('posta_cis_ceskaposta_ck');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_ceskaposta_ck');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('rok', 'integer', $null );
      $table->addColumn('kod', 'string', array( 'notnull' => false, 'length' => 3 ));
      $table->addColumn('podaci_id', 'integer', $null );
      $table->addColumn('ck', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('stav', 'integer', $null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_cis_ceskaposta_ck');

      $table = $schema->createTable('posta_cis_ceskaposta_id');
      $table->addColumn('protokol_id', 'integer', $null );
      $table->addColumn('pisemnost_id', 'integer', $null );
      $table->addColumn('kod', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addIndex(array('protokol_id'), 'idx_protokol_id_posta_cis_ceskaposta_id');
      $table->addIndex(array('pisemnost_id'), 'idx_pisemnost_id_posta_cis_ceskaposta_id');

      $table = $schema->createTable('posta_cis_deniky');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_deniky');
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 60 ));
      $table->addColumn('zkratka', 'string', array( 'notnull' => false, 'length' => 5 ));
      $table->addColumn('lhuta', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('typ_posty', 'integer', $null );
      $table->addColumn('vec', 'string', array( 'notnull' => false, 'length' => 80 ));
      $table->addColumn('skartace', 'integer', $null );
      $table->addColumn('aktivni', 'integer', array( 'notnull' => false, 'default' => 0 ));
      $table->addColumn('stav', 'integer', $null );
      $table->addColumn('vyrizeno', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('datum_vyrizeni', 'datetime', $null );
      $table->addColumn('spis_vyrizen', 'datetime', $null );

      $table = $schema->createTable('posta_cis_dorucovatel');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_dorucovatel');
      $table->addColumn('datum_od', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('datum_do', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('protokol', 'integer', $null );
      $table->addColumn('datum_vytisteni', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('datum_vraceni', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('cislo2_od', 'integer', $null );
      $table->addColumn('rok', 'integer', $null );
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('poradi', 'integer', array( 'notnull' => false, 'default' => 1 ));
      $table->addIndex(array('protokol'), 'idx_protokol_posta_cis_dorucovatel');

      $table = $schema->createTable('posta_cis_dorucovatel_id');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_dorucovatel_id');
      $table->addColumn('protokol_id', 'integer', $null );
      $table->addColumn('pisemnost_id', 'integer', $null );
      $table->addColumn('kod', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addIndex(array('protokol_id'), 'idx_protokol_id_posta_cis_dorucovatel_id');
      $table->addIndex(array('pisemnost_id'), 'idx_pisemnost_id_posta_cis_dorucovatel_id');

      $table = $schema->createTable('posta_cis_obalky');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_obalky');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 50 ));
      $table->addColumn('velikost', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('aktivni', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('otoceni', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('poradi', 'integer', $null );
      $table->addColumn('id_superodbor', 'integer', $null );
      $table->addIndex(array('id_superodbor'), 'idx_id_superodbor_posta_cis_obalky');

      $table = $schema->createTable('posta_cis_obalky_objekty');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_obalky_objekty');
      $table->addColumn('obalka_id', 'integer', $not_null );
      $table->addColumn('velikost_fontu', 'integer', $null );
      $table->addColumn('sourx', 'integer', $null );
      $table->addColumn('soury', 'integer', $null );
      $table->addColumn('velikost', 'integer', $null );
      $table->addColumn('radkovani', 'integer', $null );
      $table->addColumn('objekt', 'integer', $null );
      $table->addColumn('font', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('text', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addIndex(array('obalka_id'), 'idx_obalka_id_posta_cis_obalky_objekty');

      $table = $schema->createTable('posta_cis_osloveni');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_osloveni');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 50 ));

      $table = $schema->createTable('posta_cis_sablony');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_sablony');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 100 ));
      $table->addColumn('ikona', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('id_dokumentu', 'integer', $null );
      $table->addColumn('poradi', 'integer', $null );
      $table->addColumn('id_superodbor', 'integer', $null );
      $table->addIndex(array('id_superodbor'), 'idx_id_superodbor_posta_cis_sablony');

      $table = $schema->createTable('posta_cis_skartace_main');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_skartace_main');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 50 ));
      $table->addColumn('platnost_od', 'date', $null );
      $table->addColumn('platnost_do', 'date', $null );
      $table->addColumn('aktivni', 'integer', $null );

      $table = $schema->createTable('posta_cis_skartacni_rezimy');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_skartacni_rezimy');
      $table->addColumn('jid', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('skar_znak', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('skar_lhuta', 'integer', $not_null );

      $table = $schema->createTable('posta_cis_spisovna');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_spisovna');
      $table->addColumn('spisovna', 'string', array( 'notnull' => true, 'length' => 50 ));
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('zkratka', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odbor', 'integer', $null );
      $table->addIndex(array('superodbor'), 'idx_superodbor_posta_cis_spisovna');

      $table = $schema->createTable('posta_cis_typ_spis_soucasti');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_typ_spis_soucasti');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 100 ));
      $table->addColumn('spis_id', 'integer', $not_null );
      $table->addIndex(array('spis_id'), 'idx_spis_id_posta_cis_typ_spis_soucasti');

      $table = $schema->createTable('posta_cis_typovy_spis');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_typovy_spis');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 100 ));
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('platny', 'integer', $null );

      $table = $schema->createTable('posta_cis_vyrizeno');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_cis_vyrizeno');
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('poradi', 'integer', array( 'notnull' => false, 'default' => 10 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );

      $table = $schema->createTable('posta_dalsi_zpracovatele');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_dalsi_zpracovatele');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('referent_id', 'integer', $not_null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_dalsi_zpracovatele');


      //hlavni tabulka
      $table = $schema->createTable('posta');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta');
      $table->addColumn('ev_cislo', 'integer', $not_null );
      $table->addColumn('rok', 'integer', $not_null );
      $table->addColumn('odes_typ', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_adrkod', 'integer', $null );
      $table->addColumn('odesl_titul', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_prijmeni', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('odesl_jmeno', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_odd', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('odesl_osoba', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_ulice', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_cp', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_cor', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_ico', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('odesl_psc', 'string', array( 'notnull' => false, 'length' => 6 ));
      $table->addColumn('odesl_posta', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_rekomando', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_postaodesl', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('lhuta', 'integer', $null );
      $table->addColumn('datum_spravce_prijeti', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('typ_posty', 'integer', $null );
      $table->addColumn('referent', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('vec', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('vyrizeno', 'text', $null );
      $table->addColumn('datum_referent_prijeti', 'datetime', $null );
      $table->addColumn('odeslana_posta', 'boolean', $null );
      $table->addColumn('datum_vyrizeni', 'datetime', $null );
      $table->addColumn('odesl_osloveni', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('doporucene', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('vlastnich_rukou', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('dorucenka', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('cislo_spisu1', 'integer', $null );
      $table->addColumn('cislo_spisu2', 'integer', $null );
      $table->addColumn('podcislo_spisu', 'integer', $null );
      $table->addColumn('skartace', 'integer', $null );
      $table->addColumn('datum_doruceni', 'datetime', $null );
      $table->addColumn('dalsi_prijemci', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('id_puvodni', 'integer', $null );
      $table->addColumn('puvodni_spis', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('datum_podatelna_prijeti', 'datetime', $null );
      $table->addColumn('dalsi_id_agenda', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('objekt_kod', 'integer', $null );
      $table->addColumn('okres_kod', 'integer', $null );
      $table->addColumn('skartovano', 'string', array( 'notnull' => false, 'length' => 25 ));
      $table->addColumn('poznamka', 'text', $null );
      $table->addColumn('frozen', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('cislo_jednaci1', 'integer', $null );
      $table->addColumn('cislo_jednaci2', 'integer', $null );
      $table->addColumn('odbor_spisu', 'string', array( 'notnull' => false, 'length' => 5 ));
      $table->addColumn('hmotnost', 'integer', $null );
      $table->addColumn('cena', 'decimal', $null );
      $table->addColumn('druh_zasilky', 'integer', $null );
      $table->addColumn('druhe_dodani', 'integer', $null );
      $table->addColumn('xertec_id', 'integer', $null );
      $table->addColumn('pocet_priloh', 'integer', $null );
      $table->addColumn('stav', 'integer', $null );
      $table->addColumn('spis_vyrizen', 'datetime', $null );
      $table->addColumn('pocet_listu', 'integer', $null );
      $table->addColumn('ulozeno', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('oddeleni', 'integer', $null );
      $table->addColumn('jine', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('nazev_spisu', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('druh_priloh', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('zpusob_podani', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('stornovano', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('datum_vypraveni', 'datetime', $null );
      $table->addColumn('znacka', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('podatelna_id', 'integer', $null );
      $table->addColumn('obyvatel_kod', 'integer', $null );
      $table->addColumn('odesl_rc', 'string', array( 'notnull' => false, 'length' => 11 ));
      $table->addColumn('prehled_spis', 'integer', $null );
      $table->addColumn('datum_predani', 'datetime', $null );
      $table->addColumn('datum_predani_ven', 'datetime', $null );
      $table->addColumn('datum_pm', 'datetime', $null );
      $table->addColumn('odesl_otocit', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_subj', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('odesl_email', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('odesl_body', 'text', $null );
      $table->addColumn('status', 'integer', $null );
      $table->addColumn('obalka_nevracet', 'integer', $null );
      $table->addColumn('obalka_10dni', 'integer', $null );
      $table->addColumn('odesl_datschranka', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_datnar', 'date', $null );
      $table->addColumn('zmocneni_zakon', 'integer', $null );
      $table->addColumn('zmocneni_rok', 'integer', $null );
      $table->addColumn('zmocneni_odst', 'integer', $null );
      $table->addColumn('zmocneni_par', 'integer', $null );
      $table->addColumn('zmocneni_pismeno', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('jejich_cj', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('text_cj', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addColumn('private', 'integer', $null );
      $table->addColumn('typ_dokumentu', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('main_doc', 'integer', $null );
      $table->addColumn('jejich_cj_dne', 'date', $null );
      $table->addColumn('lhuta_vyrizeni', 'date', $null );
      $table->addColumn('adresat_id', 'integer', $null );
      $table->addColumn('kopie', 'integer', $null );
      $table->addColumn('odesl_stat', 'string', array( 'notnull' => false, 'length' => 80 ));
      $table->addColumn('odesl_titul_za', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_jine', 'string', array( 'notnull' => false, 'length' => 80 ));
      $table->addColumn('exemplar', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
//      $table->addColumn('tsv', 'tsvector', $null );
      $table->addIndex(array('main_doc'), 'idx_main_doc_posta');
      $table->addIndex(array('superodbor'), 'idx_superodbor_posta');
      $table->addIndex(array('ev_cislo'), 'idx_ev_cislo_posta');
      $table->addIndex(array('rok'), 'idx_rok_posta');
      $table->addIndex(array('odbor'), 'idx_odbor_posta');
      $table->addIndex(array('referent'), 'idx_referent_posta');
      $table->addIndex(array('cislo_spisu1'), 'idx_cislo_spisu1_posta');
      $table->addIndex(array('cislo_spisu2'), 'idx_cislo_spisu2_posta');
      $table->addIndex(array('xertec_id'), 'idx_xertec_id_posta');
      $table->addIndex(array('spisovna_id'), 'idx_spisovna_id_posta');
      $table->addIndex(array('datum_predani'), 'idx_datum_predani_posta');
      $table->addIndex(array('datum_predani_ven'), 'idx_datum_predani_ven_posta');
      $table->addIndex(array('lhuta'), 'idx_lhuta_posta');
      $table->addIndex(array('stav'), 'idx_stav_posta');
      $table->addIndex(array('status'), 'idx_status_posta');
      $table->addIndex(array('dalsi_id_agenda'), 'idx_dalsi_id_agenda_posta');

      $table = $schema->createTable('posta_h');
      $table->addColumn('id_h', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id_h'), 'pk_posta_h');
      $table->addColumn('id', 'integer', $not_null );
      $table->addColumn('ev_cislo', 'integer', $not_null );
      $table->addColumn('rok', 'integer', $not_null );
      $table->addColumn('odes_typ', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_adrkod', 'integer', $null );
      $table->addColumn('odesl_titul', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_prijmeni', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('odesl_jmeno', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_odd', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('odesl_osoba', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_ulice', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_cp', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_cor', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_ico', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('odesl_psc', 'string', array( 'notnull' => false, 'length' => 6 ));
      $table->addColumn('odesl_posta', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_rekomando', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_postaodesl', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('lhuta', 'integer', $null );
      $table->addColumn('datum_spravce_prijeti', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('typ_posty', 'integer', $null );
      $table->addColumn('referent', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('vec', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('vyrizeno', 'text', $null );
      $table->addColumn('datum_referent_prijeti', 'datetime', $null );
      $table->addColumn('odeslana_posta', 'boolean', $null );
      $table->addColumn('datum_vyrizeni', 'datetime', $null );
      $table->addColumn('odesl_osloveni', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('doporucene', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('vlastnich_rukou', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('dorucenka', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('cislo_spisu1', 'integer', $null );
      $table->addColumn('cislo_spisu2', 'integer', $null );
      $table->addColumn('podcislo_spisu', 'integer', $null );
      $table->addColumn('skartace', 'integer', $null );
      $table->addColumn('datum_doruceni', 'datetime', $null );
      $table->addColumn('dalsi_prijemci', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('id_puvodni', 'integer', $null );
      $table->addColumn('puvodni_spis', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('datum_podatelna_prijeti', 'datetime', $null );
      $table->addColumn('dalsi_id_agenda', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('objekt_kod', 'integer', $null );
      $table->addColumn('okres_kod', 'integer', $null );
      $table->addColumn('skartovano', 'string', array( 'notnull' => false, 'length' => 25 ));
      $table->addColumn('poznamka', 'text', $null );
      $table->addColumn('frozen', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('cislo_jednaci1', 'integer', $null );
      $table->addColumn('cislo_jednaci2', 'integer', $null );
      $table->addColumn('odbor_spisu', 'string', array( 'notnull' => false, 'length' => 5 ));
      $table->addColumn('hmotnost', 'integer', $null );
      $table->addColumn('cena', 'decimal', $null );
      $table->addColumn('druh_zasilky', 'integer', $null );
      $table->addColumn('druhe_dodani', 'integer', $null );
      $table->addColumn('xertec_id', 'integer', $null );
      $table->addColumn('pocet_priloh', 'integer', $null );
      $table->addColumn('stav', 'integer', $null );
      $table->addColumn('spis_vyrizen', 'datetime', $null );
      $table->addColumn('pocet_listu', 'integer', $null );
      $table->addColumn('ulozeno', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('oddeleni', 'integer', $null );
      $table->addColumn('jine', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('nazev_spisu', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('druh_priloh', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('zpusob_podani', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('stornovano', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('datum_vypraveni', 'datetime', $null );
      $table->addColumn('znacka', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('podatelna_id', 'integer', $null );
      $table->addColumn('obyvatel_kod', 'integer', $null );
      $table->addColumn('odesl_rc', 'string', array( 'notnull' => false, 'length' => 11 ));
      $table->addColumn('prehled_spis', 'integer', $null );
      $table->addColumn('datum_predani', 'datetime', $null );
      $table->addColumn('datum_predani_ven', 'datetime', $null );
      $table->addColumn('datum_pm', 'datetime', $null );
      $table->addColumn('odesl_otocit', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_subj', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('odesl_email', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('odesl_body', 'text', $null );
      $table->addColumn('status', 'integer', $null );
      $table->addColumn('obalka_nevracet', 'integer', $null );
      $table->addColumn('obalka_10dni', 'integer', $null );
      $table->addColumn('odesl_datschranka', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_datnar', 'date', $null );
      $table->addColumn('zmocneni_zakon', 'integer', $null );
      $table->addColumn('zmocneni_rok', 'integer', $null );
      $table->addColumn('zmocneni_odst', 'integer', $null );
      $table->addColumn('zmocneni_par', 'integer', $null );
      $table->addColumn('zmocneni_pismeno', 'string', array( 'notnull' => false, 'length' => 2 ));
      $table->addColumn('jejich_cj', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('text_cj', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addColumn('private', 'integer', $null );
      $table->addColumn('typ_dokumentu', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('main_doc', 'integer', $null );
      $table->addColumn('jejich_cj_dne', 'date', $null );
      $table->addColumn('lhuta_vyrizeni', 'date', $null );
      $table->addColumn('adresat_id', 'integer', $null );
      $table->addColumn('kopie', 'integer', $null );
      $table->addColumn('odesl_stat', 'string', array( 'notnull' => false, 'length' => 80 ));
      $table->addColumn('odesl_titul_za', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_jine', 'string', array( 'notnull' => false, 'length' => 80 ));
      $table->addColumn('exemplar', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
//      $table->addColumn('tsv', 'tsvector', $null );
      $table->addIndex(array('id'), 'idx_id_posta_h');


      //ostatni
      $table = $schema->createTable('posta_adresati');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_adresati');
      $table->addColumn('odes_typ', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_adrkod', 'integer', $null );
      $table->addColumn('odesl_titul', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_prijmeni', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_jmeno', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_odd', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('odesl_osoba', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_ulice', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_cp', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_cor', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_ico', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('odesl_psc', 'string', array( 'notnull' => false, 'length' => 6 ));
      $table->addColumn('odesl_posta', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_rc', 'string', array( 'notnull' => false, 'length' => 11 ));
      $table->addColumn('odesl_email', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('odesl_datschranka', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_datnar', 'date', $null );
      $table->addColumn('frozen', 'string', array( 'notnull' => false, 'length' => 1 ));
//      $table->addColumn('tsv', 'tsvector', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );

      $table = $schema->createTable('posta_adresati_h');
      $table->addColumn('id_h', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id_h'), 'pk_posta_adresati_h');
      $table->addColumn('id', 'integer', $not_null );
      $table->addColumn('odes_typ', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_adrkod', 'integer', $null );
      $table->addColumn('odesl_titul', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_prijmeni', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_jmeno', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_odd', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('odesl_osoba', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_ulice', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_cp', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_cor', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_ico', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('odesl_psc', 'string', array( 'notnull' => false, 'length' => 6 ));
      $table->addColumn('odesl_posta', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_rc', 'string', array( 'notnull' => false, 'length' => 11 ));
      $table->addColumn('odesl_email', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('odesl_datschranka', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_datnar', 'date', $null );
      $table->addColumn('frozen', 'string', array( 'notnull' => false, 'length' => 1 ));
//      $table->addColumn('tsv', 'tsvector', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('id'), 'idx_id_posta_adresati_h');

      $table = $schema->createTable('posta_carovekody');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_carovekody');
      $table->addColumn('dokument_id', 'integer', $not_null );
      $table->addColumn('ck', 'string', array( 'notnull' => true, 'length' => 50 ));
      $table->addIndex(array('dokument_id'), 'idx_dokument_id_posta_carovekody');

      $table = $schema->createTable('posta_certifikaty');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_certifikaty');
      $table->addColumn('osoba', 'integer', $null );
      $table->addColumn('platnost_od', 'date', $null );
      $table->addColumn('platnost_do', 'date', $null );
      $table->addColumn('zneplatneni_datum', 'date', $null );
      $table->addColumn('zneplatneni_duvod', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('prichozi', 'integer', $null );
      $table->addColumn('odchozi', 'integer', $null );

      $table = $schema->createTable('posta_datova_zprava');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_datova_zprava');
      $table->addColumn('dmid', 'string', array( 'notnull' => true, 'length' => 20 ));
      $table->addColumn('dbidsender', 'string', array( 'notnull' => false, 'length' => 7 ));
      $table->addColumn('dmsender', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('dmsenderaddress', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('dmsendertype', 'integer', $null );
      $table->addColumn('dmrecipient', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('dmrecipientaddress', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('dmsenderorgunit', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('dmsenderorgunitnum', 'integer', $null );
      $table->addColumn('dbidrecipient', 'string', array( 'notnull' => false, 'length' => 7 ));
      $table->addColumn('dmrecipientorgunit', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('dmrecipientorgunitnum', 'integer', $null );
      $table->addColumn('dmtohands', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('dmannotation', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('dmrecipientrefnumber', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('dmsenderrefnumber', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('dmrecipientident', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('dmsenderident', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('dmlegaltitlelaw', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('dmlegaltitleyear', 'integer', $null );
      $table->addColumn('dmlegaltitlesect', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('dmlegaltitlepar', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('dmlegaltitlepoint', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('dmpersonaldelivery', 'boolean', $null );
      $table->addColumn('dmallowsubstdelivery', 'boolean', $null );
      $table->addColumn('dmmessagestatus', 'integer', $null );
      $table->addColumn('dmattachmentsize', 'integer', $null );
      $table->addColumn('dmdeliverytime', 'datetime', $null );
      $table->addColumn('dmacceptancetime', 'datetime', $null );
      $table->addIndex(array('dmid'), 'idx_dmid_posta_datova_zprava');

      $table = $schema->createTable('posta_dokumentace');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_dokumentace');
      $table->addColumn('nazev', 'string', array( 'notnull' => true, 'length' => 255 ));
      $table->addColumn('popis', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('superodbor', 'integer', $null );
      $table->addIndex(array('superodbor'), 'idx_superodbor_posta_dokumentace');

      $table = $schema->createTable('posta_ds');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_ds');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('ds_id', 'integer', $not_null );
      $table->addColumn('odeslana_posta', 'boolean', $null );
      $table->addColumn('datum_odeslani', 'datetime', $null );
      $table->addColumn('datum_doruceni', 'datetime', $null );
      $table->addColumn('datum_precteni', 'datetime', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_ds');
      $table->addIndex(array('ds_id'), 'idx_ds_id_posta_ds');

      $table = $schema->createTable('posta_ds_dm_timestamp');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_ds_dm_timestamp');
      $table->addColumn('dm_id', 'integer', $not_null );
      $table->addColumn('timestamp', 'datetime', $not_null );
      $table->addIndex(array('dm_id'), 'idx_dm_id_posta_ds_dm_timestamp');

      $table = $schema->createTable('posta_ds_filtry');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_ds_filtry');
      $table->addColumn('dm_item', 'string', array( 'notnull' => false, 'length' => 64 ));
      $table->addColumn('dm_item_compared_values', 'string', array( 'notnull' => false, 'length' => 8192 ));
      $table->addColumn('priority', 'integer', $null );
      $table->addColumn('ed_item_superodbor', 'integer', $null );
      $table->addColumn('ed_item_odbor', 'integer', $null );
      $table->addColumn('ed_item_referent', 'integer', $null );
      $table->addIndex(array('priority'), 'idx_priority_posta_ds_filtry');

      $table = $schema->createTable('posta_epodatelna');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_epodatelna');
      $table->addColumn('mailbox', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('smer', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('uid', 'integer', $null );
      $table->addColumn('record_uid', 'string', array( 'notnull' => false, 'length' => 200 ));
      $table->addColumn('dokument_id', 'integer', $not_null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('dokument_id'), 'idx_dokument_id_posta_epodatelna');
      $table->addIndex(array('uid'), 'idx_uid_posta_epodatelna');
      $table->addIndex(array('record_uid'), 'idx_record_uid_posta_epodatelna');

      $table = $schema->createTable('posta_hromadnaobalka');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_hromadnaobalka');
      $table->addColumn('obalka_id', 'integer', $not_null );
      $table->addColumn('dokument_id', 'integer', $not_null );
      $table->addIndex(array('dokument_id'), 'idx_dokument_id_posta_hromadnaobalka');

      $table = $schema->createTable('posta_interface_log');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_interface_log');
      $table->addColumn('datum', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('sw', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('popis', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('session_id', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('chyba', 'integer', $not_null );
      $table->addColumn('request', 'text', $null );
      $table->addColumn('response', 'text', $null );

      $table = $schema->createTable('posta_interface_login');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_interface_login');
      $table->addColumn('cas', 'integer', $null );
      $table->addColumn('sw', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('session_id', 'string', array( 'notnull' => false, 'length' => 50 ));

      $table = $schema->createTable('posta_isrzp_pracovnici');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_isrzp_pracovnici');
      $table->addColumn('idrzp', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('twist_id', 'integer', $not_null );
      $table->addIndex(array('idrzp'), 'idx_idrzp_posta_isrzp_pracovnici');
      $table->addIndex(array('twist_id'), 'idx_twist_id_posta_isrzp_pracovnici');

      $table = $schema->createTable('posta_konfigurace');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_konfigurace');
      $table->addColumn('kategorie', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('typ', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('parametr', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('hodnota', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('popis', 'string', array( 'notnull' => false, 'length' => 2550 ));
      $table->addColumn('superodbor', 'integer', $null );

      $table = $schema->createTable('posta_konfigurace_h');
      $table->addColumn('id_h', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id_h'), 'pk_posta_konfigurace_h');
      $table->addColumn('id', 'integer', $not_null );
      $table->addColumn('kategorie', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('typ', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('parametr', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('hodnota', 'string', array( 'notnull' => false, 'length' => 1024 ));
      $table->addColumn('popis', 'string', array( 'notnull' => false, 'length' => 2550 ));
      $table->addColumn('superodbor', 'integer', $null );
      $table->addIndex(array('id'), 'idx_id_posta_konfigurace_h');

      $table = $schema->createTable('posta_krizovy_spis');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_krizovy_spis');
      $table->addColumn('puvodni_spis', 'integer', $null );
      $table->addColumn('novy_spis', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('puvodni_spis'), 'idx_puvodni_spis_posta_krizovy_spis');
      $table->addIndex(array('novy_spis'), 'idx_novy_spis_posta_krizovy_spis');

      $table = $schema->createTable('posta_log');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_log');
      $table->addColumn('agenda_id', 'integer', $null );
      $table->addColumn('text', 'text', $null );
      $table->addColumn('chyba', 'integer', array( 'notnull' => false, 'default' => 0 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('chyba'), 'idx_chyba_posta_log');

      $table = $schema->createTable('posta_nastaveni_vnejsi_adresati');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_nastaveni_vnejsi_adresati');
      $table->addColumn('skupina_id', 'integer', $null );
      $table->addColumn('adresat_id', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('skupina_id'), 'idx_skupina_id_posta_nastaveni_vnejsi_adresati');
      $table->addIndex(array('adresat_id'), 'idx_adresat_id_posta_nastaveni_vnejsi_adresati');

      $table = $schema->createTable('posta_nastaveni_vnejsi_adresati_skupiny');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_nastaveni_vnejsi_adresati_skupiny');
      $table->addColumn('skupina_id', 'integer', $not_null );
      $table->addColumn('nazev_skupiny', 'string', array( 'notnull' => false, 'length' => 150 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('skupina_id'), 'idx_skupina_id_posta_nastaveni_vnejsi_adresati_skupiny');

      $table = $schema->createTable('posta_nastaveni_vnitrni_adresati');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_nastaveni_vnitrni_adresati');
      $table->addColumn('skupina_id', 'integer', $null );
      $table->addColumn('organizacni_vybor', 'integer', $null );
      $table->addColumn('zpracovatel', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('skupina_id'), 'idx_skupina_id_posta_nastaveni_vnitrni_adresati');
      $table->addIndex(array('organizacni_vybor'), 'idx_organizacni_vybor_posta_nastaveni_vnitrni_adresati');
      $table->addIndex(array('zpracovatel'), 'idx_zpracovatel_posta_nastaveni_vnitrni_adresati');

      $table = $schema->createTable('posta_nastaveni_vnitrni_adresati_skupiny');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_nastaveni_vnitrni_adresati_skupiny');
      $table->addColumn('typ', 'integer', $not_null );
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );

      $table = $schema->createTable('posta_odmitnuti');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_odmitnuti');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('duvod', 'text', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_odmitnuti');

      $table = $schema->createTable('posta_protokoly');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_protokoly');
      $table->addColumn('type', 'string', array( 'notnull' => false, 'length' => 6 ));
      $table->addColumn('cislo', 'string', array( 'notnull' => false, 'length' => 11 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );

      $table = $schema->createTable('posta_protokoly_ids');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_protokoly_ids');
      $table->addColumn('cislo', 'string', array( 'notnull' => false, 'length' => 11 ));
      $table->addColumn('dokument_id', 'integer', $not_null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('cislo'), 'idx_cislo_posta_protokoly_ids');
      $table->addIndex(array('dokument_id'), 'idx_dokument_id_posta_protokoly_ids');

      $table = $schema->createTable('posta_schvalovani');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_schvalovani');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('schvalujici_id', 'integer', $null );
      $table->addColumn('datum_zalozeni', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('datum_podpisu', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('poznamka', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('schvaleno', 'integer', $null );
      $table->addColumn('typschvaleni', 'integer', $null );
      $table->addColumn('poznamka2', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('postup', 'integer', $null );
      $table->addColumn('stornovano', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_schvalovani');
      $table->addIndex(array('schvalujici_id'), 'idx_schvalujici_id_posta_schvalovani');
      $table->addIndex(array('typschvaleni'), 'idx_typschvaleni_posta_schvalovani');
      $table->addIndex(array('postup'), 'idx_postup_posta_schvalovani');

      $table = $schema->createTable('posta_skartace');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_skartace');
      $table->addColumn('spis_id', 'integer', $not_null );
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('cj', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('datum_zahajeni', 'date', $null );
      $table->addColumn('datum_odeslani', 'date', $null );
      $table->addColumn('datum_skartace', 'date', $null );
      $table->addColumn('datum_uzavreni', 'date', $null );
      $table->addColumn('jid', 'string', array( 'notnull' => false, 'length' => 255 ));

      $table = $schema->createTable('posta_skartace_id');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_skartace_id');
      $table->addColumn('skartace_id', 'integer', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addIndex(array('skartace_id'), 'idx_skartace_id_posta_skartace_id');
      $table->addIndex(array('spisovna_id'), 'idx_spisovna_id_posta_skartace_id');

      $table = $schema->createTable('posta_skartace_soubory');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_skartace_soubory');
      $table->addColumn('rizeni_id', 'integer', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addIndex(array('rizeni_id'), 'idx_skartace_id_posta_skartace_soubory');
      $table->addIndex(array('spisovna_id'), 'idx_spisovna_id_posta_skartace_soubory');

      $table = $schema->createTable('posta_spisobal');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisobal');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('listu', 'integer', $null );
      $table->addColumn('obeh_pred', 'text', $null );
      $table->addColumn('obeh_po', 'text', $null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_posta_spisobal');

      $table = $schema->createTable('posta_spisovna');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisovna');
      $table->addColumn('dokument_id', 'integer', $null );
      $table->addColumn('skartace_id', 'integer', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addColumn('cislo_spisu1', 'integer', $null );
      $table->addColumn('cislo_spisu2', 'integer', $null );
      $table->addColumn('vec', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('listu', 'integer', $null );
      $table->addColumn('prilohy', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('skar_znak', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('lhuta', 'integer', $null );
      $table->addColumn('rok_predani', 'integer', $null );
      $table->addColumn('rok_skartace', 'integer', $null );
      $table->addColumn('datum_predani', 'date', $null );
      $table->addColumn('digitalni', 'integer', $null );
      $table->addColumn('protokol_id', 'integer', $null );
      $table->addColumn('zapujcka_id', 'integer', $null );
      $table->addColumn('datum_skartace', 'date', $null );
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('poznamka', 'text', $null );
      $table->addColumn('prevzal_id', 'integer', $null );
      $table->addColumn('ulozeni', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('registratura', 'text', $null );
      $table->addColumn('lokace_id', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('skar_znak_alt', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('rezim_id', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('dokument_id'), 'idx_dokument_id_posta_spisovna');
      $table->addIndex(array('cislo_spisu1'), 'idx_cislo_spisu1_posta_spisovna');
      $table->addIndex(array('cislo_spisu2'), 'idx_cislo_spisu2_posta_spisovna');
      $table->addIndex(array('superodbor'), 'idx_superodbor_posta_spisovna');
      $table->addIndex(array('datum_skartace'), 'idx_datum_skartace_posta_spisovna');
      $table->addIndex(array('lokace_id'), 'idx_lokace_id_posta_spisovna');

      $table = $schema->createTable('posta_spisovna_h');
      $table->addColumn('id_h', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id_h'), 'pk_posta_spisovna_h');
      $table->addColumn('id', 'integer', $not_null );
      $table->addColumn('dokument_id', 'integer', $null );
      $table->addColumn('skartace_id', 'integer', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addColumn('cislo_spisu1', 'integer', $null );
      $table->addColumn('cislo_spisu2', 'integer', $null );
      $table->addColumn('vec', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('listu', 'integer', $null );
      $table->addColumn('prilohy', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('skar_znak', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('lhuta', 'integer', $null );
      $table->addColumn('rok_predani', 'integer', $null );
      $table->addColumn('rok_skartace', 'integer', $null );
      $table->addColumn('datum_predani', 'date', $null );
      $table->addColumn('digitalni', 'integer', $null );
      $table->addColumn('protokol_id', 'integer', $null );
      $table->addColumn('zapujcka_id', 'integer', $null );
      $table->addColumn('datum_skartace', 'date', $null );
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('poznamka', 'text', $null );
      $table->addColumn('prevzal_id', 'integer', $null );
      $table->addColumn('ulozeni', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('registratura', 'text', $null );
      $table->addColumn('lokace_id', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('skar_znak_alt', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('rezim_id', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('id'), 'idx_id_posta_spisovna_h');

      $table = $schema->createTable('posta_spisovna_boxy');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisovna_boxy');
      $table->addColumn('ck', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('popis', 'text', $null );
      $table->addColumn('umisteni', 'text', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('rok', 'integer', $null );
      $table->addColumn('ev_cislo', 'integer', $null );
      $table->addColumn('skar_znak', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addColumn('skar_lhuta', 'integer', $null );
      $table->addIndex(array('odbor'), 'idx_odbor_posta_spisovna_boxy');
      $table->addIndex(array('spisovna_id'), 'idx_spisovna_id_posta_spisovna_boxy');

      $table = $schema->createTable('posta_spisovna_boxy_ids');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisovna_boxy_ids');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('box_id', 'integer', $not_null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_spisovna_boxy_ids');
      $table->addIndex(array('box_id'), 'idx_box_id_posta_spisovna_boxy_ids');

      $table = $schema->createTable('posta_spisovna_cis_lokace');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisovna_cis_lokace');
      $table->addColumn('id_parent', 'integer', $null );
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('plna_cesta', 'text', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addColumn('dalsi_lokace', 'integer', $null );
      $table->addColumn('urovne', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('id_parent'), 'idx_id_parent_posta_spisovna_cis_lokace');
      $table->addIndex(array('plna_cesta'), 'idx_plna_cesta_posta_spisovna_cis_lokace');
      $table->addIndex(array('spisovna_id'), 'idx_spisovna_id_posta_spisovna_cis_lokace');

      $table = $schema->createTable('posta_spisovna_zapujcky');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisovna_zapujcky');
      $table->addColumn('vytvoreno', 'date', $null );
      $table->addColumn('vraceno', 'date', $null );
      $table->addColumn('spisovna_id', 'integer', $null );
      $table->addColumn('vytvoreno_kym', 'integer', $null );
      $table->addColumn('pujceno_komu', 'integer', $null );
      $table->addColumn('vraceno_komu', 'integer', $null );
      $table->addColumn('superodbor', 'integer', $null );
      $table->addColumn('stornovano', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('rucne', 'integer', $null );
      $table->addColumn('rucne_cj', 'text', $null );
      $table->addColumn('poznamka', 'text', $null );
      $table->addIndex(array('spisovna_id'), 'idx_spisovna_id_posta_spisovna_zapujcky');
      $table->addIndex(array('vraceno'), 'idx_vraceno_posta_spisovna_zapujcky');
      $table->addIndex(array('superodbor'), 'idx_superodbor_spisovna_zapujcky');

      $table = $schema->createTable('posta_spisovna_zapujcky_id');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisovna_zapujcky_id');
      $table->addColumn('zapujcka_id', 'integer', $not_null );
      $table->addColumn('posta_id', 'integer', $null );
      $table->addIndex(array('zapujcka_id'), 'idx_zapujcka_id_posta_spisovna_zapujcky_id');
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_spisovna_zapujcky_id');

      $table = $schema->createTable('posta_spisprehled_zaznamy');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_spisprehled_zaznamy');
      $table->addColumn('cislo_spisu1', 'integer', $null );
      $table->addColumn('cislo_spisu2', 'integer', $null );
      $table->addColumn('nazev_spisu', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('referent', 'integer', $null );
      $table->addColumn('odbor', 'integer', $null );
      $table->addColumn('datum_podatelna_prijeti', 'datetime', $not_null );
      $table->addColumn('vec', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('pocet_listu', 'integer', $null );
      $table->addColumn('pocet_priloh', 'integer', $null );
      $table->addColumn('druh_priloh', 'string', array( 'notnull' => false, 'length' => 30 ));
      $table->addColumn('odes_typ', 'string', array( 'notnull' => false, 'length' => 1 ));
      $table->addColumn('odesl_adrkod', 'integer', $null );
      $table->addColumn('odesl_prijmeni', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_jmeno', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_odd', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addColumn('odesl_osoba', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_titul', 'string', array( 'notnull' => false, 'length' => 20 ));
      $table->addColumn('odesl_ulice', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('odesl_cp', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_cor', 'string', array( 'notnull' => false, 'length' => 15 ));
      $table->addColumn('odesl_ico', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('odesl_psc', 'string', array( 'notnull' => false, 'length' => 5 ));
      $table->addColumn('odesl_posta', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('cislo_spisu1'), 'idx_cislo_spisu1_posta_spisprehled_zaznamy');
      $table->addIndex(array('cislo_spisu2'), 'idx_cislo_spisu2_posta_spisprehled_zaznamy');

      $table = $schema->createTable('posta_transakce');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_transakce');
      $table->addColumn('doc_id', 'integer', $null );
      $table->addColumn('jmeno', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('typ', 'string', array( 'notnull' => false, 'length' => 25 ));
      $table->addColumn('text', 'text', $null );
      $table->addColumn('last_user_id', 'integer', $null );
      $table->addColumn('last_time', 'datetime', $null );
      $table->addColumn('id_superodbor', 'integer', $null );
      $table->addIndex(array('doc_id'), 'idx_doc_id_posta_transakce');
      $table->addIndex(array('id_superodbor'), 'idx_id_superodbor_posta_transakce');

      $table = $schema->createTable('posta_typovy_spis_typ_posty');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_typovy_spis_typ_posty');
      $table->addColumn('id_typovy_spis', 'integer', $null );
      $table->addColumn('id_typ_posty', 'integer', $null );
      $table->addIndex(array('id_typovy_spis'), 'idx_id_typovy_spis_posta_typovy_spis_typ_posty');
      $table->addIndex(array('id_typ_posty'), 'idx_id_typ_posty_posta_typovy_spis_typ_posty');

      $table = $schema->createTable('posta_user_filtry');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_user_filtry');
      $table->addColumn('owner_id', 'integer', $null );
      $table->addColumn('nazev', 'string', array( 'notnull' => false, 'length' => 100 ));
      $table->addColumn('nastaveni', 'text', $null );
      $table->addIndex(array('owner_id'), 'idx_owner_id_posta_user_filtry');

      $table = $schema->createTable('posta_vnitrni_adresati');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_vnitrni_adresati');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('organizacni_vybor', 'integer', $null );
      $table->addColumn('zpracovatel', 'integer', $null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_vnitrni_adresati');

      $table = $schema->createTable('posta_zastupy');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_zastupy');
      $table->addColumn('zpracovatel', 'integer', $null );
      $table->addColumn('zastoupena', 'integer', $null );
      $table->addColumn('poznamka', 'string', array( 'notnull' => false, 'length' => 255 ));
      $table->addColumn('datum', 'string', array( 'notnull' => false, 'length' => 50 ));
      $table->addIndex(array('zpracovatel'), 'idx_zpracovatel_posta_zastupy');
      $table->addIndex(array('zastoupena'), 'idx_zastoupena_posta_zastupy');

      $table = $schema->createTable('posta_zpracovatele');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_zpracovatele');
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('referent_id', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_zpracovatele');

      $table = $schema->createTable('posta_zpracovatele_h');
      $table->addColumn('id_h', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id_h'), 'pk_posta_zpracovatele_h');
      $table->addColumn('id', 'integer', $not_null );
      $table->addColumn('posta_id', 'integer', $not_null );
      $table->addColumn('referent_id', 'integer', $null );
      $table->addColumn('last_date', 'date', $not_null );
      $table->addColumn('last_time', 'string', array( 'notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', $not_null );
      $table->addColumn('owner_id', 'integer', $not_null );
      $table->addIndex(array('id'), 'idx_id_posta_zpracovatele_h');
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_zpracovatele_h');
      $table->addIndex(array('id'), 'idx_id_posta_zpracovatele');

    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
      // this down() migration is auto-generated, please modify it to your needs
      //ciselniky
      $table = $schema->getTable('cis_posta_agenda');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_jine');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_odbory');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_predani');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_prijemci');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_skartace');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_skartace_h');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_spisy');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_typ');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('cis_posta_ulozeno');
      $schema->dropTable($table->getName());


      $table = $schema->getTable('posta_cis_adresati');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_ceskaposta');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_ceskaposta_ck');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_ceskaposta_id');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_deniky');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_dorucovatel');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_dorucovatel_id');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_obalky');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_obalky_objekty');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_osloveni');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_sablony');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_skartace_main');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_skartacni_rezimy');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_spisovna');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_typ_spis_soucasti');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_typovy_spis');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_cis_vyrizeno');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_dalsi_zpracovatele');
      $schema->dropTable($table->getName());


      //hlavni tabulka
      $table = $schema->getTable('posta');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_h');
      $schema->dropTable($table->getName());


      //ostatni
      $table = $schema->getTable('posta_adresati');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_adresati_h');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_carovekody');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_certifikaty');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_datova_zprava');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_dokumentace');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_ds');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_ds_dm_timestamp');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_ds_filtry');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_epodatelna');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_hromadnaobalka');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_interface_log');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_interface_login');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_isrzp_pracovnici');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_konfigurace');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_konfigurace_h');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_krizovy_spis');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_log');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_nastaveni_vnejsi_adresati');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_nastaveni_vnejsi_adresati_skupiny');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_nastaveni_vnitrni_adresati');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_nastaveni_vnitrni_adresati_skupiny');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_odmitnuti');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_protokoly');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_protokoly_ids');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_schvalovani');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_skartace');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_skartace_id');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_skartace_soubory');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisobal');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisovna');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisovna_h');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisovna_boxy');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisovna_boxy_ids');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisovna_cis_lokace');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisovna_zapujcky');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisovna_zapujcky_id');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_spisprehled_zaznamy');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_transakce');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_typovy_spis_typ_posty');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_user_filtry');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_vnitrni_adresati');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_zastupy');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_zpracovatele');
      $schema->dropTable($table->getName());

      $table = $schema->getTable('posta_zpracovatele_h');
      $schema->dropTable($table->getName());

    }
}
