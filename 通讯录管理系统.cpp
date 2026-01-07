//封装函数显示界面
//在main函数中调用封装好的函数
#include<iostream>
#include <fstream>
#include<string>
using namespace std;
#define MAX 1000 //最大人数
const string FILE_NAME ="/Users/a1-6/Desktop/通讯录管理系统/contscts.txt";
//用户清屏
void pause() {
    cout << "按回车键继续..." << endl;
    cin.ignore(); // 处理换行符
    cin.get();
    system("clear"); // Mac/Linux 清屏
}
 
struct Person{
    string m_Name;
    int m_Sex;//1男  2女
    int m_Age;
    string m_Phone;
    string m_Addr;
};

struct Addressbooks{
    Person personArray[MAX];
    //通讯录中当前记录的联系人个数
    int m_Size;
};
//主页
void showMenu(){
    cout<<"*************************"<<endl;
    cout<<"***** 1、添加联系人 *****"<<endl;
    cout<<"***** 2、显示联系人 *****"<<endl;
    cout<<"***** 3、删除联系人 *****"<<endl;
    cout<<"***** 4、查找联系人 *****"<<endl;
    cout<<"***** 5、修改联系人 *****"<<endl;
    cout<<"***** 6、清空联系人 *****"<<endl;
    cout<<"***** 0、退出通讯录 *****"<<endl;
    cout<<"*************************"<<endl;
}

//保存联系人信息到文件
void saveToFile(Addressbooks* abs) {
    ofstream ofs(FILE_NAME, ios::out);  // 以写入模式打开文件
    for (int i = 0; i < abs->m_Size; i++) {
        ofs << abs->personArray[i].m_Name << " "
            << abs->personArray[i].m_Sex << " "
            << abs->personArray[i].m_Age << " "
            << abs->personArray[i].m_Phone << " "
            << abs->personArray[i].m_Addr << endl;
    }
    ofs.close();
}

// **从文件加载联系人信息**
void loadFromFile(Addressbooks* abs) {
    ifstream ifs(FILE_NAME, ios::in);  // 以读取模式打开文件
    if (!ifs.is_open()) {
        cout << "没有找到通讯录文件，已创建新通讯录。" << endl;
        abs->m_Size = 0;
        return;
    }

    abs->m_Size = 0; // 初始化联系人数量
    while (ifs >> abs->personArray[abs->m_Size].m_Name
               >> abs->personArray[abs->m_Size].m_Sex
               >> abs->personArray[abs->m_Size].m_Age
               >> abs->personArray[abs->m_Size].m_Phone
               >> abs->personArray[abs->m_Size].m_Addr) {
        abs->m_Size++;
    }
    ifs.close();
}


//1、添加联系人
void addPerson(Addressbooks * abs){
//首先判断通讯录是否已满
    if(abs->m_Size==MAX){
        cout<<"通讯录已满，无法添加！🥹"<<endl;
        return;
    }
    else{

    //姓名
        string name;
        cout<<"请输入姓名："<<endl;
        cin>>name;
        abs->personArray[abs->m_Size].m_Name=name;

    //性别
        int sex;
        cout<<"请输入性别："<<endl;
        cout<<"1--男  2--女"<<endl;
        cin>>sex;
        //如果输入的是正确值，可以退出循环
        while(true){
            if(sex==1||sex==2){
                abs->personArray[abs->m_Size].m_Sex=sex;
                break;
            }
            cout<<"输入有误，请重新输入"<<endl;
        }

    //年龄
        cout<<"请输入年龄："<<endl;
        int age=0;
        cin>>age;
        while(true){
            if(age<150&&age>0){
                abs->personArray[abs->m_Size].m_Age=age;
                break; 
            }
            cout<<"输入有误，请重新输入"<<endl;
        }

    //手机号
        cout<<"请输入手机号"<<endl;
        string phone;
        cin>>phone;
        abs->personArray[abs->m_Size].m_Phone=phone;
    
    //家庭住址
        cout<<"请输入家庭住址"<<endl;
        string address;
        cin>>address;
        abs->personArray[abs->m_Size].m_Addr=address;

        //更新通讯录人数
        abs->m_Size++;
        saveToFile(abs); // 添加联系人后，保存到文件
        cout<<"添加成功"<<endl;
       
        pause();   
    }
    
}

//2、显示联系人
void showPerson(Addressbooks * abs){
//判断通讯录中人数是否为0，如果为0，提示记录已空
//如果不为0，显示记录的联系人信息
    if(abs->m_Size==0){
        cout<<"当前的记录为空"<<endl;
    }
    else{
        for(int i=0;i<abs->m_Size;i++){
            cout<<"姓名："<<abs->personArray[i].m_Name<<"\t";
            cout<<"性别："<<abs->personArray[i].m_Sex<<"\t";
            cout<<"年龄："<<abs->personArray[i].m_Age<<"\t";
            cout<<"号码："<<abs->personArray[i].m_Phone<<"\t";
            cout<<"地址："<<abs->personArray[i].m_Addr<<"\t";
        }
        cout<<"\n";
    }
    pause();
}

