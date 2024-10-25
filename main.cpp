#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
using namespace std;
class student;
class Course;
class chooseclass {
    vector<student>stulist;
    vector<Course>classlist;
public:
    int classnum;
    void averinfo(string classname);
    void addclass(string name);
    void print(int i);
    void delclass(string classname);
    void stuaddclass(string classname,int ID);
    void addscore(int id);
    void cal_rank();
    void addstu();
    int checkrank(int id);
    float stuaverage;
    void studelclass();
    void stuprintclass(int id);
};
class student {
private:
    string name;
    string gender;
    int studentID;
    double averageGrade;
    int personalRank;
    int coursenum;
    map<string, int> course_score;
    string major;
public:
    friend void chooseclass::averinfo(string name);
    friend void chooseclass::stuaddclass(string name,int ID);
    friend void chooseclass::addscore(int id);
    friend void chooseclass::cal_rank();
    friend int chooseclass::checkrank(int id);
    friend void chooseclass::studelclass();
    friend void chooseclass::stuprintclass(int id);
    friend bool compareStudents(const student& a, const student& b);
    double selfaver() {
        int aver = 0;
        for (auto it = course_score.begin(); it != course_score.end(); it++) {
            aver += it->second;
        }
        aver /= course_score.size();
        this->averageGrade = aver;
        return aver;
    }
    student(std::string name, std::string gender, int studentID, std::string major) : name(name), gender(gender), studentID(studentID), major(major), averageGrade(0), personalRank(-1) {}
};
class Course {
private:
    int credit;//学分
    string courseName;//课程名称
    int enrolledStudents;//学生个数
    string teacher;//老师
    double averageGrade;//均分
public:
    friend void chooseclass:: averinfo(string name);
    friend void chooseclass:: addclass(string name);
    friend void chooseclass::delclass(string name);
    friend void chooseclass::print(int i);
    friend void chooseclass::stuaddclass(string name,int ID);
    //Course(int credit, std::string courseName, std::string teacher):credit(credit), courseName(courseName), teacher(teacher), enrolledStudents(0), averageGrade(0), rank(-1) {}
    void stunum(int num) {
        this->enrolledStudents = num;
    }
};
void chooseclass::print(int i){
        cout << "课程名称: " << classlist[i].courseName << " 学分为："<< classlist[i].credit<< " 授课教师：" << classlist[i].teacher << endl;
}
void chooseclass::averinfo(string classname) {
    bool temp=false;
    int flag = 0;
    for (int i = 0; i < classlist.size(); i++) {
        if (classlist[i].courseName == classname) {
            temp = true;
            flag = i;
            break;
        }
   }
    if (temp) {
        int num=0;
        for (int i = 0; i < stulist.size(); i++) {
            num+=stulist[i].course_score.count(classname);
        }
        num /= classlist.size();
        classlist[flag].averageGrade = num;
    }
}
void chooseclass::addclass(string classname) {
    for (int i = 0; i < classlist.size(); i++) {
        if (classlist[i].courseName == classname) {
            cout << "课程信息已存在" << endl;
            return;
        }
    }
    Course temp;
    temp.courseName = classname;
    cout << "请输入学分信息:";
    cin >> temp.credit;
    cout << "请输入最大人数信息:";
    cin >> temp.enrolledStudents;
    cout << "请输入授课教师:";
    cin >> temp.teacher;
    classlist.push_back(temp);
    cout << "添加成功" << endl;
    classnum++;
}
void chooseclass::addstu() {
    cout << "请输入要添加学生的基本信息:";
    string name;
    cout << "请输入学生姓名:";
    cin >> name;
    string gender;
    cout << "请输入学生性别:";
    cin >> gender;
    int studentID;
    cout << "请输入学生学号:";
    cin >> studentID;
    string major;
    cout << "请输入学生专业:";
    cin >> major;
    student stu1(name, gender, studentID, major);
    stulist.push_back(stu1);
}
void chooseclass::delclass(string classname) {
    auto it = find_if(classlist.begin(), classlist.end(), [classname](const Course& c) {
        return c.courseName == classname;
        });

    if (it != classlist.end()) {
        classlist.erase(it);
        cout << "课程已删除" << endl;
        classnum--;
    }
    else {
        cout << "未找到指定课程" << endl;
    }
}
void chooseclass::stuaddclass(string classname,int ID) {
    int flag = 0;
    for (int i = 0; i < classlist.size(); i++) {
        if (classlist[i].courseName == classname) {
            cout << "您要添加的课程信息为：" << endl;
            print(i);
            flag = 1;
            break;
        }
    }
    if (!flag) {
        cout << "没有该课程" << endl;
        return;
    }
    int temp=0;
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == ID) {
            temp = 1;
            if (stulist[i].course_score.count(classname)) {
                cout << "您已经选择该课程"<<endl;
                break;
            }
            else {
                temp = 1;
                cout << "课程添加成功" << endl;
                stulist[i].course_score[classname];
                stulist[i].coursenum++;
            }
        }
    }
}
void chooseclass::studelclass() {
    int id = 0;
    cout << "请输入学号：";
    cin >> id;
    int temp = 0;
    cout << "请输入想要删除的科目";
    string classname;
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == id) {
            temp = 1;
            if (stulist[i].course_score.count(classname)) {
                stulist[i].course_score.erase(classname);
                stulist[i].coursenum--;
                cout << "课程删除成功"<<endl;
            }
            else {
                cout << "您没有选择该课程"<<endl;
            }
        }
    }
    if (!temp) {
        cout << "查无此人信息"<<endl;
    }
}
void chooseclass::addscore(int id) {
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == id) {
            string classname;
            cout << "请输入要添加成绩的科目：";
            cin >> classname;
            if (stulist[i].course_score.count(classname)) {
                cout << "请输入分数：";
                int temp=0;
                cin >> temp;
                stulist[i].course_score[classname] = temp;
                return;
            }
            else {
                cout << "不存在该科目" << endl;
                return;
            }
        }
    }
    cout << "没有该学生信息" << endl;
}
bool compareStudents(const student& a, const student& b) {
    return a.averageGrade > b.averageGrade; 
}

