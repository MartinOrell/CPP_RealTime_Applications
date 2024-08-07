By using invoke a capsule can send a request to another capsule, get the response and then continue. This request gets handled by CapsuleRunner directly without using the messageStack.\
The invoke function will be defined in CapsuleRunner.
```
//CapsuleRunner.h
Message invokeMessage(Message request);
```

The request message is received as an argument and the response message is returned. The datatype used is defined in Message.h using std::variant and can be any type of message. Therefore the type needs to be checked and the value accessed before use.
```
//CapsuleRunner.cpp
Message CapsuleRunner::invokeMessage(Message request){
    if(std::holds_alternative<Request>(request)){
        Request rMessage = std::get<Request>(request);
        return _server.handleInvokeMessage(rMessage);
    }
    else{
        throw std::invalid_argument("CapsuleRunner received invokeMessage of wrong type");
    }
}
```

In order for a capsule to make an invoke request they need a reference to the CapsuleRunner. To do this CapsuleRunner needs to be forward declared in Client_Capsule.h
```
//Client_Capsule.h
class CapsuleRunner;
```
and then included in Client_Capsule.cpp
```
//Client_Capsule.cpp
#include "CapsuleRunner.h"
```
The pointer to the CapsuleRunner is defined as a private variable in Client_Capsule.h and declared in the constructor. When CapsuleRunner initiales the Client_Capsule *this* keyword is used.\
When calling invoke a generic message is produced and needs to be converted to the right type
```
Message genericResponseMessage = _capsuleRunnerPtr->invokeMessage(requestMessage);
assert(std::holds_alternative<Response>(genericResponseMessage));
Response responseMessage = std::get<Response>(genericResponseMessage);
```