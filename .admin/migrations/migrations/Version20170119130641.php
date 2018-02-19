<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170119130641 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->createTable('posta_pristupy');

      $table->addColumn('id', 'integer', array(
        'autoincrement' => true,
      ));

      //   PRIMARY KEY (id)
      $table->setPrimaryKey(array('id'), 'posta_pristupy');

      $table->addColumn('posta_id', 'integer', array(
        'default' => 0,
        'length' => 30,
      ));
      $table->addIndex(array('posta_id'), 'idx_posta_id_posta_id');

      $table->addColumn('access', 'string', array(
        'default' => 0,
      ));

      $table->addColumn('spis', 'integer', array(
        'default' => 0,
      ));
      $table->addColumn('odbor', 'integer', array(
        'default' => 0,
        'notnull' => false,
      ));
      $table->addIndex(array('odbor'), 'idx_odbor_posta_id');

      $table->addColumn('referent', 'integer', array(
        'default' => 0,
        'notnull' => false,
      ));
      $table->addIndex(array('referent'), 'idx_referent_posta_id');

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

      $table = $schema->getTable('posta_pristupy');
      $schema->dropTable($table->getName());
    }
}
