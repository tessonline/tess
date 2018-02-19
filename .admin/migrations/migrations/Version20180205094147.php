<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20180205094147 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      $options = array(
        'notnull' => false,
        'length' => 30,
      );

      $table = $schema->getTable('cis_posta_typ');
      $table->addColumn('external_id', 'string',  $options);

      $table = $schema->getTable('cis_posta_agenda');
      $table->addColumn('external_id', 'string',  $options);

    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('cis_posta_typ');
      $table->dropColumn('external_id');

      $table = $schema->getTable('cis_posta_agenda');
      $table->dropColumn('external_id');

    }
}
