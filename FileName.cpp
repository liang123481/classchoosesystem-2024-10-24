#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class candy {//�����ǹ���
public:
    int num;//��Ŀ
    string name;//�ǹ�����
    int code;//���۱��
    float price;//�۸�
    void getinfo() {//��ӡ�����Ϣ
        cout << "����:" << name << endl << "�۸�:" << price << endl << "ʣ��������" << num << endl;
    }
};
class candymachine {//�����ǹ�����
public:
    candy list[100];//�ǹ����б�
    int candynum;//�����ǹ�����
    void buy(float money, int code) {//������
        if (list[code].price <= money) {
            if (list[code].num > 0) {
                money -= list[code].price;
                cout << "����ɹ�" << endl;
                cout << "���������Ϊ��" << money << endl;
            }
            else {
                cout << "������" << endl;
            }
        }
        else {
            cout << "����ʧ�ܣ�����" << endl;
        }
    }
    void printlist() {//�ǹ��������
        for (int i = 0; i < candynum; i++) {
            list[i].getinfo();
        }
    }
};
int main() {
    candymachine Candy;
    int password = 12345678;//���ÿ����޸��ǹ����ڲ���Ϣ������
    cout << "�������Ӧ����: " << endl << "1:���� " << "2:�޸Ĳ���" << "3:��� " << endl;
    int oper;
    while (cin >> oper) {
        if (oper == 3) {
            break;
        }
        if (oper == 1) {
            Candy.printlist();//��ӡ�ǹ�list
            while (1) {
                cout << "�����빺�����н�����Ʒ����:" << endl;
                float temp;
                int	code1;
                cout << "����������" << endl;
                cin >> temp;
                cout << "������Ʒ���ţ�" << endl;
                cin >> code1;
                Candy.buy(temp, code1);//������
                Candy.list[code1].num--;
            }
        }
        else if (oper == 2) {
            cout << "���������룺";
            int Password;
            cin >> Password;
            if (Password == password) {//������ȷ�����޸Ĳ���
                int i = 0;
                ifstream file("list.txt"); // ���ļ�
                if (file.is_open()) {
                    string line;
                    while (getline(file, line)) { // ������ȡ�ļ�
                        istringstream a(line);//�ļ���ȡ��¼����Ϣ��list
                        a >> Candy.list[i].code >> Candy.list[i].name >> Candy.list[i].price >> Candy.list[i].num; // �ӵ�ǰ�ж�ȡ����
                        i++;
                    }
                    Candy.candynum = i;//���������ǹ�����
                    file.close(); // �ر��ļ�
                }
            }
            else {
                cout << "������������²���";
            }
        }
        else {
            continue;
        }
    }
}

