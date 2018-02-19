<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170731093552 extends AbstractMigration
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

      $table = $schema->getTable('posta_spisovna');
      $table->addColumn('predal_id', 'integer',  $options);

      $table = $schema->getTable('posta_spisovna_h');
      $table->addColumn('predal_id', 'integer',  $options);
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_spisovna');
      $table->dropColumn('predal_id');

      $table = $schema->getTable('posta_spisovna_h');
      $table->dropColumn('predal_id');
    }
}
