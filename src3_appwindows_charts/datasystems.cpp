#include "datasystems.h"
#include <QApplication>


void DataSystems::clear()
{
    // ****************************************************

    //0,125,128 007D80


    settings___color_header="#14B143"; // зеленый (20,177,67)
    settings___color_header___decimal="(20,177,67)"; //    (20,177,67)

    settings___color_header="#FF6C6C"; // красный (255,108,108)
    settings___color_header___decimal="(255,108,108)"; //    (255,108,108)

    settings___color_header="#0683FF"; // синий   (06,131,255)
    settings___color_header___decimal="(06,131,255)"; // синий   (06,131,255)

    settings___color_header="#2222FF"; // синий   (34,34,255)
    settings___color_header___decimal="(34,34,255)"; // синий   (34,34,255)

    settings___color_header="#DB24C9"; //    (219,36,201)
    settings___color_header___decimal="(219,36,201)"; // синий   (219,36,201)

    settings___color_header="#DEE173"; //    ()
    settings___color_header___decimal="(222, 225, 115)"; // синий   ()

    settings___color_header="#5999B5"; //    ()
    settings___color_header___decimal="(89, 153, 181)"; // синий   ()

    settings___color_header="#"; //    ()
    settings___color_header___decimal="()"; // синий   ()

    settings___color_header="#"; //    ()
    settings___color_header___decimal="()"; // синий   ()



    settings___color_header="#FF6C6C"; // красный (255,108,108)
    settings___color_header_dialog="#ffffff"; //
    settings___color_header___decimal="(255,108,108)"; //    (255,108,108)

    settings___color_header="#DB24C9"; //    (219,36,201)
    settings___color_header_textedit_code = "(208, 255, 208)";
    settings___color_header___decimal="(219,36,201)"; // синий   (219,36,201)

      //("#2222FF", "(81, 34, 129)"
    settings___color_header="#2222FF"; //    (219,36,201)
    settings___color_header_textedit_code = "(81, 34, 129)";
    settings___color_header___decimal="(219,36,201)"; // синий   (219,36,201)


    settings___tabwidget_width="700px";

    // ****************************************************

    icons = {":/icons/icons/calendar__.png",
             ":/icons/icons/delete__.png",
             ":/icons/icons/detail_record__.png",
             ":/icons/icons/edit2__.png",
             ":/icons/icons/edit__.png",
             ":/icons/icons/graphic__.png",
             ":/icons/icons/report__.png",
             ":/icons/icons/search__.png"};

    //db = nullptr;

    log="";
    log_execution_result = "";
    log_create_db="";
    //mj.clear();

    log_execution_result__lists.clear();
    log__lists.clear();

    //mjpj.clear();
    //db_sql.clear();
    //db_sql_table_insert.clear();

    //db_check = DB_check::SQLITE;
    db_check = DB_check::PGSQL;
    db_check_create = false;
    //db_check_create = true;
    exit_application = false;

    //db_host="192.168.124.135";
    //db_host="192.168.124.153";
    //db_host="192.168.1.3";
    //db_host="192.168.0.3";
    db_host="127.0.0.1";
    //db_name="vim3";
    //db_name="vim5";
    db_name="vim3";
    db_port=5433;
    //db_port=5433;
    db_login="postgres";
    //db_login="zanxi";
    db_login="vim";
    //db_login="user1";
    db_date_work="";
    db_generate_random = true;
    //db_generate_random = false;
    id_max=2500;

    db_password="000";
    db_sql_create="create.sql";
    db_sql_insert="insert.sql";
    db_sql_drop="drop.sql";
    db_sqlite_file = "c://lely//db-lely3.db";
    db_sqlite_file_autorization = QApplication::applicationDirPath()+"/"+ "autorization_user_data.db";
    //db_sqlite_file="c://db-prolely3.db";
    //db_sqlite_file="db-test.db";
    //db_sqlite_file="003.db";

    db_connection_counter = 0;

    y=0;

    name_animals="корова";

    savePath = QApplication::applicationDirPath();


}
