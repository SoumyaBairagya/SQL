#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<sstream>
#include<iomanip>

std::fstream schema;


std::string space_delimiter = " ";

void select(std::string);
void create(std::string);
void describe(std::string);
void drop(std::string);
void help(std::string);
void insert(std::string);

std::vector<std::string> split_query(std::string str, char delimiter)
{
    std::vector<std::string> tokens;
    
    std::stringstream check1(str);

    std::string token;

    while(getline(check1, token, delimiter))
    {
        tokens.push_back(token);
        // std::cout<<token<<"\t";
    }

    return tokens;
}

std::vector<std::string> split_create(std::string str)
{
    std::vector<std::string> tokens;
    
    tokens = split_query(str, '(');
    
    std::string token;

    std::stringstream check1(tokens[1]);

    std::vector<std::string> sub_tokens;

    while(getline(check1, token, ','))
    {
        sub_tokens.push_back(token);
    }

    return sub_tokens;
}

void create(std::string query)
{
    std::vector<std::string> tokens = split_query(query, ' ');
    std::string table_name = tokens[2];

    table_name.erase(table_name.length() - 1, table_name.length());
    //std::cout<<table_name;
    std::vector<std::string> col_var = split_create(query);

    // for(int i = 0; i < col_var.size(); i++)
    // {
    //     std::cout<<col_var[i]<<"\t";
    // }
    // std::cout<<std::endl;

    for(int i = 0; i < col_var.size(); i++)
    {
        if(col_var[i][0] == ' ')
        {
            col_var[i].erase(0, 1);
        }
    }


    std::string :: iterator itr = col_var[col_var.size() - 1].end();

    col_var[col_var.size() - 1].erase(itr - 2, itr);

    std::unordered_map<std::string, std::string>col_map;
    std::vector<std::string> col_names;

    for(int i = 0; i < col_var.size(); i++)
    {
        std::vector<std::string> temp;

        temp = split_query(col_var[i], ' ');

        //std::cout<<"COL NAME: "<<temp[0]<<std::endl;
        //std::cout<<"COL DATA-TYPE: "<<temp[1]<<std::endl;
        col_map[temp[0]] = temp[1];
        col_names.push_back(temp[0]);
    }

    std::unordered_map<std::string, std::string> :: iterator map_itr;
    //std::vector<std::string> :: iterator v_itr;



    // for(map_itr = col_map.begin(); map_itr != col_map.end(); map_itr++)
    // {
    //     std::cout<<map_itr->first<<"\t"<<map_itr->second<<std::endl;;
    // }

    std::fstream dataFile(table_name, std::ios::in);

    if(dataFile)
    {
        std::cout<<"Table Already Exists!!!!"<<std::endl;
    }
    else
    {
        dataFile.close();
        schema.open("SCHEMA.txt", std::ios::app);

        dataFile.open(table_name, std::ios::out);

        for(int i = 0; i < col_names.size(); i++)
        {
            map_itr = col_map.find(col_names[i]);
            if(map_itr != col_map.end())
            {
                schema<<table_name<<"#"<<map_itr->first<<"#"<<map_itr->second<<std::endl;
            }
        }

        for(int i = 0; i < col_names.size(); i++)
        {
            map_itr = col_map.find(col_names[i]);
            if(map_itr != col_map.end())
            {
                dataFile<<map_itr->first<<"#";   
            }
        }
        dataFile<<1<<std::endl;



        dataFile.close();
        schema.close();
    }
    
   
}


