#ifndef DataSystems_H
#define DataSystems_H

#include <QString>
#include <QList>
//#include "utils/Utils.h"
//#include "db/database.h"

enum DB_check{ SQLITE, PGSQL };
enum icons_i{calendar_i, delete_i, detail_record_i, edit2_i, edit_i, graphic_i, report_i, search_i };

enum MenuTypes{
    HeaderMenu = 0,
    FooterMenu = 1
};


class DataSystems   //Singleton
{
public:

    QList<QString> icons;

    //DataBase *db;

    DB_check db_check;
    bool db_check_create;
    bool exit_application;

    QString db_host;
    QString db_name;
    int db_port;
    int db_connection_counter;
    QString db_login;
    QString db_password;
    QString db_sql_create;
    QString db_sql_insert;
    QString db_sql_drop;
    QString db_date_work;

    bool db_generate_random;

    QString db_sqlite_file;
    QString db_sqlite_file_autorization;

    QString name_animals;

    QString log="";
    QString log_execution_result="";
    QString log_create_db;

    QList<QString> log__lists;
    QList<QString> log_execution_result__lists;

    int id_max;

    QString settings___color_header;
    QString settings___color_header_textedit_code;
    QString settings___color_header_dialog;
    QString settings___color_header___decimal;
    QString settings___tabwidget_width;

    QString savePath;

    long long y;

    static DataSystems& Instance()
    {
        static DataSystems singleton;
        return singleton;
    }

    static DataSystems& I()
    {
        static DataSystems singleton;
        return singleton;
    }

    void clear();

    // Other non-static member functions
private:
    DataSystems() { }                                  // Private constructor
    ~DataSystems() {}
    DataSystems(const DataSystems&);                 // Prevent copy-construction
    DataSystems& operator=(const DataSystems&);      // Prevent assignment

public:



};

#endif // DataSystems_H
