<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20171031084514 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
      // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('cis_posta_agenda');
      $table->addColumn('neaktivni', 'boolean', array(
        'notnull' => true,
        'default' => false
      ));
      $table = $schema->getTable('cis_posta_typ');
      $table->addColumn('neaktivni', 'boolean', array(
        'notnull' => true,
        'default' => false
      ));
      $table->addColumn('neaktivni_agenda', 'boolean', array(
        'notnull' => true,
        'default' => false
      ));
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
      // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('cis_posta_agenda');
      $table->dropColumn('neaktivni');
      $table = $schema->getTable('cis_posta_typ');
      $table->dropColumn('neaktivni');
      $table = $schema->getTable('cis_posta_typ');
      $table->dropColumn('neaktivni_agenda');
      
    }
}
