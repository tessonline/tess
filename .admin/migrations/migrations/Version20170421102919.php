<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170421102919 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      $options = array(
        'notnull' => true,
        'default' => 1
      );
      
      $table = $schema->getTable('posta_dokumentace');
      $table->addColumn('poradi', 'integer',  $options);
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      
      $table = $schema->getTable('posta_dokumentace');
      $table->dropColumn('poradi');
      
    }
}
