/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "SqlParsingTest.h"
#include "GlobalVariables.h"

void Osmmd::SqlParsingTest::Test()
{
    Timer timer;
    timer.Start();

    SqlParseResult result = SqlParser::Parse
    (
        " \
        CREATE TABLE test_table ( \
            column1 int(4), \
            column2 int(5), \
            column3 char(10), \
            column4 double(8), \
            column5 datetime(7), \
            primary key(column1), \
            index(column2, column3) \
        ) hash \
        "

        //"CREATE TABLE test_table(column1 int(4), column2 char(10), column3 double(8), column4 datetime(7), primary key(column2))"

        //"INSERT INTO test_table VALUES(1, '103140148', '2021-09-07 22:52:00', 43.2)"
    );

    timer.End();

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("Sql Parsing test:");
    Debug::WriteLine("Costs {}ms", timer.Duration(TimeAccuracy::Millisecond));

    result.Successful
        ? Debug::WriteLine("Result:\n{}", result.ToString())
        : Debug::ErrorLine("Result:\n{}", result.ToString());

    Debug::WriteLine("-------------------------------------------------------------");
}
