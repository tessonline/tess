<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170802093409 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
      // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta');
      $table->addColumn('dalsi_id_spis_agenda', 'string', array(
        'length' => 255,
        'notnull' => false,
      ));
      $table = $schema->getTable('posta_h');
      $table->addColumn('dalsi_id_spis_agenda', 'string', array(
        'length' => 255,
        'notnull' => false,
      ));

    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
      // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta');
      $table->dropColumn('dalsi_id_spis_agenda');

      $table = $schema->getTable('posta_h');
      $table->dropColumn('dalsi_id_spis_agenda');
    }
}
