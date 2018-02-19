<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20180206190650 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      $this->addSql('DROP VIEW posta_view_spisy');
      $this->addSql('ALTER TABLE posta ALTER column znacka TYPE varchar(20)');
      $this->addSql('ALTER TABLE posta_h ALTER column znacka TYPE varchar(20)');
      $this->addSql('CREATE view posta_view_spisy as
       select * FROM posta
      WHERE (posta.main_doc = 1)');
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $this->addSql('DROP VIEW posta_view_spisy');
      $this->addSql('ALTER TABLE posta ALTER column znacka TYPE varchar(10)');
      $this->addSql('ALTER TABLE posta_h ALTER column znacka TYPE varchar(10)');
      $this->addSql('CREATE view posta_view_spisy as
       select * FROM posta
      WHERE (posta.main_doc = 1)');

    }
}
