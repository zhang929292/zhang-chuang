#include "student.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
    //init properties: id, name and password
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;
        // get computer room information
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    ComputerRoom com;
    while ( ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    
    ifs.close();
}

//submenu
void Student::operMenu()
{
    cout << "welcome" << this->m_Name << "Log in!" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.Apply reservation     |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.View my reservation   |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          3.View all reservation  |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          4.Cancel reservation    |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.Exit                  |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "Select your operation:  " << endl;
}


void Student::applyOrder()
{
    cout << "The computer room is open from Monday to Friday!" << endl;
    cout << "Enter apply date: " << endl;
    cout << "1 Mon" << endl;
    cout << "2 Tues" << endl;
    cout << "3 Wes" << endl;
    cout << "4 Thur" << endl;
    cout << "5 Fir" << endl;
    
    int date = 0;
    int interval = 0;
    int room = 0;
    
    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << " Wrong input, please enter again!" << endl;
    }
    
    cout << "Enter appointment time：" << endl;
    cout << "1 8:00 - 12:00" << endl;
    cout << "2 13:00 - 18:00 " << endl;
    
    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << " Wrong input, please enter again!" << endl;
    }
    
    cout << " Please select computer room: " << endl;
    for (int i = 0; i < vCom.size(); i++)
    {
        cout << "Capacity of computer room " << vCom[i].m_ComId << ": " << vCom[i].m_MaxNum << endl;
    }
    
    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "Wrong input, please enter again!" << endl;
    }
    
    cout << "Reservation successful! The application is under review" << endl;
    
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;  // 1 represents  application is under review
    
    ofs.close();

}

void Student::showMyOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "No record" << endl;

        return;
    }
    
    for (int i = 0; i < of.m_Size; i++)
    {
        
        if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            cout << " reservation date: " << of.m_orderData[i]["date"];
            cout << "; reservation time: " << (of.m_orderData[i]["interval"] == "1" ? "8:00 - 12:00" : "13:00 - 18:00");
            cout << "; computer room: " << of.m_orderData[i]["roomId"];
            string status = "; status: ";
            // 1 Under review  2 Reservation made  -1 Reservation failed  0 Reservation canceled
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "Under review";
            }
            else if (of.m_orderData[i]["status"] == "2")
            {
                status += "Reservation made";
            }
            else if (of.m_orderData[i]["status"] == "-1")
            {
                status += "Reservation failed";
            }
            else
            {
                status += "Reservation canceled";
            }
            cout << status << endl;
        }
    }

}


void Student::showAllOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "No record" << endl;
        system("pasue");
        system("cls");
        return;
    }
    
    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i + 1 << ". ";
        cout << " reservation date: " << of.m_orderData[i]["date"];
        cout << "; reservation time: " << (of.m_orderData[i]["interval"] == "1" ? "8:00 - 12:00" : "13:00 - 18:00");
        cout << "; id: " << of.m_orderData[i]["stuId"];
        cout << "; name: " << of.m_orderData[i]["stuName"];
        cout << "; computer room: " << of.m_orderData[i]["roomId"];
        string status = "; status: ";
        // 1 Under review  2 Reservation made  -1 Reservation failed  0 Reservation canceled
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "Under review ";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "Reservation made";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "Reservation failed";
        }
        else
        {
            status += "Reservation canceled";
        }
        cout << status << endl;
    }
    

}

void Student::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "No record" << endl;

        return;
    }
    
    cout << "Reservations can be cancelled. Please enter the record information you wish to cancel" << endl;
        //Store subscript number in the largest container
    vector<int>v;
    int index = 1;
    for (int i = 0; i < of.m_Size; i++)
    {
                // decide whether it matches its student id
        if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << ". ";
                cout << " Reservation date: " << of.m_orderData[i]["date"];
                cout << " Reservation time:  " << (of.m_orderData[i]["interval"] == "1" ? "8:00 - 12:00" : "13:00 - 18:00");
                cout << " computer room: " << of.m_orderData[i]["roomId"];
                string status = " status: ";
                                //1 Under review  2 Reservation made
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "Under review";
                }
                else if (of.m_orderData[i]["status"] == "2")
                {
                    status += "Reservation made successfully";
                }
                cout << status << endl;
            }
        }
    }
    
    
    cout << "Please enter the record information you wish to cancel; 0 represents return" << endl;
    int select = 0;
    
    while (true)
    {
        cin >> select;
        
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                of.m_orderData[v[select - 1]]["status"] = "0";
                
                of.updateOrder();
                
                cout << "Already cancelled reservation" << endl;
                break;
            }
        }
        
        cout << "Wrong ！Please enter again" << endl;
    }
    

}

