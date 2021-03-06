// PATH : RIOT/tests/pkg_semtech-loramac

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>

#include "msg.h"
#include "shell.h"
#include "fmt.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

semtech_loramac_t loramac;

/*  #########################################
    BEGIN STATIC INFORMATION
    appeuis, deveuis ecc
    NB : This section is only for testing purposes. Each device will have its own identity later.
*/

uint8_t dev_00_deveui[LORAMAC_DEVEUI_LEN];
uint8_t dev_00_appeui[LORAMAC_APPEUI_LEN];
uint8_t dev_00_appkey[LORAMAC_APPKEY_LEN];

uint8_t dev_01_deveui[LORAMAC_DEVEUI_LEN];
uint8_t dev_01_appeui[LORAMAC_APPEUI_LEN];
uint8_t dev_01_appkey[LORAMAC_APPKEY_LEN];

uint8_t dev_02_deveui[LORAMAC_DEVEUI_LEN];
uint8_t dev_02_appeui[LORAMAC_APPEUI_LEN];
uint8_t dev_02_appkey[LORAMAC_APPKEY_LEN];

uint8_t dr_standard = 5;
loramac_class_t cls_standard = LORAMAC_CLASS_C;
uint8_t join_type_standard = LORAMAC_JOIN_OTAA;
char devid[6];

/*
    END STATIC INFORMATION
    #########################################
*/

/* Functions to emulate Profile With Brachelet
*  Generating random values for the sensors simulation
* */

char profiles[3][10] = {"Maria", "Hugo", "Ettore"};
char ids[3][6] = {"dev_00", "dev_01", "dev_02"};
uint8_t profile;

uint8_t get_random_value(uint8_t lower, uint8_t upper)
{
    return (rand() % (upper + 1 - lower) + lower);
}

uint8_t get_random_payload(char *payload)
{
    profile = get_random_value(0, 2);
    uint8_t hrate = get_random_value(50, 120);
    uint8_t timestamp = get_random_value(0, 254);

    sprintf(payload, "{\"dev_id\" : \"%s\", \"profile_id\": \"%s\", \"hrate\": \"%d\",\"timestamp\": \"%d\"}", devid, profiles[profile], hrate,timestamp);

    return 0;
}
/* END FUNCTIONS to emulate Profiles With Brachelet */

/* Application key is 16 bytes long (e.g. 32 hex chars), and thus the longest
   possible size (with application session and network session keys) */
static char print_buf[LORAMAC_APPKEY_LEN * 2 + 1];

static void _loramac_usage(void)
{
    puts("Usage: loramac <start|get|set|join|tx|link_check"
#ifdef MODULE_PERIPH_EEPROM
         "|save|erase"
#endif
         ">");
}

static void _loramac_join_usage(void)
{
    puts("Usage: loramac join <otaa|abp>");
}

static void _loramac_tx_usage(void)
{
    puts("Usage: loramac tx <payload> [<cnf|uncnf>] [port]");
}

static void _loramac_set_usage(void)
{
    puts("Usage: loramac set <deveui|appeui|appkey|appskey|nwkskey|devaddr|"
         "class|dr|adr|public|netid|tx_power|rx2_freq|rx2_dr> <value>");
}

static void _loramac_get_usage(void)
{
    puts("Usage: loramac get <deveui|appeui|appkey|appskey|nwkskey|devaddr|"
         "class|dr|adr|public|netid|tx_power|rx2_freq|rx2_dr>");
}

