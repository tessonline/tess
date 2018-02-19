<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170103092938 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
         /*CREATE TABLE public.posta_workflow
      (
          id serial,
          id_workflow int,
          id_typ int,
          promenna varchar(30),
          hodnota varchar(100),
          last_date date,
          last_time varchar(10)	,
          last_user_id smallint,
          owner_id smallint
          )
          WITH (
              OIDS=TRUE
              );*/
      
      $table = $schema->createTable('posta_workflow');
      
      $table->addColumn('id', 'integer', array(
        'autoincrement' => true,
      ));
      
      //   PRIMARY KEY (id)
      $table->setPrimaryKey(array('id'), 'pk_posta_workflow');
     
      $table->addColumn('id_workflow', 'integer', array(
        'notnull' => true,
      ));
      
      $table->addColumn('id_typ', 'integer', array(
        'notnull' => true,
      ));
      
      $table->addColumn('promenna', 'string', array(
        'notnull' => false,
        'length' => 30,
      ));
      
      $table->addColumn('hodnota', 'string', array(
        'notnull' => false,
        'length' => 100,
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
        
      $table = $schema->getTable('posta_workflow');
      $schema->dropTable($table->getName());

    }
}
