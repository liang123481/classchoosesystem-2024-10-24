#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class candy {//定义糖果类
public:
    int num;//数目
    string name;//糖果名字
    int code;//销售编号
    float price;//价格
    void getinfo() {//打印相关信息
        cout << "名称:" << name << endl << "价格:" << price << endl << "剩余数量：" << num << endl;
    }
};
class candymachine {//定义糖果机类
public:
    candy list[100];//糖果类列表
    int candynum;//现有糖果种类
    void buy(float money, int code) {//购买函数
        if (list[code].price <= money) {
            if (list[code].num > 0) {
                money -= list[code].price;
                cout << "购买成功" << endl;
                cout << "购买后的余额为：" << money << endl;
            }
            else {
                cout << "已售罄" << endl;
            }
        }
        else {
            cout << "购买失败，金额不足" << endl;
        }
    }
    void printlist() {//糖果种类陈列
        for (int i = 0; i < candynum; i++) {
            list[i].getinfo();
        }
    }
};
int main() {
    candymachine Candy;
    int password = 12345678;//设置可以修改糖果机内部信息的密码
    cout << "请输入对应操作: " << endl << "1:购买 " << "2:修改参数" << "3:完毕 " << endl;
    int oper;
    while (cin >> oper) {
        if (oper == 3) {
            break;
        }
        if (oper == 1) {
            Candy.printlist();//打印糖果list
            while (1) {
                cout << "请输入购买现有金额和商品代号:" << endl;
                float temp;
                int	code1;
                cout << "输入现有余额：" << endl;
                cin >> temp;
                cout << "输入商品代号：" << endl;
                cin >> code1;
                Candy.buy(temp, code1);//购买函数
                Candy.list[code1].num--;
            }
        }
        else if (oper == 2) {
            cout << "请输入密码：";
            int Password;
            cin >> Password;
            if (Password == password) {//密码正确可以修改参数
                int i = 0;
                ifstream file("list.txt"); // 打开文件
                if (file.is_open()) {
                    string line;
                    while (getline(file, line)) { // 持续读取文件
                        istringstream a(line);//文件读取后录入信息到list
                        a >> Candy.list[i].code >> Candy.list[i].name >> Candy.list[i].price >> Candy.list[i].num; // 从当前行读取数据
                        i++;
                    }
                    Candy.candynum = i;//修正现有糖果种类
                    file.close(); // 关闭文件
                }
            }
            else {
                cout << "密码错误，请重新操作";
            }
        }
        else {
            continue;
        }
    }
}

