<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170524140516 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      /*$this->addSql('ALTER TABLE ceu_id_provider DROP CONSTRAINT ceu_id_provider_pkey');
      $this->addSql('ALTER TABLE ceu_id_provider ADD PRIMARY KEY (ceu_id)');*/
      $this->addSql('DROP INDEX ceu_id_provider_login_system');
      $this->addSql('CREATE INDEX ceu_id_provider_login_system ON ceu_id_provider (login,system)');
      
    }
    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $this->addSql('DROP INDEX ceu_id_provider_login_system');
      $this->addSql('CREATE UNIQUE INDEX ceu_id_provider_login_system ON ceu_id_provider (login,system)');
    }
}
