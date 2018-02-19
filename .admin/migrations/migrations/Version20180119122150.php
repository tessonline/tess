<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20180119122150 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->createTable('cis_posta_typ_odbor');
      
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_cis_posta_typ_odbor');
      
      $table->addColumn('id_posta_typ', 'integer', array(
        'notnull' => true,
      ));

      $table->addColumn('id_odbor', 'integer', array(
        'notnull' => true,
      ));
            
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_workflow_pole');
      $schema->dropTable($table->getName());
    }
}
