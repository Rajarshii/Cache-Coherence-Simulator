enum class CoreOpType { LOAD, STORE, NOP };

enum class BusTransactionType { GetS, GetM, Upg, PutS, PutE, PutO, PutM, Illegal };


class CoreRequest {
public: 
    CoreRequest() : RequestType{CoreOpType::NOP} {}

    CoreRequest(CoreOpType type) : RequestType{type} {}

    ~CoreRequest() = default;

private:
    CoreOpType RequestType;
};



class BusTransaction {
public:
    BusTransaction() : TransactionType{BusTransactionType::Illegal} {}

    BusTransaction(BusTransactionType type) : TransactionType{type} {}

    ~BusTransaction() = default;

private:
    BusTransactionType TransactionType ;

};