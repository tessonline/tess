<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170504104532 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
      // this up() migration is auto-generated, please modify it to your needs
      $this->addSql('ALTER TABLE posta_version ALTER column popis TYPE text');
      $table = $schema->getTable('posta_version');
      
      $table->addColumn('plugin', 'string', array(
        'length' => 80,
        'notnull' => false,
      ));

      $table->addColumn('opravy', 'text', array(
        'length' => 80,
        'notnull' => false,
      ));

    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
      // this down() migration is auto-generated, please modify it to your needs
      $this->addSql('ALTER TABLE posta_version ALTER column popis TYPE varchar(100)');
      $table = $schema->getTable('posta_version');
      $table->dropColumn('plugin');
      $table->dropColumn('opravy');
    }
}

