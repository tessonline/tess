<?php

namespace DoctrineMigrations;

use Doctrine\DBAL\Migrations\AbstractMigration;
use Doctrine\DBAL\Schema\Schema;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
class Version20170322141813 extends AbstractMigration
{
    /**
     * @param Schema $schema
     */
    public function up(Schema $schema)
    {
        // this up() migration is auto-generated, please modify it to your needs


      $table = $schema->getTable('posta_hromadny_import');
      $table->dropColumn('zamceno');
      $table->addColumn('zamceno', 'decimal', array(
        'notnull' => false,
        'precision' => 2,
        'scale' => 0,
      ));
      $table->addColumn('superodbor', 'integer',   array(
        'notnull' => false)
          );
      $table->addColumn('odbor', 'integer',   array(
        'notnull' => false)
          );
      $table->addColumn('referent', 'integer',   array(
        'notnull' => false)
          );
    }

    /**
     * @param Schema $schema
     */
    public function down(Schema $schema)
    {
        // this down() migration is auto-generated, please modify it to your needs
      $table = $schema->getTable('posta_hromadny_import');
      $table->dropColumn('zamceno');
      $table->addColumn('zamceno', 'decimal', array(
        'notnull' => false,
        'precision' => 5,
        'scale' => 5,
      ));
      $table->dropColumn('superodbor');
      $table->dropColumn('odbor');
      $table->dropColumn('referent');
    }
}
