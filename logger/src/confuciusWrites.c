#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>

// tables: Logger, SensorsData, Payload

/** @brief writes entries to Logger Table
*
* Logger:
* ID  | DATE_TIME | SOURCE | SEVERITY | MESSAGE | VALUE (voltage)
* int |    text   |  text  |   text   |   text  | double
*
*  @param ch The table name
*  @param 
*  @return false if any errors occur, other wise true
*/

// SIDE NOTE --> read "char *charPointer;" as: 
// "when I deference charPointer, I get a char"

bool writeLogger(int id, char *dateTime, char *src, char *severity, char *msg, double val) {
    char dbName[] = "Confucius";
    char tableName[] = "Logger";
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc; 

    rc = sqlite3_open(tableName, &db);

    if ( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    char sql[512];
    
    sprintf(sql, "%s %s %s %d, %s, %s, %s, %s, %d, %s" ,
        "INSERT INTO ", *tableName, 
        " (ID, DATE_TIME, SOURCE, SEVERITY, MESSAGE, VALUE) VALUES (",
        *id, *dateTime, *src, *severity, *msg, *val, ");");

    sqlite3_exec(&db, sql, callback, 0, &zErrMsg);

    sqlite3_close(db);
} 

/** @brief writes entries to SensorsData table
*
* SensorsData:
* ID  | SOURCE | VALUE | TIME_STAMP
* int |  text  |  int  | text
*
*/
bool writeSensorsData(int id, char *src, int *val, char *timeStamp) {
    char dbName[] = "Confucius";
    char tableName[] = "SensorsData";
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc; 

    rc = sqlite3_open(tableName, &db);

    if ( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    char sql[512];
    
    sprintf(sql, "%s %s %s %d, %s, %d, %s", 
        "INSERT INTO ", *tableName, 
        " (ID, SOURCE, VALUE, TIME_STAMP) VALUES (", 
        *id, *src, *val, *timeStamp);

    sqlite3_exec(&db, sql, callback, 0, &zErrMsg);

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
    char dbName[] = "Confucius";
    char tableName[] = "Payload";
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc; 

    rc = sqlite3_open(tableName, &db);

    if ( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    char sql[512];
    
    sprintf(sql, "%s %s %s %d, %s, %s", 
        "INSERT INTO ", *tableName, 
        " (ID, VALUE, TIME_STAMP) VALUES (",
        *id, *val, *timeStamp);

    sqlite3_exec(&db, sql, callback, 0, &zErrMsg);

    sqlite3_close(db);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}