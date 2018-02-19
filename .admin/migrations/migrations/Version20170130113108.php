<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170130113108 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
      // this up() migration is auto-generated, please modify it to your needs      
      
      $table = $schema->getTable('posta_cis_sablony');
      $table->addColumn('typ_posty', 'integer',   array(
        'notnull' => false)
      );
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
      // this down() migration is auto-generated, please modify it to your needs
        
      $table = $schema->getTable('posta_cis_sablony');
      $table->dropColumn('typ_posty');
    }
}
