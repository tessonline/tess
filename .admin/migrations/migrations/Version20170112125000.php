<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170112125000 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs

      $table = $schema->createTable('posta_hromadny_import_posta');
      
     
      $table->addColumn('id_import', 'integer', array(
        'default' => 0,
      ));

      $table->addColumn('id_posta', 'integer', array(
        'default' => 0,
      ));      
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
        
      $table = $schema->getTable('posta_hromadny_import_posta');
      $schema->dropTable($table->getName());

    }
}
