#include <iostream>
#include <fstream> 
#include <string.h>
#include <ctime>

using namespace std;
int main(int argc, char** argv)
{
    //for(int i=0;i<argc;i++)cout<<argv[i]<<" ";
    if(argc==3)
    {
        if(strcmp(argv[1],"add")==0)
        {
            fstream todo_file,temp_file;
            todo_file.open("todo.txt",ios::in | ios::out | ios::app);
            temp_file.open("temp.txt",ios::in | ios::out | ios::app);
            string str;
            int no_of_lines=1;
            while(getline(todo_file,str))
            no_of_lines++;
            todo_file.close();  

            todo_file.open("todo.txt",ios::in | ios::out | ios::app);
            temp_file<<"["<<no_of_lines<<"] "<<argv[2]<<"\n";
            
            cout<<"Added todo: \""<<argv[2]<<"\"";

            while(getline(todo_file,str))
            {
                temp_file<<str<<"\n";
            }
            todo_file.close();  

            todo_file.open("todo.txt",ios::out | ios::trunc);
            todo_file.close();    
            
            todo_file.open("todo.txt",ios::in | ios::out | ios::app);
            temp_file.seekg(0, ios::beg);

            while(getline(temp_file,str))
            {
                todo_file<<str<<"\n";
            }
            temp_file.close();
            temp_file.open("temp.txt",ios::out | ios::trunc);
            temp_file.close();   
            todo_file.close();
        }
        else if(strcmp(argv[1],"del")==0)
        {
            fstream todo_file,temp_file;
            todo_file.open("todo.txt",ios::in | ios::out | ios::app);
        
            string str;
            int no_of_lines=0;
            while(getline(todo_file,str))
            no_of_lines++;

            todo_file.close();  

            int line_to_delete=stoi(argv[2]);
            if(no_of_lines<line_to_delete || line_to_delete==0)
            {
                cout<<"Error: todo #"<<line_to_delete<<" does not exist. Nothing deleted.";
            }
            else
            {
               cout<<"Deleted todo #"<<line_to_delete;
               no_of_lines--;

                temp_file.open("temp.txt",ios::in | ios::out | ios::app);
                todo_file.open("todo.txt",ios::in | ios::out | ios::app);  

                while(getline(todo_file,str))
                {
                    int i=1,length_to_erase=2;
                    string temp_num_string="";
                    while(str[i]!=']')
                    {
                        temp_num_string+=str[i];
                        length_to_erase++;
                        i++;
                    }
                    str.erase(0,length_to_erase);
                    if(stoi(temp_num_string)!=line_to_delete)
                    temp_file<<"["<<no_of_lines<<"]"<<str<<"\n",no_of_lines--;
                }
                todo_file.close();  

                todo_file.open("todo.txt",ios::out | ios::trunc);
                todo_file.close();    
                
                todo_file.open("todo.txt",ios::in | ios::out | ios::app);
                temp_file.seekg(0, ios::beg);

                while(getline(temp_file,str))
                {
                    todo_file<<str<<"\n";
                }
                temp_file.close();
                temp_file.open("temp.txt",ios::out | ios::trunc);
                temp_file.close();   
                todo_file.close();  
            }
            
        }
        else if(strcmp(argv[1],"done")==0)
        {
            fstream todo_file,temp_file,done_file;
            todo_file.open("todo.txt",ios::in | ios::out | ios::app);
            
            string str;
            int no_of_lines=0;
            while(getline(todo_file,str))
            no_of_lines++;

            todo_file.close();  

            int line_to_delete=stoi(argv[2]);
            if(no_of_lines<line_to_delete || line_to_delete==0)
            {
                cout<<"Error: todo #"<<line_to_delete<<" does not exist.";
            }
            else
            {
               cout<<"Marked todo #"<<line_to_delete<<" as done.";
               no_of_lines--;

                temp_file.open("temp.txt",ios::in | ios::out | ios::app);
                todo_file.open("todo.txt",ios::in | ios::out | ios::app);  
                done_file.open("done.txt",ios::in | ios::out | ios::app);    
                while(getline(todo_file,str))
                {
                    int i=1,length_to_erase=3;  // 3 for "[" , "]" and " " (space)
                    string temp_num_string="";
                    while(str[i]!=']')
                    {
                        temp_num_string+=str[i];
                        length_to_erase++;
                        i++;
                    }
                    str.erase(0,length_to_erase);
                    if(stoi(temp_num_string)!=line_to_delete)
                    temp_file<<"["<<no_of_lines<<"] "<<str<<"\n",no_of_lines--;
                    else
                    {
                        time_t now = time(0);
                        tm *ltm = localtime(&now);

                        done_file<<"x "<<(1900 + ltm->tm_year)<<"-"<<(1+ltm->tm_mon)<<"-"<<(ltm->tm_mday)<<" "<<str<<"\n";
                        done_file.close();
                    }
                    
                }
                todo_file.close();  

                todo_file.open("todo.txt",ios::out | ios::trunc);
                todo_file.close();    
                
                todo_file.open("todo.txt",ios::in | ios::out | ios::app);
                temp_file.seekg(0, ios::beg);

                while(getline(temp_file,str))
                {
                    todo_file<<str<<"\n";
                }
                temp_file.close();
                temp_file.open("temp.txt",ios::out | ios::trunc);
                temp_file.close();   
                todo_file.close();  
            }
            
        }
    // todo_file.seekg(0, ios::beg); 
  
     
    }
    else if(argc==2)
    {
        if(strcmp(argv[1],"help")==0)
        {
            cout << ifstream("my_file.txt").rdbuf();
        }
        else if(strcmp(argv[1],"ls")==0)
        {
            fstream todo_file;
            string line;
            int f=0;
            todo_file.open("todo.txt",ios::in | ios::out | ios::app);
                while (todo_file) { 
                getline(todo_file, line); 
                if(line=="")
                break;
                cout << line << "\n"; 
                f=1;    
                }
                if(f==0)
                cout<<"There are no pending todos!";
            todo_file.close();
        }
        else if(strcmp(argv[1],"report")==0)
        {
            fstream todo_file,done_file;
            todo_file.open("todo.txt",ios::in | ios::out | ios::app);
            done_file.open("done.txt",ios::in | ios::out | ios::app);
            string str;
            int no_of_lines_pending=0,no_of_lines_completed=0;

            while(getline(todo_file,str))
            no_of_lines_pending++;
            todo_file.close();  

            while(getline(done_file,str))
            no_of_lines_completed++;
            done_file.close();  

            time_t now = time(0);
            tm *ltm = localtime(&now);

            
            cout<<(1900 + ltm->tm_year)<<"-"<<(1+ltm->tm_mon)<<"-"<<(ltm->tm_mday)<<" Pending : "<<no_of_lines_pending<<" Completed : "<<no_of_lines_completed;
        }
        else if(strcmp(argv[1],"add")==0)
        {
            cout<<"Error: Missing todo string. Nothing added!";
        }
        else if(strcmp(argv[1],"del")==0)
        {
            cout<<"Error: Missing NUMBER for deleting todo.";
        }
        else if(strcmp(argv[1],"done")==0)
        {
            cout<<"Error: Missing NUMBER for marking todo as done.";
        }
    }
    else
    {
        cout << ifstream("my_file.txt").rdbuf();       
    }
    return 0;
}
