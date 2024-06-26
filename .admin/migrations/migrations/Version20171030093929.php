<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20171030093929 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
      // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_hromadny_import');
      $table->addColumn('predef_vars', 'text', array(
        'notnull' => false,
      ));
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
      // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_hromadny_import');
      $table->dropColumn('predef_vars');
    }
}
