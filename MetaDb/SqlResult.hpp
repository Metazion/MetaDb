#ifndef _METADB_SQLRESULT_HPP_
#define _METADB_SQLRESULT_HPP_

#include "MetaDb/CoreInclude.hpp"

#include <string>

#include "MetaDb/SqlBuffer.hpp"
#include "MetaDb/SqlDefine.hpp"
#include "MetaDb/SqlFieldParam.hpp"

DECL_NAMESPACE_METADB_BEGIN

class SqlConnection;

class SqlResult {
public:
    SqlResult();

    ~SqlResult();

public:
    bool Reset(SqlConnection* sqlConnection, MYSQL_STMT* stmt);

    bool Bind(SqlFieldParam* fieldParams, int number);

    bool Next();

    bool IsNull(int index, bool& value);

    bool GetInt8(int index, int8_t& value);

    bool GetUint8(int index, uint8_t& value);

    bool GetInt16(int index, int16_t& value);

    bool GetUint16(int index, uint16_t& value);

    bool GetInt32(int index, int32_t& value);

    bool GetUint32(int index, uint32_t& value);

    bool GetInt64(int index, int64_t& value);

    bool GetUint64(int index, uint64_t& value);

    bool GetFloat(int index, float& value);

    bool GetDouble(int index, double& value);

    bool GetString(int index, char* value, int& length);

    bool GetBinary(int index, void* value, int& length);

private:
    bool BindParams();

    bool PullField(int index, void* value, int& length);

    bool CheckIndex(int index) const;

    void AcquireErrorInfo();

private:
    SqlConnection* m_sqlConnection = nullptr;
    MYSQL_STMT* m_stmt = nullptr;

    SqlFieldParam* m_fieldParams = nullptr;
    int m_fieldNumber = 0;

    SqlBuffer<MYSQL_BIND, 16, 2> m_bindBuffer;
    SqlBuffer<char, 1024, 1024> m_dataBuffer;
};

DECL_NAMESPACE_METADB_END

#endif // _METADB_SQLRESULT_HPP_
