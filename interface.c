#include <sqlite3.h>
#include <stdio.h>
#include <direct.h>
sqlite3 *db;//定义数据库指针
int Opensql(){
    char current_dir[256];//用来存储当前目录的路径
    char db_path[256];//用来存储数据库的路径
if (getcwd(current_dir, sizeof(current_dir)) != NULL) {//获取当前目录的路径
    snprintf(db_path, sizeof(db_path), "%s/information.db", current_dir);//将数据库的路径存储到db_path中
}
    int rc = sqlite3_open(db_path, &db);//打开数据库
    if (rc != SQLITE_OK) {//判断是否打开成功
        fprintf(stderr, "无法打开数据库: %s\n", sqlite3_errmsg(db));
    } else {
        printf("成功打开数据库\n");
    }
    return 0;
}

int Closesql(){
    int rc = sqlite3_close(db);
if (rc != SQLITE_OK) {
    fprintf(stderr, "关闭数据库失败: %s\n", sqlite3_errmsg(db));
} else {
    printf("成功关闭数据库\n");
}
return 0;
}

int CreateSTUTable(){
    const char *sql = "CREATE TABLE IF NOT EXISTS STUDENT("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "AVG_GRADES     INT     NOT NULL );";//创建学生表格
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);//五个参数的意思为：数据库指针，sql语句，回调函数，回调函数参数，错误信息
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int InsertSTU(int id, char *name, int age, char *address, int grades){//插入学生信息
    char sql[100];
    sprintf(sql, "INSERT INTO STUDENT (ID,NAME,AGE,ADDRESS,AVG_GRADES) "  \
        "VALUES (%d, '%s', %d, '%s', %d); ", id, name, age, address, grades);//将学生信息插入到sql语句中
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SelectSTU(int id){
    const char *sql = "SELECT * from STUDENT";
    sqlite3_stmt *stmt;//
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);//这里参数是-1不是0的原因是因为-1是指全部，0是指第一个
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s: ", sqlite3_column_text(stmt, 2));
            printf("%s: ", sqlite3_column_text(stmt, 3));
            printf("%s\n", sqlite3_column_text(stmt, 4));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int DeleteSTU(int id){
    char sql[100];
    sprintf(sql, "DELETE from STUDENT where ID=%d;", id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int UpdateSTU(int id, char *name, int age, char *address, int grades){
    char sql[100];
    sprintf(sql, "UPDATE STUDENT set NAME='%s',AGE=%d,ADDRESS='%s',AVG_GRADES=%d where ID=%d;", name, age, address, grades, id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SortStuBySCORE(){
    const char *sql = "SELECT * from STUDENT ORDER BY AVG_GRADES DESC";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s: ", sqlite3_column_text(stmt, 2));
            printf("%s: ", sqlite3_column_text(stmt, 3));
            printf("%s\n", sqlite3_column_text(stmt, 4));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int CreateStaffTable(){
    const char *sql = "CREATE TABLE IF NOT EXISTS STAFF("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         INT     NOT NULL );";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return 0;
}

int InsertStaff(int id, char *name, int age, char *address, int salary){
    char sql[100];
    sprintf(sql, "INSERT INTO STAFF (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (%d, '%s', %d, '%s', %d); ", id, name, age, address, salary);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SelectStaff(){
    const char *sql = "SELECT * from STAFF";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s: ", sqlite3_column_text(stmt, 2));
            printf("%s: ", sqlite3_column_text(stmt, 3));
            printf("%s\n", sqlite3_column_text(stmt, 4));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int DeleteStaff(int id){
    char sql[100];
    sprintf(sql, "DELETE from STAFF where ID=%d;", id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int UpdateStaff(int id, char *name, int age, char *address, int salary){
    char sql[100];
    sprintf(sql, "UPDATE STAFF set NAME='%s',AGE=%d,ADDRESS='%s',SALARY=%d where ID=%d;", name, age, address, salary, id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SortStaffBySalary(){
    const char *sql = "SELECT * from STAFF ORDER BY SALARY DESC";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s: ", sqlite3_column_text(stmt, 2));
            printf("%s: ", sqlite3_column_text(stmt, 3));
            printf("%s\n", sqlite3_column_text(stmt, 4));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int CreateStuAttendenceTable(){
    const char *sql = "CREATE TABLE IF NOT EXISTS ATTENDENCE("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "ISATTENDENCE   INT     NOT NULL );";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int InsertStuAttendence(int id, char *name, int isattendence){
    char sql[100];
    sprintf(sql, "INSERT INTO ATTENDENCE (ID,NAME,ISATTENDENCE) "  \
        "VALUES (%d, '%s', %d); ", id, name, isattendence);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SelectStuAttendence(){
    const char *sql = "SELECT * from ATTENDENCE";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s\n", sqlite3_column_text(stmt, 2));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int DeleteStuAttendence(int id){
    char sql[100];
    sprintf(sql, "DELETE from ATTENDENCE where ID=%d;", id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}


int UpdateStuAttendence(int id, char *name, int isattendence){
    char sql[100];
    sprintf(sql, "UPDATE ATTENDENCE set NAME='%s',ISATTENDENCE=%d where ID=%d;", name, isattendence, id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int CreateStaffAttendenceTable(){
    const char *sql = "CREATE TABLE IF NOT EXISTS STAFFATTENDENCE("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "ISATTENDENCE   INT     NOT NULL );";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int InsertStaffAttendence(int id, char *name, int isattendence){
    char sql[100];
    sprintf(sql, "INSERT INTO STAFFATTENDENCE (ID,NAME,ISATTENDENCE) "  \
        "VALUES (%d, '%s', %d); ", id, name, isattendence);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SelectStaffAttendence(){
    const char *sql = "SELECT * from STAFFATTENDENCE";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s\n", sqlite3_column_text(stmt, 2));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int DeleteStaffAttendence(int id){
    char sql[100];
    sprintf(sql, "DELETE from STAFFATTENDENCE where ID=%d;", id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int UpdateStaffAttendence(int id, char *name, int isattendence){
    char sql[100];
    sprintf(sql, "UPDATE STAFFATTENDENCE set NAME='%s',ISATTENDENCE=%d where ID=%d;", name, isattendence, id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int CreateEmailTable(){
    const char *sql = "CREATE TABLE IF NOT EXISTS EMAIL("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "EMAIL          CHAR(50) NOT NULL );";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int InsertEmail(int id, char *name, char *email){
    char sql[100];
    sprintf(sql, "INSERT INTO EMAIL (ID,NAME,EMAIL) "  \
        "VALUES (%d, '%s', '%s'); ", id, name, email);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SelectEmail(){
    const char *sql = "SELECT * from EMAIL";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s\n", sqlite3_column_text(stmt, 2));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int DeleteEmail(int id){
    char sql[100];
    sprintf(sql, "DELETE from EMAIL where ID=%d;", id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int CreateMailTable(){
    const char *sql = "CREATE TABLE IF NOT EXISTS MAIL("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "MAIL          CHAR(50) NOT NULL );";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int InsertMail(int id, char *name, char *mail){
    char sql[100];
    sprintf(sql, "INSERT INTO MAIL (ID,NAME,MAIL) "  \
        "VALUES (%d, '%s', '%s'); ", id, name, mail);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

int SelectMail(){
    const char *sql = "SELECT * from MAIL";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }
    while (1) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(stmt, 0));
            printf("%s: ", sqlite3_column_text(stmt, 1));
            printf("%s\n", sqlite3_column_text(stmt, 2));
        }
        if (rc == SQLITE_DONE) {
            printf("Records created successfully\n");
            break;
        }
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            break;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}

int DeleteMail(int id){
    char sql[100];
    sprintf(sql, "DELETE from MAIL where ID=%d;", id);
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    return 0;
}

