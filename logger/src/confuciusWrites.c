#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>

/** @brief writes entries to Logger Table
 *
 * Logger:
 * ID  | DATE_TIME | SOURCE | SEVERITY | MESSAGE | VALUE (voltage)
 * int |    text   |  text  |   text   |   text  | int
 *
 *  @param ch The table name
 *  @param 
 *  @return false if any errors occur, other wise true
 */

 // tables: Logger, SensorsData, Payload
 
bool writeLogger(int id, char *dateTime, char *src, char* severity, char* msg, int val) {
   char[] dbName = "Confucius";
   char[] tableName = "Logger";
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open(tableName, &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   sqlite3_exec(&db, char *sql, sqlite_callback, void *data, char **errmsg);

   sqlite3_close(db);
} 

/** @brief writes entries to SensorsData table
 *
 * SensorsData:
 * ID  | SOURCE | VALUE | TIME_STAMP
 * int |  text  |  int  | text
 *
 */
bool writeSensorsData(int id, char *src, char *val, char *timeStamp) {
    char[] dbName = "Confucius";
    char[] tableName = "SensorsData";
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(tableName, &db);

    if( rc ){
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return(0);
    } else {
       fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_exec(&db, char *sql, sqlite_callback, void *data, char **errmsg);

    sqlite3_close(db);
}

/** @brief writes entries to Payload table
 *
 * Payload:
 * ID  | VALUE | TIME_STAMP
 * int |  int  | text
 *
 */

bool writePayload(int id, char *val, char* timeStamp) {
    char[] dbName = "Confucius";
    char[] tableName = "Payload";
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(tableName, &db);

    if( rc ){
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return(0);
    } else {
       fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_exec(&db, char *sql, sqlite_callback, void *data, char **errmsg);

    sqlite3_close(db);
}

/** @brief helper function for cWrite
 * 
 *  creates insert query based on which table is selected
 *  0 - Logger
 *  1 - SensorsData
 *  2 - Payload
 *
 */
char[] prepareInsertQuery(int table) {
    char[] sqlToExec = "INSERT INTO "+*tableName+" VALUES ("+" )";

}