//检测联系人是否存在，如果存在，返回联系人所在数组中的具体位置，不存在返回-1
//参数1 通讯录    参数2 对比姓名
int isExist(Addressbooks * abs,string name){
    for(int i=0;i<abs->m_Size;i++){
        if(abs->personArray[i].m_Name==name){
            return i;//如果找到了，返回这个人在数组中的下标编号
        }
    }
    return -1;//如果遍历没有找到，返回-1
}

//3、删除联系人
void deletepPerson(Addressbooks *abs){
    cout<<"请输入您要删除的联系人"<<endl;

    string name;
    cin>>name;
    //ret=-1 未查到
    //ret!=-1 查到了
    int ret = isExist(abs,name);
    if(ret!=-1){
        //查到此人，进行删除
        for(int i=ret;i<abs->m_Size;i++){
            abs->personArray[i]=abs->personArray[i+1];
        }
        abs->m_Size--;//更新通讯录中的人员个数
        saveToFile(abs); // 更新文件
        cout<<"删除成功"<<endl;
    }
    else{
        cout<<"查无此人"<<endl;
    }
    pause();
}

//4、查找查找联系人
void findPerson(Addressbooks * abs){
    cout<<"请输入你要查找的联系人"<<endl;
    string name;
    cin>>name;

    //判断指定联系人是否存在在通讯录值中
    int ret=isExist(abs,name);

    if(ret!=-1){
        cout<<"姓名："<<abs->personArray[ret].m_Name<<"\t";
        cout<<"性别："<<abs->personArray[ret].m_Sex<<"\t";
        cout<<"年龄："<<abs->personArray[ret].m_Age<<"\t";
        cout<<"号码："<<abs->personArray[ret].m_Phone<<"\t";
        cout<<"住址："<<abs->personArray[ret].m_Addr<<"\t";
        cout<<endl;
    }
    else{
        cout<<"查无此人"<<endl;
    }
    pause();
}

//5、修改联系人
void modifyPerson(Addressbooks * abs){
    cout<<"请输入您要修改的联系人"<<endl;
    string name;
    cin>>name;
    int ret=isExist(abs,name);
    if(ret!=-1){
        //姓名
        string name;
        cout<<"请输入新的姓名"<<endl;
        cin>>name;
        abs->personArray[ret].m_Name=name;
        //性别
        cout<<"请输入性别："<<endl;
        cout<<"1---男"<<endl;
        cout<<"2---女"<<endl;
        int sex=0;
        while(true){
            cin>>sex;
            if(sex==1||sex==2){ 
                abs->personArray[ret].m_Sex=sex;
                break;
            }
            cout<<"输入有误，请重新输入"<<endl;
        }
        //年龄
        cout<<"请输入年龄"<<endl;
        int age=0;
        cin>>age;
        abs->personArray[ret].m_Age=age;
        //电话
        cout<<"请输入联系电话："<<endl;
        string phone;
        cin>>phone;
        abs->personArray[ret].m_Phone=phone;
        //住址
        cout<<"请输入住址："<<endl;
        string address;
        cin>>address;
        abs->personArray[ret].m_Addr=address;
        saveToFile(abs); // 更新文件
        cout<<"修改成功！"<<endl;
        }
    else{
        cout<<"查无此人"<<endl;
    }
    pause();
}

//6、清空联系人
void cleanPerson(Addressbooks * abs){
    cout<<"您确定要全部清空？"<<endl;
    cout<<"1---确定"<<endl;
    cout<<"2---再想想"<<endl;
    int choose=0;
    cin>>choose;
    if(choose==1){
        abs->m_Size = 0;
        saveToFile(abs); // 更新文件
        cout<<"通讯录已清除"<<endl;
    }
    else{
        cout<<"请继续"<<endl;
    }
    pause();
}

//
int main(){
    //创建通讯录结构体变量
    Addressbooks abs;
    //初始化通讯录中当前人员个数
    abs.m_Size=0;
    loadFromFile(&abs);
    int select=0;//创建用户选择输入的变量
    while(true){
        showMenu();
        cin>>select;
        switch(select){
            case 1:     //1、添加联系人
                addPerson(&abs);   //利用地址传递，可以修饰实参
                break;
            case 2:     //2、显示联系人
                showPerson(&abs);
                break;
            case 3:/* {     //3、删除联系人
                cout<<"请输入删除联系人姓名："<<endl;
                string name;
                cin>>name;
                if(isExist(&abs,name)==-1){
                    cout<<"查无此人"<<endl;
                }
                else{
                    cout<<"找到此人"<<endl;
                }
            } */
            deletepPerson(&abs);
                break;
            case 4:     //4、查找联系人
            findPerson(&abs);
                break;
            case 5:     //5、修改联系人
            modifyPerson(&abs);
                break;
            case 6:     //6、清空联系人
            cleanPerson(&abs);
                break;
            case 0:     //0、退出通讯录
                cout<<"欢迎下次使用"<<endl;
                break;
            default:
                break;
        }
    }   
    return 0;
}