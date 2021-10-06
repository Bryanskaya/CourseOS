#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>

#include <unistd.h>

#include "errors.h"
#include "fw.h"


#define TCP_PROTOCOL "TCP"
#define UDP_PROTOCOL "UDP"


/*
* Function to show all commands.
*/
void show_info()
{
    printf("\n"
            "-a --add \t\t Add the rule\n"
            "-d --delete INDEX \t Delete the rule having index = INDEX\n"
            "-A --all \t\t Show all the rules\n"
            "\n"
            "-i --in \t\t Input\n"
            "-o --out \t\t Output\n"
            "-p --protocol PROTOCOL \t Protocol = {TCP, UDP}\n"
            "\n"
            "   --src_ip IP \t\t Source IP\n"
            "   --src_port PORT \t Source port\n"
            "\n"
            "   --dest_ip IP \t Destination IP\n"
            "   --dest_port PORT \t Destinamtion port\n"
            "\n"
            "-h --help \t\t Available commands\n\n");
}

/*
* Function to print a head of table.
*/
void print_head()
{
    printf("IN/OUT \t source address \t source port \t"
	       "destination address \t destination port \t protocol\n");
    for (int i = 0; i < 110; i++)
        printf("¯");
    printf("\n");
}

/*
* Function to show all rules.
*/
int show_rules()
{
    //FILE *fd;
    int fd;
    char *buf;
    struct fw_rule *rule;

    fd = open("/dev/fw_file", O_RDONLY);
    if (fd < 0)
        return DEVICE_NOT_AVAILABLE;

    /*fd = fopen("/dev/fw_file", "r");
	if(fd == NULL) {
		return DEVICE_NOT_AVAILABLE;
	}*/

    buf = (char *)malloc(sizeof(*rule));
    if (buf == NULL)
        return MEMORY_ERROR;

    print_head();
    
    while (read(fd, buf, sizeof(struct fw_comm *)) > 0) 
    //while (fread(buf, 1, sizeof(struct fw_comm), fd) > 0)
    {
		rule = (struct fw_rule *)buf;

		printf("%-8s %d", rule->in == IN ? "IN" : "OUT", rule->in);
		/*addr.s_addr = rule->s_ip;
		printf("%-15s  ", inet_ntoa(addr));
		addr.s_addr = rule->s_mask;
		printf("%-15s  ", inet_ntoa(addr));
		printf("%-5d  ", ntohs(rule->s_port));
		addr.s_addr = rule->d_ip;
		printf("%-15s  ", inet_ntoa(addr));
		addr.s_addr = rule->d_mask;
		printf("%-15s  ", inet_ntoa(addr));
		printf("%-5d  ", ntohs(rule->d_port));
		printf("%-3d\n", rule->proto);*/
        printf("\n");
        break;
	}

	free(buf);
	close(fd);

    return EXIT_SUCCESS;
}

/*
* Function to write rule to a char file.
*/
int write_rule(struct fw_comm *comm)
{
    int fd;
    int count_byte;

    fd = open("/dev/fw_file", O_WRONLY | O_APPEND);
    if (fd < 0)
        return DEVICE_NOT_AVAILABLE;

    //write(fd, comm, sizeof(comm));
    write(fd, comm, sizeof(*comm));

    close(fd);

    return EXIT_SUCCESS;
}

/*
* Initialization of structure of rule
*/
void init_comm(struct fw_comm *comm)
{
    comm->action = NONE;
    comm->rule.in = NOT_STATED;
    comm->rule.src_ip = NOT_STATED;
    comm->rule.src_mask = NOT_STATED; /*TODO*/
    comm->rule.src_port = NOT_STATED;
    comm->rule.dest_ip = NOT_STATED;
    comm->rule.dest_mask = NOT_STATED;
    comm->rule.dest_port = NOT_STATED;
    comm->rule.protocol = NOT_STATED;

    comm->rule.index = NOT_STATED;
}

