<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170104125153 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
       // this up() migration is auto-generated, please modify it to your needs
      $this->addSql('
      CREATE OR REPLACE FUNCTION cis_posta_agenda_delete() RETURNS trigger
      LANGUAGE plpgsql
      AS $$DECLARE
      BEGIN
      DELETE FROM cis_posta_typ WHERE id_agendy = OLD.id;
      RETURN NEW;
      END;$$;
      ');
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs

    }
}
