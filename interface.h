#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <sqlite3.h>

int Opensql();
int Closesql();
int CreateSTUTable();
int InsertSTU(int id, char *name, int age, char *address, int grades);
int SelectSTU(int id);
int DeleteSTU(int id);
int UpdateSTU(int id, char *name, int age, char *address, int grades);
int CreateStaffTable();
int InsertStaff(int id, char *name, int age, char *address, int salary);
int DeleteStaff(int id);
int UpdateStaff(int id, char *name, int age, char *address, int salary);
int SelectStaff();
int CreateStuAttendenceTable();
int InsertStuAttendence(int id, char *name, int isattendence);
int SelectStuAttendence();
int DeleteStuAttendence(int id);
int UpdateStuAttendence(int id, char *name, int isattendence);
int CreateStaffAttendenceTable();
int InsertStaffAttendence(int id, char *name, int isattendence);
int SelectStaffAttendence();
int DeleteStaffAttendence(int id);
int UpdateStaffAttendence(int id, char *name, int isattendence);
int CreateEmailTable();
int InsertEmail(int id, char *name, char *email);
int SelectEmail();
int DeleteEmail(int id);
int CreateMailTable();
int InsertMail(int id, char *name, char *mail);
int SelectMail();
int DeleteMail(int id);
int SortStuBySCORE();
int SortStaffBySalary();



#endif