void chooseclass::cal_rank() {
    sort(stulist.begin(), stulist.end(), compareStudents);
    for (int i = 0; i < stulist.size(); i++) {
        stulist[i].personalRank = i + 1;
    }
}
int chooseclass::checkrank(int id) {
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == id) {
            return stulist[i].personalRank;
        }
    }
    return -1;
}
void chooseclass::stuprintclass(int id) {
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == id) {
            cout << "所选科目为："<<endl;
            for (auto it = stulist[i].course_score.begin(); it != stulist[i].course_score.end(); it++) {
                cout << it->first << " ";
            }
            return;
        }
    }
    cout << "查无此人"<<endl;
}
int main() {
    chooseclass operation;
    int temp = 0;
    while (temp!=9) {
        cout << "欢迎来到课程选择系统：" << endl;
        cout << "请输入相应操作：" << endl << "1.添加科目" << "2.删除科目" << "3.添加学生信息" << "4.学生选课" << "5.学生分数录入" << "6.学生排名查询" << "7.显示已有科目信息" << "8.学生已选科目查询"<<"9.退出" << endl;
        cin >> temp;
        if (temp == 1) {
            system("cls");
            cout << "请输入想要添加的科目:";
            string temp1;
            cin >> temp1;
            operation.addclass(temp1);
        }
        else if (temp == 2) {
            system("cls");
            cout << "请输入想要删除的科目";
            string temp1;
            cin >> temp1;
            operation.delclass(temp1);
        }
        else if (temp == 3) {
            system("cls");
            operation.addstu();
        }
        else if (temp == 4) {
            system("cls");
            cout << "请输入学号:";
            int id;
            cin >> id;
            cout << "请输入添加科目:";
            string Class;
            cin >> Class;
            operation.stuaddclass(Class, id);
        }
        else if (temp == 5) {
            system("cls");
            cout << "请输入学号:";
            int id;
            cin >> id;
            operation.addscore(id);
        }
        else if (temp == 6) {
            system("cls");
            operation.cal_rank();
            cout << "请输入学号:";
            int id;
            cin >> id;
            int rank=operation.checkrank(id);
            if (rank) {
                cout <<"排名为" << rank<<endl;
            }
            else {
                cout << "查无此人"<<endl;
            }
        }
        else if (temp == 7) {
            system("cls");
            if (operation.classnum == 0) {
                cout << "没有添加课程" << endl;
                continue;
            }
            for (int i = 0; i < operation.classnum; i++) {
                operation.print(i);
            }
        }
        else if (temp == 8) {
            system("cls");
            int id = 0;
            cout << "请输入学号：";
            cin >> id;
            operation.stuprintclass(id);
        }
        else {
            cout << "请重新输入"<<endl;
        }
    }
}
