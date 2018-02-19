<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170111140931 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs

      $not_null = array(
        'notnull' => true,
      );


      $table = $schema->createTable('posta_version');

      $table->addColumn('id', 'integer', array(
        'autoincrement' => true,
      ));

      //   PRIMARY KEY (id)
      $table->setPrimaryKey(array('id'), 'pk_posta_version');

      $table->addColumn('cislo', 'string', array(
        'notnull' => false,
        'length' => 30,
      ));

      $table->addColumn('git_hash', 'string', array(
        'notnull' => false,
        'length' => 100,
      ));

      $table->addColumn('git_autor', 'string', array(
        'notnull' => false,
        'length' => 100,
      ));

      $table->addColumn('datum', 'datetime', array(
        'notnull' => false
      ));

      $table->addColumn('popis', 'string', array(
        'notnull' => false,
        'length' => 100,
      ));

      $table->addColumn('last_date', 'date', array(
        'notnull' => false,
      ));

      $table->addColumn('last_time', 'string', array(
        'notnull' => false,
        'length' => 10,
      ));

      $table->addColumn('last_user_id', 'integer', array(
        'notnull' => false,
      ));

      $table->addColumn('owner_id', 'integer', array(
        'notnull' => false,
      ));


    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs

      $table = $schema->getTable('posta_version');
      $schema->dropTable($table->getName());

    }
}
