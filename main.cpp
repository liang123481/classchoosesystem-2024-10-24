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
    int credit;//ѧ��
    string courseName;//�γ�����
    int enrolledStudents;//ѧ������
    string teacher;//��ʦ
    double averageGrade;//����
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
        cout << "�γ�����: " << classlist[i].courseName << " ѧ��Ϊ��"<< classlist[i].credit<< " �ڿν�ʦ��" << classlist[i].teacher << endl;
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
            cout << "�γ���Ϣ�Ѵ���" << endl;
            return;
        }
    }
    Course temp;
    temp.courseName = classname;
    cout << "������ѧ����Ϣ:";
    cin >> temp.credit;
    cout << "���������������Ϣ:";
    cin >> temp.enrolledStudents;
    cout << "�������ڿν�ʦ:";
    cin >> temp.teacher;
    classlist.push_back(temp);
    cout << "��ӳɹ�" << endl;
    classnum++;
}
void chooseclass::addstu() {
    cout << "������Ҫ���ѧ���Ļ�����Ϣ:";
    string name;
    cout << "������ѧ������:";
    cin >> name;
    string gender;
    cout << "������ѧ���Ա�:";
    cin >> gender;
    int studentID;
    cout << "������ѧ��ѧ��:";
    cin >> studentID;
    string major;
    cout << "������ѧ��רҵ:";
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
        cout << "�γ���ɾ��" << endl;
        classnum--;
    }
    else {
        cout << "δ�ҵ�ָ���γ�" << endl;
    }
}
void chooseclass::stuaddclass(string classname,int ID) {
    int flag = 0;
    for (int i = 0; i < classlist.size(); i++) {
        if (classlist[i].courseName == classname) {
            cout << "��Ҫ��ӵĿγ���ϢΪ��" << endl;
            print(i);
            flag = 1;
            break;
        }
    }
    if (!flag) {
        cout << "û�иÿγ�" << endl;
        return;
    }
    int temp=0;
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == ID) {
            temp = 1;
            if (stulist[i].course_score.count(classname)) {
                cout << "���Ѿ�ѡ��ÿγ�"<<endl;
                break;
            }
            else {
                temp = 1;
                cout << "�γ���ӳɹ�" << endl;
                stulist[i].course_score[classname];
                stulist[i].coursenum++;
            }
        }
    }
}
void chooseclass::studelclass() {
    int id = 0;
    cout << "������ѧ�ţ�";
    cin >> id;
    int temp = 0;
    cout << "��������Ҫɾ���Ŀ�Ŀ";
    string classname;
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == id) {
            temp = 1;
            if (stulist[i].course_score.count(classname)) {
                stulist[i].course_score.erase(classname);
                stulist[i].coursenum--;
                cout << "�γ�ɾ���ɹ�";
            }
            else {
                cout << "��û��ѡ��ÿγ�";
            }
        }
    }
    if (!temp) {
        cout << "���޴�����Ϣ";
    }
}
void chooseclass::addscore(int id) {
    for (int i = 0; i < stulist.size(); i++) {
        if (stulist[i].studentID == id) {
            string classname;
            cout << "������Ҫ��ӳɼ��Ŀ�Ŀ��";
            cin >> classname;
            if (stulist[i].course_score.count(classname)) {
                cout << "�����������";
                int temp=0;
                cin >> temp;
                stulist[i].course_score[classname] = temp;
                return;
            }
            else {
                cout << "�����ڸÿ�Ŀ" << endl;
                return;
            }
        }
    }
    cout << "û�и�ѧ����Ϣ" << endl;
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
            cout << "��ѡ��ĿΪ��";
            for (auto it = stulist[i].course_score.begin(); it != stulist[i].course_score.end(); it++) {
                cout << it->first << " ";
            }
            return;
        }
    }
    cout << "���޴���"<<endl;
}
int main() {
    chooseclass operation;
    int temp = 0;
    while (temp!=9) {
        cout << "��ӭ�����γ�ѡ��ϵͳ��" << endl;
        cout << "��������Ӧ������" << endl << "1.��ӿ�Ŀ" << "2.ɾ����Ŀ" << "3.���ѧ����Ϣ" << "4.ѧ��ѡ��" << "5.ѧ������¼��" << "6.ѧ��������ѯ" << "7.��ʾ���п�Ŀ��Ϣ" << "8.ѧ����ѡ��Ŀ��ѯ"<<"9.�˳�" << endl;
        cin >> temp;
        if (temp == 1) {
            system("cls");
            cout << "��������Ҫ��ӵĿ�Ŀ:";
            string temp1;
            cin >> temp1;
            operation.addclass(temp1);
        }
        else if (temp == 2) {
            system("cls");
            cout << "��������Ҫɾ���Ŀ�Ŀ";
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
            cout << "������ѧ��:";
            int id;
            cin >> id;
            cout << "��������ӿ�Ŀ:";
            string Class;
            cin >> Class;
            operation.stuaddclass(Class, id);
        }
        else if (temp == 5) {
            system("cls");
            cout << "������ѧ��:";
            int id;
            cin >> id;
            operation.addscore(id);
        }
        else if (temp == 6) {
            system("cls");
            operation.cal_rank();
            cout << "������ѧ��:";
            int id;
            cin >> id;
            int rank=operation.checkrank(id);
            if (rank) {
                cout <<"����Ϊ" << rank;
            }
            else {
                cout << "���޴���";
            }
        }
        else if (temp == 7) {
            system("cls");
            if (operation.classnum == 0) {
                cout << "û����ӿγ�" << endl;
                continue;
            }
            for (int i = 0; i < operation.classnum; i++) {
                operation.print(i);
            }
        }
        else if (temp == 8) {
            system("cls");
            int id = 0;
            cout << "������ѧ�ţ�";
            cin >> id;
            operation.stuprintclass(id);
        }
    }
}