void select(std::string query)
{
    std::vector<std::string> tokens = split_query(query, ' ');

    std::string table_name = tokens[tokens.size() - 1];
    table_name.erase(table_name.size() - 1, table_name.size());

    std::fstream dataFile(table_name, std::ios::in);
    dataFile.close();
    dataFile.open(table_name, std::ios::in);

    if(tokens[1] == "*")
    {
        std::cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<std::endl;
        
        while(!dataFile.eof())
        {
            std::string record;

            getline(dataFile, record);

            std::vector<std::string>record_vector = split_query(record, '#');

            if(record_vector[record_vector.size() - 1] == "0")
            {
                continue;
            }

            for(int i = 0; i < record_vector.size() - 1; i++)
            {
                std::cout<<std::setw(20)<<record_vector[i]<<" | ";
            }
            std::cout<<std::endl;
        }

        std::cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  "<<std::endl;
        
    }
    else
    {
        std::vector<std::string>queried_cols;
        std::vector<int> column_indices;
        
        for(int i = 1; i < tokens.size() - 2; i++)
        {
            queried_cols.push_back(tokens[i]);
        }

        for(int i = 0; i < queried_cols.size() - 1; i++)
        {
            queried_cols[i].erase(queried_cols[i].size() - 1);
        }

        std::string cols;
        getline(dataFile, cols);

        std::vector<std::string>columns = split_query(cols, '#');
        columns.pop_back();
        for(int i = 0; i < queried_cols.size(); i++)
        {
            for(int j = 0; j < columns.size(); j++)
            {
                if(queried_cols[i] == columns[j])
                {
                    column_indices.push_back(j);
                }
            }
        }

        std::cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<std::endl;
        
        dataFile.seekg(0);
        while(!dataFile.eof())
        {
            std::string record;
    
            getline(dataFile, record);

            std::vector<std::string>record_vector = split_query(record, '#');

            if(record_vector[record_vector.size() - 1] == "0")
            {
                continue;
            }

            for(int i = 0; i < column_indices.size(); i++)
            {
                std::cout<<std::setw(20)<<record_vector[column_indices[i]]<<" | ";
            }
            std::cout<<std::endl;
        }

        std::cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  "<<std::endl;
        

    }
    dataFile.close();
}

void describe(std::string query)
{
    std::vector<std::string> tokens = split_query(query, ' ');

    std::string table_name = tokens[1];
    table_name.erase(table_name.size() - 1, table_name.size());

    std::vector<std::string> schema_records;

    //schema.open("SCHEMA.txt", std::ios::in);

    while (!schema.eof())
    {
        std::string record;
        getline(schema, record);

        if (record.substr(0, table_name.length() + 1) == table_name + "#")
        {
            schema_records.push_back(record);
        }
    }
    std::cout << table_name << std::endl;
    for (int i = 0; i < schema_records.size(); i++)
    {
        std::vector<std::string> describe_vector = split_query(schema_records[i], '#');

        for (int j = 1; j < describe_vector.size(); j = j + 2)
        {
            std::cout << "\t" << describe_vector[j] << " --> " << describe_vector[j + 1] << std::endl;
        }
    }

    std::cout << std::endl;
}

void help(std::string query)
{
    std::vector<std::string>tokens = split_query(query, ' ');

    if(tokens.size() == 1 && tokens[0] == "HELP")
    {
        std::cout<<"HELP"<<std::endl;
        std::cout<<"Use following help commands to get help for a particular command: "<<std::endl;
        std::cout<<"\t"<<"-- HELP CREATE --> Help for CREATE command"<<std::endl;
        std::cout<<"\t"<<"-- HELP SELECT --> Help for SELECT command"<<std::endl;
        std::cout<<"\t"<<"-- HELP DESCRIBE --> Help for DESCRIBE command"<<std::endl;
        std::cout<<"\t"<<"-- HELP DROP --> Help for DROP command"<<std::endl;
        std::cout<<"\t"<<"-- HELP TRUNCATE --> Help for TRUNCATE command"<<std::endl;
        std::cout<<"\t"<<"-- HELP DELETE --> Help for DELETE command"<<std::endl;
        std::cout<<"\t"<<"-- HELP INSERT --> Help for INSERT command"<<std::endl;    
        std::cout<<std::endl;
        return;
    }

    else if(tokens[1] == "CREATE;")
    {
        std::cout<<"CREATE is used to create a new table \n";
        std::cout<<"\t"<<"CREATE TABLE table_name (attr_name1 attr_type1, attr_name2 attr_type2, …);\n\n";
        return;
    }

    else if(tokens[1] == "DROP;")
    {
        std::cout<<"DROP is used to delete a table along with data\n";
        std::cout<<"\t"<<"DROP TABLE table_name;\n\n";

        return;
    }

    else if(tokens[1] == "DESCRIBE;")
    {
        std::cout<<"DESCRIBE Describes the schema of table T_NAME\n";
        std::cout<<"\t"<<"DESCRIBE table_name;\n\n";
        return;
    }

    else if(tokens[1] == "INSERT;")
    {
        std::cout<<"INSERT is used to insert a record in the table\n";
        std::cout<<"\t"<<"INSERT INTO table_name VALUES(attr_value1,attr_value2, …);\n\tNote that NULL is not permitted for any attribute.";
        return;
    }


    else if(tokens[1] == "DELETE;")
    {
        std::cout<<"DELETE is used to delete an entry from a table\n";
        std::cout<<"\t"<<"DELETE FROM table_name WHERE condition_list;\n\n";
        return;
    }

    else if(tokens[1] == "SELECT;")
    {
        std::cout<<"SELECT is used to select a set of records from the given table\n";
        std::cout<<"\t"<<"SELECT attr_list FROM table_list WHERE condition_list;\n\n";
        return;
    }
}

