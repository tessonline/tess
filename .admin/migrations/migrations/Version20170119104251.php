<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170119104251 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
        
      $this->addSql('
      CREATE OR REPLACE FUNCTION posta_hromadny_import_delete() RETURNS trigger
      LANGUAGE plpgsql
      AS $$DECLARE
      BEGIN
      DELETE FROM posta_hromadny_import_posta WHERE id_import = OLD.tid;
      RETURN NEW;
      END;$$;
      ');
      
      $this->addSql('CREATE TRIGGER posta_hromadny_import_delete AFTER DELETE ON posta_hromadny_import FOR EACH row execute procedure
        posta_hromadny_import_delete();
      ');
      
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $this->addSql('DROP trigger if exists posta_hromadny_import_delete on posta_hromadny_import;
      ');
      $this->addSql('
      DROP FUNCTION if exists posta_hromadny_import_delete();
      ');
      
    }
}