static int _cmd_loramac(int argc, char **argv)
{
    if (argc < 2)
    {
        _loramac_usage();
        return 1;
    }

    /*  #########################################
        BEGIN LORAMAC GET
        get: deveui, appeui, appkey, appskey, nwkskey, devaddr, class, dr, adr
            public, netid, tx_power, rx2_freq, rx2_dr
    */

    if (strcmp(argv[1], "get") == 0)
    {
        if (argc < 3)
        {
            _loramac_get_usage();
            return 1;
        }

        if (strcmp("deveui", argv[2]) == 0)
        {
            uint8_t deveui[LORAMAC_DEVEUI_LEN];
            semtech_loramac_get_deveui(&loramac, deveui);
            fmt_bytes_hex(print_buf, deveui, LORAMAC_DEVEUI_LEN);
            print_buf[LORAMAC_DEVEUI_LEN * 2] = '\0';
            printf("DEVEUI: %s\n", print_buf);
        }
        else if (strcmp("appeui", argv[2]) == 0)
        {
            uint8_t appeui[LORAMAC_APPEUI_LEN];
            semtech_loramac_get_appeui(&loramac, appeui);
            fmt_bytes_hex(print_buf, appeui, LORAMAC_APPEUI_LEN);
            print_buf[LORAMAC_APPEUI_LEN * 2] = '\0';
            printf("APPEUI: %s\n", print_buf);
        }
        else if (strcmp("appkey", argv[2]) == 0)
        {
            uint8_t appkey[LORAMAC_APPKEY_LEN];
            semtech_loramac_get_appkey(&loramac, appkey);
            fmt_bytes_hex(print_buf, appkey, LORAMAC_APPKEY_LEN);
            print_buf[LORAMAC_APPKEY_LEN * 2] = '\0';
            printf("APPKEY: %s\n", print_buf);
        }
        else if (strcmp("appskey", argv[2]) == 0)
        {
            uint8_t appskey[LORAMAC_APPSKEY_LEN];
            semtech_loramac_get_appskey(&loramac, appskey);
            fmt_bytes_hex(print_buf, appskey, LORAMAC_APPSKEY_LEN);
            print_buf[LORAMAC_APPSKEY_LEN * 2] = '\0';
            printf("APPSKEY: %s\n", print_buf);
        }
        else if (strcmp("nwkskey", argv[2]) == 0)
        {
            uint8_t nwkskey[LORAMAC_NWKSKEY_LEN];
            semtech_loramac_get_nwkskey(&loramac, nwkskey);
            fmt_bytes_hex(print_buf, nwkskey, LORAMAC_NWKSKEY_LEN);
            print_buf[LORAMAC_NWKSKEY_LEN * 2] = '\0';
            printf("NWKSKEY: %s\n", print_buf);
        }
        else if (strcmp("devaddr", argv[2]) == 0)
        {
            uint8_t devaddr[LORAMAC_DEVADDR_LEN];
            semtech_loramac_get_devaddr(&loramac, devaddr);
            fmt_bytes_hex(print_buf, devaddr, LORAMAC_DEVADDR_LEN);
            print_buf[LORAMAC_DEVADDR_LEN * 2] = '\0';
            printf("DEVADDR: %s\n", print_buf);
        }
        else if (strcmp("class", argv[2]) == 0)
        {
            printf("Device class: ");
            switch (semtech_loramac_get_class(&loramac))
            {
            case LORAMAC_CLASS_A:
                puts("A");
                break;
            case LORAMAC_CLASS_B:
                puts("B");
                break;
            case LORAMAC_CLASS_C:
                puts("C");
                break;
            default:
                puts("Invalid");
                break;
            }
        }
        else if (strcmp("dr", argv[2]) == 0)
        {
            printf("DATARATE: %d\n",
                   semtech_loramac_get_dr(&loramac));
        }
        else if (strcmp("adr", argv[2]) == 0)
        {
            printf("ADR: %s\n",
                   semtech_loramac_get_adr(&loramac) ? "on" : "off");
        }
        else if (strcmp("public", argv[2]) == 0)
        {
            printf("Public network: %s\n",
                   semtech_loramac_get_public_network(&loramac) ? "on" : "off");
        }
        else if (strcmp("netid", argv[2]) == 0)
        {
            printf("NetID: %" PRIu32 "\n", semtech_loramac_get_netid(&loramac));
        }
        else if (strcmp("tx_power", argv[2]) == 0)
        {
            printf("TX power index: %d\n", semtech_loramac_get_tx_power(&loramac));
        }
        else if (strcmp("rx2_freq", argv[2]) == 0)
        {
            printf("RX2 freq: %" PRIu32 "\n", semtech_loramac_get_rx2_freq(&loramac));
        }
        else if (strcmp("rx2_dr", argv[2]) == 0)
        {
            printf("RX2 dr: %d\n", semtech_loramac_get_rx2_dr(&loramac));
        }
        else
        {
            _loramac_get_usage();
            return 1;
        }
    }
    /*
        END LORAMAC GET
        #########################################
    */

    /*  #########################################
        BEGIN LORAMAC SET
        set: deveui, appeui, appkey, appskey, nwkskey, devaddr, class [A, B, C], dr, adr
            public [on, off], netid, tx_power, rx2_freq, rx2_dr
    */

    else if (strcmp(argv[1], "set") == 0)
    {
        if (argc < 3)
        {
            _loramac_set_usage();
            return 1;
        }

        if (strcmp("deveui", argv[2]) == 0)
        {
            if ((argc < 4) || (strlen(argv[3]) != LORAMAC_DEVEUI_LEN * 2))
            {
                puts("Usage: loramac set deveui <16 hex chars>");
                return 1;
            }
            uint8_t deveui[LORAMAC_DEVEUI_LEN];
            fmt_hex_bytes(deveui, argv[3]);
            semtech_loramac_set_deveui(&loramac, deveui);
        }
        else if (strcmp("appeui", argv[2]) == 0)
        {
            if ((argc < 4) || (strlen(argv[3]) != LORAMAC_APPEUI_LEN * 2))
            {
                puts("Usage: loramac set appeui <16 hex chars>");
                return 1;
            }
            uint8_t appeui[LORAMAC_APPEUI_LEN];
            fmt_hex_bytes(appeui, argv[3]);
            semtech_loramac_set_appeui(&loramac, appeui);
        }
        else if (strcmp("appkey", argv[2]) == 0)
        {
            if ((argc < 4) || (strlen(argv[3]) != LORAMAC_APPKEY_LEN * 2))
            {
                puts("Usage: loramac set appkey <32 hex chars>");
                return 1;
            }
            uint8_t appkey[LORAMAC_APPKEY_LEN];
            fmt_hex_bytes(appkey, argv[3]);
            semtech_loramac_set_appkey(&loramac, appkey);
        }
        else if (strcmp("appskey", argv[2]) == 0)
        {
            if ((argc < 4) || (strlen(argv[3]) != LORAMAC_APPSKEY_LEN * 2))
            {
                puts("Usage: loramac set appskey <32 hex chars>");
                return 1;
            }
            uint8_t appskey[LORAMAC_APPSKEY_LEN];
            fmt_hex_bytes(appskey, argv[3]);
            semtech_loramac_set_appskey(&loramac, appskey);
        }
        else if (strcmp("nwkskey", argv[2]) == 0)
        {
            if ((argc < 4) || (strlen(argv[3]) != LORAMAC_NWKSKEY_LEN * 2))
            {
                puts("Usage: loramac set nwkskey <32 hex chars>");
                return 1;
            }
            uint8_t nwkskey[LORAMAC_NWKSKEY_LEN];
            fmt_hex_bytes(nwkskey, argv[3]);
            semtech_loramac_set_nwkskey(&loramac, nwkskey);
        }
        else if (strcmp("devaddr", argv[2]) == 0)
        {
            if ((argc < 4) || (strlen(argv[3]) != LORAMAC_DEVADDR_LEN * 2))
            {
                puts("Usage: loramac set devaddr <8 hex chars>");
                return 1;
            }
            uint8_t devaddr[LORAMAC_DEVADDR_LEN];
            fmt_hex_bytes(devaddr, argv[3]);
            semtech_loramac_set_devaddr(&loramac, devaddr);
        }
        else if (strcmp("class", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set class <A,B,C>");
                return 1;
            }
            loramac_class_t cls;
            if (strcmp(argv[3], "A") == 0)
            {
                cls = LORAMAC_CLASS_A;
            }
            else if (strcmp(argv[3], "B") == 0)
            {
                cls = LORAMAC_CLASS_B;
            }
            else if (strcmp(argv[3], "C") == 0)
            {
                cls = LORAMAC_CLASS_C;
            }
            else
            {
                puts("Usage: loramac set class <A,B,C>");
                return 1;
            }
            semtech_loramac_set_class(&loramac, cls);
        }
        else if (strcmp("dr", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set dr <0..16>");
                return 1;
            }
            uint8_t dr = atoi(argv[3]);
            if (dr > LORAMAC_DR_15)
            {
                puts("Usage: loramac set dr <0..16>");
                return 1;
            }
            semtech_loramac_set_dr(&loramac, dr);
        }
        else if (strcmp("adr", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set adr <on|off>");
                return 1;
            }
            bool adr;
            if (strcmp("on", argv[3]) == 0)
            {
                adr = true;
            }
            else if (strcmp("off", argv[3]) == 0)
            {
                adr = false;
            }
            else
            {
                puts("Usage: loramac set adr <on|off>");
                return 1;
            }
            semtech_loramac_set_adr(&loramac, adr);
        }
        else if (strcmp("public", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set public <on|off>");
                return 1;
            }
            bool public;
            if (strcmp("on", argv[3]) == 0)
            {
            public
                = true;
            }
            else if (strcmp("off", argv[3]) == 0)
            {
            public
                = false;
            }
            else
            {
                puts("Usage: loramac set public <on|off>");
                return 1;
            }
            semtech_loramac_set_public_network(&loramac, public);
        }
        else if (strcmp("netid", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set netid <integer value>");
                return 1;
            }
            semtech_loramac_set_netid(&loramac, strtoul(argv[2], NULL, 0));
        }
        else if (strcmp("tx_power", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set tx_power <0..16>");
                return 1;
            }
            uint8_t power = atoi(argv[3]);
            if (power > LORAMAC_TX_PWR_15)
            {
                puts("Usage: loramac set tx_power <0..16>");
                return 1;
            }
            semtech_loramac_set_tx_power(&loramac, power);
        }
        else if (strcmp("rx2_freq", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set rx2_freq <frequency>");
                return 1;
            }
            uint32_t freq = atoi(argv[3]);
            semtech_loramac_set_rx2_freq(&loramac, freq);
        }
        else if (strcmp("rx2_dr", argv[2]) == 0)
        {
            if (argc < 4)
            {
                puts("Usage: loramac set rx2_dr <0..16>");
                return 1;
            }
            uint8_t dr = atoi(argv[3]);
            if (dr > LORAMAC_DR_15)
            {
                puts("Usage: loramac set rx2_dr <0..16>");
                return 1;
            }
            semtech_loramac_set_rx2_dr(&loramac, dr);
        }
        else if (strcmp("dev_00", argv[2]) == 0)
        {
            fmt_hex_bytes(dev_00_deveui, "00E826F416B86F3F");
            fmt_hex_bytes(dev_00_appeui, "70B3D57ED002F7A1");
            fmt_hex_bytes(dev_00_appkey, "D4608EA823673E4381F3328AECE139EF");
            semtech_loramac_set_deveui(&loramac, dev_00_deveui);
            semtech_loramac_set_appeui(&loramac, dev_00_appeui);
            semtech_loramac_set_appkey(&loramac, dev_00_appkey);
            semtech_loramac_set_dr(&loramac, dr_standard);
            semtech_loramac_set_class(&loramac, cls_standard);
            strcpy(devid, "dev_00");
        }
        else if (strcmp("dev_01", argv[2]) == 0)
        {
            fmt_hex_bytes(dev_01_deveui, "00BBBC8EC6FF6DD2");
            fmt_hex_bytes(dev_01_appeui, "70B3D57ED002F7A1");
            fmt_hex_bytes(dev_01_appkey, "86C9166C4540AC53B4EA29526D2C0306");
            semtech_loramac_set_deveui(&loramac, dev_01_deveui);
            semtech_loramac_set_appeui(&loramac, dev_01_appeui);
            semtech_loramac_set_appkey(&loramac, dev_01_appkey);
            semtech_loramac_set_dr(&loramac, dr_standard);
            semtech_loramac_set_class(&loramac, cls_standard);
            strcpy(devid, "dev_01");
        }
        else if (strcmp("dev_02", argv[2]) == 0)
        {
            fmt_hex_bytes(dev_02_deveui, "0077981F53BF8BD9");
            fmt_hex_bytes(dev_02_appeui, "70B3D57ED002F7A1");
            fmt_hex_bytes(dev_02_appkey, "685E563574362452A88F75074097E35E");
            semtech_loramac_set_deveui(&loramac, dev_02_deveui);
            semtech_loramac_set_appeui(&loramac, dev_02_appeui);
            semtech_loramac_set_appkey(&loramac, dev_02_appkey);
            semtech_loramac_set_dr(&loramac, dr_standard);
            semtech_loramac_set_class(&loramac, cls_standard);
            strcpy(devid, "dev_02");
        }

        else
        {
            _loramac_set_usage();
            return 1;
        }
    }

    /*
        END LORAMAC SET
        #########################################
    */

    /*  #########################################
        BEGIN LORAMAC JOIN
        join : otaa, abp
    */
    else if (strcmp(argv[1], "join") == 0)
    {
        if (argc < 3)
        {
            _loramac_join_usage();
            return 1;
        }

        uint8_t join_type;
        if (strcmp(argv[2], "otaa") == 0)
        {
            join_type = LORAMAC_JOIN_OTAA;
        }
        else if (strcmp(argv[2], "abp") == 0)
        {
            join_type = LORAMAC_JOIN_ABP;
        }
        else
        {
            _loramac_join_usage();
            return 1;
        }

        switch (semtech_loramac_join(&loramac, join_type))
        {
        case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
            puts("Cannot join: dutycycle restriction");
            return 1;
        case SEMTECH_LORAMAC_BUSY:
            puts("Cannot join: mac is busy");
            return 1;
        case SEMTECH_LORAMAC_JOIN_FAILED:
            puts("Join procedure failed!");
            return 1;
        case SEMTECH_LORAMAC_ALREADY_JOINED:
            puts("Warning: already joined!");
            return 1;
        case SEMTECH_LORAMAC_JOIN_SUCCEEDED:
            puts("Join procedure succeeded!");
            break;
        default: /* should not happen */
            break;
        }
        return 0;
    }
    /*
        END LORAMAC JOIN
        #########################################
    */

    /*  #########################################
        BEGIN LORAMAC TX
    */
    else if (strcmp(argv[1], "tx") == 0)
    {
        if (argc < 3)
        {
            _loramac_tx_usage();
            return 1;
        }

        uint8_t cnf = LORAMAC_DEFAULT_TX_MODE;  /* Default: confirmable */
        uint8_t port = LORAMAC_DEFAULT_TX_PORT; /* Default: 2 */
        /* handle optional parameters */
        if (argc > 3)
        {
            if (strcmp(argv[3], "cnf") == 0)
            {
                cnf = LORAMAC_TX_CNF;
            }
            else if (strcmp(argv[3], "uncnf") == 0)
            {
                cnf = LORAMAC_TX_UNCNF;
            }
            else
            {
                _loramac_tx_usage();
                return 1;
            }

            if (argc > 4)
            {
                port = atoi(argv[4]);
                if (port == 0 || port >= 224)
                {
                    printf("error: invalid port given '%d', "
                           "port can only be between 1 and 223\n",
                           port);
                    return 1;
                }
            }
        }

        semtech_loramac_set_tx_mode(&loramac, cnf);
        semtech_loramac_set_tx_port(&loramac, port);

        switch (semtech_loramac_send(&loramac,
                                     (uint8_t *)argv[2], strlen(argv[2])))
        {
        case SEMTECH_LORAMAC_NOT_JOINED:
            puts("Cannot send: not joined");
            return 1;

        case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
            puts("Cannot send: dutycycle restriction");
            return 1;

        case SEMTECH_LORAMAC_BUSY:
            puts("Cannot send: MAC is busy");
            return 1;

        case SEMTECH_LORAMAC_TX_ERROR:
            puts("Cannot send: error");
            return 1;
        }

        /* wait for receive windows */
        switch (semtech_loramac_recv(&loramac))
        {
        case SEMTECH_LORAMAC_DATA_RECEIVED:
            loramac.rx_data.payload[loramac.rx_data.payload_len] = 0;
            printf("Data received: %s, port: %d\n",
                   (char *)loramac.rx_data.payload, loramac.rx_data.port);
            break;

        case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
            puts("Cannot send: dutycycle restriction");
            return 1;

        case SEMTECH_LORAMAC_BUSY:
            puts("Cannot send: MAC is busy");
            return 1;

        case SEMTECH_LORAMAC_TX_ERROR:
            puts("Cannot send: error");
            return 1;

        case SEMTECH_LORAMAC_TX_DONE:
            puts("TX complete, no data received");
            break;
        }

        if (loramac.link_chk.available)
        {
            printf("Link check information:\n"
                   "  - Demodulation margin: %d\n"
                   "  - Number of gateways: %d\n",
                   loramac.link_chk.demod_margin,
                   loramac.link_chk.nb_gateways);
        }

        return 0;
    }

    /*
        END LORAMAC TX
        #########################################
    */

    /*
        #########################################
        BEGIN LORAMAC NFC
    */
    else if (strcmp(argv[1], "NFC") == 0)
    {
        printf("Sending message\n");

        uint8_t cnf = LORAMAC_DEFAULT_TX_MODE;  /* Default: confirmable */
        uint8_t port = LORAMAC_DEFAULT_TX_PORT; /* Default: 2 */

        if (argc > 3)
        {
            if (strcmp(argv[3], "cnf") == 0)
            {
                cnf = LORAMAC_TX_CNF;
            }
            else if (strcmp(argv[3], "uncnf") == 0)
            {
                cnf = LORAMAC_TX_UNCNF;
            }
            else
            {
                _loramac_tx_usage();
                return 1;
            }

            if (argc > 4)
            {
                port = atoi(argv[4]);
                if (port == 0 || port >= 224)
                {
                    printf("error: invalid port given '%d', "
                           "port can only be between 1 and 223\n",
                           port);
                    return 1;
                }
            }
        }

        semtech_loramac_set_tx_mode(&loramac, cnf);
        semtech_loramac_set_tx_port(&loramac, port);

        // For random value
        srand(time(0));
        char payload[128];

        get_random_payload(payload);

        switch (semtech_loramac_send(&loramac,
                                     (uint8_t *)payload, strlen(payload)))
        {
        case SEMTECH_LORAMAC_NOT_JOINED:
            puts("Cannot send: not joined");
            return 1;

        case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
            puts("Cannot send: dutycycle restriction");
            return 1;

        case SEMTECH_LORAMAC_BUSY:
            puts("Cannot send: MAC is busy");
            return 1;

        case SEMTECH_LORAMAC_TX_ERROR:
            puts("Cannot send: error");
            return 1;
        }

        /* wait for receive windows */
        switch (semtech_loramac_recv(&loramac))
        {
        case SEMTECH_LORAMAC_DATA_RECEIVED:
            loramac.rx_data.payload[loramac.rx_data.payload_len] = 0;
            printf("Data received: %s, port: %d\n",
                   (char *)loramac.rx_data.payload, loramac.rx_data.port);
            break;

        case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
            puts("Cannot send: dutycycle restriction");
            return 1;

        case SEMTECH_LORAMAC_BUSY:
            puts("Cannot send: MAC is busy");
            return 1;

        case SEMTECH_LORAMAC_TX_ERROR:
            puts("Cannot send: error");
            return 1;

        case SEMTECH_LORAMAC_TX_DONE:
            puts("TX complete, no data received");
            break;
        }

        if (loramac.link_chk.available)
        {
            printf("Link check information:\n"
                   "  - Demodulation margin: %d\n"
                   "  - Number of gateways: %d\n",
                   loramac.link_chk.demod_margin,
                   loramac.link_chk.nb_gateways);
        }

        puts("Info sent to the cloud...\n");
        switch (profile)
        {
        case 0:
            puts("Easy description: good for young students and who is not very familiar with museum in general.");
            break;
        case 1:
            puts("Medium description: suitable for average people who have not been forced to come to the museum, but they are here for their will.");
            break;
        case 2:
            puts("Deep description: perfect for bookworm and ancient history fans.");
            break;
        }
    }
    /*
        END LORAMAC NFC
        #########################################
    */

    /*  #########################################
        BEGIN LORAMAC START
    */
    else if (strcmp(argv[1], "start") == 0)
    {

        printf("Starting . . .\n");

        uint8_t cnf = LORAMAC_DEFAULT_TX_MODE;  /* Default: confirmable */
        uint8_t port = LORAMAC_DEFAULT_TX_PORT; /* Default: 2 */

        /* handle optional parameters */
        if (argc > 3)
        {
            if (strcmp(argv[3], "cnf") == 0)
            {
                cnf = LORAMAC_TX_CNF;
            }
            else if (strcmp(argv[3], "uncnf") == 0)
            {
                cnf = LORAMAC_TX_UNCNF;
            }
            else
            {
                _loramac_tx_usage();
                return 1;
            }

            if (argc > 4)
            {
                port = atoi(argv[4]);
                if (port == 0 || port >= 224)
                {
                    printf("error: invalid port given '%d', "
                           "port can only be between 1 and 223\n",
                           port);
                    return 1;
                }
            }
        }
        semtech_loramac_set_tx_mode(&loramac, cnf);
        semtech_loramac_set_tx_port(&loramac, port);

        // For random value
        srand(time(0));
        char payload[128];

        // Start sending data
        while (true)
        {

            semtech_loramac_set_tx_mode(&loramac, cnf);
            semtech_loramac_set_tx_port(&loramac, port);

            get_random_payload(payload);

            /* semtech_loramac_send @ RIOT/pkg/semtech-loramac/contrib/semtech_loramac.c */
            switch (semtech_loramac_send(&loramac,
                                         (uint8_t *)payload, strlen(payload)))
            {
            case SEMTECH_LORAMAC_NOT_JOINED:
                puts("Cannot send: not joined");
                return 1;

            case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
                puts("Cannot send: dutycycle restriction");
                return 1;

            case SEMTECH_LORAMAC_BUSY:
                puts("Cannot send: MAC is busy");
                return 1;

            case SEMTECH_LORAMAC_TX_ERROR:
                puts("Cannot send: error");
                return 1;

            case SEMTECH_LORAMAC_TX_CNF_FAILED:
                puts("Fail to send: no ACK received");
                return 1;
            }

            /* wait for receive windows */
            switch (semtech_loramac_recv(&loramac))
            {
            case SEMTECH_LORAMAC_DATA_RECEIVED:
                loramac.rx_data.payload[loramac.rx_data.payload_len] = 0;
                printf("Data received: %s, port: %d\n",
                       (char *)loramac.rx_data.payload, loramac.rx_data.port);
                break;

            case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
                puts("Cannot send: dutycycle restriction");
                return 1;

            case SEMTECH_LORAMAC_BUSY:
                puts("Cannot send: MAC is busy");
                return 1;

            case SEMTECH_LORAMAC_TX_ERROR:
                puts("Cannot send: error");
                return 1;

            case SEMTECH_LORAMAC_TX_DONE:
                puts("TX complete, no data received");
                break;
            }

            if (loramac.link_chk.available)
            {
                printf("Link check information:\n"
                       "  - Demodulation margin: %d\n"
                       "  - Number of gateways: %d\n",
                       loramac.link_chk.demod_margin,
                       loramac.link_chk.nb_gateways);
            }

            puts("Message sent with success");

            // Maintain this value high in order to avoid duty cycle restrictions
            int sleep = (int)get_random_value(40, 150);
            printf("Sleep for : %d secs\n", sleep);
            xtimer_sleep(sleep);
        }
        return 0;
    }
    /*
        END LORAMAC START
        #########################################
    */

    /*  #########################################
        BEGIN STUFFS
    */
    else if (strcmp(argv[1], "link_check") == 0)
    {
        if (argc > 2)
        {
            _loramac_usage();
            return 1;
        }

        semtech_loramac_request_link_check(&loramac);
        puts("Link check request scheduled");
    }
#ifdef MODULE_PERIPH_EEPROM
    else if (strcmp(argv[1], "save") == 0)
    {
        if (argc > 2)
        {
            _loramac_usage();
            return 1;
        }

        semtech_loramac_save_config(&loramac);
    }
    else if (strcmp(argv[1], "erase") == 0)
    {
        if (argc > 2)
        {
            _loramac_usage();
            return 1;
        }

        semtech_loramac_erase_config();
    }
#endif
    else
    {
        _loramac_usage();
        return 1;
    }

    return 0;
}

/*
    END STUFFS
    #########################################
*/

static const shell_command_t shell_commands[] = {
    {"loramac", "control the loramac stack", _cmd_loramac},
    {NULL, NULL, NULL}};

int main(void)
{
    semtech_loramac_init(&loramac);

    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
}
