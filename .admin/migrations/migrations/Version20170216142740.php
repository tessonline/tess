<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170216142740 extends AbstractMigration
  {
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
      // this up() migration is auto-generated, please modify it to your needs
    
        // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->createTable('security_groups_kontakty');

      $table->addColumn('id', 'integer', array(
        'autoincrement' => true,
      ));

     
      //   PRIMARY KEY (id)
      $table->setPrimaryKey(array('id'), 'pk_security_groups_kontakty');

      
      $table->addColumn('id_security_group', 'integer', array(
        'notnull' => true,
      ));
      
      
      $table->addColumn('adresa', 'string', array(
        'notnull' => false,
        'length' => 200,
      ));

      $table->addColumn('telefon', 'string', array(
        'notnull' => false,
        'length' => 20,
      ));

      $table->addColumn('mobilni_tel', 'string', array(
        'notnull' => false,
        'length' => 20,
      ));
      
      
      $table->addColumn('email', 'string', array(
        'notnull' => false,
        'length' => 60,
      ));
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs

      $table = $schema->getTable('security_groups_kontatky');
      $schema->dropTable($table->getName());
    }
}