<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170428203608 extends AbstractMigration
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

      $table = $schema->getTable('posta');
      $table->addColumn('whois_number', 'integer',  $options);
      $table->addColumn('whois_idstudia', 'integer',  $options);

      $table = $schema->getTable('posta_h');
      $table->addColumn('whois_number', 'integer',  $options);
      $table->addColumn('whois_idstudia', 'integer',  $options);
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta');
      $table->dropColumn('whois_number');
      $table->dropColumn('whois_idstudia');

      $table = $schema->getTable('posta_h');
      $table->dropColumn('whois_number');
      $table->dropColumn('whois_idstudia');
    }
}
