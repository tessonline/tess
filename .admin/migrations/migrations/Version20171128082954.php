<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20171128082954 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
  public function up(Schema $schema)
  {
    // this up() migration is auto-generated, please modify it to your needs
    
    // this up() migration is auto-generated, please modify it to your needs
    $table = $schema->createTable('posta_workflow_pole');
    
    $table->addColumn('id', 'integer', array('autoincrement' => true ));
    $table->setPrimaryKey(array('id'), 'pk_posta_workflow_pole');
    
    $table->addColumn('id_posta', 'integer', array(
      'notnull' => true,
    ));
    
    
    $table->addColumn('promenna', 'string', array(
      'notnull' => false,
      'length' => 30,
    ));
    
    //   PRIMARY KEY (id_posta,promenna)
    //$table->setPrimaryKey(array('id_posta','promenna'), 'pk_posta_workflow_pole');
    
    
    $table->addColumn('hodnota', 'string', array(
      'notnull' => false,
      'length' => 255,
    ));
    
    $table->addColumn('datovy_typ', 'string', array(
      'notnull' => false,
      'length' => 25,
    ));    
    
    $table->addIndex(array('id_posta','promenna'), 'idx_posta_workflow_pole_h');
    
    
    $table = $schema->createTable('posta_workflow_pole_h');

    
    $table->addColumn('id', 'integer', array('notnull' => true ));
    
    $table->addColumn('id_posta', 'integer', array(
      'notnull' => true,
    ));
    
    
    $table->addColumn('promenna', 'string', array(
      'notnull' => false,
      'length' => 30,
    ));
    
    //   PRIMARY KEY (id_posta,promenna)
    //$table->setPrimaryKey(array('id_posta','promenna'), 'pk_posta_workflow_pole');
    
    
    $table->addColumn('hodnota', 'string', array(
      'notnull' => false,
      'length' => 255,
    ));
    
    $table->addColumn('datovy_typ', 'string', array(
      'notnull' => false,
      'length' => 25,
    ));
    
    $table->addColumn('id_h', 'integer', array('autoincrement' => true ));
    $table->setPrimaryKey(array('id_h'), 'pk_posta_workflow_pole_h');   
    
    
  }
  
  /**
   * @param Schema $schema
   */
  public function down(Schema $schema)
  {
    // this down() migration is auto-generated, please modify it to your needs
    
    $table = $schema->getTable('posta_workflow_pole');
    $schema->dropTable($table->getName());
    
    $table = $schema->getTable('posta_workflow_pole_h');
    $schema->dropTable($table->getName());
    
    
    
  }
}
