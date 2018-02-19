<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20171206093326 extends AbstractMigration
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

      $table = $schema->getTable('posta_cis_skartace_main');
      $table->addColumn('superodbor', 'integer',  $options);
     }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_cis_skartace_main');
      $table->dropColumn('superodbor');

    }
}
