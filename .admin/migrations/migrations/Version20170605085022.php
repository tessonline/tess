<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170605085022 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('security_groups_kontakty');
      
      $table->addColumn('web', 'string', array(
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
      $table = $schema->getTable('security_groups_kontakty');
      $table->dropColumn('web');
    }
}