/*
* Function to get additional argument (number).
*/
uint64_t parse_add_arg(const char *str, int min_value, int max_value)
{
    int num;
    char *end;

    num = strtol(str, &end, 10);
    if (num < min_value || num > max_value || str == end)
        return EXIT_FAILURE;

    return num;
}

/*
* Function to get type of protocol.
*/
int parse_add_prot(const char *protocol)
{
    if (strcmp(protocol, TCP_PROTOCOL) == 0)
        return IPPROTO_TCP;

    if (strcmp(protocol, UDP_PROTOCOL) == 0)
        return IPPROTO_UDP;

    return EXIT_FAILURE;
}

/*
* Function to get params from console
*/
int parse_comm(int argc, char **argv, struct fw_comm *res_comm)
{
    int res, comm_ind, protocol;
    int64_t param;
    const char* short_comm = "ad:Aiop:s:r:t:e:h";
    struct in_addr addr;
    struct fw_comm comm;

    if (argc == 1)
    {
        show_info();
        return LACK_ARGUMENTS;
    }

    struct option long_comm[] = 
    {
        {"add", no_argument, 0, 'a'},
        {"delete", required_argument, 0, 'd'},
        {"all", no_argument, 0, 'A'},
        {"in", no_argument, 0, 'i'},
        {"out", no_argument, 0, 'o'},
        {"protocol", required_argument, 0, 'p'},
        {"src_ip", required_argument, 0, 's'},
        {"src_port", required_argument, 0, 'r'},
        {"dest_ip", required_argument, 0, 't'},
        {"dest_port", required_argument, 0, 'e'},
        {"help", no_argument, 0, 'h'},
        {NULL, 0, NULL, 0}
    };
    

    init_comm(&comm);
    
    while (1)
    {
        res = getopt_long(argc, argv, short_comm, long_comm, &comm_ind);
        if (res < 0)
            break;
    
        switch (res)
        {
        case 'a':
            if (comm.action != NONE)
                return ACTION_MENTIONED;

            comm.action = ADD;
            break;

        case 'd':
            if (comm.action != NONE)
                return ACTION_MENTIONED;

            comm.action = DELETE;

            param = parse_add_arg(optarg, 0, USHRT_MAX);
            if (param == EXIT_FAILURE)
                return INCORRECT_INDEX_RULE;

            comm.rule.index = param;
            break;

        case 'A':
            if (comm.action != NONE)
                return ACTION_MENTIONED;

            comm.action = SHOW;
            break;

        case 'i':
            if (comm.rule.in == OUT)
                return DIRECTION_MENTIONED;

            comm.rule.in = IN;
            break;

        case 'o':
            if (comm.rule.in == IN)
                return DIRECTION_MENTIONED;

            comm.rule.in = OUT;
            break;

        case 'p':
            if (comm.rule.protocol != NOT_STATED)
                return PROTOCOL_MENTIONED;

            protocol = parse_add_prot(optarg);
            if (protocol == EXIT_FAILURE)
                return WRONG_PROTOCOL;

            comm.rule.protocol = protocol;        
            break;

        case 's':
            if (comm.rule.src_ip != NOT_STATED)
                return SRC_IP_MENTIONED;

            if (!inet_aton(optarg, &addr))
                return INCORRECT_SCR_IP;

            comm.rule.src_ip = addr.s_addr;
            break;

        case 't':
            if (comm.rule.dest_ip != NOT_STATED)
                return DEST_IP_MENTIONED;

            inet_aton(optarg, &addr);
            printf("optarg %s %d\n\n", optarg, addr.s_addr);
            if (!inet_aton(optarg, &addr))
                return INCORRECT_DEST_IP;

            comm.rule.dest_ip = addr.s_addr;
            break;

        case 'r':
            if (comm.rule.src_port != NOT_STATED)
                return SRC_PORT_MENTIONED;

            param = parse_add_arg(optarg, 0, USHRT_MAX);
            if (param == EXIT_FAILURE)
                return INCORRECT_SRC_PORT;

            comm.rule.src_port = htons((uint16_t)param);
            break;

        case 'e':
            if (comm.rule.dest_port != NOT_STATED)
                return DEST_PORT_MENTIONED;

            param = parse_add_arg(optarg, 0, USHRT_MAX);
            if (param == EXIT_FAILURE)
                return INCORRECT_DEST_PORT;

            comm.rule.dest_port = htons((uint16_t)param);
            break;
        
        default:
            show_info();
            return EXIT_FAILURE;
        }
    }

    if (comm.action == NONE)
        return ACTION_NOT_MENTIONED;

    if (comm.action == DELETE || comm.action == SHOW)
    {
        *res_comm = comm;
        return EXIT_SUCCESS;
    }

    if (comm.rule.in == NOT_STATED)
        return DIRECTION_NOT_MENTIONED;

    if (comm.rule.src_ip == NOT_STATED && comm.rule.src_port == NOT_STATED && \
        comm.rule.dest_ip == NOT_STATED && comm.rule.dest_port == NOT_STATED && \
        comm.rule.protocol == NOT_STATED && comm.rule.index == NOT_STATED)
        return KEYS_NOT_MENTIONED;

    *res_comm = comm;

    return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{
    struct fw_comm comm;
    int res;

    res = parse_comm(argc, argv, &comm);

    if (res)
    {
        switch (res)
        {
        case LACK_ARGUMENTS:
            printf("ERROR: not enough arguments.\n");
            break;
        case ACTION_MENTIONED:
            printf("ERROR: action is already mentioned\n");
            break;
        case DIRECTION_MENTIONED:
            printf("ERROR: direction is already mentioned\n");
            break;
        case PROTOCOL_MENTIONED:
            printf("ERROR: protocol is already mentioned\n");
            break;
        case WRONG_PROTOCOL:
            printf("ERROR: wrong parameter of protocol\n");
            break;
        case SRC_IP_MENTIONED:
            printf("ERROR: source IP is already mentioned\n");
            break;
        case INCORRECT_SCR_IP:
            printf("ERROR: incorrect source IP\n");
            break;
        case DEST_IP_MENTIONED:
            printf("ERROR: destination IP is already mentioned\n");
            break;
        case INCORRECT_DEST_IP:
            printf("ERROR: incorrect destination IP\n");
            break;
        case SRC_PORT_MENTIONED:
            printf("ERROR: source port is already mentioned\n");
            break;
        case INCORRECT_SRC_PORT:
            printf("ERROR: incorrect source port\n");
            break;
        case DEST_PORT_MENTIONED:
            printf("ERROR: destination port is already mentioned\n");
            break;
        case INCORRECT_DEST_PORT:
            printf("ERROR: incorrect destination port\n");
            break;
        case ACTION_NOT_MENTIONED:
            printf("ERROR: action (add/delete) is not mentioned\n");
            break;
        case DIRECTION_NOT_MENTIONED:
            printf("ERROR: direction (in/out) is not mentioned\n");
            break;
        case INCORRECT_INDEX_RULE:
            printf("ERROR: incorrect index of rule\n");
            break;
        case KEYS_NOT_MENTIONED:
            printf("ERROR: keys are not mentioned\n");
            break;
        /*case :

            break;*/
        
        default:
            break;
        }
        
        return res;
    }
        
    switch (comm.action)
    {
        case ADD:
        case DELETE:
            res = write_rule(&comm);

            switch (res)
            {
                case DEVICE_NOT_AVAILABLE:
                    printf("ERROR: denied access to the device\n");
                    break;
                case RULE_ADDITION_FAILED:
                    printf("ERROR: operation was failed.\n");
                    break;
                case EXIT_SUCCESS:
                    printf("Rule was successfully added.\n");
                    break;
                default:
                    break;
            }
            break;
        case SHOW:
            res = show_rules();

            switch (res)
            {
                case DEVICE_NOT_AVAILABLE:
                    printf("ERROR: denied access to the device\n");
                    break;
                case MEMORY_ERROR:
                    printf("ERROR: problems with memory allocation");
                    break;
                
                default:
                    break;
            }
            break;
    }
    

    return EXIT_SUCCESS;
}