#include "request.h"

#include "debug/logger.h"

void Request::process()
{
    //outFnc("Statrting processing request " + std::to_string(value) + "...");
    logger::WriteDebug_process("void Request::process()");
    sdiFnc(this->dmi);    
}

void Request::process(DataModelInput dmi)
{
    //qDebug()<<"void Request::process(DataModelInput dmi)";
    //sdiFnc(dmi);
}


void Request::finish()
{
    //outFnc("Finished request " + std::to_string(value) + "...");
}
