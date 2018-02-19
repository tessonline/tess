<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170109144101 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs

      $options = array(
        'notnull' => false
      );
      
      $options = array(
        'notnull' => true,
        'default' => 1
      );
      
      $table = $schema->getTable('cis_posta_agenda');
      $table->addColumn('poradi', 'integer',  $options);
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      
      $table = $schema->getTable('cis_posta_agenda');
      $table->dropColumn('poradi');

    }
}
