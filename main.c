#include <stdio.h>
#include <sqlite3.h>
#include "interface.h"
#include <stdlib.h>
int main(){
    //设计用户菜单
    printf("1.学生信息管理\n");
    printf("2.员工信息管理\n");
    printf("3.学生考勤管理\n");
    printf("4.员工考勤管理\n");
    printf("5.邮件信息管理\n");
    printf("6.快递信息管理\n");
    printf("7.退出\n");
    printf("请选择：");
    int choice;
    scanf("%d",&choice);
    
    Opensql();//打开数据库

    while(1){//循环,直到用户选择退出
    //学生信息管理
    if(choice == 1){
        CreateSTUTable();
        printf("1.添加学生信息\n");
        printf("2.删除学生信息\n");
        printf("3.修改学生信息\n");
        printf("4.查询学生信息\n");
        printf("5.返回上一级\n");
        printf("6.按照成绩排序\n");
        printf("7.退出\n");
        printf("请选择：");
        int choice1;//用户选择
        scanf("%d",&choice1);
        if(choice1 == 1){
            //添加学生信息
            printf("请输入学生信息：\n");
            printf("学号：");
            int id;
            scanf("%d",&id);
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("年龄：");
            int age;
            scanf("%d",&age);
            printf("地址：");
            char address[50];
            scanf("%s",address);
            printf("平均成绩：");
            int grades;
            scanf("%d",&grades);
            InsertSTU(id,name,age,address,grades);
        }
        else if(choice1 == 2){
            //删除学生信息
            printf("请输入要删除的学生学号：");
            int id;
            scanf("%d",&id);
            DeleteSTU(id);
        }
        else if(choice1 == 3){
            //修改学生信息
            printf("请输入要修改的学生学号：");
            int id;
            scanf("%d",&id);
            printf("请输入修改后的学生信息：\n");
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("年龄：");
            int age;
            scanf("%d",&age);
            printf("地址：");
            char address[50];
            scanf("%s",address);
            printf("平均成绩：");
            int grades;
            scanf("%d",&grades);
            UpdateSTU(id,name,age,address,grades);
        }
        else if(choice1 == 4){
            //查询学生信息
            int ID;
            printf("请输入要查询的学生学号：");
            scanf("%d",ID);
            SelectSTU(ID);
        }
        else if(choice1 == 5){
            //返回上一级
            main();
        }
        else if(choice1 == 6){
            //按照成绩排序
            SortStuBySCORE();
        }
        else if(choice1 == 7){
            exit(0);
        }
    }
    
    //员工信息管理
    else if(choice == 2){
        CreateStaffTable();
        printf("1.添加员工信息\n");
        printf("2.删除员工信息\n");
        printf("3.修改员工信息\n");
        printf("4.查询员工信息\n");
        printf("5.返回上一级\n");
        printf("6.按照工资排序\n");
        printf("7.退出\n");
        printf("请选择：");
        int choice2;
        scanf("%d",&choice2);
        if(choice2 == 1){
            //添加员工信息
            printf("请输入员工信息：\n");
            printf("工号：");
            int id;
            scanf("%d",&id);
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("年龄：");
            int age;
            scanf("%d",&age);
            printf("地址：");
            char address[50];
            scanf("%s",address);
            printf("工资：");
            int salary;
            scanf("%d",&salary);
            InsertStaff(id,name,age,address,salary);
        }
        else if(choice2 == 2){
            //删除员工信息
            printf("请输入要删除的员工工号：");
            int id;
            scanf("%d",&id);
            DeleteStaff(id);
        }
        else if(choice2 == 3){
            //修改员工信息
            printf("请输入要修改的员工工号：");
            int id;
            scanf("%d",&id);
            printf("请输入修改后的员工信息：\n");
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("年龄：");
            int age;
            scanf("%d",&age);
            printf("地址：");
            char address[50];
            scanf("%s",address);
            printf("工资：");
            int salary;
            scanf("%d",&salary);
            UpdateStaff(id,name,age,address,salary);
        }
        else if(choice2 == 4){
            //查询员工信息
            SelectStaff();
        }
        else if(choice2 == 5){
            //返回上一级
            main();
        }
        else if(choice2 == 6){
            //按照工资排序
            SortStaffBySalary();
        }
        else if(choice2 == 7){
            exit(0);
        }
    }

    //学生考勤管理
    else if(choice == 3){
        CreateStuAttendenceTable();
        printf("1.添加学生考勤信息\n");
        printf("2.查询学生考勤信息\n");
        printf("3.修改学生考勤信息\n");
        printf("4.删除学生考勤信息\n");
        printf("5.返回上一级\n");
        printf("6.退出\n");
        printf("请选择：");
        int choice3;
        scanf("%d",&choice3);
        if(choice3 == 1){
            //添加学生考勤信息
            printf("请输入学生考勤信息：\n");
            printf("学号：");
            int id;
            scanf("%d",&id);
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("是否考勤(是输入1，否输入0)：");
            int isattendence;
            scanf("%d",&isattendence);
            InsertStuAttendence(id,name,isattendence);
        }
        else if(choice3 == 2){
            //查询学生考勤信息
            SelectStuAttendence();
        }
        else if(choice3 == 3){
            //修改学生考勤信息
            printf("请输入要修改的学生学号：");
            int id;
            scanf("%d",&id);
            printf("请输入修改后的学生考勤信息：\n");
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("是否考勤(是输入1，否输入0)：");
            int isattendence;
            scanf("%d",&isattendence);
            UpdateStuAttendence(id,name,isattendence);
        }
        else if(choice3 == 4){
            //删除学生考勤信息
            printf("请输入要删除的学生学号：");
            int id;
            scanf("%d",&id);
            DeleteStuAttendence(id);
        }
        else if(choice3 == 5){
            //返回上一级
            main();
        }
        else if(choice3 == 6){
            exit(0);
        }
        
    }

    //员工考勤管理
    else if(choice == 4){
        CreateStaffAttendenceTable();
        printf("1.添加员工考勤信息\n");
        printf("2.查询员工考勤信息\n");
        printf("3.修改学生考勤信息\n");
        printf("4.删除员工考勤信息\n");
        printf("5.返回上一级\n");
        printf("6.退出\n");
        printf("请选择：");
        int choice4;
        scanf("%d",&choice4);
        if(choice4 == 1){
            //添加员工考勤信息
            printf("请输入员工考勤信息：\n");
            printf("工号：");
            int id;
            scanf("%d",&id);
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("是否考勤(是输入1，否输入0)：");
            int isattendence;
            scanf("%d",&isattendence);
            InsertStaffAttendence(id,name,isattendence);
        }
        else if(choice4 == 2){
            //查询员工考勤信息
            SelectStaffAttendence();
        }
        else if(choice4 == 3){
            //修改员工考勤信息
            printf("请输入要修改的员工工号：");
            int id;
            scanf("%d",&id);
            printf("请输入修改后的员工考勤信息：\n");
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            printf("是否考勤(是输入1，否输入0)：");
            int isattendence;
            scanf("%d",&isattendence);
            UpdateStaffAttendence(id,name,isattendence);
        }
        else if(choice4 == 4){
            //删除员工考勤信息
            printf("请输入要删除的员工工号：");
            int id;
            scanf("%d",&id);
            DeleteStaffAttendence(id);
        }
        else if(choice4 == 5){
            //返回上一级
            main();
        }
        else if(choice4 == 6){
            exit(0);
        }
        
    }
    
    //邮件信息管理
    else if(choice == 5){
        CreateEmailTable();
        printf("1.添加邮件信息\n");
        printf("2.查询邮件信息\n");
        printf("3.删除邮件信息\n");
        printf("4.返回上一级\n");
        printf("5.退出\n");
        printf("请选择：");
        int choice5;
        scanf("%d",&choice5);
        if(choice5 == 1){
            //添加邮件信息
            printf("请输入邮件信息：\n");
            
            printf("邮件号：");
            int id;
            scanf("%d",&id);
            getchar();
            
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            getchar();
            
            printf("邮箱：");
            char email[50];
            scanf("%s",email);
            InsertEmail(id,name,email);
        }
        else if(choice5 == 2){
            //查询邮件信息
            SelectEmail();
        }
        else if(choice5 == 3){
            //删除邮件信息
            printf("请输入要删除的邮件号：");
            int id;
            scanf("%d",&id);
            DeleteEmail(id);
        }
        else if(choice5 == 4){
            //返回上一级
            main();
        }
        else if(choice5 == 5){
            exit(0);
        }
    }
    //快递信息管理
    else if(choice == 6){
        CreateMailTable();
        printf("1.添加快递信息\n");
        printf("2.查询快递信息\n");
        printf("3.删除快递信息\n");
        printf("4.返回上一级\n");
        printf("5.退出\n");
        printf("请选择：");
        int choice6;
        scanf("%d",&choice6);
        if(choice6 == 1){
            //添加快递信息
            printf("请输入快递信息：\n");
            printf("快递号：");
            int id;
            scanf("%d",&id);
            getchar();
            printf("姓名：");
            char name[20];
            scanf("%s",name);
            getchar();
            printf("快递存放地址：");
            char mail[50];
            scanf("%s",mail);
            getchar();
            InsertMail(id,name,mail);
        }
        else if(choice6 == 2){
            //查询快递信息
            SelectMail();
        }
        else if(choice6 == 3){
            //删除快递信息
            printf("请输入要删除的快递号：");
            int id;
            scanf("%d",&id);
        }
        else if(choice6 == 4){
        //返回上一级
        main();
        }
        else if(choice6 == 5){
            exit(0);//退出
        }
    }
    if(choice == 7){
        exit(0);
    }
    }
        //退出
        Closesql();
        return 0;
    
}