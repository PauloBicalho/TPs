#ifndef MESSAGETYPE_HPP
#define MESSAGETYPE_HPP

class MessageType{
  public:
    enum Type{
      SEND_ID,
      SEND_INTERVAL,
      SEND_RESULT,
      CONFIRM_INTERVAL,
      CONFIRM_RESULT
    };
};


#endif // MESSAGETYPE_HPP
