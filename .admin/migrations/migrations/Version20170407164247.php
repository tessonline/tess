<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170407164247 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_cis_typ_spis_soucasti');
      $table->addColumn('skartace_id', 'integer',   array(
        'notnull' => false)
      );
      $table->addColumn('skar_znak', 'string',   array(
        'notnull' => false,
        'length' => 1)
      );
      $table->addColumn('lhuta', 'integer',   array(
        'notnull' => false)
      );
      $table->addColumn('rezim_id', 'integer',   array(
        'notnull' => false)
      );


      $table = $schema->getTable('cis_posta_spisy');
      $table->addColumn('skartace_id', 'integer',   array(
        'notnull' => false)
      );
      $table->addColumn('skar_znak', 'string',   array(
        'notnull' => false,
        'length' => 1)
      );
      $table->addColumn('lhuta', 'integer',   array(
        'notnull' => false)
      );
      $table->addColumn('rezim_id', 'integer',   array(
        'notnull' => false)
      );

      $table = $schema->createTable('posta_interface_bp_app');
      $table->addColumn('id', 'integer', array('autoincrement' => true ));
      $table->setPrimaryKey(array('id'), 'pk_posta_interface_bp_app');
      $table->addColumn('nazev', 'string', array('notnull' => true, 'length' => 50));
      $table->addColumn('zdroj_id', 'string', array('notnull' => true, 'length' => 50));
      $table->addColumn('ext_zdroj_id', 'string', array('notnull' => true, 'length' => 50));

      $table->addColumn('username', 'string', array('notnull' => true, 'length' => 50));
      $table->addColumn('password', 'string', array('notnull' => true, 'length' => 50));

      $table->addColumn('last_date', 'date', array('notnull' => true) );
      $table->addColumn('last_time', 'string', array('notnull' => false, 'length' => 10 ));
      $table->addColumn('last_user_id', 'integer', array('notnull' => true) );
      $table->addColumn('owner_id', 'integer', array('notnull' => true) );

    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_cis_typ_spis_soucasti');
      $table->dropColumn('skartace_id');
      $table->dropColumn('skar_znak');
      $table->dropColumn('lhuta');
      $table->dropColumn('rezim_id');

      $table = $schema->getTable('cis_posta_spisy');
      $table->dropColumn('skartace_id');
      $table->dropColumn('skar_znak');
      $table->dropColumn('lhuta');
      $table->dropColumn('rezim_id');

      $table = $schema->getTable('posta_interface_bp_app');
      $schema->dropTable($table->getName());
    }
}
