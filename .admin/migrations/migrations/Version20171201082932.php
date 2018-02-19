<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20171201082932 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
      $this->addSql('
      CREATE OR REPLACE FUNCTION posta_workflow_pole_copy2history() RETURNS TRIGGER
      LANGUAGE plpgsql
      AS $$DECLARE
      BEGIN
      INSERT INTO posta_workflow_pole_h(id,id_posta,promenna,hodnota,datovy_typ) SELECT * FROM posta_workflow_pole WHERE id=OLD.id;
      RETURN OLD;
      END;$$
      ');
      
      
      $this->addSql('CREATE  TRIGGER posta_workflow_pole_history BEFORE DELETE OR UPDATE ON posta_workflow_pole
       FOR EACH ROW EXECUTE PROCEDURE posta_workflow_pole_copy2history();');

    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
        
      
      $this->addSql('drop trigger if exists posta_workflow_pole_history on posta_workflow_pole;');
      
      $this->addSql('DROP FUNCTION IF EXISTS posta_workflow_pole_copy2history()');

    }
}
