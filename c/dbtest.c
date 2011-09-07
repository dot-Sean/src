#include <db3/db.h>
#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  DB * db;
  DB_ENV * dbenv1;
    db_env_create(& dbenv1, 0);
    dbenv1->set_errfile(dbenv1, stderr);
    dbenv1->set_errpfx(dbenv1, "hoge");
    dbenv1->set_verbose(dbenv1, DB_VERB_CHKPOINT, 1);
    dbenv1->open(dbenv1, (void *) 0, DB_INIT_LOG | DB_INIT_TXN | DB_USE_ENVIRON, 0) != 0 &&
    dbenv1->open(dbenv1, (void *) 0, DB_CREATE | DB_INIT_LOG | DB_INIT_TXN | DB_USE_ENVIRON, 0);
    db_create(& db, dbenv1, 0);
    db->open(db, "/tmp/tmp.db", NULL, DB_BTREE, 0, 0);
  return (0);
}