void drop(std::string query)
{
    std::vector<std::string> tokens = split_query(query, ' ');
    std::string table_name = tokens[2];

    table_name.erase(table_name.length() - 1, table_name.length());
    //std::cout<<table_name;

    // for(int i = 0; i < tokens.size(); i++)
    // {
    //     std::cout<<tokens[i]<<std::endl;
    // }

    //schema.open("SCHEMA.txt", std::ios::out);

    const char* file = table_name.c_str();

    int status = remove(file);
    if(status == 0)
        std::cout<<"Table Dropped!!!"<<std::endl;
    else
        std::cout<<"Error!!! Table was not dropped"<<std::endl;


}

void insert(std::string query)
{
    std::vector<std::string> tokens = split_query(query, ' ');
    std::string table_name = tokens[2];

    //std::cout<<table_name<<"check";

    std::vector<std::string> values = split_create(query);

    

    // for(int i = 0; i < values.size(); i++)
    // {
    //     std::cout<<"check"<<values[i]<<"Check";
    // }

    for(int i = 0; i < values.size(); i++)
    {
        if(values[i][0] == ' ')
        {
            values[i].erase(0, 1);
        }
    }

    // for(int i = 0; i < values.size(); i++)
    // {
    //     std::cout<<"check"<<values[i]<<"Check";
    // }

    std::string :: iterator itr = values[values.size() - 1].end();
    values[values.size() - 1].erase(itr - 2, itr);

    // for(int i = 0; i < values.size(); i++)
    // {
    //     std::cout<<values[i];
    // }


    std::fstream dataFile(table_name, std::ios::in);

    if(dataFile)
    {
        dataFile.close();
        dataFile.open(table_name, std::ios::app);

        for(int i = 0; i <= values.size(); i++)
        {
            dataFile<<values[i]<<"#";
            //std::cout<<values[i];
        }
        dataFile<<"1#"<<std::endl;

        //dataFile.close();
    }
    else
    {
        std::cout<<"No Such Table exists!!!"<<std::endl;
    }

    

    

    
}

int main()
{
    std::string query;
    
    do
    {
        std::getline(std::cin, query);

        std::string :: iterator itr = query.end();

        if(*(itr-1) != ';')
        {
            std::cout<<"\nError, Missing semicolon!!!"<<std::endl;
        }

        std::vector<std::string> tokens = split_query(query, ' ');

        std::cout<<std::endl;;
        

        int query_index;

        if(tokens[0] == "SELECT")
        {
            query_index = 1;
        }
        else if(tokens[0] == "CREATE")
        {
            query_index = 2;
        }
        else if(tokens[0] == "DROP")
        {
            query_index = 3;
        }
        else if(tokens[0] == "TRUNCATE")
        {
            query_index = 4;
        }
        else if(tokens[0] == "DELETE")
        {
            query_index = 5;
        }
        else if(tokens[0] == "DESCRIBE")
        {
            query_index = 6;
        }
        else if(tokens[0] == "HELP")
        {
            query_index = 7;
        }
        else if(tokens[0] == "INSERT")
        {
            query_index = 8;
        }




        switch (query_index)
        {
            case 1:
                select(query);
                break;
            
            case 2:
                create(query);
                break;
            
            case 3:
                drop(query);
                break;
            
            case 6:
                describe(query);
                break;
            
            case 7:
                help(query);
                break;
            
            case 8:
                insert(query);
                break;
            
            default:
                break;
        }

    } while (query != "EXIT;");
    
}



