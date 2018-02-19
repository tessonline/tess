<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170112124957 extends AbstractMigration
{
  
  
    /*CREATE TABLE posta_hromadny_import (
      tid int4 NOT NULL DEFAULT nextval('posta_hromadny_import_tid_seq'::regclass),
      popis varchar(255) NULL DEFAULT NULL::character varying,
      stav int4 NOT NULL DEFAULT 0,
      zamceno numeric(5,5) NULL DEFAULT NULL::numeric,
      last_date_import date NULL,
      last_time_import varchar(10) NULL DEFAULT NULL::character varying,
      last_date date NULL,
      last_time varchar(10) NULL DEFAULT NULL::character varying,
      last_user_id int4 NULL,
      owner_id int4 NULL,
      CONSTRAINT oby_t_import_pkey PRIMARY KEY (tid)
      );
    */
  
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
        
      $table = $schema->createTable('posta_hromadny_import');
      
      $table->addColumn('tid', 'integer', array(
        'autoincrement' => true,
      ));
      
      //   PRIMARY KEY (id)
      $table->setPrimaryKey(array('tid'), 'pk_posta_hromadny_import');
      
      
      $table->addColumn('popis', 'string', array(
        'notnull' => false,
        'length' => 255,
      ));
      
      $table->addColumn('stav', 'integer', array(
        'default' => 0,
      ));
      
      $table->addColumn('zamceno', 'decimal', array(
        'notnull' => false,
        'precision' => 5,
        'scale' => 5,
      ));
       
      $table->addColumn('last_date_import', 'date', array(
        'notnull' => false,
      ));
      
      $table->addColumn('last_time_import', 'string', array(
        'notnull' => false,
        'length' => 10,
      ));
      
      $table->addColumn('last_date', 'date', array(
        'notnull' => false,
      ));
      
      $table->addColumn('last_time', 'string', array(
        'notnull' => false,
        'length' => 10,
      ));
      
      $table->addColumn('last_user_id', 'integer', array(
        'notnull' => false,
      ));
      
      $table->addColumn('owner_id', 'integer', array(
        'notnull' => false,
      ));
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
        
      $table = $schema->getTable('posta_hromadny_import');
      $schema->dropTable($table->getName());

    }
}
