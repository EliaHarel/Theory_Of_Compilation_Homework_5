//
// Created by EliaHarel on 23/12/2020.
//

#include "funcSymbolsTable.h"
#include "varsSymbolsTable.h"

/*FuncSymbolsTable* FuncSymbolsTable::funcs_table = nullptr;

FuncSymbolsTable& FuncSymbolsTable::getSymbolFunc(){
    if(!funcs_table) funcs_table = new FuncSymbolsTable();
    return *funcs_table;
}
*/

bool FuncSymbolsTable::isValidName(const std::string& id, void* VarsSymbolsTable_t){
    if(isDefined(id)){
        return false;
    }
    return !((VarsSymbolsTable*)VarsSymbolsTable_t)->isDefined(id);
}
