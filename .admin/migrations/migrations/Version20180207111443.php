<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20180207111443 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
        
      $options = array(
        'notnull' => false,
      );
      
      $table = $schema->getTable('posta_pristupy');
      $table->addColumn('spis_id', 'integer',  $options);
        
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_pristupy');
      $table->dropColumn('spis_id');

    }
}
