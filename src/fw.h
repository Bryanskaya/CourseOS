#ifndef FW_H
#define FW_H


#define IN          1
#define OUT         2
#define NOT_STATED  100

#define DEVICE_FNAME            "fw_file"
#define DEVICE_CLASS            "fw_class"


struct fw_rule 
{
    u_int32_t in;
    
    u_int32_t src_ip;
    /*u_int32_t src_mask;*/
    u_int16_t src_port;
    
    u_int32_t dest_ip;
    /*u_int32_t dest_mask;*/ /*mask нужна ли*/
    u_int32_t dest_port;

    u_int8_t protocol;
};

enum fw_action 
{
    ADD = 1,
    DELETE = 2,
    SHOW = 3,
    NONE = 0
};

struct fw_comm
{
    enum fw_action action;
    struct fw_rule rule;
};


#endif // FW_H
